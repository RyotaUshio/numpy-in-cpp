#pragma once
#include <typeinfo> // for dtype
#include <vector>
#include <stdexcept> // invalid_argument
#include <algorithm> // find
#include <string>
#include <sstream>
#include <numpy/pyobject.hpp>
#include <numpy/dtype.hpp>
#include <numpy/utils.hpp>
#include <numpy/python.hpp>


namespace numpy {

  template <class T> class ndarray;
  template <class T> class array_transpose;
  template <class T> class array_iter;
  
  class array_metadata : public python::object {
    template <class Dtype> friend class ndarray;
    template <class Dtype> friend class array_transpose;
    template <class Dtype> friend class array_iter;
    
    shape_type shape;
    dim_type ndim;
    size_type size;
    offset_type offset;
    stride_type stride;

    array_metadata(const shape_type& shape_, const stride_type& stride_, const offset_type& offset_=0)
      : shape(shape_), offset(offset_), stride(stride_) {
      adjust_to_shape();
      if (stride.size() != ndim)
	throw std::invalid_argument("Stride and shape must have the same length.");
    }

    array_metadata(const shape_type& shape_, const offset_type& offset_=0)
      : shape(shape_), offset(offset_) {
      adjust_to_shape();
      stride = stride_type(shape.size());
      stride[ndim-1] = 1;
      for(int i=ndim-2; i>=0; i--){
	stride[i] = stride[i+1] * shape[i+1];
      }
    }
    
    array_metadata(const array_metadata& src)
      : shape(src.shape), ndim(src.ndim), size(src.size), offset(src.offset), stride(src.stride) {}

    template <class Dtype>
    array_metadata(const array_metadata& src)
      : shape(src.shape), ndim(src.ndim), size(src.size), offset(src.offset), stride(src.stride) {}

    void set_shape(const shape_type& newshape) {
      shape = newshape;
      adjust_to_shape();
    }

    void adjust_to_shape() {
      size = utils::product(shape);
      ndim = shape.size();
    }
    
    void _indexer_inplace_impl(dim_type axis) {}
    
    template <class... Tail>
    void _indexer_inplace_impl(dim_type axis, python::slice head, Tail... tail) {
      offset += head.abs_start(shape[axis]) * stride[axis];
      shape[axis] = head.size(shape[axis]);
      stride[axis] *= head.step;
      _indexer_inplace_impl(axis + 1, tail...);
    }

    template <class... Tail>
    void _indexer_inplace_impl(dim_type axis, int head, Tail... tail) {
      offset += head * stride[axis];
      shape.erase(shape.begin() + axis);
      stride.erase(stride.begin() + axis);
      _indexer_inplace_impl(axis, tail...);
    }

    template <class... Index>
    void indexer_inplace(Index... indices) {
      if (sizeof...(indices) > ndim) {
	throw std::invalid_argument("IndexError: too many indices for array: array is " + std::to_string(ndim) + "-dimensional, but " + std::to_string(sizeof...(indices)) + " were indexed");
      }      
      _indexer_inplace_impl(0, indices...);
      adjust_to_shape();
    }

    template <class... Index>
    array_metadata indexer(Index... indices) const {
      array_metadata newmeta(*this);
      newmeta.indexer_inplace(indices...);
      return newmeta;
    }

    array_metadata transpose(const std::vector<dim_type>& axes) const {
      if (axes.size() != ndim)
	throw std::invalid_argument("ValueError: axes don't match array");
      shape_type newshape;
      stride_type newstride;
      for (const auto e : axes) {
	newshape.push_back(shape[e]);
	newstride.push_back(stride[e]);
      }
      return array_metadata(newshape, newstride);
    }

    array_metadata transpose() const {
      std::vector<dim_type> axes(ndim);
      for(int i=0; i<ndim; i++)
	axes[i] = ndim - 1 - i;
      return transpose(axes);
    }

  public:
    // for debug
    std::string __repr__() const override {
      std::stringstream ss;
      ss << "array_metadata(";
      ss << "shape=" << utils::str(shape);
      ss << ", size=" << size;
      ss << ", ndim=" << ndim;
      ss << ", offset=" << offset;
      ss << ", stride=" << utils::str(stride);
      ss << ")";
      return ss.str();
    }
  };
  
}

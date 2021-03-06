#pragma once

#include <functional>
#include <algorithm> // transform
#include <utility> // move
#include <type_traits> // is_same

namespace numpy {

  template <class Dtype> class ndarray;
  template <class Dtype> ndarray<Dtype> empty(const shape_type& shape);

  class ufunc {
  /**
   * https://numpy.org/doc/stable/reference/ufuncs.html 
   * https://numpy.org/doc/stable/reference/generated/numpy.ufunc.html
   **/
    
    /**
     * Attributes
     * ----------
     * identity
     *   The identity value.
     * nargs
     *   The number of arguments.
     * nin
     *   The number of inputs.
     * nout
     *   The number of outputs.
     * ntypes
     *   The number of types.
     * signature
     *   Definition of the core elements a generalized ufunc operates on.
     * types
     *   Returns a list with types grouped input->output.
     **/

    /**
     * Methods
     * -------
     * __call__(*args, **kwargs)
     *   Call self as a function.
     * accumulate(array[, axis, dtype, out])
     *   Accumulate the result of applying the operator to all elements.
     * at(a, indices[, b])
     *   Performs unbuffered in place operation on operand ‘a’ for elements specified by ‘indices’.
     * outer(A, B, /, **kwargs)
     *   Apply the ufunc op to all pairs (a, b) with a in A and b in B.
     * reduce(array[, axis, dtype, out, keepdims, …])
     *   Reduces array’s dimension by one, by applying ufunc along one axis.
     * reduceat(array, indices[, axis, dtype, out])
     *   Performs a (local) reduce with specified slices over a single axis.
    **/
  };


  template <template <class> class UnaryOperation>
  struct ufunc_unary: public ufunc {

    template <class Type> using return_type = typename std::remove_const<typename std::invoke_result<UnaryOperation<Type>, Type>::type>::type;
    constexpr ufunc_unary() = default;
    
    template <class Type>
    auto operator()(const ndarray<Type>& x) const -> ndarray< return_type<Type> > {
      auto out = empty<decltype(UnaryOperation<Type>()(Type()))>(x.shape());
      return operator()(x, out);
    }
    
    template <class Type, class OutputType>
    auto operator()(const ndarray<Type>& x, ndarray<OutputType>& out) const
      -> ndarray< return_type<Type> >& {
					
      static_assert(std::is_same_v<OutputType, return_type<Type>>,
		    "output operand of invalid type");
      
      auto x_copy = x.view;
      array_view::broadcast(out.view, x_copy);
      ndarray<Type> x_broadcasted(x.memory_ptr, x_copy, x.base_ptr);
      std::transform(x_broadcasted.begin(), x_broadcasted.end(),
		     out.begin(), UnaryOperation<Type>());
      return out;
    }
    
    template <class Type, class... Args>
    auto operator()(const Type& x, const Args&... args) const
      ->typename std::enable_if<std::is_arithmetic<Type>::value,
				decltype(operator()(ndarray(x), args...))
				>::type {
      return operator()(ndarray(x), args...);
    }     

  };
  

  template <template <class, class> class BinaryOperation>
  struct ufunc_binary: public ufunc {

    template <class Type1, class Type2>
    using return_type = typename std::remove_const<typename std::invoke_result<BinaryOperation<Type1, Type2>, Type1, Type2>::type>::type;
    // template <class Type1, class Type2, class... Args>
    // using return_type_scolar_args =
    //   typename std::enable_if<std::is_arithmetic<Type1>::value,
    // 			      decltype(operator()(std::declval<ndarray<Type1>>(),
    // 						  std::declval<Type2>(),
    // 						  std::declval<Args>()...))>::type;
    constexpr ufunc_binary() = default;

    template <class Type1, class Type2>
    auto operator()(const ndarray<Type1>& x1, const ndarray<Type2>& x2) const
      -> ndarray< return_type<Type1, Type2> > {
      auto outshape = array_view::get_broadcasted_shape(x1.view, x2.view);
      auto out = empty<return_type<Type1, Type2>>(outshape);
      return operator()(x1, x2, out);
    }
    
    template <class Type1, class Type2, class OutputType>
    auto operator()(const ndarray<Type1>& x1, const ndarray<Type2>& x2, ndarray<OutputType>& out) const
      -> ndarray< return_type<Type1, Type2>> & {
      static_assert(std::is_same_v<OutputType, return_type<Type1, Type2>>,
		    "output operand of invalid type");

      // avoid the memory overlap problem (issue #13)
      if (may_share_memory(x1, out)) {
	auto tmp = x1.copy();
	return operator()(tmp, x2, out);
      }

      if (may_share_memory(x2, out)) {
	auto tmp = x2.copy();
	return operator()(x1, tmp, out);
      }
      
      auto x1_copy = x1.view;
      auto x2_copy = x2.view;
      array_view::broadcast(out.view, x1_copy, x2_copy);
      ndarray<Type1> x1_broadcasted(x1.memory_ptr, x1_copy, x1.base_ptr);
      ndarray<Type2> x2_broadcasted(x2.memory_ptr, x2_copy, x2.base_ptr);
      std::transform(x1_broadcasted.begin(), x1_broadcasted.end(),
		     x2_broadcasted.begin(), out.begin(), BinaryOperation<Type1, Type2>());
      return out;
    }

    template <class Type1, class Type2, class... Args>
    auto operator()(const Type1& x1, const Type2& x2, const Args&... args) const
      ->typename std::enable_if<isscolar<Type2>(),//std::is_arithmetic<Type2>::value,
				decltype(operator()(x1, ndarray(x2), args...))
				>::type {
      return operator()(x1, ndarray(x2), args...);
    }     

    template <class Type1, class Type2, class... Args>
    auto operator()(const Type1& x1, const Type2& x2, const Args&... args) const
      -> typename std::enable_if<isscolar<Type1>(),// std::is_arithmetic<Type1>::value,
      				 decltype(operator()(ndarray(x1),
      						     std::declval<Type2>(),
      						     std::declval<Args>()...
      						     ))>::type
    {
      return operator()(ndarray(x1), x2, args...);
    }
    
  };
}

#include <numpy/ufunc_instances.hpp>

namespace numpy {

  namespace _ufunc_internal {
    
    template <class Type1, class Type2>
    struct _divide {
      constexpr _divide() = default;
      template <class Type> using Float = typename std::conditional<std::is_integral<Type>::value, double, Type>::type;
      auto operator()(Type1 x1, Type2 x2)
	-> decltype(static_cast<Float<Type1>>(x1) / static_cast<Float<Type2>>(x2)) const {
	return static_cast<Float<Type1>>(x1) / static_cast<Float<Type2>>(x2);
      }
    };
    
  }
  
  constexpr ufunc_binary<_ufunc_internal::_divide> divide;	// Returns a true division of the inputs, element-wise.
  constexpr auto true_divide = divide;	// Returns a true division of the inputs, element-wise.

}

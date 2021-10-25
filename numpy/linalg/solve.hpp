#pragma once

namespace numpy {

  namespace linalg {

    using python::slice;
    using python::str;
    
    template <class Dtype>
    using matrix = ndarray<Dtype>;
    template <class Type>
    using Float = typename std::conditional<std::is_floating_point<Type>::value, Type, double>::type;

    /* direct solvers */
    
    template <class Dtype>
    void _forward_elimination_step(matrix<Dtype>& a, ndarray<int>& p) {
      // pivot selection
      auto abs_first_col = fabs(a(":", 0));
      auto itr_pivot = std::max_element(abs_first_col.begin(), abs_first_col.end());
      auto idx_pivot = itr_pivot.get_index();

      // swap
      if (idx_pivot) {
	auto tmp = a(idx_pivot).copy();
	a(idx_pivot) = a(0);
	a(0) = tmp;

	auto tmp_p = p[{idx_pivot}];
	p(idx_pivot) = p(0);
	p(0) = tmp_p;
      }
      
      // sweap
      auto sl = slice("1:");
      a(sl, 0) *= 1.0 / *a.begin();
      a(sl, sl) -= a(0, sl) * a(sl, slice(0, 1));
    }

    template <class Dtype>
    ndarray<int> _forward_elimination(matrix<Dtype>& Ab) {
      // Let us consider the following equation:
      //   Ax = b.
      // This function conducts forward elimination in-place.
      //
      // parameter:
      // Ab : coefficient matrix A or augmented coefficient matrix (A|b)
      
      // !add exception handling here!
      static_assert(std::is_floating_point_v<Dtype>);

      int i;
      auto n = Ab.shape(0);
      auto p = array(python::range(n)); // permutation

      for (i=0; i<n-1; i++) {
	auto sl = slice(str(i) + ":");
	auto lower_right_block = Ab(sl, sl);
	auto p_sliced = p(sl);
	_forward_elimination_step(lower_right_block, p_sliced);
      }

      return p;
    }

    template <class Dtype>
    void _backward_substitution_upper(const matrix<Dtype>& A, matrix<Dtype>& b, bool diag_is_1=false) {
      // conducts backward substitution in-place.
      //
      // parameters:
      // A : UPPER triangular coefficient matrix
      // b : constant vector

      auto n = A.shape(0);
      for (int i=n-1; i>=0; i--) {
	auto sl = slice(str(i+1) + ":");
	if (i < n-1) {
	  auto sum = matmul(A(i, sl).copy(), b(sl).copy());
	  b(i) -= sum;
	}
	if (not diag_is_1)
	  b(i) /= A(i, i);
      }
    }

    template <class Dtype>
    void _backward_substitution_lower(const matrix<Dtype>& A, matrix<Dtype>& b, bool diag_is_1=false) {
      // conducts backward substitution in-place.
      //
      // parameters:
      // A : LOWER triangular coefficient matrix
      // b : constant vector

      auto n = A.shape(0);
      for (int i=0; i<n; i++) {
	auto sl = slice(":" + str(i));
	if (i > 0) {
	  auto sum = matmul(A(i, sl).copy(), b(sl).copy());
	  b(i) -= sum;
	}
	if (not diag_is_1)
	  b(i) /= A(i, i);
      }      
    }

    template <class Dtype>
    struct LU_decomposition {

      matrix<Dtype> LU;
      ndarray<int> p;
      
      LU_decomposition(const matrix<Dtype>& a, bool overwrite_a=false) {
	if (overwrite_a)
	  LU = a;
	else
	  LU = a.copy();
	assert(LU.shape(0) == LU.shape(1));
	p = _forward_elimination(LU);
      }

      matrix<Dtype> L() const {
	auto ret = zeros(LU.shape());
      	int i, j;
      	int n = LU.shape(0);
	for (i=0; i<n; i++)
	  for (j=0; j<n; j++) {
	    if (i > j)
	      ret(i, j) = LU(i, j);
	    if (i == j)
	      ret(i, j) = 1.0;
	  }
	return ret;
      }

      matrix<Dtype> U() const {
	auto ret = zeros(LU.shape());
      	int i, j;
      	int n = LU.shape(0);
	for (i=0; i<n; i++)
	  for (j=0; j<n; j++)
	    if (i <= j)
	      ret(i, j) = LU(i, j);
	return ret;
      }

      ndarray<Dtype> permute(const ndarray<Dtype>& b, bool overwrite_b=false) const {
	auto tmp = b.copy();
	ndarray<Dtype> rhs;
	if (overwrite_b)
	  rhs = b;
	else
	  rhs = empty(b.shape());

	auto itr = p.begin();
	auto end = p.end();
	int i = 0;
	for(; itr!=end; itr++, i++)
	  rhs(i) = tmp(*itr);

	return rhs;
      }

      ndarray<Dtype> solve(const ndarray<Dtype>& b, bool overwrite_b=false) const {	
	auto rhs = permute(b, overwrite_b);
	
	_backward_substitution_lower(LU, rhs, true);
	_backward_substitution_upper(LU, rhs, false);

	return rhs;
      }
    };
    
  }
}

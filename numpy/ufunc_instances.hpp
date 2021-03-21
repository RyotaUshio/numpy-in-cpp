// https://numpy.org/doc/stable/reference/ufuncs.html

#pragma once

#include <cmath>
#include <numeric>

namespace numpy {
  namespace _ufunc_internal {

    template <class Type1, class Type2>
    struct _add {
      constexpr _add() = default;
      auto operator()(Type1 x1, Type2 x2) -> decltype(x1 + x2) const {
        return x1 + x2;
      }
    };

    template <class Type1, class Type2>
    struct _subtract {
      constexpr _subtract() = default;
      auto operator()(Type1 x1, Type2 x2) -> decltype(x1 - x2) const {
        return x1 - x2;
      }
    };

    template <class Type1, class Type2>
    struct _multiply {
      constexpr _multiply() = default;
      auto operator()(Type1 x1, Type2 x2) -> decltype(x1 * x2) const {
        return x1 * x2;
      }
    };

    template <class Type1, class Type2>
    struct _divide {
      constexpr _divide() = default;
      auto operator()(Type1 x1, Type2 x2) -> decltype(double(x1) / double(x2)) const {
        return double(x1) / double(x2);
      }
    };

    template <class Type1, class Type2>
    struct _logaddexp {
      constexpr _logaddexp() = default;
      auto operator()(Type1 x1, Type2 x2) -> decltype(std::log(std::exp(x1) + std::exp(x2))) const {
        return std::log(std::exp(x1) + std::exp(x2));
      }
    };

    template <class Type1, class Type2>
    struct _logaddexp2 {
      constexpr _logaddexp2() = default;
      auto operator()(Type1 x1, Type2 x2) -> decltype(std::log2(std::exp2(x1) + std::exp2(x2))) const {
        return std::log2(std::exp2(x1) + std::exp2(x2));
      }
    };

    template <class Type1, class Type2>
    struct _true_divide {
      constexpr _true_divide() = default;
      auto operator()(Type1 x1, Type2 x2) -> decltype(double(x1) / double(x2)) const {
        return double(x1) / double(x2);
      }
    };

    template <class Type1, class Type2>
    struct _floor_divide {
      constexpr _floor_divide() = default;
      auto operator()(Type1 x1, Type2 x2) -> decltype(long(x1) / long(x2)) const {
        return long(x1) / long(x2);
      }
    };

    template <class Type>
    struct _negative {
      constexpr _negative() = default;
      auto operator()(Type x) -> decltype(-x) const {
        return -x;
      }
    };

    template <class Type>
    struct _positive {
      constexpr _positive() = default;
      auto operator()(Type x) -> decltype(+x) const {
        return +x;
      }
    };

    template <class Type1, class Type2>
    struct _power {
      constexpr _power() = default;
      auto operator()(Type1 x1, Type2 x2) -> decltype(std::pow(x1, x2)) const {
        return std::pow(x1, x2);
      }
    };

    template <class Type1, class Type2>
    struct _float_power {
      constexpr _float_power() = default;
      auto operator()(Type1 x1, Type2 x2) -> decltype(std::pow(x1, x2)) const {
        return std::pow(x1, x2);
      }
    };

    template <class Type1, class Type2>
    struct _fmod {
      constexpr _fmod() = default;
      auto operator()(Type1 x1, Type2 x2) -> decltype(std::fmod(x1, x2)) const {
        return std::fmod(x1, x2);
      }
    };

    template <class Type>
    struct _absolute {
      constexpr _absolute() = default;
      auto operator()(Type x) -> decltype(std::abs(x)) const {
        return std::abs(x);
      }
    };

    template <class Type>
    struct _fabs {
      constexpr _fabs() = default;
      auto operator()(Type x) -> decltype(std::fabs(x)) const {
        return std::fabs(x);
      }
    };

    template <class Type>
    struct _rint {
      constexpr _rint() = default;
      auto operator()(Type x) -> decltype(std::round(x)) const {
        return std::round(x);
      }
    };

    template <class Type>
    struct _sign {
      constexpr _sign() = default;
      auto operator()(Type x) -> decltype((Type(0) < x) - (x < Type(0))) const {
        return (Type(0) < x) - (x < Type(0));
      }
    };

    template <class Type1, class Type2>
    struct _heaviside {
      constexpr _heaviside() = default;
      auto operator()(Type1 x1, Type2 x2) -> decltype(std::max(x1, 0)) const {
        return std::max(x1, 0);
      }
    };

    template <class Type>
    struct _conj {
      constexpr _conj() = default;
      auto operator()(Type x) -> decltype(std::conj(x)) const {
        return std::conj(x);
      }
    };

    template <class Type>
    struct _conjugate {
      constexpr _conjugate() = default;
      auto operator()(Type x) -> decltype(std::conj(x)) const {
        return std::conj(x);
      }
    };

    template <class Type>
    struct _exp {
      constexpr _exp() = default;
      auto operator()(Type x) -> decltype(std::exp(x)) const {
        return std::exp(x);
      }
    };

    template <class Type>
    struct _exp2 {
      constexpr _exp2() = default;
      auto operator()(Type x) -> decltype(std::exp2(x)) const {
        return std::exp2(x);
      }
    };

    template <class Type>
    struct _log {
      constexpr _log() = default;
      auto operator()(Type x) -> decltype(std::log(x)) const {
        return std::log(x);
      }
    };

    template <class Type>
    struct _log2 {
      constexpr _log2() = default;
      auto operator()(Type x) -> decltype(std::log2(x)) const {
        return std::log2(x);
      }
    };

    template <class Type>
    struct _log10 {
      constexpr _log10() = default;
      auto operator()(Type x) -> decltype(std::log10(x)) const {
        return std::log10(x);
      }
    };

    template <class Type>
    struct _expm1 {
      constexpr _expm1() = default;
      auto operator()(Type x) -> decltype(std::expm1(x)) const {
        return std::expm1(x);
      }
    };

    template <class Type>
    struct _log1p {
      constexpr _log1p() = default;
      auto operator()(Type x) -> decltype(std::log1p(x)) const {
        return std::log1p(x);
      }
    };

    template <class Type>
    struct _sqrt {
      constexpr _sqrt() = default;
      auto operator()(Type x) -> decltype(std::sqrt(x)) const {
        return std::sqrt(x);
      }
    };

    template <class Type>
    struct _square {
      constexpr _square() = default;
      auto operator()(Type x) -> decltype(x * x) const {
        return x * x;
      }
    };

    template <class Type>
    struct _cbrt {
      constexpr _cbrt() = default;
      auto operator()(Type x) -> decltype(std::cbrt(x)) const {
        return std::cbrt(x);
      }
    };

    template <class Type>
    struct _reciprocal {
      constexpr _reciprocal() = default;
      auto operator()(Type x) -> decltype(std::pow(x, -1)) const {
        return std::pow(x, -1);
      }
    };

    template <class Type1, class Type2>
    struct _gcd {
      constexpr _gcd() = default;
      auto operator()(Type1 x1, Type2 x2) -> decltype(std::gcd(x1, x2)) const {
        return std::gcd(x1, x2);
      }
    };

    template <class Type1, class Type2>
    struct _lcm {
      constexpr _lcm() = default;
      auto operator()(Type1 x1, Type2 x2) -> decltype(std::lcm(x1, x2)) const {
        return std::lcm(x1, x2);
      }
    };

    template <class Type>
    struct _sin {
      constexpr _sin() = default;
      auto operator()(Type x) -> decltype(std::sin(x)) const {
        return std::sin(x);
      }
    };

    template <class Type>
    struct _cos {
      constexpr _cos() = default;
      auto operator()(Type x) -> decltype(std::cos(x)) const {
        return std::cos(x);
      }
    };

    template <class Type>
    struct _tan {
      constexpr _tan() = default;
      auto operator()(Type x) -> decltype(std::tan(x)) const {
        return std::tan(x);
      }
    };

    template <class Type>
    struct _arcsin {
      constexpr _arcsin() = default;
      auto operator()(Type x) -> decltype(std::asin(x)) const {
        return std::asin(x);
      }
    };

    template <class Type>
    struct _arccos {
      constexpr _arccos() = default;
      auto operator()(Type x) -> decltype(std::acos(x)) const {
        return std::acos(x);
      }
    };

    template <class Type>
    struct _arctan {
      constexpr _arctan() = default;
      auto operator()(Type x) -> decltype(std::atan(x)) const {
        return std::atan(x);
      }
    };

    template <class Type1, class Type2>
    struct _arctan2 {
      constexpr _arctan2() = default;
      auto operator()(Type1 x1, Type2 x2) -> decltype(std::atan(x1, x2)) const {
        return std::atan(x1, x2);
      }
    };

    template <class Type1, class Type2>
    struct _hypot {
      constexpr _hypot() = default;
      auto operator()(Type1 x1, Type2 x2) -> decltype(std::hypot(x1, x2)) const {
        return std::hypot(x1, x2);
      }
    };

    template <class Type>
    struct _sinh {
      constexpr _sinh() = default;
      auto operator()(Type x) -> decltype(std::sinh(x)) const {
        return std::sinh(x);
      }
    };

    template <class Type>
    struct _cosh {
      constexpr _cosh() = default;
      auto operator()(Type x) -> decltype(std::cosh(x)) const {
        return std::cosh(x);
      }
    };

    template <class Type>
    struct _tanh {
      constexpr _tanh() = default;
      auto operator()(Type x) -> decltype(std::tanh(x)) const {
        return std::tanh(x);
      }
    };

    template <class Type>
    struct _arcsinh {
      constexpr _arcsinh() = default;
      auto operator()(Type x) -> decltype(std::asinh(x)) const {
        return std::asinh(x);
      }
    };

    template <class Type>
    struct _arccosh {
      constexpr _arccosh() = default;
      auto operator()(Type x) -> decltype(std::acosh(x)) const {
        return std::acosh(x);
      }
    };

    template <class Type>
    struct _arctanh {
      constexpr _arctanh() = default;
      auto operator()(Type x) -> decltype(std::acosh(x)) const {
        return std::acosh(x);
      }
    };

    template <class Type>
    struct _degrees {
      constexpr _degrees() = default;
      auto operator()(Type x) -> decltype(double(x) * 180.0 / M_PI) const {
        return double(x) * 180.0 / M_PI;
      }
    };

    template <class Type>
    struct _radians {
      constexpr _radians() = default;
      auto operator()(Type x) -> decltype(double(x) * M_PI / 180.0) const {
        return double(x) * M_PI / 180.0;
      }
    };

  }

  auto add = ufunc_binary<_ufunc_internal::_add>();	// Add arguments element-wise.
  auto subtract = ufunc_binary<_ufunc_internal::_subtract>();	// Subtract arguments, element-wise.
  auto multiply = ufunc_binary<_ufunc_internal::_multiply>();	// Multiply arguments element-wise.
  auto divide = ufunc_binary<_ufunc_internal::_divide>();	// Returns a true division of the inputs, element-wise.
  auto logaddexp = ufunc_binary<_ufunc_internal::_logaddexp>();	// Logarithm of the sum of exponentiations of the inputs.
  auto logaddexp2 = ufunc_binary<_ufunc_internal::_logaddexp2>();	// Logarithm of the sum of exponentiations of the inputs in base-2.
  auto true_divide = ufunc_binary<_ufunc_internal::_true_divide>();	// Returns a true division of the inputs, element-wise.
  auto floor_divide = ufunc_binary<_ufunc_internal::_floor_divide>();	// Return the largest integer smaller or equal to the division of the inputs.
  auto negative = ufunc_unary<_ufunc_internal::_negative>();	// Numerical negative, element-wise.
  auto positive = ufunc_unary<_ufunc_internal::_positive>();	// Numerical positive, element-wise.
  auto power = ufunc_binary<_ufunc_internal::_power>();	// First array elements raised to powers from second array, element-wise.
  auto float_power = ufunc_binary<_ufunc_internal::_float_power>();	// First array elements raised to powers from second array, element-wise.
  auto fmod = ufunc_binary<_ufunc_internal::_fmod>();	// Return the element-wise remainder of division.
  auto absolute = ufunc_unary<_ufunc_internal::_absolute>();	// Calculate the absolute value element-wise.
  auto fabs = ufunc_unary<_ufunc_internal::_fabs>();	// Compute the absolute values element-wise.
  auto rint = ufunc_unary<_ufunc_internal::_rint>();	// Round elements of the array to the nearest integer.
  auto sign = ufunc_unary<_ufunc_internal::_sign>();	// Returns an element-wise indication of the sign of a number.
  auto heaviside = ufunc_binary<_ufunc_internal::_heaviside>();	// Compute the Heaviside step function.
  auto conj = ufunc_unary<_ufunc_internal::_conj>();	// Return the complex conjugate, element-wise.
  auto conjugate = ufunc_unary<_ufunc_internal::_conjugate>();	// Return the complex conjugate, element-wise.
  auto exp = ufunc_unary<_ufunc_internal::_exp>();	// Calculate the exponential of all elements in the input array.
  auto exp2 = ufunc_unary<_ufunc_internal::_exp2>();	// Calculate 2**p for all p in the input array.
  auto log = ufunc_unary<_ufunc_internal::_log>();	// Natural logarithm, element-wise.
  auto log2 = ufunc_unary<_ufunc_internal::_log2>();	// Base-2 logarithm of x.
  auto log10 = ufunc_unary<_ufunc_internal::_log10>();	// Return the base 10 logarithm of the input array, element-wise.
  auto expm1 = ufunc_unary<_ufunc_internal::_expm1>();	// Calculate exp(x) - 1 for all elements in the array.
  auto log1p = ufunc_unary<_ufunc_internal::_log1p>();	// Return the natural logarithm of one plus the input array, element-wise.
  auto sqrt = ufunc_unary<_ufunc_internal::_sqrt>();	// Return the non-negative square-root of an array, element-wise.
  auto square = ufunc_unary<_ufunc_internal::_square>();	// Return the element-wise square of the input.
  auto cbrt = ufunc_unary<_ufunc_internal::_cbrt>();	// Return the cube-root of an array, element-wise.
  auto reciprocal = ufunc_unary<_ufunc_internal::_reciprocal>();	// Return the reciprocal of the argument, element-wise.
  auto gcd = ufunc_binary<_ufunc_internal::_gcd>();  auto lcm = ufunc_binary<_ufunc_internal::_lcm>();

    /************************************* Tip **************************************/
	// The optional output arguments can be used to help you save memory for large calculations. If your arrays are large, complicated expressions can take longer than absolutely necessary due to the creation and (later) destruction of temporary calculation spaces. For example, the expression G = a * b + c is equivalent to t1 = A * B; G = T1 + C; del t1. It will be more quickly executed as G = A * B; add(G, C, G) which is the same as G = A * B; G += C.
	// All trigonometric functions use radians when an angle is called for. The ratio of degrees to radians is 180^{\circ}/\pi.
  auto sin = ufunc_unary<_ufunc_internal::_sin>();	// Trigonometric sine, element-wise.
  auto cos = ufunc_unary<_ufunc_internal::_cos>();	// Cosine element-wise.
  auto tan = ufunc_unary<_ufunc_internal::_tan>();	// Compute tangent element-wise.
  auto arcsin = ufunc_unary<_ufunc_internal::_arcsin>();	// Inverse sine, element-wise.
  auto arccos = ufunc_unary<_ufunc_internal::_arccos>();	// Trigonometric inverse cosine, element-wise.
  auto arctan = ufunc_unary<_ufunc_internal::_arctan>();	// Trigonometric inverse tangent, element-wise.
  auto arctan2 = ufunc_binary<_ufunc_internal::_arctan2>();	// Element-wise arc tangent of x1/x2 choosing the quadrant correctly.
  auto hypot = ufunc_binary<_ufunc_internal::_hypot>();	// Given the “legs” of a right triangle, return its hypotenuse.
  auto sinh = ufunc_unary<_ufunc_internal::_sinh>();	// Hyperbolic sine, element-wise.
  auto cosh = ufunc_unary<_ufunc_internal::_cosh>();	// Hyperbolic cosine, element-wise.
  auto tanh = ufunc_unary<_ufunc_internal::_tanh>();	// Compute hyperbolic tangent element-wise.
  auto arcsinh = ufunc_unary<_ufunc_internal::_arcsinh>();	// Inverse hyperbolic sine element-wise.
  auto arccosh = ufunc_unary<_ufunc_internal::_arccosh>();	// Inverse hyperbolic cosine, element-wise.
  auto arctanh = ufunc_unary<_ufunc_internal::_arctanh>();	// Inverse hyperbolic tangent element-wise.
  auto degrees = ufunc_unary<_ufunc_internal::_degrees>();	// Convert angles from radians to degrees.
  auto radians = ufunc_unary<_ufunc_internal::_radians>();	// Convert angles from degrees to radians.
  const auto deg2rad = radians;	// Convert angles from degrees to radians.
  const auto rad2deg = degrees;	// Convert angles from radians to degrees.

}

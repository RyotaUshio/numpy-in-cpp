// https://numpy.org/doc/stable/reference/ufuncs.html

#pragma once
#include <algorithm>

namespace numpy {

  ufunc_binary add(); 	// Add arguments element-wise.
  ufunc_binary subtract(); 	// Subtract arguments, element-wise.
  ufunc_binary multiply(); 	// Multiply arguments element-wise.
  ufunc_binary matmul(); 	// Matrix product of two arrays.
  ufunc_binary divide(); 	// Returns a true division of the inputs, element-wise.
  ufunc_binary logaddexp(); 	// Logarithm of the sum of exponentiations of the inputs.
  ufunc_binary logaddexp2(); 	// Logarithm of the sum of exponentiations of the inputs in base-2.
  ufunc_binary true_divide(); 	// Returns a true division of the inputs, element-wise.
  ufunc_binary floor_divide(); 	// Return the largest integer smaller or equal to the division of the inputs.
  ufunc_unary negative();  	// Numerical negative, element-wise.
  ufunc_unary positive();  	// Numerical positive, element-wise.
  ufunc_binary power(); 	// First array elements raised to powers from second array, element-wise.
  ufunc_binary float_power(); 	// First array elements raised to powers from second array, element-wise.
  ufunc_binary remainder(); 	// Return element-wise remainder of division.
  ufunc_binary mod(); 	// Return element-wise remainder of division.
  ufunc_binary fmod(); 	// Return the element-wise remainder of division.
  ufunc_binary divmod(); 	// Return element-wise quotient and remainder simultaneously.
  ufunc_unary absolute();  	// Calculate the absolute value element-wise.
  ufunc_unary fabs();  	// Compute the absolute values element-wise.
  ufunc_unary rint();  	// Round elements of the array to the nearest integer.
  ufunc_unary sign();  	// Returns an element-wise indication of the sign of a number.
  ufunc_binary heaviside(); 	// Compute the Heaviside step function.
  ufunc_unary conj();  	// Return the complex conjugate, element-wise.
  ufunc_unary conjugate();  	// Return the complex conjugate, element-wise.
  ufunc_unary exp();  	// Calculate the exponential of all elements in the input array.
  ufunc_unary exp2();  	// Calculate 2**p for all p in the input array.
  ufunc_unary log();  	// Natural logarithm, element-wise.
  ufunc_unary log2();  	// Base-2 logarithm of x.
  ufunc_unary log10();  	// Return the base 10 logarithm of the input array, element-wise.
  ufunc_unary expm1();  	// Calculate exp(x) - 1 for all elements in the array.
  ufunc_unary log1p();  	// Return the natural logarithm of one plus the input array, element-wise.
  ufunc_unary sqrt();  	// Return the non-negative square-root of an array, element-wise.
  ufunc_unary square();  	// Return the element-wise square of the input.
  ufunc_unary cbrt();  	// Return the cube-root of an array, element-wise.
  ufunc_unary reciprocal();  	// Return the reciprocal of the argument, element-wise.
  ufunc_binary gcd();   ufunc_binary lcm(); 

  /************************************* Tip **************************************/
	// The optional output arguments can be used to help you save memory for large calculations. If your arrays are large, complicated expressions can take longer than absolutely necessary due to the creation and (later) destruction of temporary calculation spaces. For example, the expression G = a * b + c is equivalent to t1 = A * B; G = T1 + C; del t1. It will be more quickly executed as G = A * B; add(G, C, G) which is the same as G = A * B; G += C.
	// All trigonometric functions use radians when an angle is called for. The ratio of degrees to radians is 180^{\circ}/\pi.
  ufunc_unary sin();  	// Trigonometric sine, element-wise.
  ufunc_unary cos();  	// Cosine element-wise.
  ufunc_unary tan();  	// Compute tangent element-wise.
  ufunc_unary arcsin();  	// Inverse sine, element-wise.
  ufunc_unary arccos();  	// Trigonometric inverse cosine, element-wise.
  ufunc_unary arctan();  	// Trigonometric inverse tangent, element-wise.
  ufunc_binary arctan2(); 	// Element-wise arc tangent of x1/x2 choosing the quadrant correctly.
  ufunc_binary hypot(); 	// Given the “legs” of a right triangle, return its hypotenuse.
  ufunc_unary sinh();  	// Hyperbolic sine, element-wise.
  ufunc_unary cosh();  	// Hyperbolic cosine, element-wise.
  ufunc_unary tanh();  	// Compute hyperbolic tangent element-wise.
  ufunc_unary arcsinh();  	// Inverse hyperbolic sine element-wise.
  ufunc_unary arccosh();  	// Inverse hyperbolic cosine, element-wise.
  ufunc_unary arctanh();  	// Inverse hyperbolic tangent element-wise.
  ufunc_unary degrees();  	// Convert angles from radians to degrees.
  ufunc_unary radians();  	// Convert angles from degrees to radians.
  ufunc_unary deg2rad();  	// Convert angles from degrees to radians.
  ufunc_unary rad2deg();  	// Convert angles from radians to degrees.
	// These function all require integer arguments and they manipulate the bit-pattern of those arguments.
  ufunc_binary bitwise_and(); 	// Compute the bit-wise AND of two arrays element-wise.
  ufunc_binary bitwise_or(); 	// Compute the bit-wise OR of two arrays element-wise.
  ufunc_binary bitwise_xor(); 	// Compute the bit-wise XOR of two arrays element-wise.
  ufunc_unary invert();  	// Compute bit-wise inversion, or bit-wise NOT, element-wise.
  ufunc_binary left_shift(); 	// Shift the bits of an integer to the left.
  ufunc_binary right_shift(); 	// Shift the bits of an integer to the right.
  ufunc_binary greater(); 	// Return the truth value of (x1 > x2) element-wise.
  ufunc_binary greater_equal(); 	// Return the truth value of (x1 >= x2) element-wise.
  ufunc_binary less(); 	// Return the truth value of (x1 < x2) element-wise.
  ufunc_binary less_equal(); 	// Return the truth value of (x1 <= x2) element-wise.
  ufunc_binary not_equal(); 	// Return (x1 != x2) element-wise.
  ufunc_binary equal(); 	// Return (x1 == x2) element-wise.


  /*********************************** Warning ************************************/
	// Do not use the Python keywords and and or to combine logical array expressions. These keywords will test the truth value of the entire array (not element-by-element as you might expect). Use the bitwise operators & and | instead.
  ufunc_binary logical_and(); 	// Compute the truth value of x1 AND x2 element-wise.
  ufunc_binary logical_or(); 	// Compute the truth value of x1 OR x2 element-wise.
  ufunc_binary logical_xor(); 	// Compute the truth value of x1 XOR x2, element-wise.
  ufunc_unary logical_not();  	// Compute the truth value of NOT x element-wise.


  /*********************************** Warning ************************************/
	// The bit-wise operators & and | are the proper way to perform element-by-element array comparisons. Be sure you understand the operator precedence: (a > 2) & (a < 5) is the proper syntax because a > 2 & a < 5 will result in an error due to the fact that 2 & a is evaluated first.
  ufunc_binary maximum(); 	// Element-wise maximum of array elements.


  /************************************* Tip **************************************/
	// The Python function max() will find the maximum over a one-dimensional array, but it will do so using a slower sequence interface. The reduce method of the maximum ufunc is much faster. Also, the max() method will not give answers you might expect for arrays with greater than one dimension. The reduce method of minimum also allows you to compute a total minimum over an array.
  ufunc_binary minimum(); 	// Element-wise minimum of array elements.


  /*********************************** Warning ************************************/
	// the behavior of maximum(a, b) is different than that of max(a, b). As a ufunc, maximum(a, b) performs an element-by-element comparison of a and b and chooses each element of the result according to which element in the two arrays is larger. In contrast, max(a, b) treats the objects a and b as a whole, looks at the (total) truth value of a > b and uses it to return either a or b (as a whole). A similar difference exists between minimum(a, b) and min(a, b).
  ufunc_binary fmax(); 	// Element-wise maximum of array elements.
  ufunc_binary fmin(); 	// Element-wise minimum of array elements.
	// Recall that all of these functions work element-by-element over an array, returning an array output. The description details only a single operation.
  ufunc_unary isfinite();  	// Test element-wise for finiteness (not infinity or not Not a Number).
  ufunc_unary isinf();  	// Test element-wise for positive or negative infinity.
  ufunc_unary isnan();  	// Test element-wise for NaN and return result as a boolean array.
  ufunc_unary isnat();  	// Test element-wise for NaT (not a time) and return result as a boolean array.
  ufunc_unary fabs();  	// Compute the absolute values element-wise.
  ufunc_unary signbit();  	// Returns element-wise True where signbit is set (less than zero).
  ufunc_binary copysign(); 	// Change the sign of x1 to that of x2, element-wise.
  ufunc_binary nextafter(); 	// Return the next floating-point value after x1 towards x2, element-wise.
  ufunc_unary spacing();  	// Return the distance between x and the nearest adjacent number.
  ufunc_unary modf();  	// Return the fractional and integral parts of an array, element-wise.
  ufunc_binary ldexp(); 	// Returns x1 * 2**x2, element-wise.
  ufunc_unary frexp();  	// Decompose the elements of x into mantissa and twos exponent.
  ufunc_binary fmod(); 	// Return the element-wise remainder of division.
  ufunc_unary floor();  	// Return the floor of the input, element-wise.
  ufunc_unary ceil();  	// Return the ceiling of the input, element-wise.
  ufunc_unary trunc();  	// Return the truncated value of the input, element-wise.

}

// https://numpy.org/doc/stable/user/basics.types.html
// https://numpy.org/doc/1.17/reference/c-api.dtype.html

#pragma once
#include <vector>
#include <cstdint>
#include <cfloat>
#include <complex>

namespace numpy {

  
  // (In the original NumPy, Booleans are represented in native bool type. But since std::vector<bool> is specialized and not able to be handled as vectors of other types, alternative representaion of Boolean values.) 
  // using bool_ = bool;			// Boolean (True or False) stored as a byte

  enum bool_ : char {False, True};
  using byte = signed char;		// Platform-defined
  using ubyte = unsigned char;		// Platform-defined
  using short_ = short;		        // Platform-defined (underscore is appended to make it unqualified-id)
  using ushort = unsigned short;	// Platform-defined
  using intc = int;			// Platform-defined
  using uintc = unsigned int;		// Platform-defined
  using int_ = long;			// Platform-defined
  using uint = unsigned long;		// Platform-defined
  using longlong = long long;		// Platform-defined
  using ulonglong = unsigned long long; // Platform-defined
  // using half = ...; using float16 = ...; // Half precision float: sign bit, 5 bits exponent, 10 bits mantissa
  using single = float;			// Platform-defined single precision float: typically sign bit, 8 bits exponent, 23 bits mantissa
  using double_ = double;        	// Platform-defined double precision float: typically sign bit, 11 bits exponent, 52 bits mantissa. (underscore is appended to make it unqualified-id)
  using longdouble = long double;	// Platform-defined extended-precision float
  // (In the original NumPy, complex numbers are represented in C-style data type defined in complex.h)
  using csingle = std::complex<float>;			 // Complex number, represented by two single-precision floats (real and imaginary components)
  using cdouble = std::complex<double>;			 // Complex number, represented by two double-precision floats (real and imaginary components).
  using clongdouble = std::complex<long double>;	 // Complex number, represented by two extended-precision floats (real and imaginary components).
  
  /******** fixed-size aliases ********/
  using bool8 = bool_; // https://numpy.org/doc/stable/reference/arrays.scalars.html#numpy.bool8
  using int8 =  std::int8_t;			   // Byte (-128 to 127)
  using int16 =  std::int16_t;		   // Integer (-32768 to 32767)
  using int32 = std::int32_t;		   // Integer (-2147483648 to 2147483647)
  using int64 = std::int64_t;		   // Integer (-9223372036854775808 to 9223372036854775807)
  using uint8 = std::uint8_t;		   // Unsigned integer (0 to 255)
  using uint16 = std::uint16_t;		   // Unsigned integer (0 to 65535)
  using uint32 = std::uint32_t;		   // Unsigned integer (0 to 4294967295)
  using uint64 = std::uint64_t;		   // Unsigned integer (0 to 18446744073709551615)
  using intp = std::intptr_t;		   // Integer used for indexing, typically the same as ssize_t
  using uintp = std::uintptr_t;		   // Integer large enough to hold a pointer
  using float32 = float;
  using float64 = double;		   // Note that this matches the precision of the builtin python float.
  using float_ = float64;
  using complex64 = std::complex<float>;   // Complex number, represented by two 32-bit floats (real and imaginary components)
  using complex128 = std::complex<double>; // Note that this matches the precision of the builtin python complex.
  using complex_ = complex128;

  template <class Dtype>
  struct is_complex : std::false_type {};
  template <class value_type>
  struct is_complex<std::complex<value_type>> : std::true_type {};
  // template <class Dtype>
  // struct isscolar : public std::false_type {};
  template <class Dtype>
  // struct isscolar<typename std::enable_if<std::is_arithmetic<Dtype>::value, Dtype>::type>
  //   : public std::true_type {};
  // struct isscolar<Dtype> : public std::enable_if<std::is_arithmetic<Dtype>::value, std::true_type>::type {};
  constexpr bool isscolar() {
    return std::is_arithmetic<Dtype>::value or is_complex<Dtype>::value;
  }

  /******** type aliases for internal use ********/
  using size_type = intp;
  using shape_elem_type = intp;
  using shape_type = std::vector<shape_elem_type>;
  using dim_type = intp;
  using axis_type = dim_type;
  using axes_type = std::vector<axis_type>;
  using stride_type = std::vector<intp>;
  using offset_type = intp;
  using coord_type = std::vector<dim_type>;
}

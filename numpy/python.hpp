#pragma once
#include <iostream>
#include <iomanip> // setprecision
#include <string>
#include <sstream>
#include <stdexcept>
#include <utility> // forward
#include <set>
#include <map>
#include <typeinfo>
#include <type_traits>
#include <numpy/slice.hpp>
#include <numpy/range.hpp>
#include <numpy/typename.hpp>
#include <numpy/dtype.hpp>
#include <numpy/utils.hpp>

namespace python {

  struct NoneType {
    operator bool() const {
      return false;
    }
    std::string __repr__() const {
      return "None";
    }
  };
  constexpr NoneType None;

  template <typename T>
  inline auto type(const T& obj) -> decltype(typeid(T)) {
    return typeid(T);
  }
  
  template <typename T>
  auto len(const T& obj) -> decltype(obj.__len__()) {
    return obj.__len__();
  }
  
  template <typename T>
  auto operator<<(std::ostream& os, const T& a) -> decltype(a.__repr__(), os) {
    os << a.__repr__();
    return os;
  }

  // template <typename T>
  // auto str(const T& obj) -> decltype(obj.__str__()) {
  //   return obj.__str__();
  // }

  std::string str(const bool obj) {
    return obj ? "True" : "False";
  }
  
  std::string str(const numpy::bool_& obj) {
    return str(static_cast<bool>(obj));
  }
  
  template <typename T>
  auto str(const T& obj) -> decltype((std::declval<std::stringstream>()<<obj).str()) {
    std::stringstream ss;
    ss << std::setprecision(2);
    ss << std::showpoint;
    ss << obj;
    return ss.str();
  }

  std::string str(const std::exception& e) {
    return e.what();
  }
  
  template <typename T>
  std::string vector_as_python_list(const std::vector<T>& vec) {
    return numpy::utils::vector_to_string(vec, "[", "]");
  }

  template <typename T>
  std::string vector_as_python_tuple(const std::vector<T>& vec) {
    if (vec.size() > 1)
      return numpy::utils::vector_to_string(vec, "(", ")");
    return numpy::utils::vector_to_string(vec, "(", ",)");
  }

  template <typename T>
  std::string str(const std::vector<T>& vec) {
    return vector_as_python_tuple(vec);
  }

  template <typename T1, typename T2>
  std::string str(const std::pair<T1, T2>& pair) {
    return "(" + str(pair.first) + ", " + str(pair.second) + ")";
  }

  template <typename T>
  std::string str(const std::set<T>& set) {
    return str(std::vector(set.begin(), set.end()));
  }

  template <typename Container>
  std::string str(const typename Container::iterator itr) {
    return str(*itr);
  }

  template <typename T>
  std::string str(std::__1::__wrap_iter<T> itr) {
    return str(*itr);
  }
  
  template <typename... T>
  std::string str(const std::map<T...>& map) {
    std::stringstream ss;
    bool first = true;
    ss << "{";
    for(const auto e : map) {
      if (not first) 
	ss << ", \n";
      ss << str(e.first) << ": " << str(e.second);
      first = false;
    }
    ss << "}";
    return ss.str();  
  }

  std::string str(const std::type_info& type) {
    return getNameByTypeInfo(type);
  }

  template <typename T>
  auto repr(const T& obj) -> decltype(std::declval<T>().__repr__()) {
    return obj.__repr__();
  }

  /**
   * `print_sep` can be writen concisely without recursion with C++17 Fold expression! 
   */

  /* Former implementation with recursion */
  
  // void _print_impl(bool first, std::string sep) {
  //   std::cout << std::endl;
  // }
  
  // template <class Head, class... Tail>
  // void _print_impl(bool first, std::string sep, Head&& head, Tail&&... tail) {
  //   if (not first)
  //     std::cout << sep;
  //   std::cout << str(head);
  //   _print_impl(false, sep, std::forward<Tail>(tail)...);
  // }

  // template <class... Args>
  // void print_sep(std::string sep, Args&&... args) {
  //   std::cout << std::boolalpha;
  //   _print_impl(true, sep, std::forward<Args>(args)...);
  // }

  /* New implementation with the fold expression (& generic lambda) */
  
  template <class... Args>
  void print_sep(std::string sep, Args&&... args) {
    bool first = true;
    std::cout << std::setprecision(8) << std::showpoint;
    (std::cout << ... << [sep, &first](auto&& arg){
			   if (first) {first = false; return str(arg);}
			   else return sep + str(arg);}(args));
    std::cout << std::endl;
  }

  template <class... Args>
  void print(Args&&... args) {
    print_sep(" ", std::forward<Args>(args)...);
  }

}

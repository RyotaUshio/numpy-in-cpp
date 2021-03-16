#include "python.hpp"
using namespace python;
#include "numpy.hpp"
#include <iostream>

namespace np = numpy;

int main() {
  np::ndarray<int> a({0, 1, 2, 3, 4, 5}, {2, 3});
  std::cout << std::boolalpha;
  print(repr(a.begin()));
  print(repr(a.end()));
  // for(np::ndarray<int>::iterator it=a.begin(); it!=a.end(); it++)
  //   std::cout << *it << std::endl;
 
}

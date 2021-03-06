#include <cassert>
#include <string>
#include <vector>
#include <numpy/python.hpp>
#include <numpy/numpy.hpp>

using namespace python;
namespace np = numpy;

int main() {
  // <initialization from a std::vector>
  // equivalent to `auto a = np::array(range(24)).reshape({2, 3, 4});`, which is more concise.
  std::vector<int> src;
  for(int i=0; i<24; i++) src.push_back(i);
  np::ndarray<int> a(src, {2, 3, 4});

  // <slice & indexing 1>
  auto b = a(":", -1, "::-1");
  auto c = a(0, ":", 1);
  auto d = c(1);
  auto e = a("+00000000000000:", "1:2:", 1);

  np::utils::test(a);
  np::utils::test(b);
  np::utils::test(c);
  np::utils::test(d);
  np::utils::test(e);

  // <indexing 2>
  int i, j, k;
  for(i=0; i<int(a.shape(0)); i++) for(j=0; j<int(a.shape(1)); j++) for(k=0; k<int(a.shape(2)); k++) print_sep("", "a(", i, ", ", j, ", ", k, ") = ", a(i, j, k));
      
  // <initialization from a C-style array>
  int src_carray[] = {0, 1, 2, 3};
  np::ndarray<int> carray1(src_carray, src_carray+4, {2, 2});
  assert(carray1.size() == 4);
  assert(carray1.ndim() == 2);
  np::ndarray<int> carray2(std::begin(src_carray), std::end(src_carray), {2, 2});
  assert(carray2.size() == 4);
  assert(carray2.ndim() == 2);

  // <reshaping>
  print_sep("\n", carray1, np::reshape(carray1, {1, 4}), np::reshape(carray1, {4, 1}), np::reshape(carray1, {4}));

  // <transpose() method>
  print_sep("\n", a, np::transpose(a, {0, 1, 2}), np::transpose(a, {0, 2, 1}), np::transpose(a, {1, 0, 2}), np::transpose(a, {1, 2, 0}), np::transpose(a, {2, 0, 1}), np::transpose(a, {2, 1, 0}), np::transpose(a));

  // <.T() method>
  auto a_T = a.T();
  print(a_T);
  
  // <full, zeros, ones>
  auto pies = np::full({2, 3}, np::pi);
  auto zeros = np::zeros({2, 3});
  auto ones_int = np::ones<np::int64>({2, 3});
  print(pies);
  print(zeros);
  print(ones_int);

  // <dtype conversion>
  auto ones = ones_int.astype<np::float64>();
  print(ones);

  // <arithmetic operations>
  print( pies += ones );
  print( ones -= pies );
  print( ones *= zeros );
  print( pies /= pies );
}

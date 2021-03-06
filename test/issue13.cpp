// THIS ISSUE'S ALREADY SOLVED.

#include <numpy/numpy.hpp>
using namespace python;
namespace np = numpy;

int main() {

  try{
    // self-assinment & compound assinment
    // メモリを共有するndarrayどうしの演算結果を、ふたたびその同じメモリに書き込むのでおかしなことになる
    auto x1 = np::array(range(9)).reshape({3, 3});
    auto x2 = x1.T();

    print(x1);
    print(x2);
    print(np::may_share_memory(x1, x2));

    auto x3 = x1 + x2;
    print(x3); // OK
    print(np::may_share_memory(x1, x3));
    x1 = x3; // OK
    print(np::may_share_memory(x1, x3));
    print(x1);
    print(x2);
    print(np::may_share_memory(x1, x2));

    auto x = np::array(range(9)).reshape({3, 3});
    auto y = x.T();

    print(x);
    print(y);
    print(np::may_share_memory(x, y));
    x += y; // not working -> PROBLEM SOLVED!!
    print(x);
    print(y);
    print(np::may_share_memory(x, y));

    // problems regarding broadcasting
    auto a = np::array(range(1, 5)).reshape({4, 1});
    auto b = np::array(range(1, 4)).reshape({1, 3});

    print(a);
    print(b);

    auto c = a + b; // not working -> PROBLEM SOLVED!!
  
    print(a);
    print(b);
    print(c);

    a += b; // This is invalid. An exception is thrown.
  
  } catch (const std::exception& e) {
    print(e);
  }
  
}

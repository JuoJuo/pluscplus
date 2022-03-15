#include <iostream>
using namespace std;

// 默认A = 0， B = 1， C=2；默认是一个32位的整形
enum Example {
  A,B,C
};

// 会从A = 5，递增B6， C7
enum Example2 {
  A2 = 5, B2, C2
};

//节约内存，8位就行了
enum Example3: unsigned char {
  A3 = 5, B3, C3
};

enum Example4 : char {
  A4 = 5, B4, C4
};

void useEnum() {
  Example value = A;
  Example2 value2 = A2;
  Example3 value3 = A3;
  Example4 value4 = A4;

  // 主要是提高代码可读性。相比if (value == 1) 或者你定义了很多单个的常量
  if (value == A) {
    cout << value;
  }
}

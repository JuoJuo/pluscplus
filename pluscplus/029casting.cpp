#include<iostream>



int main() {
  double value = 5.25;

  /*
    效果一样，主要是为了可读性，c++推荐写第二种
  */
  int v1 = value;
  int a = static_cast<int>(value);

  // dynamic_case 是用来检查两者是否有继承关系

  std::cout << a;
  return 1;
}

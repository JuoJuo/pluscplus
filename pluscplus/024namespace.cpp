#include<iostream>



int main024() {
  /*
    尽量全局避免写使用命名空间。因为多个库可能存在同一个函数名。就完了,

    还有C语言没有namspace的概念。所以更不推荐使用using namespace xxx。 所以c你都会发现，函数名都带 glInit之类的（OpenGL）


    可以写到某个函数里

    还可以重命名
  */
  using namespace std;

  namespace lirenjie = std;


  return 1;
}


namespace A {

  namespace B {
    void test() {
      std::cin.get();
    }
  }
}

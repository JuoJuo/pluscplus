#include <iostream>
using namespace std;

// 运行报错，因为，在static2.cpp里也有一个同名的全局可见的变量了。
// 但是如果我们把任何一个地方变量改成static，就不会报错了。static int s_Variable = 10;因为staic在这个编译单元有效，链接的时候不会去别的obj查找。
// 引用外部变量 extern int s_Variable 
int s_Variable = 10;

//结构体，默认就是public的,结构体与类的唯一区别，就是类成员默认是private的；
struct MyStruct
{
public:
  int a;
  int b;

  void sayHello() {
    cout << a << b;
  }
};

class Player {
public:
  int x, y;
  int speed;

  void Move(int xa, int ya) {
    x += xa * speed;
    y += ya * speed;

    cout << x << y;
  }
};
// 整个应用的入口函数，可以通过项目属性修改入口函数的名称
// 入口函数可以补写返回值，虽然函数要求了，应该是编译器处理过了
int main11() {
  MyStruct my;
  my.a = 1;
  my.b = 9;

  my.sayHello();

  Player player;
  player.x = 0;
  player.y = 0;
  player.speed = 2;
  player.Move(1,2);

  return 0;
}

// static（变量或函数）在类或者结构体里，所有类的对象，或者结构体对象，都是共享。内存里只有一份。通过类名::静态属性名调用
// 如果不在类或者结构体里，就是在那个编译单元内共享。函数内部的静态变量，也是共享的。不会去外部文件做链接。

#include<iostream>


struct Vector2
{
  float x, y;
};

struct Vector4
{
  union
  {
    struct
    {
      float x, y,z,w;
    };

    struct
    {
      Vector2 a,b;
    };
  };
};
/*
  联合体就是取所有属性最大的空间作为自己申请的内存大小。
  然后每个属性都是在同一块内存上写数据

  demo中Vector4一个对象占16字节（x86平台哈）

  原因里面联合体，两个结构体实际上是用的同一块内存，取大的申请。


  z赋值500，是修改了第三块4字节内存 所以打印结果 vector.b.x成了500
*/
int main028() {

  Vector4 vector = { 1.0f, 2.0f, 3.0f, 4.0f };

  std::cout << vector.a.x << vector.a.y;
  std::cout << vector.b.x << vector.b.y;

  vector.z = 500.0f;

  std::cout << vector.a.x << vector.a.y;
  std::cout << vector.b.x << vector.b.y;
  return 1;

}

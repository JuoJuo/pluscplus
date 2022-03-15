#include <iostream>
using namespace std;

class Entity {
public:
  float x, y;
  Entity() {
    x = 0.0f;
    y = 0.0f;
  }
  // 重载
  Entity(float z, float a) {
    x = z;
    y = a;
  }
  ~Entity() {
    cout << "destoryed entity";
    x = 0.0f;
    y = 0.0f;
  }
  void print() { 
    cout << x << endl << y << endl;
  }
};

static void test() {
  // 这样创建，不用new是在堆栈上创建一个对象，这个方法调用结束，就会自动回收内存，调用析构函数
  Entity e;

  Entity e2(1, 2);
}

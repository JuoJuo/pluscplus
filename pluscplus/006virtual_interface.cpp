#include <iostream>
#include <string>
using namespace std;

class Entity
{
public:
  virtual string GetName() {
    return "Entity";
  }
  // c++里，没有interface关键字，如果一个class里全是这种虚函数。那么就是接口,这种是必须要复写的。
  // virtual string GetName222() = 0;
};

// 继承多个用逗号隔开
class Player : public Entity {
private:
  string m_Name;
public:
  Player(const string& name):m_Name(name) {}

  string GetName() override {
    return m_Name;
  }
};

void PrintName(Entity* en) {

  cout << en->GetName() << endl;
}

int main() {

  Entity* e = new Entity();
  PrintName(e);

  Player* p = new Player("Lirenjie");
  PrintName(p);  // 此处如果不给需要复写的方法加virtual，就还是打印entity
  // 为了了代码可读性，我们最好还是给加上override
}

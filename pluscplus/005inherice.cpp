#include <iostream>;
using namespace std;


class Entity005
{
public:
  int x, y;
  Entity005() {
    cout << "init Entity";
  }
  virtual ~Entity005()
  {
    cout << "destory Entity";
  }

  void Move(int a, int b) {
    x += a;
    x += b;
  }

};

class Player : public Entity005 {
public:
  const char* Name;
  Player() {
    cout << "init Player";
  }
  ~Player()
  {
    cout << "destory Player";
  }
  void PrintName() {
    cout << Name << x << y;
  }
};


void test005() {

  Entity005* en = new Entity005();
  Player* play = new Player();

  /*
   多态这种，必须要在基类协商virtual，否则不会调用析构函数
  */
  Entity005* en2 = new Player();
}

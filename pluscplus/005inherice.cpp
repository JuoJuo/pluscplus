#include <iostream>;
using namespace std;


class Entity
{
public:
  int x, y;

  void Move(int a, int b) {
    x += a;
    x += b;
  }

   
};

class Player : public Entity {
public:
  const char* Name;

  void PrintName() {
    cout << Name << x << y;
  }
};

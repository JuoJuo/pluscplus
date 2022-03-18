#include<iostream>

struct MyStruct
{
  float a, b, c;
};


class Entity015 {
public:
  void print() const {
    std::cout << "hello";
  }
};

class ScopedPtr015 {
private:
  Entity015* m_Obj;
public:
  ScopedPtr015(Entity015* enc)
    :m_Obj(enc){}

  ~ScopedPtr015()
  {
    delete m_Obj;
  }

  Entity015* operator->() {
    return m_Obj;
  }

  Entity015* getObj() const {
    return m_Obj;
  }

};

/*
 手写->原理   取内容语法糖
*/
void main2() {
  ScopedPtr015 encc = new Entity015();

  //(*encc.getObj()).print();

  encc->print();
}


int main015() {
  /*
      (MyStruct*)nullptr  弄一个匿名指针（值为0）， MyStruct类型
      ((MyStruct*)nullptr)->a  访问a变量的值。（又一次说明了，不写&，默认就是访问变量地址里对应的内存里的值。）
      &((MyStruct*)nullptr)->a  取a变量的地址。
      (int)&((MyStruct*)nullptr)->a  把a变量的地址转为整数，就是偏移量
  */
  const int offseta = (int)&((MyStruct*)nullptr)->a;
  const int offsetb = (int)&((MyStruct*)nullptr)->b;
  const int offsetc = (int)&((MyStruct*)nullptr)->c;
  
  std::cout << offseta << std::endl << offsetb << std::endl << offsetc << std::endl;


  return 0;
}

#include<iostream>
#include<string>


class Example011 {
  public:
    Example011() {
      std::cout << "Example created" << std::endl;
    }
    Example011(int x) {
      std::cout << "Create Entity with: " << x << std::endl;
    }
};

class Entity011 {
  private:
    std::string m_Name;
    /*
      创建了一次
    */
    Example011 m_Example;
  public:
    Entity011() {
      m_Name = std::string("Unknonw");

      /*
        又创建了一次
      */
      m_Example = Example011(8);
    }

    /*
    这种方式会避免创建两次Example011
    Entity011() :m_Name(), m_Example(Example011(99)) {}
     */
};

int main011() {

  Entity011 eee;

  /*
   创建对象 Person p(); 堆栈
           Person* p = new Person();

           new在堆空间，需要手动delete
           第一种在堆栈，退出函数自己销毁，性能高。但是堆栈大小有限
  */

  Entity011* e11 = new Entity011();
  Entity011*  e11Arr = new Entity011[20];
  /*
  等价于上面这个new，只不过少了调用构造函数这一步
  */
  //Entity011* e12 = (Entity011*)malloc(sizeof(Entity011));

  return 0;
}

#include<iostream>
/*

  - operator

  - 每个变量名可以看成就是一个地址。

  - 只不过访问的时候，有些类型的变量里（地址对应的内存）存的是业务数据，有些还是存的地址。

  - code里的 var a = b，默认都是对地址里直接存的东西的赋值。

  - 那如果想对变量本身赋值怎么办？&variable
*/

/*
调用后堆栈就回收了（array）。因为这种方式是放在堆栈里的。
*/
int* getArr() {

  int array[50];

  return array;
}

class Jack {
  public:
    Jack()
    {
      std::cout << "created";
    }

    ~Jack()
    {
      std::cout << "deleted";
    }
};

class ScopedPtr {
  private:
    Jack* m_prt;
  public:
    ScopedPtr(Jack* ptr) :m_prt(ptr) {}
    ~ScopedPtr()
    {
      delete m_prt;
    }
};

void test()
{
  /*
    这里用到了隐式转换，相当于。利用堆栈会在离开作用域，自动回收内存的特性。
     ScopedPtr autoDelete(new A());

     自己释放了内存
  */
  ScopedPtr autoDelete = new Jack();
}

void smartPointer() {
  /* 原理跟上面一样。但是缺点是不能复制指针。 */
  std::unique_ptr<Jack> a = std::make_unique<Jack>();

  /* 共享版本,原理就是引用计数 */
  {
    std::shared_ptr<Jack> a2;
    {
      std::shared_ptr<Jack> a = std::make_shared<Jack>();
      a2 = a;
    }/*
      此时不会销毁Jack，计数还有1
      */
    
  }/*
      销毁Jack， 计数0
     */


     /* 共享版本,原理就是引用计数 */
  {
    std::weak_ptr<Jack> weak;
    {
      std::shared_ptr<Jack> a = std::make_shared<Jack>();
      weak = a;
    }/*
      此时销毁Jack因为是弱引用，离开第一个作用域就收了
      */
  }
}

#include<iostream>
using namespace std;


class Person {
private:
  int a;
  int* b;
  mutable int c;
public:

  Person(int a, int* b, mutable int c2):a(a),b(b), c(c2){

  }
  /* 函数里不能修改this */
  int getA() const {
    /* a = 1; 会报错,表示函数里不能修改变量的值 */
    /* b = nullptr; 会报错,表示函数里不能修改变量的值 */

     /* 因为c是mutable的 */
    c = 2;
    *b = 3;
    return a;
  }

  /* 暂时不知道*/
  int const getB() {
    a = 1;
    b = nullptr;
    c = 2;
    *b = 3;
    return *b;
  }

  /* 表示返回值的类型是const int* */
  const int* getB2() {
    return b;
  }
};

/*
p.getB();getB2（） error 因为引用p是const，我们要求能使用的成员函数，必要要是const的（结尾要带const）
*/
void test22(const Person& p) {
  p.getA();
}



int main009() {

  const int MAX_AGE = 90;

  /* const变量可以被 (int *)&MAX_AGE干成可以修改的。&MAX_AGE是一个 const int*类型，我们强转成了int* */
  int* test = (int *)&MAX_AGE;
  *test = 12;
  cout << *test << endl;

  /* const 指针类型是指的不能改里面的内容，指针本身能改 */
  const int* a = new int;
  /* 与上面一行等价 */
  int const* a_same = new int;
  a = &MAX_AGE;
  cout << *a;

  /* 改变const的位置，这个表示指针不能被修改。内容不可以*/
  int* const a1 = new int;
  *a1 = 111;

  /* 叠加版，都不能改 */

  const int* const a_all_no_change = new int;


  Person p(1, new int, 2);
  const int* b2 = p.getB2();
 // *b2 = 2;
  b2 = nullptr;
  /*  *b2 = 2; error */

  return 0;
}

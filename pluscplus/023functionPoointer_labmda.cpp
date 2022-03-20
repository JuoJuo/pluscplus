#include<iostream>
#include<string>
#include<vector>
#include<functional>


void Hello(const char* s) {

  std::cout << "hello--" << s << std::endl;

}

void PrintValue(int v) {
  std::cout << v << std::endl;
}

void forEach(const std::vector<int>& values, void(*func)(int)) {
  for (int value : values) {
    func(value);
  }
}

int main23() {

  auto fn = Hello;

  fn("world1");
  fn("world2");

  /*
   难看了点，函数指针类型就是两个括号带一个*，名字随便起 void(*xxx)()
 */
  void(*anyName)(const char*) = Hello;
  anyName("amny");

  /*
    换个方式
  */
  typedef void(*Hello2FN)(const char*);
  Hello2FN fntest = Hello;
  fntest("aaa");


  /*
   把函数当参数传递的demo，直接写函数名即可
*/
  std::vector<int> values = { 1,5,4,2,3 };

  forEach(values, PrintValue);

  /*
  自己定义一个lambda表达式作为函数传进去
*/
  forEach(values, [](int value) {  std::cout << value << std::endl; });


  /*
    传参的方式。=自动把用到的，都值传递，&自动把用到的，都引用传递

    lambda类型需要引入functional

    还有一个修改按照值传递进来的变量，需要加mutable
*/
  int testa = 111;
  auto lmbda = [=](int value) {  std::cout << testa << std::endl << value; };
  auto lmbda1 = [&](int value) {  std::cout << testa << std::endl << value; };
  auto lmbda2 = [testa](int value) {  std::cout << testa << std::endl << value; };
  auto lmbda3 = [&testa](int value) {  std::cout << testa << std::endl << value; };

  const std::function<void(int)>& func = lmbda;
  return 1;
}

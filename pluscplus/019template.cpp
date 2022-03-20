#include<iostream>
#include<string>

template<typename T>
void Print(T value) {
  std::cout << value;
}

template<typename T, int n>
class Array019 {
private:
  T m_Array[n];
public:
  int GetSize() const { return 5; }
};

/*

  通过泛型传进去的，可以由编译器替换任何位置的同名变量。原理就这样
  然后名字可以随便写，前面的key可以是typename（同于自动识别类型） int（用于固定的值替换）  float 等等
*/
int main019() {

  // compiler 会根据使用，自己生成对应的函数
  Print(1);
  Print("5");
  Print(1.1f);

  Array019<std::string, 2> a;

  Print(a.GetSize());


  std::cout << std::endl << sizeof(int);
  return 1;
}

#include<iostream>;



class Entity012 {

private:
  std::string m_name;
  int m_Age;
public:
  Entity012(const std::string& name):m_name(name),m_Age(-1){}

  Entity012(int age) :m_Age(age) {}
};

void printEntiry(const Entity012& enc) {

}

int main() {
  /*
    自带隐式数据类型转换。
  */
  Entity012 a1 = std::string("lirenjie");
  Entity012 a2 = 2;

  printEntiry(22);
  printEntiry(std::string("lirenjie"));
   
  /*
  可以关掉自动转换 explicit Entity012(const std::string& name):m_name(name),m_Age(-1){}
  */
  return 0;
}

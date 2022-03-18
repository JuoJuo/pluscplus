#include<iostream>
#include<vector>
#include<array>
#include<utility>


void useRef(int& a, int& b) {

  a = 1;
  b = 1;

}

void usePointer(int* a, int* b) {

  if (a) {
    *a = 0;
  }

  if (b) {
    *b = 0;
  }

}

std::string* useArr() {
  return new std::string[2] { "3", "3" };
}

std::array<std::string, 2> useArray() {
  return std::array<std::string, 2>{ "4", "4" };
}

std::vector<std::string> useVector() {
  std::vector<std::string> v(2);

  v[0] = "5";
  v[1] = "5";

  return v;
}

std::tuple<std::string, std::string> useTuple() {
  
  return std::make_pair("6", "6");
}


int main018() {

  int v1, v2;

  useRef(v1, v2);

  std::cout << v1 << v2;

  usePointer(&v1, &v2);

  std::cout << v1 << v2;

  /*
    因为是new的，需要自己释放内存
  */
  std::string * str = useArr();

  std::cout << str[0] << str[1];


  std::array<std::string, 2> aaa = useArray();

  std::cout << aaa[0] << aaa[1];


  std::vector<std::string> vct = useVector();
  std::cout << vct[0] << vct[1];


  std::tuple<std::string, std::string> tu = useTuple();
  // auto好使
  auto tu2 = useTuple();
  std::cout << std::get<0>(tu)<< std::get<1>(tu);
  std::cout << std::get<0>(tu2)<< std::get<1>(tu2);

  return 1;
}

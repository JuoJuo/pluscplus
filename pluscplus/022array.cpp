#include<iostream>
#include<array>


void PrintArray(std::array<int, 5>& data) {

  for (int i = 0; i < data.size(); i++)
  {
    std::cout << data[i];
  }

}

/*
  静态数组，初始化需要指定长度。在栈里。快一些


  相比int[5]需要自己维护记录length

*/

int main022() {

  std::array<int, 5> data;

  data[0] = 1;
  data[1] = 3;
  data[2] = 2;
  data[3] = 4;
  data[4] = 5;

  PrintArray(data);

  return 1;
}

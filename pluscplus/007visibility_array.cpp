#include <iostream>
#include <array>
using namespace std;



class Entity
{
// 类的内部可以访问
private:
// 类的内部，子类可以访问
protected:
// 都可以
public:

};


class Player : public Entity {
private:

public:

};



int main1() {
  int example[5];
  for (int i = 0; i < 5; i++)
  {
    example[i] = 0;
  }

  int* ptr = example;
  /* 这两个操作等价 */ 
  example[2] = 5;
  /*因为ptr是int*，所以加2实际上是加的 2 * 4 */
  *(ptr + 2) = 6;
  /* 加速理解，char*是一个字节，加2被转为 1*8，注意解引用的时候还是得转回去。不然只读一个字节就不是7了
   这个操作等价于*(ptr + 2) = x; */
  *(int *)((char *)ptr + 8) = 7;

  /*new 在堆上创建8*/
  int* anoter = new int[5];
  delete anoter;


  /*anoter里的数据，是堆里的一个地址，还得再去堆里的地址才能找到new的那块内存
   堆栈方式就是直接放的数据*/


   /*堆栈上的数组获取长度
   int len = sizeof(example) / sizeof(int); todo好像会在某些情况出错
  标准的是自己维护一个size变量*/


  /*标准库出了一个array*/
  array<int, 5> testArr;
  cout << testArr.size();

  return 0;
}

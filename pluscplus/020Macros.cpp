#include<iostream>

#define WAIT std::cin.get();
#define OPEN_CURY {;
#define LOG(x) std::cout<<x<<std::endl

#ifdef ENV
#define LOG(x) std::cout<<x<<std::endl
#else
#define DEVELOPMENT 132;
#endif


#define PRINT void print() \
{\
std::cout<<"print"<<std::endl;\
}

/*

  1.直接就是替换的含义。

  2.或者有参数的时候，可以把对应的参数替换到对应的地方


  3.属性选项里，c/c++ ，processor里设置一些相当于环境变量的变量名。

    配合#ifdef #else  #endif可以在运行时却分一些执行或不执行的代码

  4. define里斜杠是换行的意思
*/
PRINT

int main020() OPEN_CURY

  LOG("hello world");
  print();
  WAIT

  return 1;
}




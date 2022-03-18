#include<iostream>;
#include <GLFW/glfw3.h>;
/*
 还可以下#include <GLFW/glfw3.h> 引号跟尖括号其实没区别。 引号一般在本项目的解决方案的某个目录  尖括号一般就是不需要我们编译的

 提前下载好预编译好的二进制包，一般有include的头文件，跟在某个版本编译后的对应的二进制

 解决方案 右键  找到properties  c/c++ 常规  附加包含目录

 包含linker，常规  输入  一个写目录，一个写文件名


 还有动态链接库的引入，可以包含glfw3dll.lib,然后在生成的exe下面赋值那个DLL进去
*/

int main018() {


  const int a = glfwInit();

  std::cout << a;

  return 1;
}
/*
 在解决方案里新建项目，Engine


 在项目上右键，属性，设置编译输出的类型，就是配置类型： 改成lib或者dll

 然后在引入的项目里，项目使用，跟以前一样，include.h, 然后右键 添加 -》refrence -》 勾选engin项目即可
 
*/

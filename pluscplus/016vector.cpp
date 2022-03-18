#include<iostream>
#include<vector>


struct Vertex
{
  float x, y, z;
};

std::ostream& operator<<(std::ostream& stream, const Vertex& vertex) {

  stream << vertex.x << ", " << vertex.y << ", " << vertex.z;

  return stream;
}


/*
vertices传给函数当参数，也要时刻考虑对象拷贝的问题，是不是要传引用
*/ 
int main016() {
  /*
  std::vector<*Vertex> vertices 注意这个哦。在不同地址的内存，释放内存也是自动跟手动的区别哦

  */
  std::vector<Vertex> vertices;

  /*

  隐含创建的是堆栈对象额！

  */
  vertices.push_back({ 1,2,3 });
  vertices.push_back({ 4,5,6 });

  for (int i = 0; i < vertices.size(); i++)
  {
    std::cout << vertices[i] << std::endl;
  }

  vertices.erase(vertices.begin() + 1);
  /*
   始终记住，C++变量赋值，都会是拷贝！所以我们能用&就用&，const也是，能用就用
  */
  for (const Vertex& v : vertices)
  {
    std::cout << v << std::endl;
  }


  vertices.clear();

  for (const Vertex& v : vertices)
  {
    std::cout << v << std::endl;
  }


  /*

    c++里默认都会提供一个浅拷贝copy的构造函数。

    默认赋值都是浅拷贝

    数组有个默认容量，超了会拷贝原来的。到一块容量更大的内存空间。

    所以设置初始容量很重要，节约性能。


    下面的做法，相比于之前，就会没有拷贝，对象的创建，交给vector

  */
  std::vector<Vertex> v2;
  v2.reserve(888);

 // v2.emplace_back(1, 2, 3);
 // v2.emplace_back(11, 22, 33);
 // v2.emplace_back(11, 22, 33);


  //std::vector<Vertex&> v3;

  return 0;
}

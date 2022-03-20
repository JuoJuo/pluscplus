#include<iostream>

class String {
private:
  char* m_Buffer;
  unsigned int m_Size;

public:
  String(const char* str) {
    m_Size = strlen(str) + 1;
    m_Buffer = new char[m_Size];
    memcpy(m_Buffer, str, m_Size);
    m_Buffer[m_Size] = 0;
  }

  /* 自己提供一个用户拷贝的方法 */
  String(const String& other) :m_Size(other.m_Size) {
    m_Buffer = new char[m_Size + 1];
    memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
  }

  ~String()
  {
    delete[] m_Buffer;
  }

  unsigned int getSize() const {
    return m_Size;
  }

  void setSize(unsigned int c) {
    m_Size = c;
  }

  char& operator[](unsigned int index) {
    return m_Buffer[index];
  }

  /*
     friend表示 << 是咱们的朋友。可以在外部访问private变量
  */
  friend std::ostream& operator<<(std::ostream& stream, const String& string);
};

std::ostream& operator<<(std::ostream& stream, const String& string) {
  stream << string.m_Buffer;
  return stream;
}

void PrintString(String strObj) {
  std::cout << strObj << std::endl;
  std::cout << strObj.getSize() << std::endl;
}

void PrintStringref(const String& strObj) {
  std::cout << strObj << std::endl;
  std::cout << strObj.getSize() << std::endl;
}
int main014() {

  String strObj = "lirenjie";
  String strObjCopy = strObj;

  strObj[0] = 'a';
  strObj.setSize(2);

  // 会触发拷贝构造函数，因为参数不是引用
  PrintString(strObj);
  PrintString(strObjCopy);

  // 这种就不会触发拷贝构造函数，因为参数是引用
  PrintStringref(strObj);
  PrintStringref(strObjCopy);
  //std::cout << strObj << std::endl;
  //std::cout << strObjCopy << std::endl;
  //std::cout << strObj.getSize() << std::endl;
  //std::cout << strObjCopy.getSize() << std::endl;
  std::cin.get();
  return 0;

  /*
   总的来说C++里的赋值,只拷贝变量直接对应的内存区域的内容.
   对象的赋值，就是把里面的所有成员赋值一下。（就是大家常讲的浅拷贝）

   int a = 1;
   int b = a;

   Obj o1 = new Object
   Obj o2 = o1

   翻译：

   int 0x0011e6 = 1
   int 0x123457 = 1;

   Obj 0x25468a = 0xa6e811(这个地址指向一块内存)
   Obj 0x13368b = 0xa6e811(这个地址指向一块内存)

   那如果只想传递左侧的地址怎么办？
   没错，就是引用！ &a &b &o1
  */
}


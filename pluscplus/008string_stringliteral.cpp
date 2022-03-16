#include <iostream>
#include <string>
using namespace std;


int main008() {

  const char* str = "test";

  // c里字符是以\0为结束标记的
  char name[3] = {'j', 'i', '\0' };
  
  cout << strlen(name);

  //int a = strlen(str);
  //char copy[a];
  //strcpy(copy, str);

  //cout << copy;

  string strlin = "hello world";
  

  cout << strlin.size();


  if (strlin.find("world") != string::npos) {
    cout << "find !"; 
  }

  // 不同字节数的char
  const char* name0 = u8"fdsa";
  const wchar_t* name1 = L"fdsa";
  const char16_t* name2 = u"fdsa";
  const char32_t* name3 = U"fdsa";
  const char* name4 = u8"fdsa";
  const char* name5 = u8"fdsa";

  // 字符串字面量，是定义在read only memory
  /* 所以char* a1= "xxx"; string  a = "xxx"; 都是不可变的。*/
  string a = "a";
  string a1 = a + "b";
  string a2 = string("a") + "b";

  using namespace std::string_literals;
  string a3 = "a"s + "b";
  cout << endl;
  cout << endl;
  cout << a << endl << a1 << endl << a2 << endl <<a3;

  /* 换行操作 */
  const char* xxx = R"(line1
line2
line3)";

  const char* xxx2 = "aaa\n"
    "bbb\n"
    "ccc\n";

  cout << xxx << xxx2;

  return 1;
}

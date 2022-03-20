#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>

class Device {};

class DeviceMananger {
private:
  std::unordered_map<std::string, std::vector<Device*>> m_Deveices;
public:
  const std::unordered_map<std::string, std::vector<Device*>>& GetDevices() const {
    return m_Deveices;
  }
};

/*
  auto虽然可以不用关心数据类型，但是代码可读性降低

  有时候，类型又太长了。写起来很蛮麻烦
*/
int main021() {

  int a = 1;

  auto b = a;


  std::cout << a << b << std::endl;


  std::vector<std::string> strings;

  strings.push_back("Apple");
  strings.push_back("Orange");


  for (std::vector<std::string>::iterator it = strings.begin(); it != strings.end();it++)
  {
    std::cout << *it << std::endl;
  }

  for (auto it = strings.begin(); it != strings.end();it++)
  {
    std::cout << *it << std::endl;
  }

  // 太长了,也可以使用using 或者 typedef
  DeviceMananger dm;
  const std::unordered_map<std::string, std::vector<Device*>>& deviesMap = dm.GetDevices();

  using DeviceMapType1 = std::unordered_map<std::string, std::vector<Device*>>;
  typedef std::unordered_map<std::string, std::vector<Device*>> DeviceMapType2;

  const DeviceMapType1& deviesMap1 = dm.GetDevices();
  const DeviceMapType2& deviesMap2 = dm.GetDevices();
  return 1;
}

#include <iostream>
using namespace std;



/*
  mutable除了009里的作用，突破const限制。
  还可以让labmda函数，在值传递的情况下。可以内部自己创建一个自己的变量，做修改。
*/
int main() {
  int x = 8;


  auto fn_auto_pass_param_by_ref = [&]() {
    x++;
    cout << x << endl;
  };

  auto fn_auto_pass_param_by_Value = [=]() mutable {
    x++;
    cout << x << endl;
  };


  fn_auto_pass_param_by_ref();

  fn_auto_pass_param_by_Value();

  cout << "after: "<< x  << endl;

}

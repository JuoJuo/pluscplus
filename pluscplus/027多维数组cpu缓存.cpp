#include<iostream>

/*
 多维数组不如用一位数组性能好，因为以为数组，内存连续，寻址快。且容易命中cpu缓存


 一位数组表示二维，  
*/

int main27() {

  const int size = 3;

  int*** arr3d = new int**[size];

  for (int i = 0; i < size; i++)
  {
    arr3d[i] = new int*[size];

    for (int j = 0; j < size; j++)
    {
      
      arr3d[i][j] = new int[size];

      for (int k = 0; k < size; k++)
      {
        arr3d[i][j][k] = k;

        std::cout << arr3d[i][j][k];
      }

      std::cout << std::endl;
    }

    std::cout << std::endl;
  }


  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      delete[] arr3d[i][j];
    }

    delete[] arr3d[i];
  }
  return 1;
}

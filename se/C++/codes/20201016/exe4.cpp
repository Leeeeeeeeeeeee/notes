/*输入两个升序排列的整数数组a1和a2，将a1和a2合并成同一个数组，该新数组仍然按升序排列，要求：使用指针实现。

例如：输入｛1，2，3，5，8｝和｛2，4，6，9｝

输出：｛1，2，2，3，4，5，6，8，9｝*/

//KMP算法

#include <iostream>
#include <string.h>
using namespace std;

int main(){
  int a[5] = {1,2,3,5,8};
  int b[4] = {2,4,6,8};
  int len = sizeof(a) / sizeof(a[0]) + sizeof(b) / sizeof(b[0]);
  int c[len-1];
  int i_a = 0,i_b = 0;
  for(int i = 0;i<len-1;i++){
    if(a[i_a]<b[i_b]){
      c[i] = a[i_a];
      i_a++;
    }else{
      c[i] = b[i_b];
      i_b++;
    }
  }

  for(int i = 0;i<len-1;i++){
    cout << c[i];
  }

}

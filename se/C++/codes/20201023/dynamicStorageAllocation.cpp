#include <iostream>
using namespace std;

int main(){
  int a = int(1);//int a = 1;在栈里
  int* p1 = new int(1);//声明int变量在堆区，和delete配套,new出来的东西一定要用指针去接
  int* p2 = new int[3];//声明int数组在堆区

  delete p1;
  delete[] p2;
}

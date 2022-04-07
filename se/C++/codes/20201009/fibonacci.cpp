/*编写一个递归函数（自己调用自己），输入一个整数n，返回斐波那契（Fibonacci）级数相应位置元素的值。斐波那契级数为：0，1，1，2，3，5，8，13，21，……。
例如：输入5，返回3。
*/
#include<iostream>
using namespace std;

int fibonacci(int n){
  int i=2;
  int seq[n]={};
  *seq = 0;
  *(seq+1) = 1;
  while(i<n){
    *(seq+i) = *(seq+i-1)+*(seq+i-2);
    i++;
  }
  return seq[n-1];
}
int main(){
  int n;
  cin >> n;
  int seq[n]={};
  cout << fibonacci(n) << endl;
  return 0;
}

/*
编写一个函数，输入整数n，判断是否等于某个连续整数序列的和，若是，则输出所有可能的序列，否则输出“找不到”。

例如：当输入100时，输出

100=9+10+11+12+13+14+15+16

100=18+19+20+21+22
*/
#include <iostream>
using namespace std;
void creatNumbers(int* seq,int n){
  int i=0;
  for(i=0;i<n;i++){
    *(seq+i) = i;
  }
}
int isSerialNumbers(int* seq,int n){
  int i=0,j=0,z=0;
  int sum=0;
  for(i=1;i<n;i++){
    sum=0;
    j=0;
    while(sum<n){
      sum = sum + *(seq+i+j);
      //cout << "sum:" << sum;
      if(sum==n){
        cout << n << ": ";
        for(z=0;z<=j;z++){
          cout << *(seq+i+z) << " ";
        }
        cout << endl;
      }
      j++;
    }
  }
  return 0;
}
int main(){
  int i=0;
  int n=0;
  cin >> n;
  int numbers[n]={};
  creatNumbers(numbers,n);
  /*for(i=0;i<n;i++){
    cout << numbers[i] << " ";
  }
  cout << endl;*/
  cout << isSerialNumbers(numbers,n) << endl;
}

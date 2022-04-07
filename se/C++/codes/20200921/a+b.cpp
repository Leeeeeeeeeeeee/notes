/*程序目标：输入一串数字，然后逆序输出。*/

#include <iostream>
#include <math.h>
using namespace std;
int myPow(int n,int t){
  int i=0;
  int sum=n;
  if(t==0) return 1;
  for(i=0;i<t-1;i++){
    sum*=n;
  }
  return sum;
}
int main(){
  int i=0;
  int a=0;
  int b=0;
  int temp=0;
  int sum=0;
  cin >> a;
  temp=a;
  for(i=0;i<4;i++){
    b+=int(temp/myPow(10,4-i-1))*myPow(10,i);
    temp-=int(temp/myPow(10,4-i-1))*myPow(10,4-i-1);
  }
  cout << a+b << endl;
  return 0;
}

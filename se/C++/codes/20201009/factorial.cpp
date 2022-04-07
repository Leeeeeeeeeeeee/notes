//编写一个函数，输入一个整数n，返回1！+2！+3！+……+n！的值。
#include <iostream>
using namespace std;

int factorial(int n){
  int i=0;
  int sum=0;
  for(i=1;i<=n;i++){
    sum+=i*i;
  }
  return sum;
}

int main(){
  int n = 0;
  cin >> n ;
  cout << factorial(n) << endl;
  return 0;
}

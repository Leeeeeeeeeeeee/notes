//检查一个字符串（C语言的字符数组形式）是否是回文，回文即正向与反向的拼写都一样，如：adgda，要求：直接使用指针进行字符比较。
#include <iostream>
using namespace std;

int isPalsquare(string num_s){
  int i=0;
  int digits=num_s.length();
  for(i=0;i<digits;i++){
    if(num_s[i]!=num_s[digits-i-1]) return 0;
    if(i == digits/2 || digits-i-1 == digits/2) break;
  }
  return 1;
}

int main(){
  string str_test;
  cout << "input:" ;
  cin >> str_test;
  cout << isPalsquare(str_test) << endl;
}

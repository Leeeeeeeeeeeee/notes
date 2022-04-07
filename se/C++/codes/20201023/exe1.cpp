//编写一个函数，输入一个字符串（字符数组形式），拷贝该字符串并返回，要求：使用指针实现。
#include <iostream>
#define CHAR_LEN 10
using namespace std;
void copyString(char* old_s,char* new_s){
  int i=0;
  for(i=0;i<CHAR_LEN;i++){
    new_s[i]=old_s[i];
  }
}
int main(){
  int i=0;
  char a[CHAR_LEN]="";//将字符数组置0
  char b[CHAR_LEN]="";

  for(i=0;i<CHAR_LEN;i++){
    cin >> a[i] ;
  }
  copyString(a,b);
  for(i=0;i<CHAR_LEN;i++){
    cout << b[i];
  }
  return 0;
}

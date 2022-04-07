//假设有n个字符串（字符数组形式），按字典顺序排序好按顺序输出字符串，要求：使用指针实现。
//例如：输入s1=”abc”，s2=”aacd”，s3=”aac”，s4=”bcd”，s5=”bcdef”
//输出aac，aacd，abc，bcd，bcdef
#include <iostream>
#include <string>
using namespace std;
int main(){
  int i=0,j=0;
  char s[5][5]={{'a','b','c'},{'a','a','c','d'},{'a','a','c'},{'b','c','d'},{'b','c','d','e','f'}};
  while(i!=5){
    if(s[i][0]=='a'){
      for(j=0;j<5;j++){
        if(s[i][j]==0) break;
        else{
          cout << s[i][j];
        }
      }
      cout << endl;
      i++;
    }else if(s[i][0]=='b'){
      for(j=0;j<5;j++){
        if(s[i][j]==0) break;
        else{
          cout << s[i][j];
        }
      }
      cout << endl;
      i++;
    }
  }

  return 0;
}

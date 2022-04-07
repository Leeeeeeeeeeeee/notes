/*
输入一个字符串（C语言的字符数组形式），提取其中的数字字符，将每个连续的数字串单独转换成整数并且相加，输出相加后的结果，要求：使用指针实现。

例如：输入tre89a533uert ier2567jr4p

输出3193（89+533+2567+4）
*/
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int myatoi(char* str,int length){
    int result = 0;
    for(int i = 0; i < length; i++)
      result = result * 10 + (str[i] - '0');
    return result;
}

int main(){
  char str_input[100];
  int i = 0,j=0;
  char str_temp[10];
  int sum = 0;
  memset(str_input,0,sizeof(str_input));
  memset(str_temp,0,sizeof(str_temp));

  scanf("%[^\n]",&str_input);

  while(str_input[i]!='\0'){
    //cout << str_input[i] << endl;
    if(*(str_input+i)>='0' && *(str_input+i)<='9'){
      //cout << "number" << endl;
      str_temp[j]=str_input[i];
      j++;
    }else{
      //cout << "letter" << endl;
      //printf("%s",&str_temp);
      if(int(str_temp[0])==0){
        i++;
        continue;
      }
      //cout << "myatoi:" << myatoi(str_temp,j) << endl;
      sum = sum + myatoi(str_temp,j);
      //cout << sum << endl;
      memset(str_temp,0,sizeof(str_temp));
      j=0;
    }
    i++;
  }
  cout << sum;

  //printf("%s\n",&str_input);

  return 0;

}

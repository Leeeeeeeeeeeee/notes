/*程序目标：输入a-z或者A-Z，a输出z A输出Z b输出y，以此类推*/

#include <iostream>
#include <cstring>
using namespace std;

int main(){
  int i=0;
  char letters[20];
  memset(letters,0,sizeof(char)*20);
  char letters_new[20];
  memset(letters_new,0,sizeof(char)*20);
  //input
  cin >> letters;
  //compute
for(i=0;i<20;i++){
  if(letters[i]>='A' && letters[i]<='Z'){
    //letters[i]-'A'使得A-Z分别编码为0-25
    letters_new[i]=(25-(letters[i]-'A'))+'A';
  }
  if(letters[i]>='a' && letters[i]<='z'){
    letters_new[i]=(25-(letters[i]-'a'))+'a';
  }
}
cout << letters_new << endl;
  //output
  return 0;
}

/*假设有一个按升序排序的数组，输入一个整数n，将n插入到相应的位置，使得该数组仍然是升序排列的，如果n已经存在，则不插入，要求使用指针实现。
例如：输入[1,2,3,5,7,9]和8 输出[1,2,3,5,7,8,9]*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
int main(){
  int i=0;
  string str_input;
  int num_insert;
  vector<int>num_seq;
  //input:[1,2,3,5,7,9] (空格)8
  ifstream fin("exe1.in");
  fin >> str_input >> num_insert;
  //execute
  for(i=0;i<str_input.length();i++){
    if(str_input[i]=='[' || str_input[i]==']' || str_input[i]==',')
      continue;
    else{
      //cout << str_input[i] << endl;
      num_seq.push_back(int(str_input[i])-48);
    }
  }
  /*for(i=0;i<num_seq.size();i++)
    cout << num_seq[i];*/
  num_seq.push_back(num_insert);
  sort(num_seq.begin(),num_seq.end());
  //output
  for(i=0;i<num_seq.size();i++)
    cout << num_seq[i];
  return 0;
}

#include <string>
#include <iostream>
using namespace std;

int main(){
  //false
  char a[] = "jinan";
  char b[] = "jinan";

  //true
  //string a = "jinan";
  //string b = "jinan";
  if(a==b){
    cout << "true" << endl;
  }else{
    cout << "false" << endl;
  }
  return 0;
}

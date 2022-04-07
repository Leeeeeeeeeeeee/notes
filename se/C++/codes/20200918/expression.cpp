#include <iostream>
using namespace std;
int main(){
  int x=1;
  int y=2;

  cout << (x=y) << endl;//2
  cout << (x==y) << endl;//1
  cout << ('a'==97) << endl;//1
  cout << "a = " << x+++y << endl;//a = 4 //x已经被赋值为2 2+2=4

  return 0;
}

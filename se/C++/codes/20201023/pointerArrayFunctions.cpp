#include <iostream>
using namespace std;

void swap(int sc[]){
  //这里int sc[]是语法糖,实际上int *sc ,可判断sc==mc,如果int sc[]，则sc!=mc
  int t = sc[0];
  sc[0] = sc[1];
  sc[1] = t;

  cout << "In swap(): (sc[0],sc[1])=("<< sc[0] << "," << sc[1] <<")" << endl;
  cout << "In swap(): size(sc) = " << sizeof(sc) << endl;//这里为4因为sc是数组指针
}

int main(){
  int a=1,b=2;
  int mc[]={1,2};

  swap(mc);

  cout << "In main(): (mc[0],mc[1])=("<< mc[0] << "," << mc[1] <<")" << endl;
  cout << "In main(): size(mc) = " << sizeof(mc) << endl;//这里为8因为mc是数组

  //主函数的c[]和swap的c[]并不是同一个，swap中的c[]属于swap的局部变量
  //main中的c代表&c[0],swap中的c也指向&c[0],故可以改变主函数中c[]的值

  return 0;

}

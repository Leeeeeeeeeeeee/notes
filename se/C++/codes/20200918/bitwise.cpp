#include <iostream>
using namespace std;
int main(){
  int a=25,b=18,m,n,i,j,k;
  m=a&b;  cout << "m=" << m << endl;
  n=a|b;  cout << "n=" << n << endl;
  i=a^b;  cout << "i=" << i << endl;
  j=a<<1; cout << "j=" << j << endl;
  k=a>>1; cout << "k=" << k << endl;
  return 0;
}

/*1.	编写猜数字游戏，生成一个1~100的随机数，然后由用户输入数字来猜，告诉用户输入的数字是大了、小了、或是猜中了，程序一直循环直到用户猜中。*/

#include <iostream>
#include <stdlib.h>
#include <typeinfo>
#include <time.h>
#include <string>
using namespace std;

int judge(int guess,int random){
  if(guess == random){
    cout << "Great! You guess right." << endl;
    return 1;
  }else if (guess > random){
    cout << "No! Your guess above random." << endl;
    return 0;
  }else{
    cout << "No! Your guess below random." << endl;
    return 0;
  }
}
int main(){
  int random;
  int guess;
  //1.产生伪随机数
  srand(time(NULL));
  random=rand();
  //2.猜测过程
  do{
    cout << "guess number:" << endl;
    cin >> guess;
  }while(!judge(guess,random));
}

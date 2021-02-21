#include <iostream>
using namespace std;

int num1(1);
int num2(2);

int foo1(int val) {
  val = val + 1;

  // ...code manquant 1...
  return val;
}

int foo2(int& val) {
  val = val + 1;
  num1 = num2 + 1;

  // ...code manquant 2...
  return val-1;
}

int foo3(int& val) {
  int num2(2);
  num2 = num2 + 1;
  return foo1(3*num1) + foo2(val) ;
}

int main() {
  int num1(3);
  cout << "Resultat 1 : " << foo3(num1) << endl;
  cout << "Resultat 2 : " << num1 << endl;
  cout << "Resultat 3 : " << num2 << endl;
  return 0;
}

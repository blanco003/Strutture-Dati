#include <iostream>
#include "hash_table.h"

using namespace std;

int main() {
  HashTable<string,string> t(10);
  cout << "size " << t.size() << endl;
  struct Entry<string,string> e1;
  e1.first="rossi";
  e1.second="giovanni";
  t.insert(e1);
  cout << t.find("rossi")->second << endl;

  struct Entry<string,string> e2;
  e2.first="rossi";
  e2.second="marco";
  t.insert(e2);
  cout << t.find("rossi")->second << endl;
  
  struct Entry<string,string> e3;
  e3.first="verdi";
  e3.second="giuseppe";
  t.insert(e3);
  cout << t.find("verdi")->second << endl;
  cout << "size " << t.size() << endl;  

  return 0;
}

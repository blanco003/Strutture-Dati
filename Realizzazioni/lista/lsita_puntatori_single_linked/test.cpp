#include "single_linked_list.h"

using namespace std;


int main(){
  Linked_List<int> list1;

	
  list1.insert(1, list1.begin());
  list1.insert(2, list1.begin());
  list1.insert(3, list1.begin());
  list1.insert(4, list1.begin());
  list1.erase(list1.begin());
  list1.insert(5, list1.begin());
  list1.insert(6, list1.begin());
  list1.insert(7, list1.begin());
  list1.insert(8, list1.begin());
  list1.erase(list1.begin());
  
  
  cout << "list1 = " ; cout << list1;


  return 0;

}

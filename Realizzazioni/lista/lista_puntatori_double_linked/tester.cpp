#include "linked_list.h"
#include <iostream>

using namespace std;


int main(){
  Linked_list<int> list1, list2;
  Linked_list<int>::position iter;

	int x;

	/* inserting three elements into the list list1 */
	x = 1;
  list1.insert(x, list1.begin());
	x = 2;
  list1.insert(x, list1.begin());
	x = 3;
  list1.insert(x, list1.begin());
	x = 4;
  list1.insert(x, list1.begin());

	/* visualizing the list list1 */
	cout << "list1=" ; cout << list1;

	/* assigning the list list1 to the list list2.
	 * Here we are using the operator =
	 */


	list2 = list1;
	/* visualizing the list list2 */
	cout << "After list2=list1, list2="; cout << list2;

	/* comparing for equality the lists list1 and list2 */
	if (list1 == list2)
			cout << "list1 == list2" << endl;
	else
			cout << "list1 != list2" << endl;

	/* erasing the first element from the list list2 */
	list2.erase(list2.begin());
	/* visualizing the list list2 */
	cout << "After erasing the first element, list2="; cout << list2;
	/* comparing for equality the lists list1 and list2 */
	if (list1 == list2)
			cout << "list1 == list2" << endl;
	else
			cout << "list1 != list2" << endl;

}


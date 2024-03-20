#include "TreeList.h"

int main(){

	TreeList<char> Tree;

	TreeList<char>::node n;
	Tree.insRoot(n);
	Tree.writeNode(Tree.root(),'a');

	Tree.insFirst(Tree.root(), 'b');
	Tree.insFirst(Tree.root(), 'c');

	n = Tree.root();
	n = Tree.firstChild(n);

	Tree.ins(n, 'd');

	n = Tree.root();
	n = Tree.firstChild(n);
	Tree.insFirst(n, 'e');
	Tree.insFirst(n, 'f');

	Tree.print();	

	n = Tree.root();
	n = Tree.firstChild(n);
	Tree.removeSubTree(n);

	Tree.print();	

	return 0;
}

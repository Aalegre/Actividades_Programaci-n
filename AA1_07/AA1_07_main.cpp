
#include "BST.h"
#include "BSTv.h"

int main() {
	BST holi;
	BSTv<int> holi2;

	holi.Insert(10);
	holi.Insert(13);
	holi.Insert(9);
	holi.Insert(11);
	holi.Insert(14);
	holi.Insert(8);

	holi2.Insert(10);
	holi2.Insert(13);
	holi2.Insert(9);
	holi2.Insert(11);
	holi2.Insert(14);
	holi2.Insert(8);

	BinaryNode* node9 = holi.Search(9);
	BinaryNode* node14 = holi.Search(14);
	BinaryNode* node15 = holi.Search(15);

	bool exists11 = holi.Exist(11);

	return 0;
}
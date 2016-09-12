#include "BinarySearchTree.h"

int main()
{
	BinarySearchTree<char> firstTree{ 'a', 'b', 'z', 'g' };
	std::cout << firstTree << std::endl;

	std::ofstream ofs("Tree.txt");
	ofs << firstTree;
	ofs.close();

	BinarySearchTree<int> secondTree;
	std::cin >> secondTree;

	if (secondTree.insert(7))
		std::cout << secondTree << std::endl;
	else
		std::cin >> secondTree;

	auto w = 5;
	auto found = secondTree.find(w);

	if (found)
		std::cout << *found << std::endl;
	else
		std::cout << w << " has not been found\n";

	system("pause");
	return 0;
}
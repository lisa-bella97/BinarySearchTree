#include "BinarySearchTree.h"

int main()
{
	BinarySearchTree<char> firstTree{ 'a', 'b', 'z', 'g' };
	std::cout << firstTree << std::endl;

	std::ofstream ofs("Tree.txt");
	ofs << firstTree;
	ofs.close();

	BinarySearchTree<double> secondTree;

	std::ifstream ifs("BinTree.txt");
	ifs >> secondTree;
	ifs.close();

	std::cout << secondTree << std::endl;

	BinarySearchTree<int> thirdTree;
	std::cin >> thirdTree;

	if (thirdTree.insert(7))
		std::cout << thirdTree << std::endl;
	else
		std::cin >> thirdTree;

	auto w = 5;
	auto found = thirdTree.find(w);

	if (found)
		std::cout << *found << std::endl;
	else
		std::cout << w << " has not been found\n";

	return 0;
}
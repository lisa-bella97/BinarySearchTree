#include <BinarySearchTree.hpp>

int main()
{
	BinarySearchTree<char> firstTree{ 'a', 'b', 'z', 'g' };
	std::cout << firstTree << std::endl;

	std::ofstream ofs("D:\\Tree.txt");
	ofs << firstTree;
	ofs.close();

	BinarySearchTree<double> secondTree;

	std::ifstream ifs("D:\\BinTree.txt");
	ifs >> secondTree;
	ifs.close();

	if (secondTree.insert(7.2))
		std::cout << secondTree << std::endl;

	auto w = 5.0;
	auto found = secondTree.find(w);

	if (found)
		std::cout << *found << std::endl;
	else
		std::cout << w << " has not been found" << std::endl;

    BinarySearchTree<char> thirdTree(firstTree);
    std::cout << thirdTree << std::endl;

    BinarySearchTree<double> fourthTree = std::move(secondTree);
    std::cout << fourthTree << std::endl;
    std::cout << secondTree << std::endl;

    if (secondTree == fourthTree)
        std::cout << "secondTree is equal to fourthTree" << std::endl;

    BinarySearchTree<char> fifthTree;
    std::cin >> fifthTree;

    if (firstTree == fifthTree)
        std::cout << "firstTree is equal to fifthTree" << std::endl;
    else
        fifthTree = firstTree;

    BinarySearchTree<char> test;
    fifthTree = test;
    std::cout << fifthTree << std::endl;

	return 0;
}
#include <BinarySearchTree.hpp>

int main()
{
    try
    {
        BinarySearchTree<char> firstTree{'a', 'b', 'z', 'g'};
        std::cout << firstTree << std::endl;

        std::ofstream ofs("/home/elizaveta/ClionProjects/BinarySearchTree/examples/Tree.txt");
        ofs << firstTree;
        ofs.close();

        BinarySearchTree<double> secondTree;

        std::ifstream ifs("/home/elizaveta/ClionProjects/BinarySearchTree/examples/BinTree.txt");
        ifs >> secondTree;
        ifs.close();

        secondTree.insert(7.2);
        std::cout << secondTree << std::endl;
        auto w = 5.0;
        auto found = secondTree.find(w);
        std::cout << found << std::endl;

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

        BinarySearchTree<short> sixthTree{7, -5, 10, 2, 5, 4, 6};
        std::cout << sixthTree << std::endl;
        sixthTree.remove(5);
        std::cout << sixthTree << std::endl;
    }
    catch (logical_error<char> &e)
    {
        std::cout << e.what() << ": " << e.getValue() << std::endl;
    }
    catch (logical_error<double> &e)
    {
        std::cout << e.what() << ": " << e.getValue() << std::endl;
    }
    catch (logical_error<short> &e)
    {
        std::cout << e.what() << ": " << e.getValue() << std::endl;
    }

    return 0;
}
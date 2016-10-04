#include <BinarySearchTree.hpp>
#include "catch.hpp"

SCENARIO("after removing element from the tree size of it must decrease by one")
{
    GIVEN("tree and its size")
    {
        BinarySearchTree<int> tree{1, 3, 5, -1, 2};
        auto size = tree.size();
        WHEN("remove element")
        {
            tree.remove(5);
            THEN("size must decrease by one")
            {
                REQUIRE(tree.size() == size - 1);
            }
        }
    }
}

SCENARIO("after removing element from the tree it's structure must be changed")
{
    GIVEN("two trees")
    {
        BinarySearchTree<int> tree1{1, 3, 5, -1, 2};
        BinarySearchTree<int> tree2{1, 3, 5, 2};
        WHEN("remove element")
        {
            tree1.remove(-1);
            THEN("trees must be equal")
            {
                REQUIRE(tree1 == tree2);
            }
        }
    }
}
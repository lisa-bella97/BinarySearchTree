#include <BinarySearchTree.hpp>
#include "catch.hpp"

SCENARIO("after removing element from the tree size of it must decrease by one")
{
    GIVEN("tree and its size")
    {
        BinarySearchTree<int> tree{ 1, 3, 5, -1, 2 };
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
        BinarySearchTree<int> tree1{ 8, 3, 10, 1, 6, 4, 7, 14, 13 };
        BinarySearchTree<int> tree2{ 8, 3, 10, 6, 4, 7, 14, 13 };
        WHEN("remove node that hasn't children")
        {
            tree1.remove(1);
            THEN("trees must be equal")
            {
                REQUIRE(tree1 == tree2);
            }
        }
        tree1 = BinarySearchTree<int>({ 8, 3, 10, 1, 6, 4, 7, 14, 13 });
        tree2 = BinarySearchTree<int>({ 8, 10, 4, 6, 1, 7, 14, 13 });
        WHEN("remove node that has only left child")
        {
            tree1.remove(3);
            THEN("trees must be equal")
            {
                REQUIRE(tree1 == tree2);
            }
        }
        tree1 = BinarySearchTree<int>({ 8, 3, 10, 1, 6, 4, 7, 14, 13 });
        tree2 = BinarySearchTree<int>({ 8, 3, 1, 6, 4, 7, 14, 13 });
        WHEN("remove node that has only right child")
        {
            tree1.remove(10);
            THEN("trees must be equal")
            {
                REQUIRE(tree1 == tree2);
            }
        }
        tree1 = BinarySearchTree<int>({ 8, 3, 10, 1, 6, 4, 7, 14, 13 });
        tree2 = BinarySearchTree<int>({ 8, 3, 10, 1, 7, 4, 14, 13 });
        WHEN("remove node that has both children")
        {
            tree1.remove(6);
            THEN("trees must be equal")
            {
                REQUIRE(tree1 == tree2);
            }
        }
        tree1 = BinarySearchTree<int>({8});
        tree2 = BinarySearchTree<int>();
        WHEN("remove root")
        {
            tree1.remove(8);
            THEN("trees must be equal")
            {
                REQUIRE(tree1 == tree2);
            }
        }
        tree1 = BinarySearchTree<int>({ 8, 3, 10, 1, 6, 4, 7, 14, 13 });
        tree2 = BinarySearchTree<int>({ 8, 3, 10, 1, 6, 4, 7, 14, 13 });
        WHEN("remove node that doesn't exist")
        {
            THEN("an exception must be thrown")
            {
                REQUIRE_THROWS_AS(tree1.remove(-1), logical_error<int>&);
            }
        }
    }
}

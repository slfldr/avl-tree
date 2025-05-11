#include "gtest.h"
#include "avl_tree.h"

TEST(AVLTreeTest, InsertAndFind)
{
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(5));
    EXPECT_TRUE(tree.find(15));
    EXPECT_FALSE(tree.find(20));
}

TEST(AVLTreeTest, DuplicateInsert)
{
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(10);
    tree.insert(10);

    EXPECT_TRUE(tree.find(10));
    EXPECT_EQ(tree.size(), 1);
}

TEST(AVLTreeTest, RemoveLeaf)
{
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    tree.remove(5);

    EXPECT_FALSE(tree.find(5));
    EXPECT_EQ(tree.size(), 2);
}

TEST(AVLTreeTest, RemoveNodeWithOneChild)
{
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(3);

    tree.remove(5);

    EXPECT_FALSE(tree.find(5));
    EXPECT_TRUE(tree.find(3));
    EXPECT_EQ(tree.size(), 2);
}

TEST(AVLTreeTest, RemoveNodeWithTwoChildren)
{
    AVLTree<int> tree;

    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(25);
    tree.insert(40);

    tree.remove(30);

    EXPECT_FALSE(tree.find(30));
    EXPECT_TRUE(tree.find(25));
    EXPECT_TRUE(tree.find(40));
    EXPECT_EQ(tree.size(), 4);
}

TEST(AVLTreeTest, RemoveNonExistentElement)
{
    AVLTree<int> tree;
    tree.insert(1);
    tree.insert(2);

    tree.remove(3);

    EXPECT_TRUE(tree.find(1));
    EXPECT_TRUE(tree.find(2));
    EXPECT_EQ(tree.size(), 2);
}

TEST(AVLTreeTest, LeftLeftRotation)
{
    AVLTree<int> tree;

    tree.insert(30);
    tree.insert(20);
    tree.insert(10);

    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(20));
    EXPECT_TRUE(tree.find(30));
    EXPECT_EQ(tree.size(), 3);
}

TEST(AVLTreeTest, RightRightRotation)
{
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(20));
    EXPECT_TRUE(tree.find(30));
    EXPECT_EQ(tree.size(), 3);
}

TEST(AVLTreeTest, LeftRightRotation)
{
    AVLTree<int> tree;

    tree.insert(30);
    tree.insert(10);
    tree.insert(20);

    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(20));
    EXPECT_TRUE(tree.find(30));
    EXPECT_EQ(tree.size(), 3);
}

TEST(AVLTreeTest, RightLeftRotation)
{
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(30);
    tree.insert(20);

    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(20));
    EXPECT_TRUE(tree.find(30));
    EXPECT_EQ(tree.size(), 3);
}

TEST(AVLTreeTest, InsertMultipleAndCheckBalance)
{
    AVLTree<int> tree;

    for (int i = 1; i <= 100; ++i)
    {
        tree.insert(i);
    }

    for (int i = 1; i <= 100; ++i)
    {
        EXPECT_TRUE(tree.find(i));
    }
        
    EXPECT_EQ(tree.size(), 100);
}

TEST(AVLTreeTest, RemoveRootNode)
{
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    tree.remove(10);

    EXPECT_FALSE(tree.find(10));
    EXPECT_TRUE(tree.find(5));
    EXPECT_TRUE(tree.find(15));
    EXPECT_EQ(tree.size(), 2);
}

TEST(AVLTreeTest, RemoveAllNodes)
{
    AVLTree<int> tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);

    tree.remove(1);
    tree.remove(2);
    tree.remove(3);

    EXPECT_FALSE(tree.find(1));
    EXPECT_FALSE(tree.find(2));
    EXPECT_FALSE(tree.find(3));
    EXPECT_EQ(tree.size(), 0);
}

TEST(AVLTreeTest, FindInEmptyTree)
{
    AVLTree<int> tree;

    EXPECT_FALSE(tree.find(42));
    EXPECT_EQ(tree.size(), 0);
}

TEST(AVLTreeTest, RemoveFromEmptyTree)
{
    AVLTree<int> tree;

    tree.remove(42);

    EXPECT_EQ(tree.size(), 0);
}

TEST(AVLTreeTest, InsertMinMaxInt)
{
    AVLTree<int> tree;

    tree.insert(INT_MIN);
    tree.insert(INT_MAX);

    EXPECT_TRUE(tree.find(INT_MIN));
    EXPECT_TRUE(tree.find(INT_MAX));
    EXPECT_EQ(tree.size(), 2);
}

TEST(AVLTreeTest, InsertNegativeValues)
{
    AVLTree<int> tree;

    tree.insert(-10);
    tree.insert(-20);
    tree.insert(-5);

    EXPECT_TRUE(tree.find(-10));
    EXPECT_TRUE(tree.find(-20));
    EXPECT_TRUE(tree.find(-5));
    EXPECT_EQ(tree.size(), 3);
}

TEST(AVLTreeTest, MassiveInsertRemove)
{
    AVLTree<int> tree;

    for (int i = 0; i < 1000; ++i)
    {
        tree.insert(i);
    }

    for (int i = 0; i < 1000; i += 2)
    {
        tree.remove(i);
    }

    for (int i = 0; i < 1000; ++i)
    {
        if (i % 2 == 0)
        {
            EXPECT_FALSE(tree.find(i));
        }
        else
        {
            EXPECT_TRUE(tree.find(i));
        }
    }

    EXPECT_EQ(tree.size(), 500);
}
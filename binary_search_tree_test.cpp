#include <gtest/gtest.h>
#include "binary_search_tree.hpp"

using namespace std;

TEST(BST, BST) {
    BinarySearchTree bst;
    for (int i = 1; i < 100; i++) {
        bst.Insert(i);
    }

    EXPECT_TRUE(bst.Size() == 99);
    EXPECT_TRUE(bst.Has(10) == true);

//    bst.Delete(10);
//    EXPECT_TRUE(bst.Has(10) == false);
}
int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

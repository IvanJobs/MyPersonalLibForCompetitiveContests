#include "binary_search_tree.hpp"

using namespace std;

int main() {
  BinarySearchTree bst;
  for (int i = 1; i < 10; i++) {
    bst.Insert(i, i);
  }

  bst.Show();
  bst.Travel();
  if (bst.Check()) {
    cout<<"Pass case 1"<<endl;
  } else {
    cout<<"Fail case 1"<<endl;
  }

  bst.Delete(5);
  bst.Show();
  bst.Travel();

  if (bst.Check()) {
    cout<<"Pass case 2"<<endl;
  } else {
    cout<<"Fail case 2"<<endl;
  }

  bst.Hack();
  bst.Show();
  if (bst.Check()) {
    cout<<"Fail case 3"<<endl;
  } else {
    cout<<"Pass case 3"<<endl;
  }

  return 0;
}

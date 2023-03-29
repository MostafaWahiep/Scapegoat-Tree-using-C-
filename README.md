
# Scapegoat Tree

An implementation of the Scapegoat Tree data structure in C++.


## Introduction

A Scapegoat Tree is a self-balancing binary search tree that can be used to store a collection of values. It was first introduced by Galperin and Rivest in 1993. The main idea behind the Scapegoat Tree is to use a dynamic threshold to determine when to rebuild the tree to maintain balance. This threshold is based on an alpha coefficient that is typically between 1/2 and 1. In this implementation, the alpha coefficient is set to 2/3.
## Implementation

The ScapegoatTree class is implemented using a nested Scapenode class that represents a node in the tree. The tree is implemented as a binary search tree with the Scapenode class containing pointers to the left and right children as well as the parent node. The tree is balanced using the Scapegoat Tree algorithm, which rebuilds the tree when the imbalance exceeds a certain threshold.

The threshold for rebuilding the tree is determined by the q parameter, which is an overestimate of the number of nodes in the tree. The q parameter is updated after each insertion and deletion operation to ensure that the tree is balanced. The α coefficient used in the Scapegoat Tree algorithm is set to 2/3 in this implementation.

## Operations
Currently, his implementation provides the following operations:

* **bool empty() const**: returns true if the tree is empty, false otherwise.

* **bool remove(T value)**: removes the value from the tree, returns true if the value was found and removed, false otherwise.

* **void insert(T value)**: inserts the value into the tree.
* **NodePointer search(T value) const**: returns a pointer to the node that contains the value, or nullptr if the value is not found.
* **int size() const**: returns the number of values stored in the tree.
* **void inorder() const**: displays the values of the tree in ascending order.

## Usage

To use this implementation, include the **ScapegoatTree.h** header file in your program. Then create an instance of the **ScapegoatTree** class:

```cpp
#include "scapegoat_tree.hpp"

ScapegoatTree<int> tree;
```

You can then use the operations provided by the class to manipulate the tree:

```cpp
tree.insert(42);
tree.insert(17);
tree.insert(99);

if (tree.search(17) != nullptr) {
    std::cout << "17 is in the tree!\n";
}

tree.remove(42);

std::cout << "Size of the tree: " << tree.size() << "\n";
std::cout << "Values of the tree: ";
tree.inorder();
std::cout << "\n";
```

## Contributing

Contributions to this project are welcome. If you find a bug or have a feature request, please open an issue on GitHub. If you would like to contribute code, please fork the repository and submit a pull request.

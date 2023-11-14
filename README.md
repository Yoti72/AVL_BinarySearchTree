# AVL_BinarySearchTree
A class template for a generic self-organizing binary search tree, which supports element insertion, deletion, search (and self-restructuring), and in-order and level-order traversals. The self-organizing binary search tree can restructure itself based on the search frequency of the data in the tree. 

# Self-Organizing Binary Search Tree (SOBST)

This repository contains a class template for a Generic Self-Organizing Binary Search Tree (SOBST). The tree data structure supports fundamental operations like element insertion, deletion, search, and two types of traversal: in-order and level-order.

## Features

- **Insertion:** Add elements into the self-organizing binary search tree.
- **Deletion:** Remove elements from the tree.
- **Search and Self-Restructuring:** Find elements in the tree. The tree dynamically adjusts itself based on the frequency of searches, optimizing search performance.
- **Traversals:** Perform in-order and level-order traversals.

## Overview

The key feature of this self-organizing binary search tree is its ability to adapt and restructure itself based on search frequency. Each node in the tree maintains a search count to track how often it is accessed.

### Self-Restructuring Mechanism

The tree utilizes a threshold value, which it maintains to evaluate the search count of nodes. When the search count of a particular node crosses this threshold, the tree performs self-restructuring. This restructuring involves reorganizing the tree to optimize future searches by placing frequently accessed nodes closer to the root.

## Usage

To use the self-organizing binary search tree in your project:

1. Include the 'SOBST.h' header file in your project.
2. Instantiate the `SOBST` class with the desired data type.
3. Utilize the provided methods for insertion, deletion, searching, and traversing the tree.

### Example Usage:

```cpp
#include "SOBST.h"
#include <iostream>

int main() {
    // Instantiate a self-organizing binary search tree with integers
    SOBST<int> tree;

    // Insert elements into the tree
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    // Perform searches and observe self-restructuring
    tree.search(5);
    tree.search(15);

    // Perform in-order traversal
    std::cout << "In-order traversal: ";
    tree.inOrderTraversal();
    
    // Perform level-order traversal
    std::cout << "\nLevel-order traversal: ";
    tree.levelOrderTraversal();

    return 0;
}

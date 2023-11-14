#ifndef BST_HPP
#define BST_HPP




    template <typename T>
    BST<T>::BST(int th) 
    {
      //cout << "BST(int th)" << endl;
      threshold = th;
      root = nullptr;
    }



    template <typename T>
    BST<T>::BST(const std::string& input, int th) : threshold(th)
    {
      //cout << "BST(const std::string& input, int th)" << endl;
      //cout << "input: " << input << " " << "threshold: " << th << endl;
      //cout << endl << "ConstructorRoot: " << root << endl;

      root = nullptr;
      buildFromInputString(input);
    }


    template <typename T>
    BST<T>::BST(const BST<T>& other) : root(clone(other.root))
    {
      //cout << "BST(const BST<T>& other) : root(copyNode(other.root))" << endl;
        //copy the element and the corresponding search count in each node
        
    }


    template <typename T>
    BST<T>::BST(BST<T> && other) : root(other.root) 
    {
      //cout << "BST(BST&&)//: root(other.root) " << endl;
      other.root = nullptr;
    }


    template <typename T>
    BST<T>::~BST()
    {
      //calls helper function to delete all the nodes in post order traversal
      deleteNode(root);
    }


    template <typename T>
    void BST<T>::deleteNode(typename BST<T>::BSTNode* node) 
    {
      if (node != nullptr) {
        deleteNode(node->left);
        deleteNode(node->right);
        delete node;
      }
    }


    template <typename T>
    void BST<T>::buildFromInputString(const string input)
    {
      
      // Delete existing tree
      clear(root);
      root = nullptr;

      // Parse input string
      std::istringstream iss(input);

      T value;

      while (iss >> value) {
        // Insert value into tree
        //cout << "inserting value: " << value << endl;
        insert(value);
      }
      //cout << endl << "buildfromRoot: " << root->element << endl;
      
    }
  



    template <typename T>
    typename BST<T>::BSTNode* BST<T>::clone(typename BST<T>::BSTNode* node) const
    {
      if (node == nullptr) {
        return nullptr;
      }
      else {
        BSTNode* newNode = new BSTNode(node->element, nullptr, nullptr);
        newNode->searchCount = node->searchCount;
        newNode->left = clone(node->left);
        newNode->right = clone(node->right);
        return newNode;
      }

    }



    template <typename T>
    const BST<T>& BST<T>::operator= (const BST & other)
    {
      if (this != &other) { // protect against invalid self-assignment
        clear(root); // delete current tree
        root = clone(other.root); // copy other tree
      }
      return *this;
    }

    template <typename T>
    const BST<T>& BST<T>::operator=(BST<T> && other)
    {
      
      if (this != &other) { // protect against invalid self-assignment
        clear(root); // delete current tree
        root = other.root; // take ownership of other tree's root
        other.root = nullptr; // leave other tree in a safely destructible state
      }
      
      return *this;
    }

    template <typename T>
    void BST<T>::clear(BSTNode* node) 
    {
      if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
      }
    }




    template <typename T>
    bool BST<T>::empty() const
    {
      return root == nullptr;
    }


    template <typename T>
    int BST<T>::height() const
    {
      return height(root);
    }
    

    template <typename T>
    int BST<T>::height(typename BST<T>::BSTNode *t) const
    {
      return t == nullptr ? -1 : t->height;
    }

    template <typename T>
    void BST<T>::insert(const T& v)
    {
      // Create a new node with the given value
      BSTNode* newNode = new BSTNode(v, nullptr, nullptr);
      //cout << "hi" << endl;

      // Perform normal BST insertion
      root = insertRecursive(root, newNode);
    }

    template <typename T>
    typename BST<T>::BSTNode* BST<T>::insertRecursive(typename BST<T>::BSTNode* node, typename BST<T>::BSTNode* newNode)
    {
      // If the current node is nullptr, insert the new node here
      //cout << "INSERT yoti RECURSIVE" << endl;
      if (node == nullptr) 
      {
        //cout << "node is nullptr" << endl;
        return newNode;
      }

      // Perform normal BST insertion
      if (newNode->element < node->element) 
      {
        node->left = insertRecursive(node->left, newNode);
      } else if (newNode->element > node->element) {
        node->right = insertRecursive(node->right, newNode);
      } else {
        // Duplicate values are not allowed in AVL trees
        delete newNode;
        return node;
      }

      // Update height of the current node
      node->height = 1 + max(height(node->left), height(node->right));

      // Get the balance factor
      //int balance = getBalance(node);

/*
      // Perform rotations if needed to maintain AVL property
      // Left Heavy (balance > 1)
      if (balance > 1 && newNode->element < node->left->element) {
        return rightRotate(node);
      }
      // Right Heavy (balance < -1)
      if (balance < -1 && newNode->element > node->right->element) {
        return leftRotate(node);
      }
      // Left Right Heavy (balance > 1 and newNode is in right subtree of left child)
      if (balance > 1 && newNode->element > node->left->element) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
      }
      // Right Left Heavy (balance < -1 and newNode is in left subtree of right child)
      if (balance < -1 && newNode->element < node->right->element) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
      }
      */

      // If the node is already balanced
      return node;
    }


    template <typename T>
    int BST<T>::getBalance(BSTNode* node) const
    {
      if (node == nullptr) {
        return 0;
      }
      return height(node->left) - height(node->right);
    }

    // Helper function to perform left rotation
    template <typename T>
    typename BST<T>::BSTNode* BST<T>::leftRotate(typename BST<T>::BSTNode* y)
    {
      BSTNode* x = y->right;
      BSTNode* T2 = x->left;

      // Perform rotation
      x->left = y;
      y->right = T2;

      // Update heights
      y->height = 1 + max(height(y->left), height(y->right));
      x->height = 1 + max(height(x->left), height(x->right));

      // Return new root
      return x;
    }

    // Helper function to perform right rotation
    template <typename T>
    typename BST<T>::BSTNode* BST<T>::rightRotate(typename BST<T>::BSTNode* x)
    {
      BSTNode* y = x->left;
      BSTNode* T2 = y->right;

      // Perform rotation
      y->right = x;
      x->left = T2;

      // Update heights
      x->height = 1 + max(height(x->left), height(x->right));
      y->height = 1 + max(height(y->left), height(y->right));

      // Return new root
      return y;
    }



    template <typename T>
    void BST<T>::printInOrder() const
    {
      printInOrder(root);
    }

        template <typename T>
    void BST<T>::printInOrder(typename BST<T>::BSTNode *t) const
    {
      if (t != nullptr) {
        printInOrder(t->left);
        cout << t->element << " ";
        printInOrder(t->right);
      }
    }


    template <typename T>
    void BST<T>::printLevelOrder() const
    {
      printLevelOrder(root);
    }

    template <typename T>
    void BST<T>::printLevelOrder(typename BST<T>::BSTNode *t) const
    {
      //checks if there is only one node in the tree is nullptr
      if (t == nullptr) {
        return;
      }

      //create empty queue for lvl order traversal 
      queue<BSTNode*> q;
      q.push(t);

      while (!q.empty()) {
        BSTNode* curr = q.front();
        q.pop();

        cout << curr->element << " ";

        if (curr->left != nullptr) {
          q.push(curr->left);
        }
        if (curr->right != nullptr) {
          q.push(curr->right);
        }
      }

    }




    template <typename T>
    void BST<T>::makeEmpty(typename BST<T>::BSTNode* &t)
    {
      if (t != nullptr) {
        // Delete left and right subtrees
        makeEmpty(t->left);
        makeEmpty(t->right);

        // Delete the current node
        delete t;
        t = nullptr;
      }

    }

    template <typename T>
    void BST<T>::remove(const T& v)
    {
        remove(v, root);
    }

    template <typename T>
    void BST<T>::remove(const T& v, typename BST<T>::BSTNode *&t)
    {
      if (t == nullptr) {
        // Value not found
        return;
      } else if (v < t->element) {
        // Search in the left subtree
        remove(v, t->left);
      } else if (v > t->element) {
        // Search in the right subtree
        remove(v, t->right);
      } else {
        // Value found
        if (t->left != nullptr && t->right != nullptr) {
            // Node has two children
            // Find and remove the smallest node in the right subtree
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        } else {
            // Node has one or zero children
            BSTNode* oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
      }
    }

    template <typename T>
    typename BST<T>::BSTNode*& BST<T>::getRoot()
    {
      return root;
  }

    template <typename T>
    typename BST<T>::BSTNode* BST<T>::findMin(typename BST<T>::BSTNode* t) const
    {
      if (t == nullptr) {
        return nullptr;
      } else if (t->left == nullptr) {
        return t;
      } else {
        return findMin(t->left);
      }
    }

    template <typename T>
    bool BST<T>::contains(const T& v) 
    {
      return contains(v, root);
    }

    template <typename T>
    bool BST<T>::contains(const T& v, typename BST<T>::BSTNode *&t) 
    {
      if (t == nullptr) {
        // Value not found
        return false;
      } else if (v < t->element) {
        // Search in the left subtree
        return contains(v, t->left);
      } else if (v > t->element) {
        // Search in the right subtree
        return contains(v, t->right);
      } else {
        // Value found
        t->searchCount++;
        if (t->searchCount >= t->threshold && t != root) {
            // Perform rotation
            if (t->parent->left == t) {
                t = rightRotate(t->parent);
            } else {
                t = leftRotate(t->parent);
            }
            t->searchCount = 0;
        } else if (t == root) {
            t->searchCount = 0;
        }
        return true;
      }
    }

    template <typename T>
    int BST<T>::numOfNodes() const
    {
      return numOfNodes(root);
    }

    template <typename T>
    int BST<T>::numOfNodes(typename BST<T>::BSTNode *t) const
    {
      if (t == nullptr) {
        return 0;
      } else {
        return 1 + numOfNodes(t->left) + numOfNodes(t->right);
      }

    }

  
    template <typename T>
    void BST<T>::insert(const T& v, typename BST<T>::BSTNode *&t)
    {
      if (t == nullptr) {
        // Insert new node here
        t = new BSTNode(v, nullptr, nullptr);
      } else if (v < t->element) {
        // Insert in the left subtree
        insert(v, t->left);
      } else if (v > t->element) {
        // Insert in the right subtree
        insert(v, t->right);
      } else {
        // Duplicate value; do nothing
      }

    }  
    
    template <typename T> 
    void BST<T>::insert(T&& v, typename BST<T>::BSTNode *&t)
    {
      if (t == nullptr) {
        // Insert new node here
        t = new BSTNode(std::move(v), nullptr, nullptr);
      } else if (v < t->element) {
        // Insert in the left subtree
        insert(std::move(v), t->left);
      } else if (v > t->element) {
        // Insert in the right subtree
        insert(std::move(v), t->right);
      } else {
        // Duplicate value; do nothing
      }
    }






#endif //BST_HPP


#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <algorithm>

using namespace std; 


 


namespace cop4530 {



    template <typename T>
    class BST  {
		
		struct BSTNode 
		{
			T element;
			int threshold;
            int searchCount;
        	BSTNode   	*left;
        	BSTNode   	*right;
			BSTNode     *parent;
        	int       	height;

            BSTNode( const T & ele, BSTNode *lt, BSTNode *rt, int h = 0 )
            : element{ ele }, left{ lt }, right{ rt }, height{ h } { }
        
            BSTNode( T && ele, BSTNode *lt, BSTNode *rt, int h = 0 )
            : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
		};

        public: 

	        BST(int th=default_threshold_value); // constructor. Parameter th specifies the value for the single-rotation threshold. The default value default_threshold_value should be 1.
	        BST(const std::string & input, int t = default_threshold_value ); //
       	 	BST(const BST&);  // copy constructor. You need to copy both the element and the corresponding search count in each node.
        	BST(BST&&); // move constructor.
        	~BST(); //destructor.


        	//BSTNode* copyNode(BSTNode* node); //helper function for making deep copies of nodes
        	void deleteNode(BSTNode* node);   //helper function for destructor
        
        	void buildFromInputString(const string input); 
        
        	const BST & operator= (const BST &);  // copy assignment operator. You need to copy both the element and the corresponding search count in each node.
        	const BST & operator=(BST &&);  // move assignment operator.
        
        	void clear(BSTNode* node); //helper function for destructor and assignment operator
        	bool empty() const;   // return true if the tree is empty. Return false otherwise.

        	void insert(const T& v);
        	BSTNode* insertRecursive(BSTNode* node, BSTNode* newNode); //helper function for rotation
        	int getBalance(BSTNode* node) const;  //helper function for balancing the tree 
        	BSTNode* leftRotate(BSTNode* y); //helper function for rotation
        	BSTNode* rightRotate(BSTNode* x);//helper function for rotation

        	void printInOrder() const;
        	void printLevelOrder() const;
			void remove(const T& v);
			int height() const; // return the height of the tree. Recall that the height of a tree is the number of the links along the longest path from the root to any of the leaf nodes. The height is an empty tree is -1.
			int numOfNodes() const; // return the number of nodes in the tree.
			bool contains(const T& v);

			BSTNode*& getRoot(); //helper function for move assignment operator

	private:
		    BSTNode* root = nullptr;



            void insert(const T& v, BSTNode *&t);  // insert v into the subtree rooted at t. No duplicated elements are allowed. If value v is already in the subtree, this function does nothing. Initialize the search count to 0 for the newly added node.
            void insert(T&& v, BSTNode *&t);  // insert v into the subtree rooted at t (move instead of copy). No duplicated elements are allowed. If value v is already in the subtree, this function does nothing. Initialize the search count to 0 for the newly added node.

	      	void printInOrder(BSTNode *t) const; // print the elements in the subtree rooted at t in the in-order traversal. 
          	void printLevelOrder(BSTNode *t) const; // print the elements in the subtree rooted at t in the level-order traversal. 
          	void makeEmpty(BSTNode* &t); // delete all nodes in the subtree rooted at t. Called by functions such as the destructor.
          	void remove(const T& v, BSTNode *&t);  // remove value v from the subtree rooted at t (if it is in the subtree). If the node x containing v has two child nodes, replace the value of node x with the smallest value in the right subtree of the node x.
          	bool contains(const T& v, BSTNode *&t);  // return true if v is in the subtree rooted at t; otherwise, return false. Note that the search count of the corresponding node containing v should be increased by 1. If search count reaches the threshold, perform the single rotation discussed above. Reset search count to 0. If the node containing the value v is already the root of the tree, do not rotate (but you do need to reset the search count to 0). Note that you can add other parameters if necessary. You may or may need to add additional parameters depending on your design and implementation of BST.
          	int numOfNodes(BSTNode *t) const;  // return the number of nodes in the subtree rooted at t.
          	int height(BSTNode *t) const;  // return the height of the subtree rooted at t. Recall that the height of a tree is the number of the links along the longest path from the root to any of the leaf nodes. The height is an empty tree is -1.
          	BSTNode * clone(BSTNode *t) const;  // clone all nodes in the subtree rooted at t. Called by functions such as the assignment operator=. Note that you also need to copy the search count in the original node to the corresponding cloned node.
		  	BSTNode* findMin(BSTNode* t) const; //helper function for remove


     	  	static const int default_threshold_value = 1;
		    int threshold; 

};

#include "bst.hpp"

}

#endif


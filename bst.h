#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include<cmath>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    static Node<Key, Value>* successor(Node<Key, Value>* current);
    void clearHelper(Node<Key, Value>* node);
    int pathLength(Node<Key, Value>* node) const; 

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    current_ = ptr; 
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    current_ = nullptr; 
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // CHECK
    if (this->current_ == rhs.current_)
    {
      return true; 
    }
    return false; 
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // CHECK
    if (this->current_ != rhs.current_)
    {
      return true; 
    }
    return false;
}

/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    current_ = successor(current_); 
    return *this; //this references to the iterator being "++"
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    //successor defined as leftmost child on right tree 
    if(current->getRight() != NULL) //I fucking hate checking for existence. So dumb. Maybe have the compiler check first so it doesn't seg fault. 
    {
        current = current->getRight(); //to the right branch 
        while(current->getLeft()) //while there is a left child 
        {
            current = current->getLeft(); //keep falling left 
        }
        return current; //should return successor 
    }
    else //From geeks4geeks: if right is null, "Travel up using the parent pointer until you see a node which is left child of its parent. The parent of such a node is the succ."
    {
        Node<Key, Value>* parentCopy = current->getParent(); 
        while(parentCopy != NULL && parentCopy->getRight() == current) //this aims to find the first parent that has a left branch with our original node. The parent is therefor next largest to the original in BST 
        {
            current = parentCopy; 
            parentCopy = parentCopy->getParent(); 
        }
        return parentCopy; 
    }
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    root_ = NULL; 
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    clearHelper(root_); //helper function 
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    //dynamic allocation of new node 
    Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL); 
    if(root_ == NULL) //if empty tree ~ base case. Sets root to new node with no parent and key/value pair 
    {
        root_ = newNode; //sets root to newly inserted 
        return; 
    }
    else //otherwise start trickling down the tree 
    {
        Node<Key, Value>* current = root_; //copy of root 
        while(newNode)
        {
            if(newNode->getKey() < current->getKey()) //going left 
            {
                if(current->getLeft() != NULL) //if left exists 
                {
                    current = current->getLeft(); //moves current comparison down left
                }
                else if (current->getLeft() == NULL) //if found spot for the inserted node
                {
                    newNode->setParent(current); //sets parent as current 
                    (newNode->getParent())->setLeft(newNode); //sets parents left child as newNode 
                    return; 
                }
            }
            else if (newNode->getKey() > current->getKey()) //going right
            {
                if (current->getRight() != NULL) //if right exists
                {
                    current = current->getRight(); 
                }
                else if (current->getRight() == NULL)
                {
                    newNode->setParent(current); 
                    (newNode->getParent())->setRight(newNode);
                    return; 
                }
            }
            else if (newNode->getKey() == current->getKey()) //if overwrite 
            {
                current->setValue(newNode->getValue()); //overwrites values
                delete newNode; 
                return; 
            }
        }
    }
}

/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    Node<Key, Value>* target = internalFind(key); //point to node to be deleted 
    if (target == NULL) 
    {
        return;  //if not found 
    }
    if (target->getLeft() && target->getRight()) //if two children, first swap. Other cases will handle the rest 
    {
        Node<Key, Value>* pred = predecessor(target);
        nodeSwap(target, pred);
    }

    Node<Key, Value>* child = target->getLeft(); //defaults to left but checks right since we want the largest child
    if (target->getRight() != NULL) 
    {
        child = target->getRight(); //child will either be NULL or right child. 
    }

    Node<Key, Value>* parent = target->getParent();
    if (child != NULL)
    {
        child->setParent(parent); // if there is a right child it's parent will be the target's (now swapped) parent
    }
    if (parent == NULL) //if target has no parent now it means it was a root and got swapped with itself
    {
        root_ = child; //and thus root should be child preceding deletion 
    }
    else //if target has a parent now 
    {
        if (target == parent->getLeft()) //if target is a left child 
        {
            parent->setLeft(child); //the child of the target must replace it as a left child 
        } 
        else 
        {
            parent->setRight(child); //replace as right child 
        }
    }
    delete target; //actual deletion once everything is done. 
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    //predecessor: rightmost child on left tree 
    if(current->getLeft() != NULL) //left tree
    {
        current = current->getLeft(); //to the left branch 
        while(current->getRight()) //while there is a right child 
        {
            current = current->getRight(); //keep falling right 
        }
        return current; //should return successor 
    }
    else if (current->getLeft() == NULL) //opposite of the successor function
    {
        Node<Key, Value>* parentCopy = current->getParent(); 
        while(parentCopy != NULL && parentCopy->getLeft() == current) 
        {
            current = parentCopy; 
            parentCopy = parentCopy->getParent(); 
        }
        return parentCopy; //will return a node pointer to the predecessor of current
    }
    return NULL; //fix later 
}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear() 
{
    //this function is so dumb. The only difference is that root is now null instead of actually gone. This little detail took me 5 hours. No exaggeration. 
    clearHelper(root_); //call on root to delete whole tree 
    root_ = NULL; 
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    //smallest node, assuming this BST is sorted and top = max, would be the leftmost 
    Node<Key, Value>* finder = root_; //copy of root 
    while (finder->getLeft() != NULL) //while there is a left
    {
        finder = finder->getLeft(); //keep trickling left 
    }
    return finder; 
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
  Node<Key, Value>* checker = root_; //makes copy of root for iteration 
  while (checker != NULL)
  {
    if (checker->getKey() == key) //if found return checker 
    {
      return checker; 
    }
    else if (checker->getKey() > key) //if current key value is greater than target key, go left
    {
      checker = checker->getLeft(); 
    }
    else if (checker->getKey() < key)
    {
      checker = checker->getRight(); 
    }
  }
  return NULL; //else return this if not found 
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const //taken from part 1. Input is the root 
{
    if(root_ == NULL)
    {
        return true; 
    }
    Node<Key, Value>* root = root_;
    if (pathLength(root_) > 0 && pathLength(root->getLeft()) == pathLength(root->getRight()))
    {
        return true;
    }
    return false; 
    /*
    Node<Key, Value>* root = root_; //makes copy of root 
    if (root == NULL)
    {
        return true; //empty tree, balanced by default 
    }
    if (root->getLeft() != NULL && root->getRight() != NULL) //if children exist
    {
        if (pathLength(root->getLeft()) == pathLength(root->getRight()) 
        && abs(pathLength(root->getLeft()) - pathLength(root->getRight())) <= 1 
        && )
        {
            return true; 
        }
        return (pathLength(root->getLeft()) == pathLength(root->getRight())); //call to helper, true if lengths equal 
    }
    else if (root->getLeft() == NULL && root->getRight() == NULL)
    {
        return true; //if just 1 node return true  
    }
    else
    {
        return false; //all other options reveal false 
    }*/
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::pathLength(Node<Key, Value>* node) const //helper function for isBalanced
{
    if (node == NULL)
    {
        return 0;  //halting condition
    }
    int leftSubtree = pathLength(node->getLeft());
    int rightSubtree = pathLength(node->getRight());
    if (leftSubtree == -1)
    {
        return -1;
    }
    if (rightSubtree == -1)
    {
        return -1;
    }
    if (abs(leftSubtree - rightSubtree) > 1)
    {
        return -1; 
    }
    else
    {
        return std::max(leftSubtree, rightSubtree) + 1;
    }

    /*
    if (node->getLeft() != NULL && node->getRight() == NULL) //if node has just left subtree
    {
        return 1 + pathLength(node->getLeft()); //return 1 + recursive length of left subtree 
    }
    else if (node->getLeft() == NULL && node->getRight() != NULL) //if node has just right subtree
    {
        return 1 + pathLength(node->getRight()); 
    }
    else if (node->getLeft() != NULL && node->getRight() != NULL) //if node has both left and right subtrees
    {
        return 1 + std::max(pathLength(node->getLeft()), pathLength(node->getRight())); //returns max for true depth
    }
    return 0; //halting condition, if node has no subtrees return 0; 
    */
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* node) //helper function since clear makes it difficult to directly reference 
{
    //INPUT SHOULD BE ROOT FIX NAME
    if (node != NULL)
    {
        clearHelper(node->getLeft()); //recursive calls to both branches 
        clearHelper(node->getRight()); 
        delete node; 
    }
    else 
    {
        return; 
    }
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif

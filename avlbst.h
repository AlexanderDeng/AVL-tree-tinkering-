#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
    // Add helper functions here
    void leftRotation(AVLNode<Key, Value>* node); 
    void rightRotation(AVLNode<Key, Value>* node); 
    void insertionRebalance(AVLNode<Key, Value> *parent, AVLNode<Key, Value>* node);
    void removalRebalance(AVLNode<Key, Value>* node, int difference);

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
  //copied from bst.h and modified. Modified things will have comments. See bst.h comments for more detail 
    AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL); 
    newNode->setBalance(0); //default balance 0 
    if(this->root_ == NULL) 
    {
        this->root_ = newNode; 
        return; 
    }
    else 
    {
        AVLNode<Key, Value>* current = static_cast<AVLNode<Key,Value>*>(this->root_); 

        while(true) //using break statements to get out of this while loop instead of clear condition 
        {
            if(newNode->getKey() < current->getKey()) 
            {
                if(current->getLeft() != NULL) //no room on the left, go down more left 
                {
                    current = current->getLeft(); 
                }
                else if (current->getLeft() == NULL) //room on the left 
                {
                    newNode->setParent(current); 
                    current->setLeft(newNode); 
                    break; 
                }
            }
            else if (newNode->getKey() > current->getKey())
            {
                if (current->getRight() != NULL) 
                {
                    current = current->getRight(); 
                }
                else if (current->getRight() == NULL)
                {
                    newNode->setParent(current); 
                    current->setRight(newNode);
                    break; 
                }
            }
            else if (newNode->getKey() == current->getKey()) 
            {
                current->setValue(newNode->getValue());
                delete newNode; 
                break; 
            }
        }

        if (current->getBalance() == -1 || current->getBalance() == 1) 
        {
          current->setBalance(0); //if parent of new node was unbalanced by 1 before it is now balanced. 
          return; //nothing needs to be done 
        }
        else //if parent of new node was originally balanced 
        {
          if (current->getLeft() == newNode) 
          {
            current->setBalance(-1); //-1 balance going left 
          }
          else 
          {
            current->setBalance(1); //+1 balance going right 
          }
          insertionRebalance(current, newNode); //call to balancing helper function at the end to see if new_node causes it's parent to be unbalanced 
        }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    AVLNode<Key, Value>* target = static_cast<AVLNode<Key,Value>*>(this->internalFind(key)); //point to node to be deleted 
    int difference; //tracks differences in height 
    if (target == NULL) 
    {
        return;  //if not found 
    }
    if (target->getLeft() && target->getRight()) //if two children, first swap. Other cases will handle the rest 
    {
        AVLNode<Key, Value>* pred = static_cast<AVLNode<Key,Value>*>(this->predecessor(target));
        nodeSwap(target, pred);
    }
    AVLNode<Key, Value>* child = target->getLeft(); //defaults to left but checks right since we want the largest child
    if (target->getRight() != NULL) 
    {
        child = target->getRight(); //child will either be NULL or right child. 
    }
    AVLNode<Key, Value>* parent = target->getParent();
    if (child != NULL)
    {
        child->setParent(parent); // if there is a right child it's parent will be the target's (now swapped) parent
    }
    if (parent == NULL) //if target has no parent now it means it was a root and got swapped with itself
    {
        this->root_ = child; //and thus root should be child preceding deletion 
    }
    else //if target has a parent now 
    {
        if (target == parent->getLeft()) //if target is a left child 
        {
            parent->setLeft(child); //the child of the target must replace it as a left child 
            difference = 1; //height going left is negative, but since we removed the difference is +1 
        } 
        else 
        {
            parent->setRight(child); //replace as right child 
            difference = -1; //height going right is positive, but since we removed the difference is -1 
        }
    }
    delete target; //actual deletion 

  removalRebalance(parent, difference); //call to helper to see if parent of removed node is now unbalanced 
}

template <typename Key, typename Value> 
void AVLTree<Key, Value>::leftRotation(AVLNode<Key, Value>* node)
{
  //to be used on a node with balance 2, meaning it's child has a balance of 1 and is the pivot of rotation. 
  //function takes in node and makes it the left subtree of its right child. 
    
    AVLNode<Key, Value>* rightChild = node->getRight(); //copy of right child 
    AVLNode<Key, Value>* parent = node->getParent(); //copy of parent
    rightChild->setParent(parent); //"promotion"

    if (parent == NULL) //if parent is null that means it was our root that was inbalanced 
    {        
        this->root_ = rightChild; //update root 
    }
    else if (node == parent->getRight()) //if node was a right child 
    {
        parent->setRight(rightChild); //sets new right child to right grandchild 
    }
    else if (node == parent->getLeft()) //if node was a left child
    {
        parent->setLeft(rightChild);
    }    

    AVLNode<Key, Value>* temp = rightChild->getLeft();
    rightChild->setLeft(node); //makes node the left subtree of pivot 
    node->setParent(rightChild); //closure of pointers
    node->setRight(temp); //makes any left grandchild now the right child of left subtree 
    
    if (temp != NULL)
    {
        temp->setParent(node); //if there is actually a left grandchild set its parent to the rotated node to complete 
    }
}

template <typename Key, typename Value> 
void AVLTree<Key, Value>::rightRotation(AVLNode<Key, Value>* node)
{
  //this is a direct copy of leftRotation except right and left are switched idk 
    AVLNode<Key, Value>* leftChild = node->getLeft(); 
    AVLNode<Key, Value>* parent = node->getParent(); 
    leftChild->setParent(parent); 

    if (parent == NULL) 
    {        
        this->root_ = leftChild; 
    }
    else if (node == parent->getLeft()) 
    {
        parent->setLeft(leftChild); 
    }
    else if (node == parent->getRight()) 
    {
        parent->setRight(leftChild);
    }    

    AVLNode<Key, Value>* temp = leftChild->getRight();
    leftChild->setRight(node); 
    node->setParent(leftChild);
    node->setLeft(temp); 
    
    if (temp != NULL)
    {
        temp->setParent(node); 
    }
}

template <typename Key, typename Value> 
void AVLTree<Key, Value>::insertionRebalance(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node)
{
  if (parent == NULL || parent->getParent() == NULL) //edge case preventing sigsegv
  {
    return; 
  }
  AVLNode<Key, Value>* grandparent = parent->getParent(); //copy of grandparent for reference
  
  if (parent == grandparent->getLeft()) // if parent is the left child of grandparent
  { 
    grandparent->setBalance(grandparent->getBalance() - 1); //first subtract 1 from balance to reflect added grandchild
    if (grandparent->getBalance() == 0) //if grandparent is now 0, its balanced--just return
    {
      return; 
    }
    if (grandparent->getBalance() == -1) //otherwise if grandparent is now -1 balance then recursively go up the family tree to fix above, which will be unbalanced now 
    {
      insertionRebalance(grandparent, parent);
      return;
    }
    if (node == parent->getLeft()) //if added node is a left child, and balance of grandparent is neither 0 or +-1  
    {
      rightRotation(grandparent); //call a single right rotation on the unbalanced grandparent
      parent->setBalance(0); //after rightrotation, should be balanced. Set parent and gp balance to 0 
      grandparent->setBalance(0);
    } 
    else //under all other cases, grandparent is unbalanced by 2 or more and node is also unbalanced 
    {
      leftRotation(parent); //left-right rotation 
      rightRotation(grandparent);

      if (node->getBalance() == -1) //if after left-right node is -1
      {
        parent->setBalance(0); //parent is balanced since it now has a left subtree 
        grandparent->setBalance(1); //grandparent is unbalanced 
      } 
      else if (node->getBalance() == 0) //if node is balanced after left-right 
      {
        parent->setBalance(0); //set balances to 0 to reflect this 
        grandparent->setBalance(0);
      } 
      else 
      {
        parent->setBalance(-1); //parent is the unbalanced one now with the only child being the node's child 
        grandparent->setBalance(0); //grandparent remains balanced however. 
      }
            
      node->setBalance(0); //at the end of left-right rotation the node should have 2 subtrees with balance 0 
    }
  }

  else //otherwise if parent is the right child of grandparent 
  { 

    grandparent->setBalance(grandparent->getBalance() + 1); //add 1 to the balance of grandparent since node was added to right subtree
    if (grandparent->getBalance() == 0) 
    {
      return; 
    }

    if (grandparent->getBalance() == 1) //if balance of grandparent is 1 the it was balanced before and requires recursive call 
    {
      insertionRebalance(grandparent, parent); 
      return;
    }

    if (node == parent->getRight()) //if added node is on the right AND grandparent balance is more than 1 
    { 
      leftRotation(grandparent); //left rotation once only 
      parent->setBalance(0); //now balanced 
      grandparent->setBalance(0);
    } 
    else //if added node is on the left and grandparent balance is more than 1
    { 
      rightRotation(parent); //right-left rotation 
      leftRotation(grandparent); 

      if (node->getBalance() == 1) //now if node is still balance 1 
      {
        parent->setBalance(0); //parent is balanced after right-left 
        grandparent->setBalance(-1); //grandparent still isn't 
      } 
      else if (node->getBalance() == 0) //if totally balanced 
      {
        parent->setBalance(0);
        grandparent->setBalance(0);
      } 
      else //if node is "squiggled"
      {
        parent->setBalance(1); //parents have unequal subtrees 
        grandparent->setBalance(0); //grandparents are balanced now. 
      }
            
      node->setBalance(0); //set balance to 0 once process is over
    }

  }

}

template <typename Key, typename Value> 
void AVLTree<Key, Value>::removalRebalance(AVLNode<Key, Value>* node, int difference)
{
  if (node == NULL) //edge case 
  {
    return; 
  }
  AVLNode<Key, Value>* parent = node->getParent(); //copy of parent for reference 
  AVLNode<Key, Value>* child; //temp to copy children onto 
  int differenceAfterRemoval = -1;
  if (parent != NULL && node == parent->getLeft()) //if removed node was left, difference will increase by 1, otherwise decrease by 1
  {
    differenceAfterRemoval = 1; 
  }

  if (node->getBalance() + difference == -2) //negative balance of 2 
  {
    child = node->getLeft(); //set child as the left one since -2 balance
    if (child->getBalance() == -1 || child->getBalance() == 0) //if child is -1 or 0 it means that 1 right rotation will fix things
    {
      rightRotation(node);
      if(child->getBalance() == -1) //if child is still unbalanced it means that it is on a subtree that is unbalanced
      {
        node->setBalance(0); //node however will be balanced after right rotation
        child->setBalance(0); //so will child 
        removalRebalance(parent,differenceAfterRemoval); //but the grandparent of the node that was removed is unbalanced still and requires fixing
      }
      if(child->getBalance() == 0) //if the left child is now balanced 
      {
        node->setBalance(-1); //the node will have -1 balance 
        child->setBalance(1); //the child will have +1 after right rotation 
        return;
      }
    }
    else //if child has unbalance of +-2 
    {
      AVLNode<Key, Value>* rightGrandChild = child->getRight();
      leftRotation(child); //left-right rotation 
      rightRotation(node);
      if (rightGrandChild->getBalance() == 1) //if rightgrandchild had a balance of 1 
      {
        node->setBalance(0); //rebalance node to 0 after left-right 
        child->setBalance(-1); //now -1 since child now has node has a left subtree 
        rightGrandChild->setBalance(0); //now balanced 
      }
      if (rightGrandChild->getBalance() == 0) //if all balanced all good. 
      {
        node->setBalance(0);
        child->setBalance(0);
        rightGrandChild->setBalance(0);
      }
      if (rightGrandChild->getBalance() == 1) //possible error here 
      {
        node->setBalance(1);
        child->setBalance(0);
        rightGrandChild->setBalance(0);
      }
      removalRebalance(parent,differenceAfterRemoval);
    }
  }
  else if (node->getBalance() == 0)
  {
    node->setBalance(node->getBalance() + difference);
    return;
  }
  else
  {
    node->setBalance(0);
    removalRebalance(parent,differenceAfterRemoval);
  }

  if (node->getBalance() + difference == 2) //positive balance of 2 
  {
    child = node->getRight();
    if (child->getBalance() == 1 || child->getBalance() == 0)
    {
      leftRotation(node);
      if(child->getBalance() == 1)
      {
        node->setBalance(0);
        child->setBalance(0);
        removalRebalance(parent,differenceAfterRemoval);
      }
      if(child->getBalance() == 0)
      {
        node->setBalance(1);
        child->setBalance(-1);
        return;
      }
    }
    else
    {
      AVLNode<Key, Value>* leftGrandChild = child->getLeft();
      rightRotation(child);
      leftRotation(node);            
      if (leftGrandChild->getBalance() == -1)
      {
        node->setBalance(0);
        child->setBalance(1);
        leftGrandChild->setBalance(0);
      }
      if(leftGrandChild->getBalance() == 0)
      {
        node->setBalance(0);
        child->setBalance(0);
        leftGrandChild->setBalance(0);
      }
      if (leftGrandChild->getBalance() == -1)
      {
        node->setBalance(-1);
        child->setBalance(0);
        leftGrandChild->setBalance(0);
      }
      removalRebalance(parent,differenceAfterRemoval);
    }
  }
  else if (node->getBalance() == 0)
  {
    node->setBalance(node->getBalance() + difference);
    return;
  }
  else
  {
    node->setBalance(0);
    removalRebalance(parent,differenceAfterRemoval);
  }

}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif

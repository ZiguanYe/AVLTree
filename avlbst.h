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
    virtual void rotateLeft( AVLNode<Key,Value>* n);
    virtual void rotateRight( AVLNode<Key,Value>* n);
    
    virtual void insertFix( AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    virtual void removeFix( AVLNode<Key,Value>* p, int8_t diff);

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    //If empty tree => set n as root, b(n) = 0, done!
    if(this->root_==nullptr)
    {
        AVLNode<Key,Value>* temp = new AVLNode<Key,Value>(new_item.first, new_item.second, nullptr);
        temp->setBalance(0);
        this->root_ = temp;
    }
    else
    {
        //temp is guaranteed not a nullptr
        AVLNode<Key,Value>* exist = static_cast<AVLNode<Key, Value>*>(this->internalFind(new_item.first));
        if(exist !=nullptr)
        {
            exist->setValue(new_item.second);
            return;
        }
        else
        {
            AVLNode<Key,Value>* temp = static_cast<AVLNode<Key, Value>*>(this->root_);
            while(temp!=nullptr)
            {
                //the node should go to the left
                if(new_item.first < temp->getKey())
                {
                    //the node is leaf node
                    if(temp->getLeft()==nullptr)
                    {
                        AVLNode<Key,Value>* newLeaf = new AVLNode<Key,Value>(new_item.first, new_item.second, temp);
                        newLeaf->setBalance(0);
                        temp->setLeft(newLeaf);
                        //newLeaf->setParent(temp);
                        if (temp->getBalance()==1 || temp->getBalance()==-1)
                        {
                            temp->setBalance(0);
                        }
                        else if (temp->getBalance()==0)
                        {
                            temp->setBalance(-1);
                            insertFix(temp, newLeaf);
                        }
                        break;
                        //try break
                    }
                    //the node is not leaf node, go to the next level
                    else
                    {
                        temp = temp->getLeft();
                    }
                }
                else if(new_item.first > temp->getKey())
                {
                    //the node is leaf node
                    if(temp->getRight()==nullptr)
                    {
                        AVLNode<Key,Value>* newLeaf = new AVLNode<Key,Value>(new_item.first, new_item.second, temp);
                        newLeaf->setBalance(0);
                        temp->setRight(newLeaf);
                        //newLeaf->setParent(temp);
                        if (temp->getBalance()==1 || temp->getBalance()==-1)
                        {
                            temp->setBalance(0);
                        }
                        else if (temp->getBalance()==0)
                        {
                            //note that here the balance shoudld be updated to +1 since it is a single right child
                            temp->setBalance(1);
                            insertFix(temp, newLeaf);
                        }
                        break;
                    }
                    //the node is not leaf node, go to the next level
                    else
                    {
                        temp = temp->getRight();
                    }
                }
            }
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix (AVLNode<Key,Value>* p, AVLNode<Key,Value>* n)
{
    AVLNode<Key,Value>* g = p->getParent();
    if(p==nullptr || g==nullptr)
    {
        return;
    }
    else
    {
        //outer case1: p is left chlid of g
        //this indeicates that zigzig is the case where n is left of p, and zigzag is the case where n is the right of p
        if(p==g->getLeft())
        {
            g->updateBalance(-1);
            if(g->getBalance()==0)
            {
                return;
            }
            else if(g->getBalance()==-1)
            {
                insertFix(g, p);
            }
            else if(g->getBalance()==-2)
            {
                //zigzig
                if(n == p->getLeft())
                {
                    rotateRight(g);
                    p->setBalance(0);
                    g->setBalance(0);
                }
                //zigzag
                else if(n == p->getRight())
                {
                    rotateLeft(p);
                    rotateRight(g);
                    if(n->getBalance()==-1)
                    {
                        p->setBalance(0);
                        g->setBalance(1);
                        n->setBalance(0);
                    }
                    else if(n->getBalance()==0)
                    {
                        p->setBalance(0);
                        g->setBalance(0);
                        n->setBalance(0);
                    }
                    else if(n->getBalance()==1)
                    {
                        p->setBalance(-1);
                        g->setBalance(0);
                        n->setBalance(0);
                    }
                }
            }
        }
        //outer case12 p is right chlid of g
        //this indicates that zigzig is the case where n is right of p, and zigzag is the case where n is the left of p
        else if(p==g->getRight())
        {
            g->updateBalance(1);
            if(g->getBalance()==0)
            {
                return;
            }
            else if(g->getBalance()==1)
            {
                insertFix(g, p);
            }
            else if(g->getBalance()==2)
            {
                //zigzig
                if(n == p->getRight())
                {
                    rotateLeft(g);
                    p->setBalance(0);
                    g->setBalance(0);
                }
                //zigzag
                else if(n == p->getLeft())
                {
                    rotateRight(p);
                    rotateLeft(g);
                    if(n->getBalance()==1)
                    {
                        p->setBalance(0);
                        g->setBalance(-1);
                        n->setBalance(0);
                    }
                    else if(n->getBalance()==0)
                    {
                        p->setBalance(0);
                        g->setBalance(0);
                        n->setBalance(0);
                    }
                    else if(n->getBalance()==-1)
                    {
                        p->setBalance(1);
                        g->setBalance(0);
                        n->setBalance(0);
                    }
                }
            }
        }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    AVLNode<Key,Value>* curr = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    if(curr==nullptr)
    {
        return;
    }
    else
    {
        if(curr->getLeft()!=nullptr && curr->getRight()!=nullptr)
        {
            nodeSwap(curr, static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::predecessor(curr)));
        }
        
        int8_t diff = 0;
        AVLNode<Key,Value>* p = curr->getParent();
        
        if(p!=nullptr && curr==p->getLeft())
        {
            diff = 1;
        }
        else if(p!=nullptr && curr==p->getRight())
        {
            diff = -1;
        }
        
        //at this point curr is guaranteed to have at most 1 children
        
        //case1: the node is a leaf node
        if(curr->getLeft()==nullptr && curr->getRight()==nullptr)
        {
            //if the node is the root, just clear the tree
            if(curr==BinarySearchTree<Key,Value>::root_)
            {
                BinarySearchTree<Key,Value>::root_ = nullptr;
                //delete curr;
            }
            //the node is a left child
            else if(curr==curr->getParent()->getLeft())
            {
                curr->getParent()->setLeft(nullptr);
                //delete curr;
            }
            //the node is a right child
            else if (curr==curr->getParent()->getRight())
            {
                curr->getParent()->setRight(nullptr);
                //delete curr;
            }
        }
        //case2: the node has one right child
        else if(curr->getLeft()==nullptr && curr->getRight()!=nullptr)
        {
            //node is root
            if(curr==BinarySearchTree<Key,Value>::root_)
            {
                curr->getRight()->setParent(nullptr);
                BinarySearchTree<Key,Value>::root_ = curr->getRight();
                //delete curr;
            }
            //node is a left child
            else if(curr == curr->getParent()->getLeft())
            {
                curr->getRight()->setParent(curr->getParent());
                curr->getParent()->setLeft(curr->getRight());
                //delete curr;
            }
            //node is a right child
            else if(curr == curr->getParent()->getRight())
            {
                curr->getRight()->setParent(curr->getParent());
                curr->getParent()->setRight(curr->getRight());
                //delete curr;
            }
        }
        //case3: the node has one left child
        else if(curr->getRight()==nullptr && curr->getLeft()!=nullptr)
        {
            //node is root
            if(curr==BinarySearchTree<Key,Value>::root_)
            {
                curr->getLeft()->setParent(nullptr);
                BinarySearchTree<Key,Value>::root_ = curr->getLeft();
                //delete curr;
            }
            //node is a left child
            else if(curr == curr->getParent()->getLeft())
            {
                curr->getLeft()->setParent(curr->getParent());
                curr->getParent()->setLeft(curr->getLeft());
                //delete curr;
            }
            //node is a right child
            else if(curr == curr->getParent()->getRight())
            {
                curr->getLeft()->setParent(curr->getParent());
                curr->getParent()->setRight(curr->getLeft());
                //delete curr;
            }
        }
        removeFix(curr->getParent(), diff);
    }
    delete curr;
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix( AVLNode<Key,Value>* n, int8_t diff)
{
    if(n == nullptr)
    {
        return;
    }
    else
    {
        AVLNode<Key,Value>* p = n->getParent();
        int8_t ndiff=0;
        if(p!=nullptr && n == p->getLeft())
        {
            ndiff = 1;
        }
        else if(p!=nullptr && n == p->getRight())
        {
            ndiff = -1;
        }
        
        //outercase 1: n is parent of its only right child
        if(diff==-1)
        {
            //case1
            if(n->getBalance() + diff == -2)
            {
                AVLNode<Key,Value>* c = n->getLeft();
                //case1a, zigzig
                if(c->getBalance()==-1)
                {
                    rotateRight(n);
                    n->setBalance(0);
                    c->setBalance(0);
                    removeFix(p, ndiff);
                }
                //case1b, zigzig
                else if(c->getBalance()==0)
                {
                    rotateRight(n);
                    n->setBalance(-1);
                    c->setBalance(1);
                    return;
                }
                //case1c, zigzag
                else if(c->getBalance()==1)
                {
                    AVLNode<Key,Value>* g = c->getRight();
                    rotateLeft(c);
                    rotateRight(n);
                    if(g->getBalance()==1)
                    {
                        n->setBalance(0);
                        c->setBalance(-1);
                        g->setBalance(0);
                    }
                    else if(g->getBalance()==0)
                    {
                        n->setBalance(0);
                        c->setBalance(0);
                        g->setBalance(0);
                    }
                    else if(g->getBalance()==-1)
                    {
                        n->setBalance(1);
                        c->setBalance(0);
                        g->setBalance(0);
                    }
                    removeFix(p, ndiff);
                }
            }
            //case2
            else if(n->getBalance() + diff == -1)
            {
                n->setBalance(-1);
            }
            //case3
            else if(n->getBalance() + diff == 0)
            {
                n->setBalance(0);
                removeFix(p, ndiff);
            }
        }
        //mirror case
        else if(diff==1)
        {
            if(n->getBalance() + diff == 2)
            {
                AVLNode<Key,Value>* c = n->getRight();
                //case1a, zigzig
                if(c->getBalance()==1)
                {
                    rotateLeft(n);
                    n->setBalance(0);
                    c->setBalance(0);
                    removeFix(p, ndiff);
                }
                //case1b, zigzig
                else if(c->getBalance()==0)
                {
                    rotateLeft(n);
                    n->setBalance(1);
                    c->setBalance(-1);
                    return;
                }
                //case1c, zigzag
                else if(c->getBalance()==-1)
                {
                    AVLNode<Key,Value>* g = c->getLeft();
                    rotateRight(c);
                    rotateLeft(n);
                    if(g->getBalance()==-1)
                    {
                        n->setBalance(0);
                        c->setBalance(1);
                        g->setBalance(0);
                    }
                    else if(g->getBalance()==0)
                    {
                        n->setBalance(0);
                        c->setBalance(0);
                        g->setBalance(0);
                    }
                    else if(g->getBalance()==1)
                    {
                        n->setBalance(-1);
                        c->setBalance(0);
                        g->setBalance(0);
                    }
                    removeFix(p, ndiff);
                }
            }
            //case2
            else if(n->getBalance() + diff == 1)
            {
                n->setBalance(1);
            }
            //case3
            else if(n->getBalance() + diff == 0)
            {
                n->setBalance(0);
                removeFix(p, ndiff);
            }
        }
    }
}
    
template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

    
template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* n)
{
    AVLNode<Key,Value>* child = n->getRight();
    //n should be guaranteed to have a right child for rotateLeft
    //n is root
	if(n==this->root_)
    {
        //update root
        this->root_ = child;
        //update n
        n->setParent(child);
        if(child->getLeft()!=nullptr)
        {
            n->setRight(child->getLeft());
            child->getLeft()->setParent(n);
        }
        else
        {
            n->setRight(nullptr);
        }
        //update chlid
        child->setParent(nullptr);
        child->setLeft(n);
    }
    //n is left child
    else if(n == n->getParent()->getLeft())
    {
        //update parent
        n->getParent()->setLeft(child);
        //parent have to be set here before modification
        child->setParent(n->getParent());
        //update n
        n->setParent(child);
        if(child->getLeft()!=nullptr)
        {
            n->setRight(child->getLeft());
            child->getLeft()->setParent(n);
        }
        else
        {
            n->setRight(nullptr);
        }
        //update child
        child->setLeft(n);
    }
    else if (n == n->getParent()->getRight())
    {
        //update parent
        n->getParent()->setRight(child);
        //parent have to be set here before modification
        child->setParent(n->getParent());
        //update n
        n->setParent(child);
        if(child->getLeft()!=nullptr)
        {
            n->setRight(child->getLeft());
            child->getLeft()->setParent(n);
        }
        else
        {
            n->setRight(nullptr);
        }
        //update child
        child->setLeft(n);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight( AVLNode<Key,Value>* n)
{
    AVLNode<Key,Value>* child = n->getLeft();
    //n should be guaranteed to have a left child for rotateLeft
    //n is root
    if(n==this->root_)
    {
        //update root
        this->root_ = child;
        //update n
        n->setParent(child);
        if(child->getRight()!=nullptr)
        {
            n->setLeft(child->getRight());
            child->getRight()->setParent(n);
        }
        else
        {
            n->setLeft(nullptr);
        }
        //update chlid
        child->setParent(nullptr);
        child->setRight(n);
    }
    //n is left child
    else if(n == n->getParent()->getLeft())
    {
        //update parent
        n->getParent()->setLeft(child);
        //parent have to be set here before modification
        child->setParent(n->getParent());
        //update n
        n->setParent(child);
        if(child->getRight()!=nullptr)
        {
            n->setLeft(child->getRight());
            child->getRight()->setParent(n);
        }
        else
        {
            n->setLeft(nullptr);
        }
        //update child
        child->setRight(n);
    }
    else if (n == n->getParent()->getRight())
    {
        //update parent
        n->getParent()->setRight(child);
        //parent have to be set here before modification
        child->setParent(n->getParent());
        //update n
        n->setParent(child);
        if(child->getRight()!=nullptr)
        {
            n->setLeft(child->getRight());
            child->getRight()->setParent(n);
        }
        else
        {
            n->setLeft(nullptr);
        }
        //update child
        child->setRight(n);
    }
}

#endif

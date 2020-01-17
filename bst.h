/*bst.h*/

//
// Binary search tree
//

#pragma once

#include <iostream>
#include <algorithm>  // std::max

using namespace std;

template<typename TKey, typename TValue>
class binarysearchtree
{
private:
  struct NODE
  {
    TValue Value;
    TKey  Key;
    NODE* Left;
    NODE* Right;
  };
  
  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)
  
  //
  // _inorder does the actual inorder traversal and output
  // to console.  Each key is output to the console followed
  // by " ", including the last key.
  //
  void _inorder(NODE* cur)
  {
     if (cur == nullptr)
       return;
     else
     {
        _inorder(cur->Left);
         cout << cur->Key << " ";
         cout << cur->Value << " ";
        _inorder(cur->Right);
     }
  }

public:
  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  binarysearchtree()
  {
    Root = nullptr;
    Size = 0;
  }
    
  // copy constructor
  binarysearchtree(const binarysearchtree &copy)
  {
      Root = copyHelp(copy.Root);
      Size = copy.Size;
  }
  // copy constructor helper
  NODE* copyHelp(const NODE *copy)
  {
     if(copy == nullptr) {
         return nullptr;
  }
     NODE *temp = new NODE;
     temp->Key = copy->Key;
     temp->Value = copy->Value;
     temp->Left = copyHelp(copy->Left);
     temp->Right = copyHelp(copy->Right);
     return temp;
}
    
  //
  // size:
  //
  // Returns the # of nodes in the tree, 0 if empty.
  //
  int size()
  {
    return Size;
  }

  //
  // height
  //
  // Computes and returns height of tree; height of an empty tree is
  // defined as -1.
  //
  int height()
  {
      return BSTGetHeight(Root);
  }
  // height helper function
  int BSTGetHeight(NODE* node) {
    if (node == NULL) {
       return -1;
    }
    int LeftHeight = BSTGetHeight(node->Left);
    int RightHeight = BSTGetHeight(node->Right);
    return 1 + max(LeftHeight, RightHeight);
}

  //
  // search:
  //
  // Searches the tree for the given key, returning true if found
  // and false if not.
  //
  TValue* search(TKey key)
  {
    NODE* cur = Root;
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return &(cur->Value);

      if (key < cur->Key)  // search left:
      {
        cur = cur->Left;
      }
      else
      {
        cur = cur->Right;
      }
    }
    // if get here, not found
    return nullptr;
  }

  //
  // insert
  //
  // Inserts the given key into the tree; if the key has already been insert then
  // the function returns without changing the tree.
  //
  void insert(TKey key, TValue value)
  {
    NODE* prev = nullptr;
    NODE* cur = Root;

    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return;

      if (key < cur->Key)  // search left:
      {
        prev = cur;
        cur = cur->Left;
      }
      else
      {
        prev = cur;
        cur = cur->Right;
      }
    }//while

    //
    // 2. if we get here, key is not in tree, so allocate
    // a new node to insert:
    //
    NODE* newNode = new NODE;
    //
    // pointer fields:
    //
    newNode->Value = value;
    newNode->Key = key;
    newNode->Left = nullptr;
    newNode->Right = nullptr;
    //
    // 3. link in the new node:
    //
    // NOTE: cur is null, and prev denotes node where
    // we fell out of the tree.  if prev is null, then
    // the tree is empty and the Root pointer needs
    // to be updated.
    //
    if (prev == nullptr) {
        Root = newNode;
    }
        else{
        if(prev->Key > newNode->Key) {
          prev->Left = newNode;
        }
        else {
            prev->Right = newNode;
        }
    }
    
      //
    // 4. update size and we're done:
    //
   ++Size;
  }

  //
  // inorder:

  void inorder2()
  {
      cout << "Inorder: ";
      _inorder2(Root);
      cout << endl;
  }
};


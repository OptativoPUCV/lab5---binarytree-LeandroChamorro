#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;

struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap* tree = (TreeMap*)malloc(sizeof(TreeMap));
    tree->root = NULL;
    tree->current = NULL;
    tree->lower_than = lower_than;
    return tree;
}

void insertTreeMap(TreeMap * tree, void* key, void * value) {
  if (tree == NULL) return; 
  if (searchTreeMap(tree, key) != NULL) return; 

  TreeNode* new_node = createTreeNode(key, value); 

  if (tree->root == NULL) { 
      tree->root = new_node;
      tree->current = new_node;
      return;
  }

  TreeNode* current = tree->root; 

  while (1) {
    if (tree->lower_than(key, current->pair->key)) {
      if (current->left == NULL) {
        current->left = new_node;
        new_node->parent = current;
        tree->current = new_node;
        return;
      }
    current = current->left;
    } 
    else {
    if (current->right == NULL) {
      current->right = new_node;
      new_node->parent = current;
      tree->current = new_node;
      return;
    }
    current = current->right;
   }
  }  
}

TreeNode * minimum(TreeNode * x){
  while (x!= NULL && x->left != NULL){
    x=x->left;
  }
  return x;
}

void removeNode(TreeMap * tree, TreeNode* node) {
  if (tree == NULL || node == NULL) return;

  // C1 0h
  if (node->left == NULL && node->right == NULL) {
    if (node == tree->root) {
      tree->root = NULL;
    } 
    else {
      if (node->parent->left == node) {
        node->parent->left = NULL;
      } 
      else {
        node->parent->right = NULL;
      }
    }
    free(node);
  }
    
  // C2 1h
  else if (node->left == NULL || node->right == NULL) {
    TreeNode* hijo = (node->left != NULL) ? node->left : node->right;

    if (node == tree->root) {
      tree->root = hijo;
      if (hijo != NULL) {
      hijo->parent = NULL;
      }
    } 
    else {
      if (node->parent->left == node) {
        node->parent->left = hijo;
      } 
      else {
        node->parent->right = hijo;
      }
      if (hijo != NULL) {
        hijo->parent = node->parent;
      }
    }
    free(node);
  }
  // C3 2h
  else {
    TreeNode* minNode = minimum(node->right);
    Pair* nodeData = (Pair*)node;
    Pair* minNodeData = (Pair*)minNode;
    nodeData->key = minNodeData->key;
    nodeData->value = minNodeData->value;
    removeNode(tree, minNode);
  }
}

void eraseTreeMap(TreeMap * tree, void* key){
  if (tree == NULL || tree->root == NULL) return;

  if (searchTreeMap(tree, key) == NULL) return;
  TreeNode* node = tree->current;
  removeNode(tree, node);
}

Pair * searchTreeMap(TreeMap * tree, void* key) {
  if (tree == NULL || tree->root == NULL) return NULL; 
  
  TreeNode* current = tree->root;
  while (current != NULL){
    if (tree->lower_than(key, current->pair->key)){
      current = current->left; 
    }
    else if (tree->lower_than(current->pair->key, key)){
      current = current->right;
    }
    else{
      tree->current = current;
      return current->pair;
    }
  }
return NULL; 
}

Pair * upperBound(TreeMap * tree, void* key) {
  TreeNode* currentNode = tree->root;
  TreeNode* nodo = NULL;

  while (currentNode != NULL) {
    int cmp = is_equal(tree, key, currentNode->pair->key);

    if (cmp == 1) {
    tree->current = currentNode;
    return currentNode->pair;
    } 
    else if (tree->lower_than(key, currentNode->pair->key)) {
      nodo = currentNode;
      currentNode = currentNode->left;
    } 
    else {
      currentNode = currentNode->right;
    }
  }

  if (nodo == NULL) {
    return NULL;
  } 
  else {
    tree->current = nodo;
    return nodo->pair;
  }
}

Pair * firstTreeMap(TreeMap * tree) {
  if (tree == NULL || tree->root == NULL) return NULL;

  TreeNode* current = tree->root;
  TreeNode* minimumNode = minimum(current);

  if (minimumNode != NULL) {
    tree->current = minimumNode; 
    return minimumNode->pair; 
  } 
  else {
    return NULL; 
  }
}

Pair * nextTreeMap(TreeMap * tree) {
  if (tree == NULL || tree->current == NULL) return NULL; 

  TreeNode* current = tree->current;

  // C1 0D
  if (current->right != NULL) {
    current = minimum(current->right);
  }
  
  // C2 1I 0D
  else {
  TreeNode* parent = current->parent;
  while (parent != NULL && current == parent->right) {
    current = parent;
    parent = parent->parent;
  }
  current = parent;
  }

  if (current != NULL) {
    tree->current = current;
    return current->pair;
  } 
  else {
    return NULL;
  }
}

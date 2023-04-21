//Por alguna razon se me negaba el acceso a test.sh entonces ocupe un comando chmod +x test.sh
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
        } else {
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

    // Caso 1: Nodo sin hijos
    if (node->left == NULL && node->right == NULL) {
        if (node == tree->root) {
            // Caso especial: Nodo es la raíz del árbol
            tree->root = NULL;
        } else {
            // Anular el puntero del padre que apuntaba al nodo
            if (node->parent->left == node) {
                node->parent->left = NULL;
            } else {
                node->parent->right = NULL;
            }
        }
        free(node); // Liberar memoria del nodo
    }
    // Caso 2: Nodo con un hijo
    else if (node->left == NULL || node->right == NULL) {
        TreeNode* child = (node->left != NULL) ? node->left : node->right;

        if (node == tree->root) {
            // Caso especial: Nodo es la raíz del árbol
            tree->root = child;
            child->parent = NULL;
        } else {
            // El padre del nodo pasa a ser padre de su hijo
            if (node->parent->left == node) {
                node->parent->left = child;
            } else {
                node->parent->right = child;
            }
            child->parent = node->parent;
        }
        free(node); // Liberar memoria del nodo
    }
    // Caso 3: Nodo con dos hijos
    else {
        // Descender al hijo derecho y obtener el nodo mínimo del subárbol
        TreeNode* minNode = minimum(node->right);
        // Reemplazar los datos (key, value) de node con los del nodo mínimo
        Pair* nodeData = (Pair*)node->data;
        Pair* minNodeData = (Pair*)minNode->data;
        nodeData->key = minNodeData->key;
        nodeData->value = minNodeData->value;
        // Eliminar el nodo mínimo recursivamente
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
    if (tree == NULL || tree->root == NULL) return NULL; // Árbol vacío
    TreeNode* current = tree->root;
    while (current != NULL){
        if (tree->lower_than(key, current->pair->key)){
            current = current->left; // Se mueve a la rama izquierda
        }
        else if (tree->lower_than(current->pair->key, key)){
            current = current->right; // Se mueve a la rama derecha
        }
        else{
            // Se encontró la clave, se actualiza el current y se retorna el Pair asociado
            tree->current = current;
            return current->pair;
        }
    }

    return NULL; // No se encontró el Pair con la clave
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}

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
  if (tree == NULL) return; // Árbol no válido
    if (searchTreeMap(tree, key) != NULL) return; // Clave duplicada, retorna sin hacer nada

    TreeNode* new_node = createTreeNode(key, value); // Crea un nuevo nodo con la clave y valor dados

    if (tree->root == NULL) { // Si el árbol está vacío, el nuevo nodo se convierte en la raíz
        tree->root = new_node;
        tree->current = new_node;
        return;
    }

    TreeNode* current = tree->root; // Comienza la búsqueda desde la raíz

    while (1) {
        if (tree->lower_than(key, current->pair->key)) {
            // Si la clave es menor a la clave del nodo actual, se mueve a la rama izquierda
            if (current->left == NULL) {
                // Si no hay más nodos en la rama izquierda, enlaza el nuevo nodo como hijo izquierdo del nodo actual
                current->left = new_node;
                new_node->parent = current;
                tree->current = new_node;
                return;
            }
            current = current->left;
        } else {
            // Si la clave es mayor o igual a la clave del nodo actual, se mueve a la rama derecha
            if (current->right == NULL) {
                // Si no hay más nodos en la rama derecha, enlaza el nuevo nodo como hijo derecho del nodo actual
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

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

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

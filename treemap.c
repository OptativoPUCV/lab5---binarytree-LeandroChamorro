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
  if (tree == NULL) {
        return; // Árbol nulo, no se puede insertar el dato
    }

    // Buscar la posición de inserción
    Pair* search_result = searchTreeMap(tree, key);
    if (search_result != NULL) {
        return; // La clave ya existe, no se puede insertar el dato
    }

    // Crear nuevo nodo
    TreeNode* new_node = (TreeNode*) malloc(sizeof(TreeNode));
    if (new_node == NULL) {
        return; // Error de asignación de memoria
    }

    // Inicializar nuevo nodo
    new_node->pair->key = key;
    new_node->pair->value = value;
    new_node->left = NULL;
    new_node->right = NULL;

    // Insertar el nuevo nodo en el árbol
    if (tree->root == NULL) {
        tree->root = new_node; // Árbol vacío, el nuevo nodo se convierte en la raíz
    } else {
        TreeNode* current = tree->current;
        int cmp_result = tree->lower_than(key, current->key);
        while (1) {
            if (cmp_result) {
                // El nuevo nodo va a la izquierda
                if (current->left == NULL) {
                    current->left = new_node; // Encontró la posición de inserción
                    break;
                } else {
                    current = current->left;
                }
            } else {
                // El nuevo nodo va a la derecha
                if (current->right == NULL) {
                    current->right = new_node; // Encontró la posición de inserción
                    break;
                } else {
                    current = current->right;
                }
            }
            cmp_result = tree->lower_than(key, current->key);
        }
    }

    tree->current = new_node; // Hacer que el current apunte al nuevo nodo
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

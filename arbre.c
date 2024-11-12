//
// Created by vdela on 12/11/2024.
//

#include "arbre.h"

#include <stdio.h>

node_t* create_node(int cost, t_move move) {
    node_t* new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        printf("Erreur\n");
        return NULL;
    }
    new_node->cost = cost;
    new_node->move = move;
    for (int i = 0; i < MAX_CHILDREN; i++) {
        new_node->children[i] = NULL;
    }
    return new_node;
}


int add_node(node_t* node, node_t* child){
    if(node->children[8]==NULL)
        return 0;
    int cpt=0;
    while(node->children[cpt]!=NULL) {
    cpt++;
    }
    node->children[cpt]=child;
    return 1;

}


void free_node(node_t* node) {
    if(node==NULL)
        return;
    for (int i = 0; i < MAX_CHILDREN; i++) {
        if(node->children[i]!=NULL)
            free_node(node->children[i]);
    }
    free(node);
}

/*
node_t* find_min(node_t* node) {
    node_t* min = node;
    int min_cost = min->cost;
    for (int i = 0; i < MAX_CHILDREN; i++)
        {
        if(node->children[i]!=NULL)
        {
            if(node->children[i]->cost<min_cost) {
                min = node->children[i];
                min_cost = node->cost;
            }
        }
    }
    return min;
}*/

int is_leaf(node_t* node){
    int val = 1;
    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (node->children[i] != NULL) {
            val = 0;
            break;
        }
    }
    return val;
}

//val : OUT
void find_smallest_Leaf(node_t *node, int *val) {
    if (node == NULL) {
        return;
    }

    if (is_leaf(node)) {
        if (node->cost < *val) {
            *val = node->cost;
        }
    } else {
        for (int i = 0; i < MAX_CHILDREN; i++) {
            find_smallest_Leaf(node->children[i], val);
        }
    }
}

void findMinPath(node_t* node, int* minCost, node_t** minNode, int path[], int* minPath, int level) {
    if (node == NULL) return;

    // Ajouter le mouvement courant au chemin
    path[level] = node->move;

    // Si le nœud est une feuille (n’a pas d’enfants)
    if (is_leaf(node)) {
        // Vérifier si cette feuille a un coût inférieur au coût minimal
        if (node->cost < *minCost) {
            *minCost = node->cost;
            *minNode = node;
            // Copier le chemin courant vers le chemin minimal
            for (int i = 0; i <= level; i++) {
                minPath[i] = path[i];
            }
            minPath[level + 1] = -1; // Marquer la fin du chemin
        }
    }

    // Parcourir les enfants
    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (node->children[i] != NULL) {
            findMinPath(node->children[i], minCost, minNode, path, minPath, level + 1);
        }
    }
}



arbre_t* create_arbre() {
    arbre_t* new_arbre = malloc(sizeof(arbre_t));
    if (new_arbre == NULL) {
        printf("Erreur\n");
        return NULL;
    }
    new_arbre->root=NULL;
    return new_arbre;
}


void free_arbre(arbre_t* arbre) {

    if (arbre == NULL)
        return;
    free_node(arbre->root);
    free(arbre);
}


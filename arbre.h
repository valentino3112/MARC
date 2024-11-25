//
// Created by vdela on 12/11/2024.
//

#ifndef ARBRE_H
#define ARBRE_H
#include "moves.h"
#include "map.h"
#define MAX_CHILDREN 9
#define HAUTEUR_ARBRE 5
#include <stdlib.h>

typedef struct node_s {
    int cost;
    t_move move;
    struct node_s* children[MAX_CHILDREN];
    int TL;
}node_t;

typedef struct arbre_s {
    node_t* root;
} arbre_t;

/**
 * @brief Function to create a node
 * @param cost : the cost associated with the node
 * @param move : the move associated with the node
 * @return pointer to the created node
 */
node_t* create_node(int cost, t_move move);

/**
 * @brief Function to add a child node to a parent node
 * @param node : the parent node
 * @param child : the child node to add
 * @return 0 on success, -1 on failure
 */
int add_node(node_t* node, node_t* child);

/**
 * @brief Function to move without teleporting
 * @param loc : the current location
 * @param da_move : the move to perform
 * @param map : the map on which the move is performed
 * @return the new location after the move
 */
t_localisation move_sans_teleporter(t_localisation loc, t_move da_move, t_map map);

/**
 * @brief Function to check if a node is a leaf
 * @param node : the node to check
 * @return 1 if the node is a leaf, 0 otherwise
 */
int is_leaf(node_t* node);

/**
 * @brief Function to find the smallest leaf value
 * @param node : the root node
 * @param val : pointer to store the smallest leaf value
 */
void find_smallest_Leaf(node_t *node, int *val);


/**
 * @brief Function to find the minimum cost path in the tree
 * @param node : the root node
 * @param minCost : pointer to store the minimum cost
 * @param minNode : pointer to store the node with the minimum cost
 * @param path : array to store the current path
 * @param minPath : array to store the minimum cost path
 * @param level : the current level in the tree
 */
void findMinPath(node_t* node, int* minCost, node_t** minNode, int path[], int* minPath, int level);

/**
 * @brief Function to create a tree
 * @return pointer to the created tree
 */
arbre_t* create_arbre();

/**
 * @brief Function to free a tree
 * @param arbre : the tree to free
 */
void free_arbre(arbre_t* arbre);

/**
 * @brief Function to fill the tree with nodes
 * @param parent : the parent node
 * @param niveau : the current level in the tree
 * @param move_occ : array of move occurrences
 * @param map : the map on which the moves are performed
 * @param sim_MARC : the current location of the robot
 * @param secoue : flag indicating if the robot is shaken
 */
void remplire_arbre(node_t* parent, int niveau, int move_occ[7], t_map map, t_localisation sim_MARC, int secoue);

/**
 * @brief Function to print the tree
 * @param node : the root node
 * @param level : the current level in the tree
 */
void printTree(node_t* node, int level);
#endif //ARBRE_H

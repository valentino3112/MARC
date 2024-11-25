//
// Created by dnum on 21/11/24.
//

#ifndef UNTITLED1_UTILS_H
#define UNTITLED1_UTILS_H

#include "loc.h"
#include "moves.h"
#include "map.h"
/**
 * @brief Function to print a move
 * @param move : the move to print
 */
void printMove(t_move move);

/**
 * @brief Function to initialize an array of moves
 * @param array : the array to initialize
 */
void initializeArray(t_move array[]);

/**
 * @brief Function to remove an element from an array
 * @param array : the array from which to remove the element
 * @param size : pointer to the size of the array
 * @param index : the index of the element to remove
 */
void removeElement(t_move array[], int *size, int index);

/**
 * @brief Function to move the robot Marc
 * @param MARC : pointer to the robot's location
 * @param da_move : the move to perform
 * @param map : the map on which the robot moves
 * @param secoue : pointer to an integer to store the shake count
 */
void move_marc(t_localisation* MARC, t_move da_move, t_map map, int* secoue);

/**
 * @brief Function to perform a random draw of moves
 * @param result : array to store the result of the draw
 */
void tirage_aleatoire(t_move result[]);

/**
 * @brief Function to count occurrences of moves
 * @param move_occ : array to store the count of each move
 * @param result : array of moves to count
 */
void to_occ(int move_occ[7], t_move result[9]);

/**
 * @brief Function to verify if the robot finds the base
 * @param map : pointer to the map
 * @param minPath : array of moves representing the minimum path
 * @param vrai_marc : pointer to the robot's location
 * @return 1 if the base is found, 0 otherwise
 */
int verif_base(t_map *map, const int *minPath, t_localisation* vrai_marc);
#endif //UNTITLED1_UTILS_H

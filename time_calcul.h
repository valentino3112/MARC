//
// Created by lilia on 11/23/2024.
//

#ifndef UNTITLED1_TIME_CALCUL_H
#define UNTITLED1_TIME_CALCUL_H
#include "arbre.h"
#include "loc.h"

double calculer_temps_construction_arbre(node_t* racine, int* move_occ, t_map map, t_localisation MARC);
double calculer_temps_recherche_feuille_min(node_t* racine);
double calculer_chemin_racine_vers_feuille(node_t* racine, node_t* feuille, int* path, int* minPath);


#endif //UNTITLED1_TIME_CALCUL_H

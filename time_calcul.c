//
// Created by lilia on 11/23/2024.
//
#include <sys/time.h>
#include "time_calcul.h"
//Fonctions pour calculer le temps d'execution de :
// • la consturction de l'arbre
// • la recherche d'une feuille de valeur minimal parmis les feuilles de l'arbre
// • le calcul du chemin de la racine vers la feuille
// • Un exemple complet de guidage de MARC depuis sa position d’origine vers la station de base.



// Fonction pour calculer le temps d'exécution de la construction de l'arbre
double calculer_temps_construction_arbre(node_t* racine, int* move_occ, int** costs, t_localisation MARC){
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    remplire_arbre(racine, 0, move_occ, costs, MARC);
    gettimeofday(&end_time, NULL);
    return (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
}



// Fonction pour calculer temps trouver la feuille de valeur minimal parmis les feuilles de l'arbre
double calculer_temps_recherche_feuille_min(node_t* racine) {
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    find_smallest_Leaf(racine, &racine->TL);
    gettimeofday(&end_time, NULL);
    return (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
}

// Fonction pour calculer le chemin de la racine vers la feuille
double calculer_chemin_racine_vers_feuille(node_t* racine, node_t* feuille, int* path, int* minPath) {
    struct timeval start_time, end_time;
    int val = 9999;
    find_smallest_Leaf(racine, &val);
    gettimeofday(&start_time, NULL);
    findMinPath(racine, &val, &feuille, path, minPath, 0);
    gettimeofday(&end_time, NULL);
    return (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
}

// Exemple complet de guidage de MARC depuis sa position d’origine vers la station de base
void guidage_complet(t_map map, t_localisation MARC) {
    // Implémentation du guidage complet
}
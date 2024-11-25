#include <stdio.h>
#include <time.h>
#include "map.h"
#include "loc.h"
#include "moves.h"
#include "arbre.h"
#include "utils.h"
#include "time_calcul.h"
//test

int final_path_buffer[999];

int verif_base(t_map *map, const int *minPath, t_localisation* vrai_marc);

void to_occ(int move_occ[7], t_move result[9]){
    for (int i = 0; i < 9; i++){
        move_occ[result[i]] = move_occ[result[i]] + 1;
    }
}



void printTree(node_t* node, int level) {
    if (!node) return;

    // Print the current node with indentation
    for (int i = 0; i < level; i++) printf("  "); // Indentation for the current level
    printf("Cost: %d, Move: ", node->cost);
    printMove(node->move);
    printf(", TL: %d\n", node->TL);

    // Recursively print each child
    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (node->children[i]) {
            printTree(node->children[i], level + 1);
        }
    }
}

int main() {
    t_localisation vrai_marc;
    for (int i = 0; i < 999; i++){
        final_path_buffer[i] = -2;
    }
    int x,y;
    int QUIT = 0;

    int phase = 0;
    printf("---MENU DE MARC ----\n");
    t_map map;
    printf("Quelle carte voulez-vous utiliser ?\n");
    int carte=-1;
    while (carte<1 || carte>5) {
        printf("Entrez le nombre de 1 à 5 correspondant à la carte\n");
        scanf("%d", &carte);
    }

    switch (carte) {
        case 1:
#if defined(_WIN32) || defined(_WIN64)
            map = createMapFromFile("..\\maps\\example1.map");
#else
            map = createMapFromFile("../maps/example1.map");
#endif
            break;
        case 2:
#if defined(_WIN32) || defined(_WIN64)
            map = createMapFromFile("..\\maps\\example2.map");
#else
            map = createMapFromFile("../maps/example2.map");
#endif
            break;
        case 3:
#if defined(_WIN32) || defined(_WIN64)
            map = createMapFromFile("..\\maps\\example3.map");
#else
            map = createMapFromFile("../maps/example3.map");
#endif
            break;
        case 4:
#if defined(_WIN32) || defined(_WIN64)
            map = createMapFromFile("..\\maps\\example4.map");
#else
            map = createMapFromFile("../maps/example4.map");
#endif
            break;
        case 5:
#if defined(_WIN32) || defined(_WIN64)
            map = createMapFromFile("..\\maps\\example5.map");
#else
            map = createMapFromFile("../maps/example5.map");
#endif
            break;
    }
    displayMap(map);

    t_localisation MARC;
    printf("Souhaitez-vous définir un point de départ aléatoire pour MARC?\n1.OUI\n2.NON\n");
    int choix_aleatoire=-1;
    while (!(choix_aleatoire == 1 || choix_aleatoire == 2)) {
        printf("Entrez un nombre, 1.OUI ou 2.NON\n");
        scanf("%d", &choix_aleatoire);
    }
    srand(time(0));
    if(choix_aleatoire == 1){
        // Generate a random number between 0 and x_max and y_max
        int random_x = rand() % map.x_max+1;
        int random_y = rand() % map.y_max+1;
        while (map.soils[random_y][random_x] == 4 || map.soils[random_y][random_x] == 0){
            int random_x = rand() % map.x_max+1;
            int random_y = rand() % map.y_max+1;
        }
        MARC = loc_init(random_x, random_y, EAST);
        x = random_x;
        y = random_y;
    }else{
        MARC = loc_init(0, 0, EAST);
        x = 0;
        y = 0;
    }
    printf("Coordonnées du robot: x: %d, y: %d\n", MARC.pos.x, MARC.pos.y);

    while(QUIT==0) {
        t_move result[9];

        // Phase test
        int move_occ[7] = {0,0,0,0,0,0,0};
        tirage_aleatoire(result);
        to_occ(move_occ, result);

        printf("---TESTE ARBRE ----\n");
        arbre_t* test = create_arbre();
        //int move_occ[7] = {2,2,0,0,1,2,2};
        node_t* racine = create_node(map.costs[MARC.pos.y][MARC.pos.x],999);
        test->root = racine;


        //remplire_arbre(racine, 0, &move_occ, map, MARC, 0);
        double temps = calculer_temps_construction_arbre(racine, move_occ, map, MARC);

        //printTree(racine,0);
        printf("---FIN TESTE ARBRE ----\n\n\n");

        printf("---TESTE TEMPS DE CALCUL ----\n");

        //double temps = 0;
        printf("Temps de construction de l'arbre: %f\n", temps);
        printf("---FIN TESTE TEMPS DE CALCUL ----\n\n\n");


        //test de la fonction find_smallest_Leaf
        printf("---TESTE FONCTION find_smallest_Leaf ----\n");
        int val = 9999;
        find_smallest_Leaf(racine, &val);
        printf("Valeur minimal de la feuille: %d\n", val);
        //tmep de recherche de la feuille minimal
        double temps_recherche = calculer_temps_recherche_feuille_min(racine);
        printf("Temps de recherche de la feuille minimal: %f\n", temps_recherche);

        printf("---FIN TESTE FONCTION find_smallest_Leaf ----\n\n\n");


        //test de la fonction findMinPath
        printf("---TESTE FONCTION findMinPath ----\n");
        int minCost = val;
        node_t* minNode = NULL;
        int path[10];
        int minPath[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
        int length = 0;
        findMinPath(racine, &minCost, &minNode, path, minPath, 0);
        printf("Chemin minimal: ");
        for (int i = 0; i < 9; i++) {
            if (minPath[i] == -1) break;
            length++;
            printMove(minPath[i]);
            printf(" -> ");
        }
        printf("\n");
        printf("Temps de recherche du chemin minimal: %f\n", calculer_chemin_racine_vers_feuille(racine, minNode, path, minPath));
        printf("---FIN TESTE FONCTION findMinPath ----\n");
        vrai_marc = MARC;
        verif_base(&map, minPath, &vrai_marc);

        for (int i = 1; i < HAUTEUR_ARBRE+1; i++){
            //printf("%d\t",i+phase*5);
            final_path_buffer[i+phase*5] = minPath[i];
        }
        if (map.costs[vrai_marc.pos.y][vrai_marc.pos.x] == 0){
            QUIT = 1;
        }else{
            MARC = vrai_marc;
            phase++;
        }
        printf("Coordonnées du robot: x: %d, y: %d\n",vrai_marc.pos.x, vrai_marc.pos.y);

        //QUIT = 1;
    }
    printf("coordonnées de MARC au debut: x: %d, y: %d\n", x, y);
    printf("CHEMIN FINALE TROUVE EN %d PHASE\n", phase);
    for (int i = 1; i < phase*5+5+2; i++){
        //if (final_path_buffer[i+phase*5] == -2) break;
        printMove(final_path_buffer[i]);
        printf("->");
    }
    printf("\n");
    printf("coordonnées de MARC à la fin: x: %d, y: %d\n", vrai_marc.pos.x, vrai_marc.pos.y);
}

int verif_base(t_map *map, const int *minPath, t_localisation* vrai_marc) {//verification si le robot trouve bien la base


    int secoue = 0;
    for (int i = 1; i < HAUTEUR_ARBRE+1; i++){
        move_marc(vrai_marc, minPath[i], (*map), &secoue);
        printf("coord x: %d, y: %d\n", vrai_marc->pos.x, vrai_marc->pos.y);
    }
    printf("Coordonnées du robot: x: %d, y: %d\n",vrai_marc->pos.x, vrai_marc->pos.y);
    if ((*map).costs[vrai_marc->pos.y][vrai_marc->pos.x] == 0){
        printf("le robot à trouvé la base\n");
    }else{
        printf("le robot ne trouve pas la base\n");
    }
    //vrai_marc = move_sans_teleporter(vrai_marc, F_20, map);
    //printf("coord x: %d, y: %d", vrai_marc.pos.x, vrai_marc.pos.y);
    printf("cost: %d\n", (*map).costs[vrai_marc->pos.y][vrai_marc->pos.x]);
}

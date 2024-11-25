//
// Created by flasque on 19/10/2024.
//

#include "loc.h"

/*----------------------------------------------------------------------------------------------------------------------
                            FONCTION : loc_init
Cette fonction initialise une structure de type `t_localisation` avec les coordonnées `x` et `y` et l'orientation `ori`
données en paramètres. Elle crée et renvoie la localisation initialisée.
Elle prend en paramètres :
  - `x` : la coordonnée en x de la localisation.
  - `y` : la coordonnée en y de la localisation.
  - `ori` : l'orientation initiale de type `t_orientation`.
Elle renvoie la structure `t_localisation` initialisée.
----------------------------------------------------------------------------------------------------------------------*/
t_localisation loc_init(int x, int y, t_orientation ori)
{
    t_localisation loc;
    loc.pos.x = x;
    loc.pos.y = y;
    loc.ori = ori;
    return loc;
}

/*----------------------------------------------------------------------------------------------------------------------
                            FONCTION : isValidLocalisation
Cette fonction vérifie si une position `loc` se situe dans les limites d'un espace défini par `x_max` et `y_max`.
Elle prend en paramètres :
  - `loc` : la position de type `t_position` à vérifier.
  - `x_max` : la limite maximale en x de l'espace.
  - `y_max` : la limite maximale en y de l'espace.
Elle renvoie 1 (vrai) si la position est valide, et 0 (faux) sinon.
----------------------------------------------------------------------------------------------------------------------*/
int isValidLocalisation(t_position loc, int x_max, int y_max)
{
    return (loc.x >= 0 && loc.x < x_max && loc.y >= 0 && loc.y < y_max);
}

/*----------------------------------------------------------------------------------------------------------------------
                            FONCTION : LEFT
Cette fonction calcule la position à gauche de la position donnée `pos`.
Elle prend en paramètre :
  - `pos` : la position de type `t_position` actuelle.
Elle renvoie la nouvelle position après un déplacement vers la gauche.
----------------------------------------------------------------------------------------------------------------------*/
t_position LEFT(t_position pos)
{
    t_position new_pos;
    new_pos.x = pos.x - 1;
    new_pos.y = pos.y;
    return new_pos;
}

/*----------------------------------------------------------------------------------------------------------------------
                            FONCTION : RIGHT
Cette fonction calcule la position à droite de la position donnée `pos`.
Elle prend en paramètre :
  - `pos` : la position de type `t_position` actuelle.
Elle renvoie la nouvelle position après un déplacement vers la droite.
----------------------------------------------------------------------------------------------------------------------*/
t_position RIGHT(t_position pos)
{
    t_position new_pos;
    new_pos.x = pos.x + 1;
    new_pos.y = pos.y;
    return new_pos;
}

/*----------------------------------------------------------------------------------------------------------------------
                            FONCTION : UP
Cette fonction calcule la position au-dessus de la position donnée `pos`.
Elle prend en paramètre :
  - `pos` : la position de type `t_position` actuelle.
Elle renvoie la nouvelle position après un déplacement vers le haut.
----------------------------------------------------------------------------------------------------------------------*/
t_position UP(t_position pos)
{
    t_position new_pos;
    new_pos.x = pos.x;
    new_pos.y = pos.y - 1;
    return new_pos;
}

/*----------------------------------------------------------------------------------------------------------------------
                            FONCTION : DOWN
Cette fonction calcule la position en dessous de la position donnée `pos`.
Elle prend en paramètre :
  - `pos` : la position de type `t_position` actuelle.
Elle renvoie la nouvelle position après un déplacement vers le bas.
----------------------------------------------------------------------------------------------------------------------*/
t_position DOWN(t_position pos)
{
    t_position new_pos;
    new_pos.x = pos.x;
    new_pos.y = pos.y + 1;
    return new_pos;
}

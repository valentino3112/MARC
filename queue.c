//
// Created by flasque on 19/10/2024.
//

#include <assert.h>
#include <stdlib.h>
#include "queue.h"

/**
 * @brief Function to create a queue
 * @param size : the size of the queue
 * @return the queue
 */
t_queue createQueue(int size)
{
    // the size of the queue must be positive
    assert(size > 0);
    t_queue queue;
    queue.size = size;
    queue.first = 0;
    queue.last = 0;
    queue.values = (t_position *)malloc(size * sizeof(t_position));
    return queue;
}


/*----------------------------------------------------------------------------------------------------------------------
                            FONCTION : enqueue
Cette fonction ajoute un élément `pos` à la fin de la file `p_queue`.
Elle prend en paramètres :
  - `p_queue` : un pointeur vers la file (`t_queue`) dans laquelle insérer l'élément.
  - `pos` : la position (`t_position`) à ajouter.
Prérequis : la file ne doit pas être pleine.
La fonction ne renvoie rien ; elle met directement à jour la file.
----------------------------------------------------------------------------------------------------------------------*/
void enqueue(t_queue *p_queue, t_position pos)
{
    // the queue must not be full
    assert((p_queue->last - p_queue->first) < p_queue->size);
    p_queue->values[(p_queue->last) % p_queue->size] = pos;
    p_queue->last++;
    return;
}


/*----------------------------------------------------------------------------------------------------------------------
                            FONCTION : dequeue
Cette fonction retire et renvoie l'élément en tête de la file `p_queue`.
Elle prend en paramètre :
  - `p_queue` : un pointeur vers la file (`t_queue`) dans laquelle retirer l'élément.
Prérequis : la file ne doit pas être vide.
Elle renvoie l'élément retiré (`t_position`).
----------------------------------------------------------------------------------------------------------------------*/
t_position dequeue(t_queue *p_queue)
{
    // the queue must not be empty
    assert(p_queue->last != p_queue->first);
    p_queue->first++;
    return p_queue->values[(p_queue->first - 1) % p_queue->size];
}
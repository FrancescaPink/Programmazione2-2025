#ifndef CODA-BFS_H
#define CODA-BFS_H

#include "tipo.h"
#include "tree.h"

struct elemBFS
{
       node* inf;
       elemBFS* pun ;
};

typedef elemBFS* lista;

typedef struct{
	lista head;
	elemBFS* tail;} codaBFS;

codaBFS enqueue(codaBFS, node*);
node* dequeue(codaBFS&);
node* first(codaBFS);
bool isEmpty(codaBFS);
codaBFS newQueue();

static elemBFS* new_elem(node*);

#endif
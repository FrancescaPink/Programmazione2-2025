#ifndef TREE_H
#define TREE_H

#include "tipo.h"

struct node {
   tipo_inf inf;
   node* parent; //opzionale
	  node* firstChild;
	  node* nextSibling;
};

typedef node* tree;

node* new_node(tipo_inf);
void insert_child(tree, tree);
void insert_sibling(node*, tree);
tipo_inf get_info(node*);
node* get_parent(node*);
node* get_firstChild(node*);
node* get_nextSibling(node*);

#endif
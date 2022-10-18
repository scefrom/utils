#pragma once

#ifndef __NODE_H
#define __NODE_H

#include "commons.h"
#include "bfr.h"

#define NODE_TYPE_NULL					255
#define NODE_NULL						(node_t) {NODE_TYPE_NULL, DATA_NULL, 0, NULL}



typedef struct node_t node_t;

typedef int8_t node_value_fn(bfr_t *, bfr_t*, node_t);

struct node_t {
	uint16_t id; //what am i?
	data_t data; //what do i have in my backpack?
	size_t children_n; //how many babies do i have?
	node_t *children; //where can i find my babies?
	//node_t *parent; //where is papa? where is mama? this ain't be...
};



node_t node_create_node(uint8_t id, data_t data, size_t children_n, uint8_t force);
void node_free_node(node_t node);

node_t *node_adopt(node_t *parent, node_t child); //bruhhhhhh adopt frfr :skull: :skull: :skull: *goofy fart sound* *goofy alarm sound*

void node_tbfr(bfr_t *bfr, bfr_t *src, node_t node, char **id_map, node_value_fn *value_fn, size_t rec);



#endif
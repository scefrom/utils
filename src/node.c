#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



node_t node_create_node(uint8_t id, data_t data, size_t children_n, uint8_t force) {
	node_t node = (node_t) {
		.id = id,
		.data = data,
		.children_n = children_n
	};

	if (force || children_n > 0)
		node.children = malloc(children_n * sizeof(node_t));
	else
		node.children = NULL;

	return node;
}

void node_free_node(node_t node) {
	if (node.id != 	NODE_TYPE_NULL) {
		if (node.children != NULL) {
			size_t i = 0;
			for (; i < node.children_n; i++) {
				node_free_node(node.children[i]);
			}

			free(node.children);
		}

		//printf("FREE'D: %d\n", node->id);

		//free(node);
	}
}



node_t *node_adopt(node_t *parent, node_t child) {
	parent->children = realloc(parent->children, (parent->children_n + 1) * sizeof(node_t));
	parent->children[parent->children_n] = child;

	return parent->children + parent->children_n++;
}



void node_tbfr_append_tabs(bfr_t *bfr, size_t rec) {
	if (!rec) return;

	bfr_t tabs = (bfr_t) { 
		.size = rec,
		.index = 0
	};

	uint8_t bfr_space[rec];
	tabs.bfr = (uint8_t*) bfr_space;

	for (size_t i = 0; i < rec; i++) tabs.bfr[i] = (uint8_t) '\t';

	bfr_append(bfr, tabs);
}

void node_tbfr(bfr_t *bfr, bfr_t src, node_t node, char **id_map, node_value_fn *value_fn, size_t rec) {
	node_tbfr_append_tabs(bfr, rec);

	bfr_append(bfr, BFR_FROM_STR_NO_NULL(id_map[node.id]));
	
	bfr_t to_append = (bfr_t) {.bfr = NULL};
	int8_t v = value_fn(&to_append, src, node);

	if (v < 0) return;

	bfr_append(bfr, BFR_FROM_CONST_NO_NULL(": "));

	if (v) {
		if (!node.children_n) {
			bfr_append(bfr, BFR_FROM_CONST_NO_NULL("{}"));
			return;
		}

		bfr_append(bfr, BFR_FROM_CONST_NO_NULL("{\n"));

		size_t e = node.children_n - 1;
		for (size_t i = 0; i < node.children_n; i++) {
			node_tbfr(bfr, src, node.children[i], id_map, value_fn, rec + 1);
			bfr_append(bfr, i < e ? BFR_FROM_CONST_NO_NULL(",\n") : BFR_FROM_CONST_NO_NULL("\n"));
		}

		node_tbfr_append_tabs(bfr, rec);
		bfr_append(bfr, BFR_FROM_CONST_NO_NULL("}"));
	} else {
		to_append.index = 0;
		bfr_append(bfr, to_append);
		free(to_append.bfr); //not bfr_free cause we dont want to free to_append too, cause it's on the stack, not created by bfr_init() (and therefore malloc'd)
	}
}
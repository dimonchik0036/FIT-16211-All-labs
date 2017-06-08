//	 Labs: 6-balanced-trees
// Author: Dimonchik0036

#ifndef AVLTREE_H_
#define AVLTREE_H_
typedef struct AvlTreeNode
{
	int key;
	unsigned char height;
	struct AvlTreeNode *left;
	struct AvlTreeNode *right;
} AvlTreeNode;


AvlTreeNode* avltree_node_new(int key);

void avltree_free(AvlTreeNode *tree);


AvlTreeNode* avltree_insert(AvlTreeNode *node, int k);

AvlTreeNode* avltree_rotateright(AvlTreeNode *node);

AvlTreeNode* avltree_rotateleft(AvlTreeNode *node);


AvlTreeNode* avltree_balance(AvlTreeNode *node);

int avltree_balance_difference(AvlTreeNode *node);


unsigned char avltree_height(AvlTreeNode *node);

void avltree_height_fix(AvlTreeNode *node);
#endif

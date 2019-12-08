#ifndef RB_H
#define RB_H

enum color { RED, BLACK, DUBLEBLACK};

typedef int data_type;

typedef struct Node {
	data_type data;
	enum color color;
	struct Node *left, *right, *parent;
} Node;

typedef Node * tree;

int is_root(tree element);
int is_left(tree element);
tree sibiling(tree element);
tree uncle(tree element);

int major_element(tree root);
void pre_order(tree root);
void print_element(tree root);
void print(tree root);

enum color color(tree element);
void rotate_right(tree *root, tree pivo);
void rotate_left(tree *root, tree pivo);
void double_rotate_right(tree *root, tree pivo);
void double_rotate_left(tree *root, tree pivo);

void start(tree *root);
void insert(int key, tree *root);
void adjust(tree *root, tree element);

tree case2a(tree root, tree element);
tree case2b(tree root, tree element);
tree case3a(tree root, tree element);
tree case3b(tree root, tree element);
tree case4a(tree root, tree element);
tree case4b(tree root, tree element);
tree case5a(tree root, tree element);
tree case5b(tree root, tree element);
tree case6a(tree root, tree element);
tree case6b(tree root, tree element);
tree search(int element, tree root);

tree remove_cases(tree root, tree sub_root);
tree remove_normal(int key, tree root);
tree remover(int key, tree root);
tree remove_aux(tree root, tree sub_root);



#endif

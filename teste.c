#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(){
    struct Node* root = NULL;
    int option;
    while(1){
        scanf("%d",&option);
        switch(option){
            int key;
            case 1:
                scanf("%d", &key);
                root = insert(root,key);
                break;
            case 2:
                preOrder(root);
                break;
            case 3:
                scanf("%d", &key);
                root = deleteNode(root, key);
                break;
            case 999:
                exit(0);
        }
    }
}

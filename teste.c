#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

int main(int argc, char * argv[]) {
	tree a;
	int opcao;
	start(&a);

	while(1) {
		scanf("%d", &opcao);

		switch(opcao) {
				int valor;
				case 1:
						scanf("%d", &valor);
						insert(valor, &a);
						break;
				case 2:
						pre_order(a);
						printf("\n");
						break;
				case 3:
						scanf("%d", &valor);
						a = remover(valor, a);
						break;
				case 999:
						exit(0);
		}
	}
}

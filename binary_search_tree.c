#include <stdio.h>
#include <stdlib.h>

struct arvore{
	int n;
	struct arvore* dir;
	struct arvore* esq;
};

// We set some default values to the tree

void inicializa(struct arvore** raiz){ 
	struct arvore* aux = (struct arvore*) malloc(sizeof(struct arvore));
	aux->n = 30;
	aux->dir = NULL;
	aux->esq = NULL;
	*raiz = aux;
}

// Function to insert data into the tree

void insere(struct arvore* raiz, struct arvore* anterior, int n){ 
	
    struct arvore* aux = raiz;
	struct arvore* novo = NULL; 
	struct arvore* ant = anterior;
	
    if (aux == NULL){ 
		novo = (struct arvore*) malloc(sizeof(struct arvore)); 
		novo->n = n;
		novo->dir = NULL;
		novo->esq = NULL;
		if (n > ant->n)  ant->dir = novo; 
		else ant->esq = novo; 
	}
	
    else{
		if (n > aux->n)  insere(aux->dir, aux, n); 
		else if(n < aux->n)  insere(aux->esq, aux, n); 
		else printf("Esse valor de %d já existe\n\n", n); 
	}
}

// This function removes the root from the tree

void removeraiz(struct arvore** raiz){ 

    struct arvore* aux = *raiz;
    struct arvore* ant = *raiz;
    struct arvore* help = *raiz; 
    
    if(aux->esq->dir == NULL){ 
        aux = aux->esq; 
        aux->dir = ant->dir; 
        free(ant); 
        ant = NULL;
        *raiz = aux; 
        return; 
    
    }
    else{ 
        aux = aux->esq; 
        while(aux->dir != NULL){ 
            ant = aux; 
            aux = aux->dir;
        }
        ant->dir = aux->esq; 
        aux->dir = help->dir; 
        aux->esq = help->esq; 
        free(help); 
        help = NULL; 
        *raiz = aux; 
    }
}

// Function to search for a value

int busca(struct arvore* raiz, int n){ 
    
    struct arvore* aux = raiz;
    
    if(aux == NULL){ 
        printf("Valor não encontrado!\n\n"); 
        return 0;
    }

    else{
        if(n == aux->n){ 
            printf("O valor existe!\n\n");
            return 1;
        }else if(n > aux->n) busca(aux->dir, n);
        else busca(aux->esq, n); 
    }
}

// Function to remove the nodes from the tree

void remover(struct arvore** raiz, int n){
    
    struct arvore* aux = *raiz;
    struct arvore* ant = *raiz;
    struct arvore* aj = NULL;
    struct arvore* help = NULL; 
    int x;
    
    x = busca(*raiz, n); 
    if(x == 0) return; 
    if(aux == NULL) return;
    

    // If the node is the root
    if(n == aux->n){ 
            removeraiz(raiz);
            return; 
    }

    else{
        while(aux->n != n){ 
                if(n > aux->n){ 
                    ant = aux;
                    aux = aux->dir;
                }else if(n < aux->n){ 
                    ant = aux;
                    aux = aux->esq;
                }
        } 

        if(aux->dir == NULL && aux->esq == NULL){ 
            free(aux);
            aux = NULL;
            if(n > ant->n) ant->dir = aux; 
            else ant->esq = aux;
        }
        else if(aux->dir == NULL){ 
            aj = aux; 
            aux = aux->esq;
            free(aj); 
            aj = NULL;
            if(n > ant->n) ant->dir = aux; 
            else ant->esq = aux;
        }
        else if(aux->esq == NULL){ 
            aj = aux;
            aux = aux->dir;
            free(aj);
            aj = NULL;
            if(n > ant->n) ant->dir = aux;
            else ant->esq = aux;
        }
        else{ 
            aj = aux->esq; 
            if(aj->dir == NULL){ 
                help = aux;  
                aux = aj; 
                aux->dir = help->dir; 
                free(help);
                help = NULL;
                if(n > ant->n) ant->dir = aux; 
                else ant->esq = aux;
            }
            else{ 
                while(aj->dir != NULL){ 
                    help = aj; 
                    aj = aj->dir; 
                }
                help->dir = aj->esq;
                aj->dir = aux->dir; 
                aj->esq = aux->esq; 
                if(n > ant->n) ant->dir = aj; 
                else ant->esq = aj;
                free(aux); 
                aux = NULL;
        }
        }
    }
}

// Function that prints the tree

void imprime(struct arvore* raiz){
	struct arvore* aux = raiz;
	if (aux == NULL) return; 
	else{
		imprime(aux->esq); 
		printf("%d\n", aux->n);
		imprime(aux->dir); 
	}
}

int main(){
	
    struct arvore* raiz = NULL;
	
    inicializa(&raiz);
	
    insere(raiz, raiz, 200);
	insere(raiz, raiz, 104);
	insere(raiz, raiz, 1);
	insere(raiz, raiz, 0);
	insere(raiz, raiz, 3);
    insere(raiz, raiz, 4);
    insere(raiz, raiz, 43);
    insere(raiz, raiz, 12);
    insere(raiz, raiz, 456);
    insere(raiz, raiz, 8);
    insere(raiz, raiz, 15);
    insere(raiz, raiz, 16);
	
    remover(&raiz, 3);
	
    imprime(raiz);
	
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista {
	char n;
	struct lista* next; 
	struct lista* prev; 
};

// This function inserts data into the double linked list

void insere(struct lista** head, char n){ 
	struct lista* novo = (struct lista*) malloc(sizeof(struct lista));
	struct lista* aux = *head;
	novo->n = n;
	novo->next = NULL;
	if(!aux){
		novo->prev = NULL;
		*head = novo;
	}
	else{
		while(aux->next) aux = aux->next;
		novo->prev = aux;
		aux->next = novo;
	}
}

// This function changes two letters

void trocaLetras(struct lista** head, char k[], char j[]){ 
	struct lista* pal1 = NULL; 
	struct lista* pal2 = NULL; 
	struct lista* aux = *head;
	char tmp;
	while(aux){ 
		if(aux->n == k[0]) pal1 = aux;		
		if(aux->n == j[0]) pal2 = aux;
		aux = aux->next;
	}
		if(!pal1){ 
			printf("%s não encontrado na palavra. Saindo...\n", k);
			return;
		}
		else if(!pal2){ 
			printf("%s não encontrado na palavra. Saindo...\n", j);
			return;	
		}
		tmp = pal2->n; 
		pal2->n = pal1->n;
		pal1->n = tmp;
}

// This function destroys the list

void destroilista(struct lista *head){ 
	struct lista *aux = head;
	struct lista *p = NULL;
	while(aux){
		p = aux->next;
		free(aux);
		aux = p;
	}
}

// This function prints the list

void imprime(struct lista* head){
	struct lista* aux = head;
	while(aux != NULL){
		printf("%c", aux->n);
		aux = aux->next;
	}
	printf("\n");
}

int main(){
	struct lista* head = NULL;
	char n[25], j[2], k[2];
	int i = 0;

	printf("Digite a palavra: ");
	scanf("%s", n);
	while(strlen(n) > 25 || strlen(n) < 2){ 
		printf("Palavra invalida. Use no minimo 2 e no maximo 25 letras: ");
		scanf("%s", n);
	}

	while(n[i] != '\0'){ 
		insere(&head, n[i]);
		i++;
	}
	
	printf("Digite a primeira letra: ");
	scanf("%s", k);
	while(strlen(k) > 1){ 
		printf("Valor invalido. Digite apenas uma letra: ");
		scanf("%s", k);
	}
	
	printf("Digite a segunda letra: ");
	scanf("%s", j);
	while(strlen(j) > 1){ 
		printf("Valor invalido. Digite apenas uma letra: ");
		scanf("%s", j);
	}

	trocaLetras(&head, k, j);
	imprime(head);
	destroilista(head);
	return 0;
}


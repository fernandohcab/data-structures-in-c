#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct lista{ 
	int cod;
	char nome[50];
	float preco;
	struct lista* next;
};

// This functios sees if the name already exists in the linked list

int nomeexistente(struct lista* head, char *nome){ 

	struct lista* aux = head;
	if(!aux) return 0;
	else{
		while(aux){
			if(strcmp(aux->nome, nome) == 0)  return 1;
			aux = aux->next;
		}
		return 0;
	}
}

// This function inserts data into the linked list

void insere(struct lista **head, int i){ 
	struct lista* novo;
	struct lista* aux = *head; 
	int res;

	novo = (struct lista*) malloc(sizeof(struct lista));
	novo->cod = i;
	printf("Digite o nome do produto: ");
	scanf("%s", novo->nome);
	res = nomeexistente((*head), novo->nome); 
	
	while(res != 0){
		printf("Este nome já está em uso. Escolha outro: ");
		scanf("%s", novo->nome);
		res = nomeexistente((*head), novo->nome);
	}

	printf("Digite o preco do produto: ");
	scanf("%f", &novo->preco);
	novo->next = NULL;
	
	if(!aux)  *head = novo;
	
	else{
		while(aux->next != NULL)  aux = aux->next;
		aux->next = novo;
	}
}

// This function searches for a given code

float buscacod(struct lista *head, int cod){ 
	struct lista* aux = head;
	if(!head) return 0;
	else{
		while(aux){
			if(aux->cod == cod)  return aux->preco;
			aux = aux->next;
		}
		printf("Produto não encontrado\n");
		return 0;
	}
}

// This function searches for a given name

float buscanome(struct lista *head, char *nome){ 
	struct lista* aux = head;
	if(!aux) return 0;
	else{
		while(aux){
			if(strcmp(aux->nome, nome) == 0)  return aux->preco;
			aux = aux->next;
		}
		printf("Produto não encontrado\n");
		return 0;
	}
}

// This function removes the nodes from the linked list

void remover(struct lista **head, char *nome){ 
	struct lista* aux = *head;
	struct lista* ant = NULL; 
	if(!aux) return;
	else{
		if(strcmp(aux->nome, nome) == 0){ 
			ant = aux->next;
			free(aux);
			*head = ant;
			return;
		}
		else{
			while(aux){
				if(strcmp(aux->nome, nome) == 0){
					ant->next = aux->next;
					free(aux);
					return;
				}
				ant = aux;
				aux = aux->next;
			}
		}
	}
	printf("Produto não encontrado\n");
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

// This function prints the linked list

void imprime(struct lista *head){ 
	while(head != NULL){ 
		printf("O código é \"%d\", o nome é \"%s\" e o preço é \"%.2f\"\n", head->cod, head->nome, head->preco); // Usamos escape characters para escapar dos caracteres especiais
		head = head->next;
	}
}

int main(){
	struct lista *head = NULL;
	int n=1, i=1, cod, op;
	char nome[50];
	float valor;

	printf("A atribuição de códigos é automática e inicia em 1 e cresce ordenadamente\n");
	printf("Insira o nome e o preço dos produtos. Digite -1 para sair ou qualquer outro numero para continuar quando for perguntado\n");
	
	while(n != -1){ 
		insere(&head, i);
		i++;
		printf("Deseja continuar? ");
		scanf("%d", &n);
	}

	printf("Deseja consultar algum produto para ver seu preço? Digite 1 para sim e 0 para não: ");
	scanf("%d", &n);
	if(n == 1){
		printf("Digite 1 para buscar um produto pelo codigo e 2 pelo nome: ");
		scanf("%d", &n);
		
		switch(n){
			case 1:
				printf("Digite o codigo buscado: ");
				scanf("%d", &cod);
				valor = buscacod(head, cod);
				printf("O valor do produto buscado é R$ %.2f\n", valor);
				break;
			
			case 2:
				printf("Digite o nome buscado: ");
				scanf("%s", nome);
				valor = buscanome(head, nome);
				printf("O valor do produto buscado é R$ %.2f\n", valor);
				break;
			
			default:
				printf("Valor inválido. Saindo...\n");
		}
	}
	printf("Deseja remover algum produto? 1 para sim e 0 para não: ");
	scanf("%d", &op);
	switch(op){
		case 0:
			break;
		case 1:
			printf("Digite o nome do produto a ser removido: ");
			scanf("%s", nome);
			remover(&head, nome);
			break;
		default:
			printf("Valor inválido. Saindo...\n");
	}
	imprime(head);
	destroilista(head);
	return 0;
}

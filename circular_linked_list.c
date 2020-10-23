//Blacljack game

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista{
	int jog;
	int pontos;
	struct lista* next;
};

// This function inserts default values to the list

void inicializa(struct lista** last, int i){ 
	struct lista* aux = *last;
	struct lista* novo = NULL;
	novo = (struct lista*) malloc(sizeof(struct lista));
	novo->jog = i;
	novo->pontos = 0;
	if(!aux) novo->next = novo;
	else{
		novo->next = aux->next;
		aux->next = novo;
	}
	*last = novo;
}

// This function removes data from the list

void remover(struct lista* aux, struct lista** last){ 
	struct lista* ant = (*last)->next; 
	printf("Jogador = %d eliminado. Pontuacao final = %d\n", aux->jog, aux->pontos);
	if(aux == *last){ 
		while(ant->next != (*last)) ant = ant->next;
		ant->next = (*last)->next;
		free(aux);
		*last = ant;
		return;
	}
	else{ 
		while(ant->next != aux) ant = ant->next;
		ant->next = aux->next;
		free(aux);
	}
}

// This function verifies if the given node is the last

int verifica(struct lista* last){ 
	struct lista* aux = last->next;
	int i = 0;
	while(aux != last){
		i++;
		aux = aux->next;
	}
	if(i == 0) return 1;
	return 0;
}

// This function sees if the given value is a known value

int busca(char n[]){ 
	char lista[12][2] = {"A", "J", "K", "Q", "2", "3", "4", "5", "6", "7", "8", "9"};
	int i;
	for(i=0;i<12;i++){
		if(strcmp(n, lista[i]) == 0) return 1;
	}
	return 0;
}

// This function inserts data into the list

int insere(struct lista* aux, struct lista** last){ 
	char n[2]; 
	if (!aux) return 0;
	else{
		printf("Digite uma carta (numero de 2 a 10 ou as letras A, J, K ou Q): ");
		scanf("%s", n);
		while(busca(n) == 0){ 
			if(strcmp(n,"10") == 0){ 
				aux->pontos += 10;
				break;
			}
			printf("Valor invalido!! Digite novamente um novo valor.\n");
			printf("Digite uma carta (numero de 2 a 10 ou as letras A, J, K ou Q): ");
			scanf("%s", n);
		}
		
		// Here the values are added
		if(atoi(n) && atoi(n) != 10) aux->pontos += atoi(n);
		else if(strcmp(n,"A") == 0) aux->pontos += 11;
		else if(strcmp(n,"J") == 0) aux->pontos += 10;
		else if(strcmp(n,"K") == 0) aux->pontos += 10;
		else if(strcmp(n,"Q") == 0) aux->pontos += 10;
	}
	if(aux->pontos == 21){
		printf("Jogador vencedor: %d. Pontuação: %d\n", aux->jog, aux->pontos);
		return 1;
	}
	else if(aux->pontos > 21){
		remover(aux, last); 
		return 0;	
	}
	return 0;
}

// This function prints the list

void imprime(struct lista* last){ 
	struct lista* aux = last->next;
	printf("Situacao da lista: \n");
	while(aux != last){
		printf("Jogador = %d pontuacao = %d\n", aux->jog, aux->pontos);
		aux = aux->next;
	}
	printf("Jogador = %d pontuacao = %d\n", aux->jog, aux->pontos);
	printf("\n");
}

// This function destroys the list

void destroilista(struct lista *last){ 
	struct lista *aux = last->next;
	struct lista *p = NULL;
	while(aux != last){
		p = aux->next;
		free(aux);
		aux = p;
	}
}

int main(){
	int n, i, j=1, k = 0;
	struct lista* last = NULL;
	struct lista* ant = NULL;

	printf("Digite o número de jogadores: ");
	scanf("%d", &n);

	while(n <= 1){ 
		printf("É necessário no mínimo 2 jogadores para jogar. Digite novamente: ");
		scanf("%d", &n);
	}
	for(i=1;i<=n;i++)  inicializa(&last, i); 
	
	struct lista* aux = last->next;
	
	while(1){ 
		
		ant = aux->next; 
		
		k =	insere(aux, &last); 
		
		if(k == 1) break; 
		
		aux = ant;
		
		if(j == n){ 
			printf("\n");
			imprime(last);
			j=0;
		}
		j++;
		
		if(verifica(last) == 1){ 
			printf("O vencedor = %d. Pontuacao = %d \n", last->jog, last->pontos);
			return 0;
		}
	}
	destroilista(last);
	return 0;
}


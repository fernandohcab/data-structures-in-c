#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprime(struct linhas* mat, int C, int F, int v);

// This struct saves the data

struct lista{ 
	int col; 
	char gen[1]; 
	struct lista* next;
};
 
// This struct saves the reference to the head of each line

struct linhas{
	struct lista* coluna;
};


// This funtion sets all the head with NULL value

void inicializa(struct linhas* mat, int C){
	int i;
	for(i=1;i<=C;i++) mat[i].coluna = NULL;
}

// This function sees the kind of movie watched

int verifica(char *s){
	char vet[9][2] = {"", "A", "R", "S", "C", "M", "D", "F", "P"};
	int i;
	for(i=1;i<9;i++){
		if(strcmp(s, vet[i]) == 0) return i;
	}
	return 0;
}

// This function sees if the value exists

int existe(struct lista* aux, int n){
	while(aux){
		if(aux->col == n) return 1;
		aux = aux->next;
	}
	return 0;
}

// This function inserts values into the matrix

void insere(struct linhas* mat, int C, int F){
	int i, n, j, v, maior, total[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	struct lista* aux = NULL;
	struct lista* novo = NULL;
	
	for(i=1;i<=C;i++){

		printf("Quantos filmes o cliente %d ja assistiu? ", i);
		scanf("%d", &n);
		while(n < 1 || n > F){
			printf("Numero de filmes assistido invalido. Digite outro: ");
			scanf("%d", &n);
		}
		
		for(j=1;j<=n;j++){
		
			novo = (struct lista*) malloc(sizeof(struct lista));
			novo->next = NULL;
			
			printf("Digite o numero do %do. filme assistido: ", j);
			scanf("%d", &novo->col);
			while(novo->col < 1 || novo->col > F){
				printf("Filme invalido. Digite o valor correto\n");
				printf("Digite o numero do %do. filme assistido: ", j);
				scanf("%d", &novo->col);
			}

			v = existe(mat[i].coluna, novo->col);
			while(v == 1){
				printf("Filme ja inserido. Insira outro\n");
				printf("Digite o numero do %do. filme assistido: ", j);
				scanf("%d", &novo->col);
				v = existe(mat[i].coluna, novo->col);
			}
			
			printf("Digite o genero do filme: ");
			scanf("%s", novo->gen);
			v = verifica(novo->gen);
			while(v == 0){
				printf("Genero invalido. Digite outro: ");
				scanf("%s", novo->gen);
				v = verifica(novo->gen);
			}
			total[v]++;

			if(!mat[i].coluna) mat[i].coluna = novo;
			
			else{
				aux = mat[i].coluna;
				while(aux->next) aux = aux->next;
				aux->next = novo;
			}
		}
	}
	maior = total[0];
	for(i=1;i<9;i++){
		if(maior < total[i]){
			maior = total[i];
			v = i;
		}
	}
	imprime(mat, C, F, v);
}

// This function prints the matrix

void imprime(struct linhas* mat, int C, int F, int v){ 
	char vet[9][10] = {"", "Acao", "Romance", "Suspense", "Comedia", "Musical", "Drama", "Ficcao", "Policial"};
	int i, j = 1, p;
	struct lista* aux = NULL;
	printf("\nMatriz inteira:\n");
	for(i=1;i<=C;i++){
		aux = mat[i].coluna;
		for(j=1;j<=F;j++){
			if(!aux){ 
				for(p=j;p<=F;p++) printf("0 ");
				break;
			}
			if(aux->col == j){
				printf("1 ");
				aux = aux->next;
			}
			else printf("0 ");
		}

		printf("\n");
	}

	printf("\nMatriz condensada:\n");
		
	for(i=1;i<=C;i++){
		aux = mat[i].coluna;
		printf("Cliente: %d\n   Filmes assistidos(filme e genero): \n", i);
		while(aux){
			printf("     %d    %s\n", aux->col, aux->gen);
			aux = aux->next;
		}
	}
	printf("O genero de filme mais assistido foi: %s\n", vet[v]);
}

// This function destroys the matrix

void destroilista(struct linhas* mat, int C){ 
	int i;
	struct lista *aux = NULL;
	struct lista *p = NULL;
	for(i=1;i<=C;i++){
		aux = mat[i].coluna;
		while(aux){
			p = aux->next;
			free(aux);
			aux = p;
		}
	}
}

int main(){
	int C, F;

	printf("Insira a quantidade de filmes disponiveis no catalogo: ");
	scanf("%d", &F);

	printf("Insira a quantidade de clientes do servico: ");
	scanf("%d", &C); 

	struct linhas mat[C];

	inicializa(mat, C);

	insere(mat, C, F);

	destroilista(mat, C);

	return 0;
}
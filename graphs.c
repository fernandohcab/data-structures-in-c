#include <stdio.h>
#include <string.h>

// This function puts zero on all values

void inicializa(int n, int mat[n][n]){
	int i, j;
	
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			mat[i][j] = 0;
		}
	}
}

// We insert values into the oriented graph

void insereOrientado(int n, int mat[n][n]){
	int num1, num2;
	
	while(1){

		scanf("%d", &num1);
		if(num1 == 0) break;
		while(num1 < 0 || num1 > n){
			printf("Valor invalido. Digite um valor entre 1 e %d: ", n);
			scanf("%d", &num1);
		}

		scanf("%d", &num2);
		if(num2 == 0) break;
		while(num2 < 0 || num2 > n){
			printf("Valor invalido. Digite um valor entre 1 e %d: ", n);
			scanf("%d", &num2);
		}

		mat[num1][num2] = 1;
	}
}

// This function inserts into a non oriented graph

void insereNaoOrientado(int n, int mat[n][n]){
	int num1, num2;
	
	while(1){
	
		scanf("%d", &num1);
		if(num1 == 0) break;
		while(num1 < 0 || num1 > n){
			printf("Valor invalido. Digite um valor entre 1 e %d: ", n);
			scanf("%d", &num1);
		}
	
		scanf("%d", &num2);
		if(num2 == 0) break;
		while(num2 < 0 || num2 > n){
			printf("Valor invalido. Digite um valor entre 1 e %d: ", n);
			scanf("%d", &num2);
		}
	
		mat[num1][num2] = 1;
		mat[num2][num1] = 1;
	}	
}

// This functions receive a node and prints all its adjacent nodes

void adjacencia(int n, int mat[n][n], int k){
	int j;

	printf("Os vértices adjacentes a %d são: ", k);
	
	for(j=1;j<=n;j++) if(mat[k][j] == 1) printf("%d ", j);
	
	printf("\n");

}

//This function prints the graphs

void imprime(int n, int mat[n][n]){
	int i, j;
	
	for(i=1;i<=n;i++){
	
		for(j=1;j<=n;j++){
			
			printf("%d ", mat[i][j]);
		
		}
		
		printf("\n");
	}
}

int main(){
	int n, k;
	char res[3];

	printf("Digite o numero de vertices: ");
	scanf("%d", &n);
	while(n <= 0){
		printf("Numero de vertices invalidos. Digite um numero maior que zero: ");
		scanf("%d", &n);
	}

	int mat[n][n];
	inicializa(n, mat);

	printf("O grafo é orientado? [sim/nao] ");
	scanf("%s", res);
	
	while(strcmp(res, "sim") != 0 && strcmp(res, "nao") != 0){
		printf("Comando invalido. Digite apenas sim ou nao: ");
		scanf("%s", res);
	}

	printf("Informe as conexões, digite 0 para sair.\n");
	
	if(strcmp(res, "sim") == 0) insereOrientado(n, mat);	
	else if(strcmp(res, "nao") == 0) insereNaoOrientado(n, mat);

	printf("Informe o vertice que deseja saber seus adjacentes: ");
	scanf("%d", &k);
	while(k <= 0 || k > n){
		printf("Vertice invalido. Digite um entre 1 e %d: ", n);
		scanf("%d", &k);
	}

	imprime(n, mat);
	adjacencia(n, mat, k);

	return 0;
}
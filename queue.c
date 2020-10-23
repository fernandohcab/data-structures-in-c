#include <stdio.h>
#include <stdlib.h>

struct fila{ 
	int id;
	int nota;
	char res; 
};

// This function inserts data into the queue

void insere(struct fila *alunos, int n){ 
	int i, j;
	for(i=0;i<n;i++){

		printf("Numero identificador do candidato: ");
		scanf("%d", &alunos[i].id);
		for(j=0;j<i;j++){
			while(1){
				if(alunos[i].id == alunos[j].id){
					printf("Já existe um candidato com o id %d. Digite outro:", alunos[i].id);
					scanf("%d", &alunos[i].id);	
				}
				else break;
			}
		}

		printf("Nota do candidato: ");
		scanf("%d", &alunos[i].nota);
		
		while(alunos[i].nota < 0 || alunos[i].nota > 100){ 
			printf("Nota inválida. Digite um inteiro entre 0 e 100: ");
			scanf("%d", &alunos[i].nota);
		}		

		printf("Candidato inserido\n");
	}
}

// This function sorts the values

void ordena(struct fila *alunos, int n){ 
  int i, j, min;
  struct fila aux; 
  for (i=0;i<n-1;i++){ 
    min = i; 
    for (j=i+1;j<n;j++) { 
      if(alunos[j].nota>alunos[min].nota) { 
        min = j; 
      } 
    } 
    if (i != min) { 
      aux = alunos[i]; 
      alunos[i] = alunos[min]; 
      alunos[min] = aux; 
    } 
  } 
}

// This function prints the queue

void imprimeFila(struct fila *alunos, int n){ 
	int i;
	if(!alunos) return;
	else{
		printf("----Impressão da fila----\n");
		for(i=0;i<n;i++){
			printf("Candidato %d, nota: %d\n", alunos[i].id, alunos[i].nota);
		}
	}
}

// This function prints the selected people

void imprimeResposta(struct fila *alunos, int n, int v){ 
	int j = 0;
	printf("---- Lista de novos alunos ----\n");
	while(v > 0 && j < n){
		if(alunos[j].res == 's'){
			printf("Candidato id: %d\n", alunos[j].id);
			v--;
		}
		j++;
	}
}

int main(){
	int n, v, i, j;

	printf("Digite a quantidade de candidatos: ");
	scanf("%d", &n);
	while(n <= 0){
		printf("O número deve ser maior que zero. Digite outro: ");
		scanf("%d", &n);
	}

	struct fila *alunos = (struct fila*) malloc(sizeof(struct fila));
	
	printf("Digite a quantidade de vagas: ");
	scanf("%d", &v);
	j = v;

	insere(alunos, n);

	ordena(alunos, n);

	imprimeFila(alunos, n);

	for(i=0;i<n;i++){
		printf("Resposta recebida pelo candidato de id %d (s/n): ", alunos[i].id);
		scanf("%s", &alunos[i].res);

		// We guarantee that the input is correct
		
		while(alunos[i].res != 's' && alunos[i].res != 'n'){
			printf("Resposta inválida. Digite apenas 's' ou 'n' minusculo: ");
			scanf("%s", &alunos[i].res);			
		}
		if(alunos[i].res == 's')  j--;	
		if(j == 0){
			printf("Vagas já preenchidas\n");
			break;
		}

	}

	imprimeResposta(alunos, n, v);

	free(alunos);
	
	return 0;
}
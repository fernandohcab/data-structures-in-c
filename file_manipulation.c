// File manipulation 

#include <stdio.h>
#include <string.h>

// Search the number of lines with the string we are searching

void quantidade(char nome[100]){
	
	FILE *arq;
	int i=0;
	char linha[100];
	arq = fopen("teste.txt", "r");
	
	if(!arq){
		printf("Erro ao abrir o arquivo");
		return;
	}
	
	while(!feof(arq)){
		fgets(linha, 100, arq);
		if(strcmp(linha,nome) == 0){
			i++;
			break;
		}
	}
	
	fclose(arq);
	printf("Foram encontradas %d pessoas\n", i);
}


int main(){

	FILE *arq;
	char nome[60];
	arq = fopen("teste.txt", "w");

	if(!arq){
		printf("Erro ao abrir o arquivo");
		return 1;
	}
	printf("Digite o nome: (FIM para sair)\n");

	while(1){
		scanf("%s", nome);
		if(strcmp(nome,"FIM") == 0) break;
		else{
			fprintf(arq, "%s", nome);
		}
	}

	fclose(arq);

	printf("Qual nome deseja procurar? ");
	scanf("%s", nome);

	quantidade(nome);
}

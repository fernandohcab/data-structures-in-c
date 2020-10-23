// Learning how to use structures

#include <stdio.h>
#include <stdlib.h>

struct Pessoa{
	char nome[60];
	int idade;
	float altura;
};

int main(){
	struct Pessoa *p = (struct Pessoa*) malloc(sizeof(struct Pessoa));
	
	printf("Digite o nome: ");
	scanf("%s", p->nome);

	printf("Digite a idade: ");
	scanf("%d", &p->idade);
	
	printf("Digite a altura: ");
	scanf("%f", &p->altura);

	printf("%s\n", p->nome);
	printf("%d\n", p->idade);
	printf("%.2f\n", p->altura);
	
	free(p);
	
	return 0;
}
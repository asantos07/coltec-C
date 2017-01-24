#ifndef MATRIX_INCLUDED
#define MATRIX_INCLUDED
#include <stdlib.h>

int** cria2d (int linha, int coluna)	///Cria uma matriz 2D
{
	int i;
	int **matriz;
	matriz= (int **) malloc(linha*sizeof(int *));
		if (matriz== NULL)
			printf("Erro de Alocação de Memória! (continuando)");
	for (i=0; i<linha; i++){
		matriz[i]= (int *) malloc(coluna * sizeof(int));
			if (matriz[i]== NULL)
				printf("Erro de Alocação de Memória! (continuando)");
	}
	return matriz;
}

void limpa2d (int** matriz, int linha, int coluna)	///Libera a memoria alocada na matriz 2D (pede a coluna apenas por segurança)
{
	int i;
	for(i=0; i<linha; i++)
		free(matriz[i]);
	free(matriz);
}

int*** cria3d (int linha, int coluna, int longitude)
{
	int i, j;
	int ***matriz;
	matriz= (int ***) malloc(linha*sizeof(int **));
		if (matriz== NULL)
			printf("Erro de Alocação de Memória! (continuando)");
	for (i=0; i<linha; i++){
		matriz[i]= (int **) malloc(coluna * sizeof(int));
			if (matriz[i]== NULL)
				printf("Erro de Alocação de Memória! (continuando)");
		for (j=0; j<coluna; j++){
			matriz[i][j]=(int *) malloc(longitude * sizeof(int));
				if (matriz[i][j]== NULL)
					printf("Erro de Alocação de Memória! (continuando)");
		}
	}
return matriz;
}

void limpa3d (int*** matriz, int linha, int coluna, int longitude)
{
	int i, j;
	for(i=0; i<linha; i++){
		for(j=0; j<coluna; j++){
			free(matriz[i][j]);
		}
		free(matriz[i]);
	}
	free(matriz);
}

#endif // MATRIX_INCLUDED

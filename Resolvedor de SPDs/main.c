#include <stdio.h>
#include <stdlib.h>
#include "determinant.h"
#include "lista.h"

/*void ResolverPorTeoremaDeCramer(double** matriz, char** variaveis, int N)
{
	int i, i2;
	double D = Determinant(matriz, N);

	if (D != 0)
	for (i=0; i <= N-1; i++)
	{
		double** matriz_var = (double**) malloc(N * sizeof(double*));

		for (i2=0; i2 <= N-1; i2++)
		{
			*(matriz_var + i2) = (double*) malloc(N * sizeof(double));
		}

		//Preenche a matriz

		int j;
		int j2;
		for (j=0; j <= N-1; j++)
		{
			for (j2=0; j2 <= N-1; j2++)
			{
				if (j2 == i)
					*(*(matriz_var + j) + j2) = *(*(matriz + j) + N);
				else
					*(*(matriz_var + j) + j2) = *(*(matriz + j) + j2);
			}
		}

		double var_val = Determinant(matriz_var, N) / D;
		printf(" %s: %.2lf\n", *(variaveis + i), var_val);


		for (i2=0; i2 <= N-1; i2++)
		{
			free(*(matriz_var + i2));
		}

		free(matriz_var);
	}
}*/

void copiarLinha(double* linha_fonte, double* linha_destino, int length)
{
	int i;
	for (i=0; i < length; i++)
	{
		*(linha_destino + i) = *(linha_fonte + i);
	}
}

void multiplicaLinha(double* linha, int length, double numero)
{
	int i;
	for (i=0; i < length; i++)
	{
		*(linha + i) *= numero;
	}
}

void somaLinhas(double* l1, double* l2, int length)
{
	int i;
	for (i=0; i < length; i++)
	{
		*(l1 + i) += *(l2 + i);
	}
}

void ResolverPorGauss(double** matriz, /*char***/lista variaveis, int N)
{
	int i, i2, i3;
	//Eliminar zeros da diagonal principal
	for (i=0; i <= N-1; i++)
	{
		if (*(*(matriz + i) + i) == 0)
		{
			//Troca linhas
			int trocou = -1;
			for (i2=0; i2 <= N-1; i2++)
			{
				if (i2 == i)
					continue;

				if (*(*(matriz + i2) + i) != 0 && *(*(matriz + i) + i2) != 0)
				{
					double* aux = *(matriz + i2);
					*(matriz + i2) = *(matriz + i);
					*(matriz + i) = aux;
					trocou = 1;
					break;
				}
			}

			if (!trocou)
			{
				printf("S. I.");
				return;
			}
		}
	}

	//Tornar elementos da diagonal principal 1
	for (i=0; i < N; i++)
	{
		if (*(*(matriz + i) + i) != 1)
			multiplicaLinha(*(matriz + i), N+1, 1 / *(*(matriz + i) + i));
	}

	//Zerar as colunas das variáveis
	for (i2=0; i2 < N; i2++)
	{
		for (i=0; i < N; i++)
		{
			if (*(*(matriz + i) + i2) != 0 && i != i2)
			{
				//double* linha_a_ser_somada = (double*) malloc(N+1 * sizeof(double));
				double linha_a_ser_somada[N+1];
				copiarLinha(*(matriz + i2), &linha_a_ser_somada, N+1);

				multiplicaLinha(&linha_a_ser_somada, N+1, -1 * *(*(matriz + i) + i2));

				somaLinhas(*(matriz + i), &linha_a_ser_somada, N+1);

				//free((void*)linha_a_ser_somada);

				//Tornar os elementos da diagonal principal 1
				for (i3=0; i3 < N; i3++)
				{
					if (*(*(matriz + i3) + i3) == 0)
					{
						printf("S.P.I. ou S.I.\n");
						return;
					}

					if (*(*(matriz + i3) + i3) != 1)
						multiplicaLinha(*(matriz + i3), N+1, 1 / *(*(matriz + i3) + i3));
				}
			}
		}
	}

    struct _listaNo* no = variaveis.prim;

	for (i=0; i < N; i++)
	{
        printf(" %s: %.2lf\n", (char*)no->data, *(*(matriz + i) + N));
        no = no->next;
	}
}

/*char* matrixToString(double** matrix, int N)
{
	int i, i2, stridx;
	char* string = (char*) malloc(200 * sizeof(char));

	stridx = 0;
	string[stridx] = '[';
	stridx++;

	for (i=0; i < N; i++)
	{
		string[stridx] = '[';
		stridx++;

		for (i2=0; i2 < N; i2++)
		{
			int length = snprintf(NULL, 0, "%.2lf", matrix[i][i2]);
			snprintf((string + stridx), length+1, "%.2lf", matrix[i][i2]);
			stridx += length;

			if (i2 != N-1)
			{
				string[stridx] = ',';
				stridx++;

				string[stridx] = ' ';
				stridx++;
			}
		}

		string[stridx] = ']';
		stridx++;

		string[stridx] = ',';
		stridx++;

		string[stridx] = ' ';
		stridx++;
	}

	string[stridx] = ']';
	stridx++;
	return string;
}*/

void free_strings(void* string)
{
    free(*(char**)string);
}

int main()
{
	//setbuf(stdout, NULL);
	//setbuf(stdin, NULL);
    char* filename = (char*)malloc(257 * sizeof(char));
    printf("Read from file: (filename max length: 256)\n");
    fflush(stdout);
    scanf("%s", filename);

    FILE* arquivo = fopen(filename, "r");

    if (arquivo == NULL)
        exit(-1);

    free(filename);

    //char* linha = (char*) malloc(257* sizeof(char));

    printf("==========\n");
    for (;;)
    {
        char c = fgetc(arquivo);
        while (c == '\n')
            c = fgetc(arquivo);

        ungetc(c, arquivo);

        if (c == EOF)
        {
            fclose(arquivo);
            break;
        }

        //Le a ordem (N)
        int N;

        fscanf(arquivo, "%d\n", &N);
        int i;
        int i2;

        //char** variaveis = (char**) malloc(N * sizeof(char*));
        lista variaveis;
        lista_new(&variaveis, sizeof(char*), free_strings);
        double** matriz = (double**) malloc(N * sizeof(double*));

        for (i=0; i <= N-1; i++)
        {
            *(matriz + i) = (double*)malloc((N+1) * sizeof(double));
            //*(variaveis + i) = NULL;
        }

        //Le as variaveis
        for (i=0; i <= N-1; i++)
        {
            for (i2=0; i2 <= N-1; i2++)
            {
                char buf[100];//* buf = (char*) malloc(100 * sizeof(char));//[100];
                fscanf(arquivo, "%lf", (*(matriz + i) + i2));
                //, (variaveis + i2));
                fscanf(arquivo, "%s", buf);

                if (variaveis.logicalLength == i2)//(*(variaveis + i2) == NULL)
                {
                    /**(variaveis + i2) = (char*) malloc(strlen(buf) * sizeof(char));
                    strcpy(*(variaveis + i2), buf);*/
                    lista_append(&variaveis, buf);
                }

                c = fgetc(arquivo);
                while (!((isdigit(c)) || c == '+' || c == '-' || c == '='))
                    c = fgetc(arquivo);

                ungetc(c, arquivo);
            }

            fscanf(arquivo, "= %lf", (*(matriz + i) + N));

            c = fgetc(arquivo);

            while (c != '\n' && c != EOF)
            {
                if (c < 0)
                    exit(-1);

                c = fgetc(arquivo);
            }
        }

        //ResolverPorTeoremaDeCramer(matriz, variaveis, N);
        ResolverPorGauss(matriz, variaveis, N);

        for (i=0; i <= N-1; i++)
        {
        	free(*(matriz + i));
        	//free(*(variaveis + i));
        }

        free(matriz);
		//free(variaveis);
		lista_destroy(&variaveis);

		printf("==========\n");
    }

    return 0;
}

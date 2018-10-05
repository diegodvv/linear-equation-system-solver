#include <stdio.h>
#include <stdlib.h>
#include "determinant.h"

int main()
{
    char* filename = (char*)malloc(257 * sizeof(char));
    printf("Read from file: (filename max length: %d)\n", 256);
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

        char* variaveis = (char*) malloc(N * sizeof(char));
        double** matriz = (double**) malloc(N * sizeof(double*));

        for (i=0; i <= N-1; i++)
        {
            *(matriz + i) = (double*)malloc((N+1) * sizeof(double));
        }

        //Le as variaveis
        for (i=0; i <= N-1; i++)
        {
            for (i2=0; i2 <= N-1; i2++)
            {
                fscanf(arquivo, "%lf%c ", (*(matriz + i) + i2), (variaveis + i2));
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

        //LAZY WAY TO DO IT
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
            printf(" %c: %.2lf\n", *(variaveis + i), var_val);



            for (i2=0; i2 <= N-1; i2++)
            {
                free(*(matriz_var + i2));
            }

            free(matriz_var);
        }

        free(matriz);
        free(variaveis);

        printf("==========\n");
    }

    return 0;
}
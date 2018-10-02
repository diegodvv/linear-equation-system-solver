#include <stdio.h>
#include <stdlib.h>

int main()
{
    char * filename = (char*)malloc(257 * sizeof(char));
    printf("Read from file: (filename max length: %d)\n", 256);
    scanf("%s", filename);

    FILE* arquivo = fopen(filename, "r");
    free(filename);

    char* linha = (char*) malloc(257* sizeof(char));

    //Le a ordem (N)
    int N;

    fscanf(arquivo, "%d\n", &N);
    int i;

    int* matriz = (int*) malloc(N * (N+1) * sizeof(int));
    for (i=0; i <= N-1; i++)
    {
        int i2;
        for (i2=0; i2 <= N-1; i2++)
        {
            fscanf(arquivo, "%d%c ", (matriz + i*N + i2));
        }

        fscanf(arquivo, "= %d\n", (matriz + i*N + N));
    }

    for (i=0; i <= N*N; i++){
        printf("%d\n", (matriz + i));
    }
    fclose(arquivo);
    return 0;
}

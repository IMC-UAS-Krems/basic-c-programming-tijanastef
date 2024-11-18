#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // initialize random number generator
    srand(time(NULL));
    int minrand = 1;
    int maxrand = 100;

    // first check if 2 arguments were given, check with 3 because one argument is always the program name
    if (argc != 3){
        // i used argc-1 so it is more clear, we want just two integers
        printf("Incorrect usage. You provided %d arguments. The correct number of arguments is 2", argc-1);
        return 0;
    }

    // try converting the arguments to integeres using strtol, better than atoi
    char *endptr1;
    char *endptr2;
    int first = strtol(argv[1], &endptr1, 10);
    int second = strtol(argv[2], &endptr2, 10);

    // check if the conversion worked
    if (*endptr1 != '\0' || *endptr2 != '\0') {
        printf("Incorrect usage. The parameters you provided are not positive integer");
        return 1;
    }

    // check if they are positive
    if (first < 0 || second < 0) {
        printf("Incorrect usage. The parameters you provided are not positive integers");
        return 1;
    }
    
    //  allocate memory for the matrix with "first" argument number of rows and "second" argument number of collums
    int **matrix = (int **)malloc(first * sizeof(int *));
    for (int i = 0; i < first; i++) { 
        matrix[i] = (int *)malloc(second * sizeof(int));
        for (int j = 0; j < second; j++) {
            matrix[i][j] = rand() % (maxrand - minrand + 1) + minrand;
        }
    }

    // make a file, a pointer to the file, and open the file in writing mode
    FILE *file = fopen("matrix.txt", "w");
    // check if the file can be opened
    if (!file) { 
        printf("Failed opening the file\n");
        return 1;
    }

    // write the matrix into to file following the given reqirements
    for (int i = 0; i < first; i++) {
        for (int j = 0; j < second; j++) {
            if (j == second - 1) {
                fprintf(file, "%d", matrix[i][j]);
            }
            else{
                fprintf(file, "%d ", matrix[i][j]); 
            }

        }
        if (i != first - 1){
            fprintf(file, "\n");
        }
    }

    // always close the file
    fclose(file);

    // always free allocated memory to avoid memory leaks 
    for (int i = 0; i < first; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}

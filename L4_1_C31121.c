#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

void reservar_matriz(int ***matriz, int size) {
    *matriz = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        *(*matriz + i) = (int *)malloc(size * sizeof(int));
    }
}

void liberar_matriz(int **matriz, int size) {
    for (int i = 0; i < size; i++) {
        free(*(matriz + i));
    }
    free(matriz);
}

void llenar_matriz(int **matriz, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(*(matriz + i) + j) = rand() % 2;
        }
    }
}

void imprimir_matriz(int **matriz, int size) {
    printf("Matriz %dx%d:\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf(" %d ", *(*(matriz + i) + j));
        }
        printf("\n");
    }
}

int encontrar_secuencia_maxima_zigzag(int **matriz, int size) {
    int max_secuencia = 0;
    int contador_actual = 0;
    
    for (int diagonal = 0; diagonal < 2 * size - 1; diagonal++) {
        if (diagonal % 2 == 0) {
            for (int i = 0; i <= diagonal; i++) {
                int j = diagonal - i;
                if (i < size && j < size) {
                    if (*(*(matriz + i) + j) == 1) {
                        contador_actual++;
                        if (contador_actual > max_secuencia) {
                            max_secuencia = contador_actual;
                        }
                    } else {
                        contador_actual = 0;
                    }
                }
            }
        } else {
            for (int j = size - 1; j >= 0; j--) {
                int i = diagonal - j;
                if (i >= 0 && i < size) {
                    if (*(*(matriz + i) + j) == 1) {
                        contador_actual++;
                        if (contador_actual > max_secuencia) {
                            max_secuencia = contador_actual;
                        }
                    } else {
                        contador_actual = 0;
                    }
                }
            }
        }
    }
    return max_secuencia;
}

void redimensionar_matriz(int ***matriz, int old_size, int new_size) {
    int **nueva_matriz;
    reservar_matriz(&nueva_matriz, new_size);
    
    for (int i = 0; i < new_size && i < old_size; i++) {
        for (int j = 0; j < new_size && j < old_size; j++) {
            *(*(nueva_matriz + i) + j) = *(*(*matriz + i) + j);
        }
    }
    
    if (new_size > old_size) {
        for (int i = 0; i < new_size; i++) {
            for (int j = 0; j < new_size; j++) {
                if (i >= old_size || j >= old_size) {
                    *(*(nueva_matriz + i) + j) = rand() % 2;
                }
            }
        }
    }
    
    liberar_matriz(*matriz, old_size);
    *matriz = nueva_matriz;
}

int main() {
    srand(time(NULL));
    int size, secuencia_maxima;
    int **matriz = NULL;
    char opcion;

    printf("Ingrese tamaño inicial de la matriz cuadrada: ");
    scanf("%d", &size);

    reservar_matriz(&matriz, size);
    llenar_matriz(matriz, size);
    
    do {
        imprimir_matriz(matriz, size);
        secuencia_maxima = encontrar_secuencia_maxima_zigzag(matriz, size);
        printf("La secuencia de 1s más larga es: %d\n", secuencia_maxima);

        printf("\n¿Desea cambiar el tamaño de la matriz? (S/N): ");
        scanf(" %c", &opcion);
        opcion = toupper(opcion);
        
        if (opcion == 'S') {
            int new_size;
            printf("Ingrese el nuevo tamaño de la matriz: ");
            scanf("%d", &new_size);
            
            if (new_size != size) {
                redimensionar_matriz(&matriz, size, new_size);
                size = new_size;
                printf("\nMatriz redimensionada:\n");
            } else {
                printf("\nEl tamaño es el mismo, no se redimensionó.\n");
            }
        }
    } while (opcion != 'N');

    liberar_matriz(matriz, size);
    printf("\nPrograma terminado.\n");
    return 0;
}
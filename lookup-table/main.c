#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define CORNERS 7
#define TILES 24
#define TOTAL_STATES 11022480
#define BLOCK_SIZE 5040
#define FILE_NAME "./test"

int rank_position(int *position);
int rank_orientation(int *orientation);
int factorial(int n);
void print_array(int *arr, int n);
int** create_table();

int main() {

    int i;

    int orientation_rank_ceil = pow(3, CORNERS);

    int** table = create_table();

    // loop para chamar para cada estado no bfs
    for(i = 0; i < BLOCK_SIZE; i++) {

        
    }

    FILE *f = fopen(FILE_NAME, "wb");
    if (!f) {
        perror("fopen");
        exit(1);
    }

    for(i = 0; i < TOTAL_STATES / BLOCK_SIZE; i++) {
        fwrite(table[i], sizeof(int), BLOCK_SIZE, f);
    }

    fclose(f);
}

int process_24array(int *in_array, int orientation_rank_ceil) {
    int i, j;

    // Referencia 1: quais indices do vetor de 24 inteiros representam cada posicao de corner (corner seria o que ocupa a posicao)

    // referencia de posicoes: serve para entender qual o index em temp_position e temp_orientation
    // POSITION BASE (nao se movimenta): index 5, 8 e 20 - valores no resolvido: 21, 22 e 23
    // POSITION 0: index 4, 21, 13 - valores no resolvido: 12, 13 e 14
    // POSITION 1: index 12, 23 e 1 - valores no resolvindo: 15, 16 e 17
    // POSITION 2: index 0, 22, 9 - valores no resolvindo: 18, 19 e 20
    // POSITION 3: index 16, 2 e 11 - valores no resolvindo: 3, 4 e 5
    // POSITION 4: index 7, 18, e 10 - valores no resolvindo: 6, 7, 8
    // POSITION 5: index 6, 15, 19 - valores no resolvindo: 9, 10, 11
    // POSITION 6: index 14, 3, 17 - valores no resolvindo: 0, 1, 2

    // Referencia 2: quais indices do vetor de 24 inteiros serao utilizados para representar cada corner
    // considera-se que quando resolvido, a corner tem o numero da position
    // CORNER BASE:
    // CORNER 0: 12
    // CORNER 1: 15
    // CORNER 2: 18
    // CORNER 3: 3
    // CORNER 4: 6
    // CORNER 5: 9
    // CORNER 6: 0

    // // referencia de valores: serve para entender qual corner esta em cada position (qual o valor de cada elemento no array temp_position)
    // int sample_arr[] = {
    //     1, 2, 3,
    //     4, 5, 6,
    //     7, 8, 9,
    //     10, 11, 12,
    //     13, 14, 15,
    //     16, 17, 18,
    //     19, 20, 21,
    //     22, 23, 24
    // };

    // Referencia 3: qual a orientacao de cada indice do vetor de 24 inteiros

    // referencia de orientacoes: serve para entender qual a orientacao de cada posicao de sticker (eixo x, y ou z) - apenas para os 7 corners
    char sample_orientation[] = {
        'z', 'z', 'z',
        'z', 'z', 'z',
        'z', 'z', 'x',
        'x', 'x', 'x',
        'x', 'x', 'x',
        'x', 'y', 'y',
        'y', 'y', 'y',
        'y', 'y', 'y'
    };

    // pega o vetor de 24 inteiros e separa em 7 corners (trios) - corners nao ordenadas, mas na ordem da position
    int corner_mat[CORNERS][3] = {
        {in_array[4], in_array[21], in_array[13]},    // POSITION 0
        {in_array[12], in_array[23], in_array[1]},    // POSITION 1
        {in_array[0], in_array[22], in_array[9]},     // POSITION 2
        {in_array[16], in_array[2], in_array[11]},    // POSITION 3
        {in_array[7], in_array[18], in_array[10]},    // POSITION 4
        {in_array[6], in_array[15], in_array[19]},    // POSITION 5
        {in_array[14], in_array[3], in_array[5]}      // POSITION 6
    };

    int temp_position[CORNERS];
    int temp_orientation[CORNERS];

    for(i = 0; i < CORNERS; i++) {
        for(j = 0; j < 3; j++) {
            switch(corner_mat[i][j]) {
                case 12: temp_position[i] = 0; temp_orientation[i] = sample_orientation[i*j + j] - 'x'; break;
                case 15: temp_position[i] = 1; temp_orientation[i] = sample_orientation[i*j + j] - 'x'; break;
                case 18: temp_position[i] = 2; temp_orientation[i] = sample_orientation[i*j + j] - 'x'; break;
                case 3: temp_position[i] = 3; temp_orientation[i] = sample_orientation[i*j + j] - 'x'; break;
                case 6: temp_position[i] = 4; temp_orientation[i] = sample_orientation[i*j + j] - 'x'; break;
                case 9: temp_position[i] = 5; temp_orientation[i] = sample_orientation[i*j + j] - 'x'; break;
                case 0: temp_position[i] = 6; temp_orientation[i] = sample_orientation[i*j + j] - 'x'; break;
            }
        }
    }

    print_array(temp_position, CORNERS);
    print_array(temp_orientation, CORNERS);

    // obtem a classificacao da posicao
    int position_rank = rank_position(temp_position);

    // obtem a classificacao da orientacao
    int orientation_rank = rank_orientation(temp_orientation);

    // obtem o int final
    return position_rank * orientation_rank_ceil + orientation_rank;
}

int rank_position(int *position) {
    int i, j, smaller, rank = 0;

    for(i = 0; i < CORNERS; i++) {
        smaller = 0;
        for(j = i + 1; j < CORNERS; j++) {
            if(position[j] < position[i]) {
                smaller++;
            }
        }

        rank += smaller * factorial(CORNERS - i - 1);
    }

    return rank;
}

int rank_orientation(int *orientation) {
    int i, rank = 0;
    
    for(i = 0; i < CORNERS; i++) {
        rank += orientation[i] * pow(3, CORNERS - i - 1);
    }

    return rank;
}

int factorial(int n) {
    int i, result = 1;
    for(i = 2; i < n; i++) {
        result *= i;
    }

    return result;
}

void print_array(int *arr, int n) {
    printf("\n-----\n");
    for(int i = 0; i < n; i ++) {
        printf("%d ", arr[i]);
    }
    printf("\n-----\n");
}

int** load_table() {
    int i;
    int** table = create_table();

    FILE *f = fopen(FILE_NAME, "rb");
    if (!f) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    for(i = 0; i < TOTAL_STATES / BLOCK_SIZE; i++) {
        size_t read = fread(table[i], sizeof(int), BLOCK_SIZE, f);
        if (read != BLOCK_SIZE) {
            fprintf(stderr, "Erro: bloco %d incompleto\n", i);
            exit(1);
        }
    }

}

int** create_table() {
    int i;
    // aloca o array principal
    int **main_array = (int**)malloc((TOTAL_STATES / BLOCK_SIZE) * sizeof(int*));

    // aloca cada um dos sub-arrys
    for(i = 0; i < TOTAL_STATES / BLOCK_SIZE; i++) {
        main_array[i] = (int*)malloc(BLOCK_SIZE * sizeof(int));
    }

    return main_array;
}

int** free_table(int **table) {
    int i;
    for(i = 0; i < TOTAL_STATES / BLOCK_SIZE; i++) {
        free(table[i]);
    }

    free(table);

    return NULL;
}

int access(int index, int **table) {
    return table[index / BLOCK_SIZE][index % BLOCK_SIZE];
}

int get_cost(int* array, int **table) {
    int orientation_rank_ceil = pow(3, CORNERS);
    return access(process_24array(array, orientation_rank_ceil), table);
}
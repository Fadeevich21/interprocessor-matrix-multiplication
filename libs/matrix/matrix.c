#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void init_matrix(Matrix* matrix, const SizeRow size_row, const SizeColumn size_column) {
    matrix->size_row = size_row;
    matrix->size_column = size_column;
    
    matrix->data = (MatrixData) calloc(matrix->size_row, sizeof(RowData));
    for (SizeRow index_row = 0; index_row < size_row; index_row++) {
        matrix->data[index_row] = (RowData) calloc(matrix->size_column,
                                                   sizeof(ElementData));
    }
}

Matrix create_matrix(const SizeRow size_row, const SizeColumn size_column) {
    Matrix matrix;
    init_matrix(&matrix, size_row, size_column);

    return matrix;
}

void delete_matrix(Matrix* matrix) {
    for (SizeRow index_row = 0; index_row < matrix->size_row; index_row++) {
        free(matrix->data[index_row]);
    }
    free(matrix->data);
}

void read_matrix(Matrix* matrix) {
    for (SizeRow index_row = 0; index_row < matrix->size_row; index_row++) {
        for (SizeColumn index_column = 0; index_column < matrix->size_column; index_column++) {
            scanf("%d", &(matrix->data[index_row][index_column]));
        }
    }
}

void print_matrix(const Matrix matrix) {
    for (SizeRow index_row = 0; index_row < matrix.size_row; index_row++)
    {
        for (SizeColumn index_column = 0; index_column < matrix.size_column; index_column++) {
            printf("%d ", matrix.data[index_row][index_column]);
        }
        printf("\n");
    }
}

Array get_array_column_matrix(const Matrix matrix, SizeColumn index_column) {
    Array array = create_array(matrix.size_row);
    for (SizeData i = 0; i < array.size; i++) {
        array.data[i] = matrix.data[i][index_column];
    }
    
    return array;
}

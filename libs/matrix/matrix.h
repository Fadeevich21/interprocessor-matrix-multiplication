#ifndef _MATRIX_H
#define _MATRIX_H 1

#include <stdint.h>
#include <stddef.h>
#include "../array/array.h"

typedef size_t SizeRow;
typedef size_t SizeColumn;

typedef int32_t ElementData;
typedef ElementData* RowData;
typedef RowData* MatrixData;

typedef struct Matrix {
    MatrixData data;
    SizeRow size_row;
    SizeColumn size_column;
} Matrix;

void init_matrix(Matrix* matrix,
                 const SizeRow size_row,
                 const SizeColumn size_column);

Matrix create_matrix(const SizeRow size_row,
                     const SizeColumn size_column);
void delete_matrix(Matrix* matrix);

void read_matrix(Matrix* matrix);
void print_matrix(const Matrix matrix);

Array get_array_column_matrix(const Matrix matrix, SizeColumn index_column);

#endif // _MATRIX_H
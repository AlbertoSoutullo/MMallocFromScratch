/*Authors:
-Jose Miguel Acitores Cortina
-Alberto Soutullo Rendo
3º IDCD UTAD
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <intrin.h>

#ifndef _CREATE_MATRIX_H_
#define _CREATE_MATRIX_H_

typedef struct Matrix_t
{
	int		rowNum;
	int		colNum;
	float** data;
}Matrix_t;


//Same region of memory
typedef union ufloat_t {
	__m128 data;
	float  floatData[4];
	char   chatData[16];
}ufloat_t;


//This method prepares the memory for our new Matrix. It's used on "readMatrix()"
//Can create non squared matrices
Matrix_t* createMatrix(int rowNum, int colNum);

//This method creates a new Matrix reading ir from a binary file.
//If the matrix given is transpose, transpose has to be "1"
int readMatrix(char* fileName, Matrix_t** m1, int transpose);

//This method copy to a binary file a Matrix given.
//If the matrix given is transpose, transpose has to be "1"
void writeMatrix(char* fileName, Matrix_t* m1, int transpose);

//This method will fulfill a matrix with the same value.
void createAndFillMatrix(Matrix_t** matrix, int rows, int cols, float value);

//This method will print a 4x4 matrix. Decimal lenght is 3.
void printMatrix(Matrix_t* matrix);

//This method compares 2 matrices.
int martrixComparator(Matrix_t* matrix1, Matrix_t* matrix2);

//Simple multiplication of 2 matrices.
void multiplyMatrixSimple(Matrix_t* m1, Matrix_t* m2, Matrix_t* mres);

#endif // !1

/*Authors:
-Jose Miguel Acitores Cortina
-Alberto Soutullo Rendo
3º IDCD UTAD
*/

#include "stdafx.h"
#include "MatrixUtilities.h"


Matrix_t* createMatrix(int rowNum, int colNum)
{
	Matrix_t* newMatrix;
	newMatrix		  = (Matrix_t*)mmalloc(sizeof(Matrix_t));
	if (newMatrix == NULL)
	{
		return NULL;
	}
	newMatrix->colNum = colNum;
	newMatrix->rowNum = rowNum;
	newMatrix->data   = (float**)mmalloc(sizeof(float*)*rowNum);
	if (newMatrix->data == NULL)
	{
		return NULL;
	}

	int i = 0;
	for (i = 0; i < rowNum; i++)
	{
		newMatrix->data[i] = (float*)mmalloc(sizeof(float)*colNum);
		if (newMatrix->data[i] == NULL)
		{
			return NULL;
		}

	}

	return newMatrix;
}

int readMatrix(char* fileName, Matrix_t** m1, int transpose)
{
	FILE* f1   = NULL;
	int rowNum = 0;
	int colNum = 0;

	fopen_s(&f1, fileName, "r"); 

	if (f1 == NULL)
	{
		printf("The file couldn't be open.\n");
		return 0;
	}
	else
	{
		fread(&(rowNum), sizeof(int), 1, f1);
		fread(&(colNum), sizeof(int), 1, f1);

		if (transpose)
		{
			(*m1) = createMatrix(colNum, rowNum);
			if (m1 == NULL)
			{
				printf("Not enough space. \n");
				return 2;
			}
			int i = 0;
			for (i = 0; i < (*m1)->colNum; i++)
			{
				int j = 0;
				for (j = 0; j < (*m1)->rowNum; j++)
				{
					fread(&(*m1)->data[j][i], sizeof(float), 1, f1);
				}
			}
		}
		else
		{
			(*m1) = createMatrix(rowNum, colNum);
			if (m1 == NULL)
			{
				printf("Not enough space. \n");
				return 2;
			}
			int i = 0;
			for (i = 0; i < (*m1)->rowNum; i++)
			{
				fread((*m1)->data[i], sizeof(float), (*m1)->colNum, f1);
			}
		}
		fclose(f1);
		return 1;
	}
}

void writeMatrix(char* fileName, Matrix_t* m1, int transpose)
{
	FILE* f1 = NULL;

	fopen_s(&f1, fileName, "w"); 

	if (f1 == NULL)
	{
		printf("The file couldn't be open.\n");
	}
	else
	{
		fwrite(&(m1->rowNum), sizeof(int), 1, f1);
		fwrite(&(m1->colNum), sizeof(int), 1, f1);

		if (transpose)
		{
			int i = 0;
			for (i = 0; i < m1->rowNum; i++)
			{
				int j = 0;
				for (j = 0; j < m1->rowNum; j++)
				{
					fwrite(&(m1->data[j][i]), sizeof(float), 1, f1);
				}
			}
		}
		else
		{
			int i = 0;
			for (i = 0; i < m1->rowNum; i++)
			{
				fwrite(m1->data[i], sizeof(float), m1->colNum, f1);
			}
		}
		fclose(f1);
	}
}

void createAndFillMatrix(Matrix_t** matrix, int rows, int cols, float value)
{
	int i = 0;
	int j = 0;

	(*matrix) = createMatrix(rows, cols);

	if (matrix != NULL)
	{
		for (i = 0; i < (*matrix)->rowNum; i++)
		{
			for (j = 0; j < (*matrix)->colNum; j++)
			{
				(*matrix)->data[i][j] = value;
			}
		}
	}

	
}

void printMatrix(Matrix_t* matrix)
{
	int i = 0;
	for (i = 0; i < matrix->rowNum; i++)
	{
		int j = 0;
		for (j = 0; j < matrix->colNum; j++)
		{
			printf("%0.3f ", matrix->data[i][j]);
		}
		printf("\n");
	}
}

int martrixComparator(Matrix_t* matrix1, Matrix_t* correctMatrix) 
{
	int  i = 0;
	for (i = 0; i < matrix1->rowNum; i++)
	{
		int  j = 0;
		for (j = 0; j < matrix1->colNum; j++)
		{
			if (matrix1->data[i][j] != correctMatrix->data[i][j])
			{
				return 0;
			}
		}
	}
	return 1;
}

void multiplyMatrixSimple(Matrix_t* m1, Matrix_t* m2, Matrix_t* mres) 
{
	int  i = 0;
	for (i = 0; i < m1->rowNum; i++)
	{
		int  j = 0;
		for (j = 0; j < m2->rowNum; j++)
		{
			mres->data[i][j] = 0;
			int  k = 0;
			for (k = 0; k < m1->colNum; k++)
			{
				mres->data[i][j] += m1->data[i][k] * m2->data[j][k];
			}
		}
	}

}
#include "libmmalloc\mmalloc.h"
#include "Practica1\Operations.h"
#include "Practica1\MatrixUtilities.h"
#include "Practica1\stdafx.h"
#include "Practica1\targetver.h"


int main(int argc, char** argv)
{
	int size = sizeof(char)  *1024*100;
	void* ptr_ram = (void*)malloc(size);
	init_mmalloc(ptr_ram, size);

	Matrix_t *m1 = NULL;
	Matrix_t *m2 = NULL;
	Matrix_t *mres = NULL;
	Matrix_t *mresSimple = NULL;


	//int * array = mmalloc(sizeof(int) * 10);
	//printf("0x%x\n", array);
	//mfree(array);
	//int * array1 = mmalloc(sizeof(int) * 10);
	//printf("0x%x\n", array1);
	//mfree(array1);

	if (0 == readMatrix("4x101.bin", &m1, 0))
	{
		printf("First Matrix unreadable. Try again. \n");
	}
	else if (2 == readMatrix("4x101.bin", &m1, 0))
	{
		printf("Not enough space for first matrix.\n");
	}
	else if (0 == readMatrix("10x41.bin", &m2, 1))
	{
		printf("Second Matrix unreadable. Try again. \n");
	}
	else if (2 == readMatrix("10x41.bin", &m2, 1))
	{
		printf("Not enough space for second matrix.\n");
	}
	else
	{
		if (m1->colNum < 4 || m2->colNum < 4 || m1->rowNum < 4 || m2->rowNum < 4)
		{
			printf("It has to be a minimum of 4x4. Try again. \n");
		}
		else if (m1->colNum != m2->colNum)
		{
			printf("You can not multiply these two matrix. Try again. \n");
		}
		else
		{
			createAndFillMatrix(&mres, m1->rowNum, m1->rowNum, 0);
			if (mres == NULL)
			{
				printf("Not enough space. \n");
				return 0;
			}
			createAndFillMatrix(&mresSimple, m1->rowNum, m1->rowNum, 0);
			if (mresSimple == NULL)
			{
				printf("Not enough space. \n");
				return 0;
			}
			multiplyMatrix(m1, m2, mres);
			multiplyMatrixSimple(m1, m2, mresSimple);
			if (mres->colNum <= 4 && mres->rowNum <= 4)
			{
				printf("Matrix 1: \n");
				printMatrix(m1);
				printf("Matrix 2 transposed: \n");
				printMatrix(m2);
				printf("Result with Optimization: \n");
				printMatrix(mres);
				printf("Result without Optimization: \n");
				printMatrix(mresSimple);
			}
			else printf("The result is too big to display. \n");
			if (martrixComparator(mres, mresSimple)) printf("The matrix match. \n");
			else printf("Matrix doesn't match. \n");
			writeMatrix("result.bin", mres, 0);
			mfree(m1);
			mfree(m2);
			mfree(mres);
			mfree(mresSimple);
		}
	}



























	getchar();

	/*
	init_mmalloc(
		malloc(1024*1024*10),
		1024*1024*10
	);

	int* array1 = (int*)mmalloc(sizeof(int) * 10);
	float* array2 = (float*)mmalloc(sizeof(float) * 10);
	array1[5] = 0;
	array2[6] = 0.5;

	array1 = (int*)mrealloc(array1, sizeof(int) * 20);
	mfree(array1);
	*/
	return 0;

}
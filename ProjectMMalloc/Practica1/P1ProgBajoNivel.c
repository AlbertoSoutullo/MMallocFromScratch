/*Authors:
	-Jose Miguel Acitores Cortina
	-Alberto Soutullo Rendo
	3º IDCD UTAD
*/
/*
#include "stdafx.h"
#include "MatrixUtilities.h"
#include "Operations.h"


int main()
{
	int option			= 0;
	int rowSizeM1		= 0;
	int colSizeM1		= 0;
	int rowSizeM2		= 0;
	int colSizeM2		= 0;
	float matrixValueM1 = 0;
	float matrixValueM2 = 0;

	Matrix_t *m1		 = NULL;
	Matrix_t *m2		 = NULL;
	Matrix_t *mres		 = NULL;
	Matrix_t *mresSimple = NULL;

	do
	{
		printf("What do you want to do, create 2 Matrix or read them? \n");
		printf("Select 1 if you want to manually create two Matrix\nSelect 2 if you want to read them \n");
		printf("Select 0 to exit program\n");

		scanf("%d", &option);
		fflush(stdin);
		
		//Manual creation
		if (option == 1)
		{
			printf("\nManual creation selected. \n");
			printf("Select row size, column size and values for the first matrix (minimum of 4x4): \n");
			scanf("%d %d %f", &rowSizeM1, &colSizeM1, &matrixValueM1);
			fflush(stdin);
			printf("Select row size, column size and values for the second matrix (minimum of 4x4): \n");
			scanf("%d %d %f", &rowSizeM2, &colSizeM2, &matrixValueM2);
			fflush(stdin);

			if (colSizeM1 < 4 || rowSizeM1 < 4 || colSizeM2 < 4 || rowSizeM2 < 4)
			{
				printf("It has to be a minimum of 4x4. Try again. \n");
			}
			else if (colSizeM1 != rowSizeM2)
			{
				printf("You can not multiply these two matrix. Try again. \n");
			}
			else
			{
				createAndFillMatrix(&m1,   rowSizeM1, colSizeM1, matrixValueM1);
				createAndFillMatrix(&m2,   colSizeM2, rowSizeM2, matrixValueM2);
				createAndFillMatrix(&mres, rowSizeM1, colSizeM2, 0);
				createAndFillMatrix(&mresSimple, rowSizeM1, colSizeM2, 0);
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
				free(m1);
				free(m2);
				free(mres);
				free(mresSimple);
			}
		}
		//Read Matrix from files
		else if (option == 2)
		{
			if (0 == readMatrix("Matrix1.bin", &m1, 0))
			{
				printf("First Matrix unreadable. Try again. \n");
			}
			else if (0 == readMatrix("Matrix2.bin", &m2, 1))
			{
				printf("Second Matrix unreadable. Try again. \n");
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
					createAndFillMatrix(&mresSimple, m1->rowNum, m1->rowNum, 0);
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
					free(m1);
					free(m2);
					free(mres);
					free(mresSimple);
				}
			}
		}

	} while (option != 0);

	getchar();


    return 0;
}
*/
/*Authors:
-Jose Miguel Acitores Cortina
-Alberto Soutullo Rendo
3º IDCD UTAD
*/

#include "stdafx.h"
#include "Operations.h"
#include <windows.h>


void* multiplyVector(void* args)
{
	thread_params_t* arguments = (thread_params_t*)args;

	int i = 0;
	float* alignedVector1;
	float* alignedVector2;
	ufloat_t result;
	int finalSize = 0;

	finalSize = arguments->size;
	
	if (arguments->size % 4 != 0) {
		finalSize += 4 - (arguments->size % 4);
	} 

	alignedVector1 = (float*)_aligned_malloc(sizeof(float)*finalSize, 16);
	alignedVector2 = (float*)_aligned_malloc(sizeof(float)*finalSize, 16);
	
	memset(alignedVector1, 0, sizeof(float)*finalSize);
	memset(alignedVector2, 0, sizeof(float)*finalSize);

	memcpy(alignedVector1, arguments->row, sizeof(float)*arguments->size);
	memcpy(alignedVector2, arguments->col, sizeof(float)*arguments->size);
	
	for (i = 0; i < arguments->size; i+= 4)
	{
		int aux = i * 4;
		__asm {
			MOV ecx, dword ptr[alignedVector1]//ecx from x86 
			MOV edx, dword ptr[alignedVector2]

			ADD ecx, aux
			ADD edx, aux
			//move to sse with simple precision(32 bits)
			//ps comes from "precision simple"
			MOVAPS xmm1, xmmword ptr[ecx] 
			MOVAPS xmm2, xmmword ptr[edx]
			MULPS xmm1, xmm2 

			HADDPS xmm1, xmm1
			HADDPS xmm1, xmm1
			MOVNTPS result, xmm1
		}
		*(arguments->result) += result.floatData[0];
	}
	
	_aligned_free(alignedVector1);
	_aligned_free(alignedVector2);

	_endthread();
}


void multiplyMatrix(Matrix_t* m1, Matrix_t* m2, Matrix_t* mres)
{
	int threadTotal  = 8;
	int threadAmount = 0;

	HANDLE* thread;
	thread = (HANDLE*)malloc(sizeof(HANDLE) * threadTotal);

	thread_params_t* parameters = (thread_params_t*)malloc(sizeof(thread_params_t) * threadTotal);
	
	int  i = 0;
	for (i = 0; i < m1->rowNum; i++)
	{
		int  j = 0;
		for (j = 0; j < m2->rowNum; j++)
		{
			if (threadAmount >= threadTotal)
			{
				int threadsToJoin = threadAmount;
				int  k = 0;
				for (k = 0; k < threadsToJoin; ++k)
				{
					WaitForSingleObject(thread[k], INFINITE);
					--threadAmount;
				}
			}

			parameters[threadAmount].thread_id = threadAmount;
			parameters[threadAmount].row	   = m1->data[i];
			parameters[threadAmount].col	   = m2->data[j];
			parameters[threadAmount].size	   = m1->colNum;
			parameters[threadAmount].result    = &(mres->data[i][j]);

			thread[threadAmount] = (HANDLE)_beginthreadex(NULL, 0, &multiplyVector, &parameters[threadAmount], 0, NULL);
			++threadAmount;
		}
	}

	//Remaining threads
	int threadsToJoin = threadAmount;
	int  l = 0;
	for (l = 0; l < threadsToJoin; ++l)
	{
		WaitForSingleObject(thread[l], INFINITE);
		--threadAmount;
	}

	free(thread);
	free(parameters);
}
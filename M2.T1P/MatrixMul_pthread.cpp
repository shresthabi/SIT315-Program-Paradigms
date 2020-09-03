#include "stdio.h"
#include "stdlib.h"
#include "chrono"
#include "pthread.h"

using namespace std;
#define MAX 20
#define TOTAL_THREAD 4

int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

pthread_t threads[TOTAL_THREAD];
int step_i = 0;

void* pthreadMultiplication(void* pthreadid)
{
	int core = step_i++;

	for (int i = core * MAX / TOTAL_THREAD; i < (core + 1) * MAX / TOTAL_THREAD; i++)
  {
		for (int j = 0; j < MAX; j++)
    {
			for (int k = 0; k < MAX; k++)
      {
				A[i][j] += B[i][k] * C[k][j];
      }
    }    
  }
	return NULL;
}

void buildMatrix(int matrix[MAX][MAX])
{
  for (int i = 0; i < MAX; i++)
  {
    for (int j = 0; j < MAX; j++)
    {
      printf("%i ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

int main()
{
  
  srand(time(NULL));

  for (int i = 0; i < MAX; i++)
  {
    for (int j = 0; j < MAX; j++)
    {
      B[i][j] = rand() % 20;
      C[i][j] = rand() % 20;
    }
  }

  printf("A random 20x20 matrix generated as Matrix B: \n");
  buildMatrix(B);
  printf("A random 20x20 matrix generated as Matrix C: \n");
  buildMatrix(C);

  auto start = chrono::high_resolution_clock::now();

  for (int i = 0; i < TOTAL_THREAD; i++)
  {
    int* p;
    pthread_create(&threads[i], NULL, pthreadMultiplication, (void*)(p));
  }

  for (int i = 0; i < TOTAL_THREAD; i++)
  {
    pthread_join(threads[i], NULL);
  }

  auto end = chrono::high_resolution_clock::now();

  printf("Matrix Multiplication of Matrix B and C is: \n");
  buildMatrix(A);
  
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  printf(" The time taken for matrix multiplication (execution time): %li microseconds\n", duration.count());

  return 0;
}
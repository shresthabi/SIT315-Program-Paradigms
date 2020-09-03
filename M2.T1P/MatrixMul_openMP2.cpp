#include "stdio.h"
#include "stdlib.h"
#include "chrono"
#include "omp.h"

using namespace std;
#define MAX 20 
#define TOTAL_THREAD 4

int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];


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
  omp_set_num_threads(TOTAL_THREAD);

  for (int i = 0; i < MAX; i++)
  {
    for (int j = 0; j < MAX; j++)
    {
      A[i][j] = 0;
      B[i][j] = rand() % 20;
      C[i][j] = rand() % 20;

    }
  }

  printf("A random 20x20 matrix generated as Matrix B: \n");
  buildMatrix(B);
  printf("A random 20x20 matrix generated as Matrix C: \n");
  buildMatrix(C);

  auto start = chrono::high_resolution_clock::now();

  int i, j, k;
  
  #pragma omp parallel for private(i,j,k) shared(A, B, C)	num_threads(TOTAL_THREAD)
  
    for (i = 0; i < MAX; ++i)
    {
		for (j = 0; j < MAX; ++j)
        {
			for (k = 0; k < MAX; ++k)
			{
				A[i][j] += B[i][k] * C[k][j];
			}
        }
    }

  auto end = chrono::high_resolution_clock::now();

  printf("Matrix Multiplication of Matrix B and C is: \n");
  buildMatrix(A);
  
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  printf(" The time taken for matrix multiplication (execution time): %li microseconds\n", duration.count());

  return 0;
}
#include "stdio.h"
#include "stdlib.h"
#include "chrono"
#include "omp.h"

using namespace std;
#define MAX 20 
#define TOTAL_THREAD 4

int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

void openmpMultiplication(int openmpid)
{
  for (int i = openmpid * MAX / TOTAL_THREAD; i < (openmpid + 1) * MAX / TOTAL_THREAD; i++)
  {
    for (int j = 0; j < MAX; j++)
    {
      
      for (int k = 0; k < MAX; k++)
      {
        (A[i][j]) += (B[i][k]) * (C[k][j]);
      }
    }
  }
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
  omp_set_num_threads(TOTAL_THREAD);

  for (int i = 0; i < MAX; i++)
  {
    for (int j = 0; j < MAX; j++)
    {
      B[i][j] = rand() % 20;
      C[i][j] = rand() % 20;
    }
  }

  printf("A random 20x20 matrix generated as Matrix A: \n");
  buildMatrix(B);
  printf("A random 20x20 matrix generated as Matrix B: \n");
  buildMatrix(C);

  auto start = chrono::high_resolution_clock::now();

  #pragma omp parallel
  {
    int i = omp_get_thread_num();
    openmpMultiplication(i);
  }

  auto end = chrono::high_resolution_clock::now();

  printf("Matrix Multiplication of Matrix A and B is: \n");
  buildMatrix(A);
  
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  printf(" The time taken for matrix multiplication (execution time): %li microseconds\n", duration.count());

  return 0;
}
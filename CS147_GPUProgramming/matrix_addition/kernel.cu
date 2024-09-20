#include <stdio.h>

#define TILE_SIZE 16

__global__ void matAdd(int dim, const float *A, const float *B, float* C) {

    /********************************************************************
     *
     * Compute C = A + B
     *   where A is a (dim x dim) matrix
     *   where B is a (dim x dim) matrix
     *   where C is a (dim x dim) matrix
     *
     ********************************************************************/

    /*************************************************************************/
    // INSERT KERNEL CODE HERE
    int row = blockIdx.x * blockDim.x + threadIdx.x;
    int col = blockIdx.y * blockDim.y + threadIdx.y; 

    if (row < dim && col < dim){
        C[row*dim + col] = A[row*dim + col] + B[row*dim + col];
    }

    /*************************************************************************/

}

void basicMatAdd(int dim, const float *A, const float *B, float *C)
{
    // Initialize thread block and kernel grid dimensions ---------------------
    const unsigned int BLOCK_SIZE = TILE_SIZE;
	
    /*************************************************************************/
    //INSERT CODE HERE
    const unsigned int g = ceil(dim / (float)BLOCK_SIZE);
    dim3 Gridder(g, g, 1);
    dim3 Blocker(BLOCK_SIZE, BLOCK_SIZE, 1);
    /*************************************************************************/
	
	// Invoke CUDA kernel -----------------------------------------------------
    matAdd<<<Gridder, Blocker>>>(dim, A, B, C);

    /*************************************************************************/
    //INSERT CODE HERE
	
    /*************************************************************************/

}


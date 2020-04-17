
#include <stdlib.h> 
#include <stdio.h>

// Declare Functions
void call_c(double *data, int *N, int *M);
void print_matrix(size_t N, size_t M, double matrix[N][M]);

/* Print a matrix
 * param *data: vector of data points (in R, this is a data frame,
         table structure must be restored in C)
  * param *N: The number of elements (i.e., number of "rows" in *data)
  * param *M: The number of features (i.e., number of "cols" in *data)
  * 
  * Change the input parameters to define a return value in R.
*/

void call_c(double *data, int *N, int *M) {
        
        const int n = *N; // number of data points
        const int m = *M; // number of variables per data point
        
        int m_ptr[m]; // index variable for indexing correct cols in data matrix
        double data_pts[n][m];

        // Column offsets (to convert one-dimensional array to Row/Col major)
        for(int i = 0; i < m; i++) {
                m_ptr[i] = i * n;
        }
        
        // Reconstruct the data points as N x M matrix
        for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                        data_pts[i][j] = data[m_ptr[j]++];
                }
        }
        
        printf("Input matrix: \n");
        
        print_matrix(n, m, data_pts);
        
}


/* Function to print a matrix
 * @param N Number of rows in `matrix`
 * @param M Number of columns in `matrix`
 * @param matrix The matrix to be transposed, has dimension N x M
 * @return VOID
 */ 
void print_matrix(size_t N, size_t M, double matrix[N][M]) {
        for (size_t i = 0; i < N; i++) {
                for (size_t j = 0; j < M; j++) {
                        printf(" %10g ", matrix[i][j]);
                }
                printf("\n");
        }
        printf("number of rows: %zu \nnumber of columns: %zu \n\n",
               N, M);
}

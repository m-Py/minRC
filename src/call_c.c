
#include <stdlib.h> 
#include <stdio.h>
#include <R.h>
#include <math.h>

// Declare Functions
void call_c(double *data, int *N, int *M);
void print_matrix(size_t N, size_t M, double matrix[N][M]);
double uniform_rnd_number();
double uni_rnd_number_range(double min, double max);
int random_integer(int min, int max);

// generate a random uniform number in range
double uni_rnd_number_range(double min, double max) {
    double number = uniform_rnd_number();
    return (min + number * (max - min));
};

int random_integer(int min, int max) {
    int integer = (int) floor(uniform_rnd_number() * (max - min + 1)) + min;
    return(integer);
}

double uniform_rnd_number() {
    GetRNGstate();
    double my_number = unif_rand();
    PutRNGstate();
    return(my_number);
}


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
        
        /*printf("Input matrix: \n");
        
        //print_matrix(n, m, data_pts);
        printf("Uniform number: \n");
        printf(" %g \n", uniform_rnd_number());
        printf("Integer: \n");
        printf(" %d \n", random_integer(0, 3));*/
        
        // return random integer via pointer
        *N = random_integer(0, 3);
        *data = uni_rnd_number_range(.2, .4);
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


#' Example function to call C from R
#' 
#' Takes a matrix and prints it, then exchanges two points and prints the 
#' matrix again.
#' 
#' @param data A N x M data matrix
#' 
#' @details 
#' The input argument is passed as a pointer to C. To get a return value,
#' change the data pointed to by this pointer in C.
#' 
#' @examples
#' N <- 8
#' data <- matrix(rnorm(N * 2), ncol = 2)
#' # Print a distance matrix
#' distance_matrix <- as.matrix(dist(data))
#' print_matrix(distance_matrix)
#' 
#' @return 
#' A list of length 3, containing (a) The number of rows in `data`; (b) the 
#' number of columns in `data`
#' 
#' @useDynLib minRC call_c
#' 
#' @export
#' 
#' 
print_matrix <- function(data) {

  data <- as.matrix(data)
  if (mode(data) != "numeric") {
    stop("The data must be numeric.")
  }
  
  N <- NROW(data)
  M <- NCOL(data)

  # Call C function
  .C(
    "call_c", 
    as.double(data),
    as.integer(N),
    as.integer(M),
    PACKAGE = "minRC" # important to call C
  )
}

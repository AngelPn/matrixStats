library("matrixStats")

# - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Subsetted tests
# - - - - - - - - - - - - - - - - - - - - - - - - - - - -
source("utils/validateIndicesFramework.R")
x <- matrix(runif(6 * 6, min = -3, max = 3), nrow = 6, ncol = 6)
storage.mode(x) <- "integer"

# To check names attribute
dimnames <- list(letters[1:6], LETTERS[1:6])

for (rows in index_cases) {
  for (cols in index_cases) {
    for (na.rm in c(TRUE, FALSE)) {
      validateIndicesTestMatrix(x, rows, cols,
                                ftest = rowMeans2, fsure = rowMeans,
                                na.rm = na.rm)
      validateIndicesTestMatrix(x, rows, cols,
                                fcoltest = colMeans2, fsure = rowMeans,
                                na.rm = na.rm)
      
      # Check names attribute
      dimnames(x) <- dimnames
      validateIndicesTestMatrix(x, rows, cols,
                                ftest = rowMeans2, fsure = rowMeans,
                                na.rm = na.rm)
      validateIndicesTestMatrix(x, rows, cols,
                                fcoltest = colMeans2, fsure = rowMeans,
                                na.rm = na.rm)
      dimnames(x) <- NULL
    }
  }
}

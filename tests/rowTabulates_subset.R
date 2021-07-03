library("matrixStats")

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Subsetted tests
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
source("utils/validateIndicesFramework.R")
x <- matrix(runif(6 * 6, min = -6, max = 6), nrow = 6, ncol = 6)
storage.mode(x) <- "integer"

# To check names attribute
dimnames <- list(letters[1:6], LETTERS[1:6])

for (rows in index_cases) {
  for (cols in index_cases) {
    validateIndicesTestMatrix(x, rows, cols,
                              ftest = rowTabulates, fsure = rowTabulates)
    validateIndicesTestMatrix(x, rows, cols,
                              ftest = rowTabulates, fsure = rowTabulates,
                              values = 1:3)

    validateIndicesTestMatrix(x, rows, cols,
                              ftest = colTabulates, fsure = colTabulates)
    validateIndicesTestMatrix(x, rows, cols,
                              ftest = colTabulates, fsure = colTabulates,
                              values = 1:3)
    
    # Check names attribute
    dimnames(x) <- dimnames
    validateIndicesTestMatrix(x, rows, cols,
                              ftest = rowTabulates, fsure = rowTabulates)
    validateIndicesTestMatrix(x, rows, cols,
                              ftest = rowTabulates, fsure = rowTabulates,
                              values = 1:3)
    
    validateIndicesTestMatrix(x, rows, cols,
                              ftest = colTabulates, fsure = colTabulates)
    validateIndicesTestMatrix(x, rows, cols,
                              ftest = colTabulates, fsure = colTabulates,
                              values = 1:3)
    dimnames(x) <- NULL
  }
}

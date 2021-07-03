library("matrixStats")

rowCummins_R <- function(x) {
  suppressWarnings({
    y <- t(apply(x, MARGIN = 1L, FUN = cummin))
  })
  
  # Preserve dimnames attribute
  dim(y) <- dim(x)
  dimnames <- dimnames(x)
  if (!is.null(dimnames)) dimnames(y) <- dimnames  
  
  y
}

rowCummaxs_R <- function(x) {
  mode <- storage.mode(x)
  # Change mode because a bug is detected on cummax for integer in R-3.2.0
  storage.mode(x) <- "numeric"
  suppressWarnings({
    y <- t(apply(x, MARGIN = 1L, FUN = cummax))
  })
  
  # Preserve dimnames attribute
  dim(y) <- dim(x)
  dimnames <- dimnames(x)
  if (!is.null(dimnames)) dimnames(y) <- dimnames  
  
  storage.mode(y) <- mode
  y
}


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Subsetted tests
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
source("utils/validateIndicesFramework.R")
x <- matrix(runif(6 * 6, min = -3, max = 3), nrow = 6, ncol = 6)
storage.mode(x) <- "integer"

# To check dimnames attribute
dimnames <- list(letters[1:6], LETTERS[1:6])

for (rows in index_cases) {
  for (cols in index_cases) {
    validateIndicesTestMatrix(x, rows, cols,
                              ftest = rowCummins, fsure = rowCummins_R)
    validateIndicesTestMatrix(x, rows, cols,
                              ftest = function(x, rows, cols, ...) {
      t(colCummins(t(x), rows = cols, cols = rows))
    }, fsure = rowCummins_R)

    validateIndicesTestMatrix(x, rows, cols,
                              ftest = rowCummaxs, fsure = rowCummaxs_R)
    validateIndicesTestMatrix(x, rows, cols,
                              ftest = function(x, rows, cols, ...) {
      t(colCummaxs(t(x), rows = cols, cols = rows))
    }, fsure = rowCummaxs_R)
    
    # Check dimnames attribute
    dimnames(x) <- dimnames
    validateIndicesTestMatrix(x, rows, cols,
                              ftest = rowCummins, fsure = rowCummins_R)
    validateIndicesTestMatrix(x, rows, cols,
                              ftest = function(x, rows, cols, ...) {
                                t(colCummins(t(x), rows = cols, cols = rows))
                              }, fsure = rowCummins_R)
    
    validateIndicesTestMatrix(x, rows, cols,
                              ftest = rowCummaxs, fsure = rowCummaxs_R)
    validateIndicesTestMatrix(x, rows, cols,
                              ftest = function(x, rows, cols, ...) {
                                t(colCummaxs(t(x), rows = cols, cols = rows))
                              }, fsure = rowCummaxs_R)
    dimnames(x) <- NULL
  }
}

library("matrixStats")

rowCumprods_R <- function(x) {
  suppressWarnings({
    y <- t(apply(x, MARGIN = 1L, FUN = cumprod))
  })

  # Preserve dimnames attribute
  dim(y) <- dim(x)
  dimnames <- dimnames(x)
  if (!is.null(dimnames)) dimnames(y) <- dimnames  
  
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
                              ftest = rowCumprods, fsure = rowCumprods_R)
    validateIndicesTestMatrix(x, rows, cols,
                              ftest = function(x, rows, cols, ...) {
      t(colCumprods(t(x), rows = cols, cols = rows))
    }, fsure = rowCumprods_R)
    
    # Check dimnames attribute
    dimnames(x) <- dimnames
    validateIndicesTestMatrix(x, rows, cols,
                              ftest = rowCumprods, fsure = rowCumprods_R)
    validateIndicesTestMatrix(x, rows, cols,
                              ftest = function(x, rows, cols, ...) {
                                t(colCumprods(t(x), rows = cols, cols = rows))
                              }, fsure = rowCumprods_R)
    dimnames(x) <- NULL
  }
}

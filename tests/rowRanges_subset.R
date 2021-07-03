library("matrixStats")

rowMins_R <- function(x, ...) {
  suppressWarnings({
    apply(x, MARGIN = 1L, FUN = min, ...)
  })
} # rowMins_R()

rowMaxs_R <- function(x, ...) {
  suppressWarnings({
    apply(x, MARGIN = 1L, FUN = max, ...)
  })
} # rowMaxs_R()

rowRanges_R <- function(x, ...) {
  suppressWarnings({
    ans <- t(apply(x, MARGIN = 1L, FUN = range, ...))
  })

  # Preserve rownames attribute
  dim <- c(dim(x)[1], 2L)
  if (!isTRUE(all.equal(dim(ans), dim))) {
    dim(ans) <- dim
    rownames <- rownames(x)
    if (!is.null(dimnames)) rownames(ans) <- rownames
  }
  
  ans
} # rowRanges_R()


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Subsetted tests
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
source("utils/validateIndicesFramework.R")
x <- matrix(runif(6 * 6, min = -6, max = 6), nrow = 6, ncol = 6)
storage.mode(x) <- "integer"

# To check rownames/names attributes
dimnames <- list(letters[1:6], LETTERS[1:6])

for (rows in index_cases) {
  for (cols in index_cases) {
    for (na.rm in c(TRUE, FALSE)) {
      validateIndicesTestMatrix(x, rows, cols,
                                ftest = rowRanges, fsure = rowRanges_R,
                                na.rm = na.rm)
      validateIndicesTestMatrix(x, rows, cols,
                                ftest = rowMins, fsure = rowMins_R,
                                na.rm = na.rm)
      validateIndicesTestMatrix(x, rows, cols,
                                ftest = rowMaxs, fsure = rowMaxs_R,
                                na.rm = na.rm)

      validateIndicesTestMatrix(x, rows, cols,
                                fcoltest = colRanges, fsure = rowRanges_R,
                                na.rm = na.rm)
      validateIndicesTestMatrix(x, rows, cols,
                                fcoltest = colMins, fsure = rowMins_R,
                                na.rm = na.rm)
      validateIndicesTestMatrix(x, rows, cols,
                                fcoltest = colMaxs, fsure = rowMaxs_R,
                                na.rm = na.rm)
      
      # Check rownames/names attributes
      dimnames(x) <- dimnames
      validateIndicesTestMatrix(x, rows, cols,
                                ftest = rowRanges, fsure = rowRanges_R,
                                na.rm = na.rm)
      validateIndicesTestMatrix(x, rows, cols,
                                ftest = rowMins, fsure = rowMins_R,
                                na.rm = na.rm)
      validateIndicesTestMatrix(x, rows, cols,
                                ftest = rowMaxs, fsure = rowMaxs_R,
                                na.rm = na.rm)
      
      validateIndicesTestMatrix(x, rows, cols,
                                fcoltest = colRanges, fsure = rowRanges_R,
                                na.rm = na.rm)
      validateIndicesTestMatrix(x, rows, cols,
                                fcoltest = colMins, fsure = rowMins_R,
                                na.rm = na.rm)
      validateIndicesTestMatrix(x, rows, cols,
                                fcoltest = colMaxs, fsure = rowMaxs_R,
                                na.rm = na.rm)
      dimnames(x) <- NULL
    }
  }
}

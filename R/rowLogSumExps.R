#' Accurately computes the logarithm of the sum of exponentials across rows or
#' columns
#'
#' Accurately computes the logarithm of the sum of exponentials across rows or
#' columns.
#'
#' @inheritParams rowAlls
#' @inheritParams logSumExp
#'
#' @param lx A \code{\link[base]{numeric}} NxK \code{\link[base]{matrix}}.
#' Typically \code{lx} are \eqn{log(x)} values.
#'
#' @param rows,cols A \code{\link[base]{vector}} indicating subset of rows
#' (and/or columns) to operate over. If \code{\link[base]{NULL}}, no subsetting
#' is done.
#'
#' @param na.rm If \code{\link[base:logical]{TRUE}}, any missing values are
#' ignored, otherwise not.
#'
#' @param dim. An \code{\link[base]{integer}} \code{\link[base]{vector}} of
#' length two specifying the dimension of \code{x}, also when not a
#' \code{\link[base]{matrix}}.
#' 
#' @param useNames If \code{\link[base]{NA}}, leave the default behavior of func.
#' If \code{\link[base:logical]{TRUE}}, set names of result.
#' If \code{\link[base:logical]{FALSE}}, dismiss names of result.
#'
#' @param ... Not used.
#'
#' @return A \code{\link[base]{numeric}} \code{\link[base]{vector}} of length N
#' (K).
#'
#' @section Benchmarking:
#' These methods are implemented in native code and have been optimized for
#' speed and memory.
#'
#' @author Native implementation by Henrik Bengtsson.  Original R code by
#' Nakayama ??? (Japan).
#'
#' @seealso To calculate the same on vectors, \code{\link{logSumExp}}().
#'
#' @keywords array
#' @export
rowLogSumExps <- function(lx, rows = NULL, cols = NULL, na.rm = FALSE,
                          dim. = dim(lx), ...) {
  dim. <- as.integer(dim.)
  has_na <- TRUE
  res <- .Call(C_rowLogSumExps,
               lx,
               dim., rows, cols, as.logical(na.rm), has_na, TRUE, NA)

  # Preserve names
  names <- rownames(lx)
  if (!is.null(names)) {
    if (!is.null(rows)) {
      names <- names[rows]
    }
    names(res) <- names
  }

  res
}


#' @rdname rowLogSumExps
#' @export
colLogSumExps <- function(lx, rows = NULL, cols = NULL, na.rm = FALSE,
                          dim. = dim(lx), useNames = NA, ...) {
  dim. <- as.integer(dim.)
  has_na <- TRUE

  ## Option is already set?
  useNames <- getOption("matrixStats.useNames", default = NA)
  
  res <- .Call(C_rowLogSumExps,
               lx,
               dim., rows, cols, as.logical(na.rm), has_na, FALSE, useNames)

  # Perserve names
  names <- colnames(lx)
  if (!is.null(names)){
    if (!is.null(cols))
      names <- names[cols]
  }

  # If useNames is NA, leave the default behavior as-is
  if (is.na(useNames)){
    names(res) <- names
    return(res)
  }

  # Else, check that the names are handled correctly according to the option

  # If useNames is TRUE, make sure that names have the value we expect
  if (useNames){
    if (!identical(names(res),names)){
      message("not the expected values in names")
    }
  }
  # If useNames is FALSE, make sure the names of resulting y are missing
  else{
    if (!is.null(names(res)))
      names(res) <- NULL
  }

  return(res)
}

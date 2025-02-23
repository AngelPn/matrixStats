% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/rowAlls.R
\name{rowAlls}
\alias{rowAlls}
\alias{colAlls}
\alias{allValue}
\alias{rowAnys}
\alias{colAnys}
\alias{anyValue}
\title{Checks if a value exists / does not exist in each row (column) of a matrix}
\usage{
rowAlls(x, rows = NULL, cols = NULL, value = TRUE, na.rm = FALSE,
  dim. = dim(x), ..., useNames = NA)

colAlls(x, rows = NULL, cols = NULL, value = TRUE, na.rm = FALSE,
  dim. = dim(x), ..., useNames = NA)

allValue(x, idxs = NULL, value = TRUE, na.rm = FALSE, ...)

rowAnys(x, rows = NULL, cols = NULL, value = TRUE, na.rm = FALSE,
  dim. = dim(x), ..., useNames = NA)

colAnys(x, rows = NULL, cols = NULL, value = TRUE, na.rm = FALSE,
  dim. = dim(x), ..., useNames = NA)

anyValue(x, idxs = NULL, value = TRUE, na.rm = FALSE, ...)
}
\arguments{
\item{x}{An NxK \code{\link[base]{matrix}} or, if \code{dim.} is specified,
an N * K \code{\link[base]{vector}}.}

\item{rows}{A \code{\link[base]{vector}} indicating subset of rows to
operate over. If \code{\link[base]{NULL}}, no subsetting is done.}

\item{cols}{A \code{\link[base]{vector}} indicating subset of columns to
operate over. If \code{\link[base]{NULL}}, no subsetting is done.}

\item{value}{A value to search for.}

\item{na.rm}{If \code{\link[base:logical]{TRUE}}, missing values are
excluded.}

\item{dim.}{An \code{\link[base]{integer}} \code{\link[base]{vector}} of
length two specifying the dimension of \code{x}, also when not a
\code{\link[base]{matrix}}.  \emph{Comment:} The reason for this argument
being named with a period at the end is purely technical (we get a run-time
error if we try to name it \code{dim}).}

\item{...}{Not used.}

\item{useNames}{If \code{\link[base]{NA}}, the default behavior of the 
function about naming support is remained. If \code{\link[base:logical]{FALSE}}, 
no naming support is done. Else if \code{\link[base:logical]{TRUE}}, names 
attributes of result are set.}

\item{idxs}{A \code{\link[base]{vector}} indicating subset of elements to
operate over. If \code{\link[base]{NULL}}, no subsetting is done.}
}
\value{
\code{rowAlls()} (\code{colAlls()}) returns an
\code{\link[base]{logical}} \code{\link[base]{vector}} of length N (K).
Analogously for \code{rowAnys()} (\code{rowAlls()}).
}
\description{
Checks if a value exists / does not exist in each row (column) of a matrix.
}
\details{
These functions takes either a matrix or a vector as input. If a vector,
then argument \code{dim.} must be specified and fulfill \code{prod(dim.) ==
length(x)}.  The result will be identical to the results obtained when
passing \code{matrix(x, nrow = dim.[1L], ncol = dim.[2L])}, but avoids
having to temporarily create/allocate a matrix, if only such is needed
only for these calculations.
}
\section{Logical \code{value}}{

When \code{value} is logical, the result is as if the function is applied
on \code{as.logical(x)}.  More specifically, if \code{x} is numeric, then
all zeros are treated as \code{FALSE}, non-zero values as \code{TRUE},
and all missing values as \code{NA}.
}

\examples{
x <- matrix(FALSE, nrow = 10, ncol = 5)
x[3:7, c(2, 4)] <- TRUE
x[2:4, ] <- TRUE
x[, 1] <- TRUE
x[5, ] <- FALSE
x[, 5] <- FALSE
print(x)

print(rowCounts(x))       # 1 4 4 4 0 3 3 1 1 1
print(colCounts(x))       # 9 5 3 5 0

print(rowAnys(x))
print(which(rowAnys(x)))  # 1  2  3  4  6  7  8  9 10
print(colAnys(x))
print(which(colAnys(x)))  # 1 2 3 4
}
\seealso{
rowCounts
}
\author{
Henrik Bengtsson
}
\keyword{array}
\keyword{iteration}
\keyword{logic}
\keyword{univar}

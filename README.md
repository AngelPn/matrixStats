
# matrixStats: Functions that Apply to Rows and Columns of Matrices (and to Vectors)

## Google Summer of Code (GSoC) 2021

Google Summer of Code is an initiative to support students to learn about and contribute to open-source software projects, while getting payed. The R community proposed a project on the matrixStats package and, as a student, I am interested in working on this project.

### Skill Tests
I completed all the tasks proposed on [Skill Tests](https://github.com/rstats-gsoc/gsoc2021/wiki/matrixStats#skill-tests).

- [x] 1. Easy: _Installing R packages with C code_
- [x] 2. Easy: _Git and R package testing_
- [x] 3. Easy: _Prototyping in R_
- [x] 4. Medium: _Simple support for name attributes_
- [x] 5. Medium: _A related, slightly different case_
- [x] 6. Medium/Hard: _Implement in C code_
- [x] 7. Hard: _Begin to work on the project._

### Work on the project

- Added `useNames = TRUE` implementation to every function that makes sense to support naming and wrote tests to check dimnames/names attributes. However, tests for subsets have not been added yet.

- In order to cover testing every significant case, checking for dimnames/names attributes is added above or below every testing of the functionality of a function that is already written.

- There are some functions that names are handled inconsistently between the various if-statements and the added naming support follows this incosistency:
  * [`rowWeightedMeans()`](https://github.com/AngelPn/matrixStats/blob/develop/R/rowWeightedMeans.R): If `has_weights` and `nw == 0L`, the default behavior is no naming support. If `has_weights` and `not na.rm`, the default behavior is also no naming support. Else, the default behavior is preserving name attributes.
  * [`rowVars()`](https://github.com/AngelPn/matrixStats/blob/develop/R/rowVars.R): If `is.null(center)`, the default behavior is no naming support. Else, if `ncol <= 1L`, the default behavior is also no naming support, else the default behavior is to preserve name attributes. Same for `colVars()`.
  
- Some of the functions that are used to test the results do not support naming because of `dim(res) <- dim(x)`, that removes any "dimnames" and "names" attributes. We need to keep this line for backward compatible, as came up from [Issue#11](https://github.com/HenrikBengtsson/GSOC-2021-matrixStats/issues/11#issuecomment-867113030). For this, code was added to preserve dimnames/names attributes, if the dimensions of the result differ from the initial matrix. These changes will be added to the functions that are used to test subsets, as `validateIndicesTestMatrix()` uses `all.equal()`:
  * [`tests/rowAllAnys.R`](https://github.com/AngelPn/matrixStats/blob/develop/tests/rowAllAnys.R#L9-L15).
  * [`tests/rowCumsums.R`](https://github.com/AngelPn/matrixStats/blob/develop/tests/rowCumsums.R#L9-L15).
  * [`tests/rowDiffs.R`](https://github.com/AngelPn/matrixStats/blob/develop/tests/rowDiffs.R#L16-L27).
  * [`tests/rowIQRs.R`](https://github.com/AngelPn/matrixStats/blob/develop/tests/rowIQRs.R#L13-L19).

- Issues in tests:
  1. [`tests/rowOrderStats.R`](https://github.com/AngelPn/matrixStats/blob/develop/tests/rowOrderStats.R#L58-L69): 
  ```
  > # Check names attributes
  > dimnames <- list(letters[1:3], LETTERS[1:3])
  > x <- matrix(1:9 + 0.1, nrow = 3, ncol = 3, dimnames = dimnames)
  > 
  > probs <- runif(1)
  > which <- round(probs * ncol(x))
  > 
  > y0 <- rowOrderStats_R(x, probs = probs)
  > y1 <- rowOrderStats(x, which = which, useNames = TRUE)
  Error in rowOrderStats(x, which = which, useNames = TRUE) : 
    Argument 'which' is out of range.
  Execution halted
  ```
  
- Kept name implementations DRY in [`rowAlls.R`](https://github.com/AngelPn/matrixStats/blob/develop/R/rowAlls.R#L92-L103).

- Reverted .Call(C_rowLogSumExps, ..., useNames).

- The package passes `R CMD check` with all OKs.

---

## About matrixStats

The matrixStats package provides highly optimized functions for
computing common summaries over rows and columns of matrices,
e.g. `rowQuantiles()`. There are also functions that operate on vectors,
e.g. `logSumExp()`. Their implementations strive to minimize both memory
usage and processing time. They are often remarkably faster compared
to good old `apply()` solutions. The calculations are mostly implemented
in C, which allow us to optimize beyond what is possible to do in
plain R. The package installs out-of-the-box on all common operating
systems, including Linux, macOS and Windows.

## Example
With a matrix
```r
> x <- matrix(rnorm(20 * 500), nrow = 20, ncol = 500)
```
it is [many times
faster](http://www.jottr.org/2015/01/matrixStats-0.13.1.html) to
calculate medians column by column using
```r
> mu <- matrixStats::colMedians(x)
```
than using
```r
> mu <- apply(x, MARGIN = 2, FUN = median)
```

Moreover, if performing calculations on a subset of rows and/or
columns, using
```r
> mu <- colMedians(x, rows = 33:158, cols = 1001:3000)
```
is much faster and more memory efficient than
```r
> mu <- apply(x[33:158, 1001:3000], MARGIN = 2, FUN = median)
```

## Benchmarks
For formal benchmarking of matrixStats functions relative to
alternatives, see the [Benchmark reports](https://github.com/HenrikBengtsson/matrixStats/wiki/Benchmark-reports).

## Installation
R package matrixStats is available on [CRAN](https://cran.r-project.org/package=matrixStats) and can be installed in R as:
```r
install.packages("matrixStats")
```


### Pre-release version

To install the pre-release version that is available in Git branch `develop` on GitHub, use:
```r
remotes::install_github("//github.com/AngelPn/matrixStats", ref="develop")
```
This will install the package from source.  Because of this and because this package also compiles native code, Windows users need to have [Rtools](https://cran.r-project.org/bin/windows/Rtools/) installed and macOS users need to have [Xcode](https://developer.apple.com/xcode/) installed.


<!-- pkgdown-drop-below -->

<!-- pkgdown-drop-below -->

## Contributing

To contribute to this package, please see [CONTRIBUTING.md](CONTRIBUTING.md).
 

## Software status

| Resource      | CRAN        | GitHub Actions      | Travis CI       | AppVeyor CI      |
| ------------- | ------------------- | ------------------- | --------------- | ---------------- |
| _Platforms:_  | _Multiple_          | _Multiple_          | _Linux & macOS_ | _Windows_        |
| R CMD check   | <a href="https://cran.r-project.org/web/checks/check_results_matrixStats.html"><img border="0" src="http://www.r-pkg.org/badges/version/matrixStats" alt="CRAN version"></a> | <a href="https://github.com/HenrikBengtsson/matrixStats/actions?query=workflow%3AR-CMD-check"><img src="https://github.com/HenrikBengtsson/matrixStats/workflows/R-CMD-check/badge.svg?branch=develop" alt="Build status"></a>       | <a href="https://travis-ci.org/HenrikBengtsson/matrixStats"><img src="https://travis-ci.org/HenrikBengtsson/matrixStats.svg" alt="Build status"></a>   | <a href="https://ci.appveyor.com/project/HenrikBengtsson/matrixstats"><img src="https://ci.appveyor.com/api/projects/status/github/HenrikBengtsson/matrixStats?svg=true" alt="Build status"></a> |
| Test coverage |                     |                     | <a href="https://codecov.io/gh/HenrikBengtsson/matrixStats"><img src="https://codecov.io/gh/HenrikBengtsson/matrixStats/branch/develop/graph/badge.svg" alt="Coverage Status"/></a>     |                  |


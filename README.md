
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

- [Issue#21](https://github.com/HenrikBengtsson/GSOC-2021-matrixStats/issues/21): workaround on [`rowAlls()`](https://github.com/AngelPn/matrixStats/blob/develop/R/rowAlls.R#L88-L90), [`colAlls()`](https://github.com/AngelPn/matrixStats/blob/develop/R/rowAlls.R#L147-L149), [`rowAnys()`](https://github.com/AngelPn/matrixStats/blob/develop/R/rowAlls.R#L237-L239), [`colAnys()`](https://github.com/AngelPn/matrixStats/blob/develop/R/rowAlls.R#L296-L299)

- [Issue#22](https://github.com/HenrikBengtsson/GSOC-2021-matrixStats/issues/22): Tests for `useNames = NA` added.

- [Issue#25](https://github.com/HenrikBengtsson/GSOC-2021-matrixStats/issues/25): Naming code placed right before the [matrix transpose](https://github.com/AngelPn/matrixStats/blob/develop/R/rowRanks.R#L147) and updated the package tests to also check with `perserveShape = TRUE`: [`tests/rowRanks.R`](https://github.com/AngelPn/matrixStats/blob/develop/tests/rowRanks.R#L184-L188), [`tests/rowRanks_subset.R`](https://github.com/AngelPn/matrixStats/blob/develop/tests/rowRanks_subset.R#L58-L63)

- When the result was zero length vector, in some cases, the matrixStats functions were keeping the names attributes, while the "expect" functions were not, causing `all.equal()` to give informative message: [Issue#19](https://github.com/HenrikBengtsson/GSOC-2021-matrixStats/issues/19) solved.

- There are some functions that names are handled inconsistently between the various if-statements. So, the added naming support and the functions that are used in tests follow this incosistency:
  * [`rowWeightedMeans()`](https://github.com/AngelPn/matrixStats/blob/develop/R/rowWeightedMeans.R): If `has_weights` and `nw == 0L`, the default behavior is no naming support. If `has_weights` and `not na.rm`, the default behavior is also no naming support. Else, the default behavior is preserving names attribute. The expect functions: [`rowWeightedMeans_R()`](https://github.com/AngelPn/matrixStats/blob/develop/tests/rowWeightedMeans_subset.R#L3-L16), [`colWeightedMeans_R()`](https://github.com/AngelPn/matrixStats/blob/develop/tests/rowWeightedMeans_subset.R#L18-L30)
  * [`rowVars()`](https://github.com/AngelPn/matrixStats/blob/develop/R/rowVars.R): If `is.null(center)`, the default behavior is no naming support. Else, if `ncol <= 1L`, the default behavior is also no naming support, else the default behavior is to preserve name attributes. Same for `colVars()`. The expect functions: [`rowRanks_R()`](https://github.com/AngelPn/matrixStats/blob/develop/tests/rowRanks_subset.R#L3-L13), [`colRanks_R()`](https://github.com/AngelPn/matrixStats/blob/develop/tests/rowRanks_subset.R#L15-L26). Same for `rowSds()`.

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


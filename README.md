
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

- Fixed errors from tests.

- - Re-enabled test on [`tests/rowLogSumExps.R`](https://github.com/AngelPn/matrixStats/blob/useNames-FALSE/tests/rowLogSumExps.R#L180-L181), but added `useNames = NA` argument because `useNames = FALSE` is the default.

- Revdep check the packages: `DelayedMatrixStats`, `matrixTests`, `abcrf`, one at a time to avoid [Issue#5](https://github.com/HenrikBengtsson/GSOC-2021-matrixStats/issues/5#issue-921332458).

- Not able to revdep check `sparseMatrixStats` because it failed downloading the package:
```
> revdep_check()
── INSTALL ─────────────────────────────────────────────── 2 versions ──
Installing CRAN version of matrixStats
Installing DEV version of matrixStats
── CHECK ───────────────────────────────────────────────── 1 packages ──
[0/1] 00:00:41 | ETA:  ?s | (1) sparseMatrixStats [D]Error: Failed downloading package sparseMatrixStats
```

- Revdep [README](https://github.com/AngelPn/matrixStats/blob/develop/revdep/README.md#failed-to-check-3) failed to check the three packages but no clues were given at [failures](https://github.com/AngelPn/matrixStats/blob/develop/revdep/failures.md). Also, the version is missing.

- Changed the default value of `useNames` to `FALSE` to run `R CMD check` and to identify reverse dependency packages that rely on `useNames = FALSE`.

- Written code to functions that the default behavior is not to support naming (e.g. [`rowSums2()`](https://github.com/AngelPn/matrixStats/blob/useNames-FALSE/R/rowSums2.R#L25-L31)):
```
  # Update names attributes?
  if (!is.na(useNames)) {
    if (useNames) {
      stop("useNames = TRUE is not currently implemented")
    } else {
      names(res) <- NULL
    }
  }
```

- Written code to functions that the default behavior is to preserve names attributes (e.g. [`rowLogSumExps()`](https://github.com/AngelPn/matrixStats/blob/useNames-FALSE/R/rowLogSumExps.R#L76-L87)):
```
  # Preserve names attributes?
  if (is.na(useNames) || useNames) {
    names <- colnames(lx)
    if (!is.null(names)){
      if (!is.null(cols)){
        names <- names[cols]
      }
      names(res) <- names
    }
  } else {
    names(res) <- NULL
  }
```

- Written code to functions that the default behavior is to support naming (e.g. [`rowVarDiffs()`](https://github.com/AngelPn/matrixStats/blob/useNames-FALSE/R/varDiff.R#L250-L253), [`rowWeightedMeans()`](https://github.com/AngelPn/matrixStats/blob/useNames-FALSE/R/rowWeightedMeans.R#L120-L123)):
```
  # Preserve names attributes?
  if (!(is.na(useNames) || useNames)) {
      rownames(x) <- NULL
  }
```

- Called the functions that already preserved names with `useNames = NA` when needed on tests, e.g. [`tests/rowLogSumExps()`](https://github.com/AngelPn/matrixStats/blob/useNames-FALSE/tests/rowLogSumExps.R#L56-L62).

- [`rowIQRs()`](https://github.com/AngelPn/matrixStats/blob/useNames-FALSE/R/rowIQRs.R#L30): Removed `colnames` of `Q` to solve [Issue#3](https://github.com/HenrikBengtsson/GSOC-2021-matrixStats/issues/3#issuecomment-857839472).

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


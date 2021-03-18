

<div id="badges"><!-- pkgdown markup -->
<a href="https://CRAN.R-project.org/web/checks/check_results_matrixStats.html"><img border="0" src="https://www.r-pkg.org/badges/version/matrixStats" alt="CRAN check status"></a></a>
<a href="https://github.com///github.com/AngelPn/matrixStats/actions?query=workflow%3AR-CMD-check"><img border="0" src="https://github.com///github.com/AngelPn/matrixStats/workflows/R-CMD-check/badge.svg?branch=develop" alt="Build status"></a></a>
<a href="https://travis-ci.org///github.com/AngelPn/matrixStats"><img border="0" src="https://travis-ci.org///github.com/AngelPn/matrixStats.svg" alt="Build status"></a></a>
<a href="https://ci.appveyor.com/project///github.com/AngelPn/matrixStats"><img border="0" src="https://ci.appveyor.com/api/projects/status/github///github.com/AngelPn/matrixStats?svg=true" alt="Build status"></a></a>
<a href="https://codecov.io/gh///github.com/AngelPn/matrixStats"><img border="0" src="https://codecov.io/gh///github.com/AngelPn/matrixStats/branch/develop/graph/badge.svg" alt="Coverage Status"></a></a>

</div>


# matrixStats: Functions that Apply to Rows and Columns of Matrices (and to Vectors)

## Google Summer of Code (GSoC) 2021 - Skill Tests

Google Summer of Code is an initiative to support students to learn about and contribute to open-source software projects, while getting payed. The R community proposed a project on the matrixStats package and, as a student, I am interested in working on this project. I am going to complete all the tasks proposed on [Skill Tests](https://github.com/rstats-gsoc/gsoc2021/wiki/matrixStats#skill-tests).

## Skill Tests progress

- [x] 1. Easy: _Installing R packages with C code_
- [x] 2. Easy: _Git and R package testing_
- [x] 3. Easy: _Prototyping in R_
    - Added argument `useNames = NA` to [`colMedians()`](https://github.com/AngelPn/matrixStats/blob/develop/R/rowMedians.R#L64-L65). If a non-`NA` value is passed, an informative error message shows up.

    - Written a package test that asserts that `colMedians(x, useNames = NA)` works and `colMedians(x, useNames = TRUE)` (or `FALSE`) gives the expected error in [`tests/rowMedians.R`](https://github.com/AngelPn/matrixStats/blob/develop/tests/rowMedians.R#L225-L235)

    - The package passes `R CMD check` with all OKs
        ```sh
        ── R CMD check results ──────────────────────────── matrixStats 0.58.0-9000 ────
        Duration: 3m 16.3s

        ❯ checking installed package size ... NOTE
            installed size is 10.7Mb
            sub-directories of 1Mb or more:
            libs   9.9Mb

        ❯ checking top-level files ... NOTE
        Non-standard file/directory found at top level:
            ‘CONTRIBUTING.md’

        0 errors ✔ | 0 warnings ✔ | 2 notes ✖
        ``` 
- [x] 4. Medium: _Simple support for name attributes_
    - Added handling of `matrixStats.useNames` to [`colMedians()`](https://github.com/AngelPn/matrixStats/blob/develop/R/rowMedians.R#L61-L62). My concept: Option is in high priority.

    - Written a package test that asserts that `matrixStats.useNames = NA` works and `matrixStats.useNames = TRUE` (or `FALSE`) gives the expected error in [`tests/rowMedians.R`](https://github.com/AngelPn/matrixStats/blob/develop/tests/rowMedians.R#L238-L252). I tried not to undo test 3.

    - The package passes `R CMD check` with all OKs
        ```sh
        ── R CMD check results ──────────────────────────── matrixStats 0.58.0-9000 ────
        Duration: 3m 22.6s

        ❯ checking installed package size ... NOTE
            installed size is 10.7Mb
            sub-directories of 1Mb or more:
            libs   9.9Mb

        ❯ checking top-level files ... NOTE
        Non-standard file/directory found at top level:
            ‘CONTRIBUTING.md’

        0 errors ✔ | 0 warnings ✔ | 2 notes ✖
        ```

- [x] 5. Medium: _A related, slightly different case_
    - Added naming support to [`colLogSumExps()`](https://github.com/AngelPn/matrixStats/blob/develop/R/rowLogSumExps.R#L69-L72): `useNames` can be `NA`, `TRUE` or `FALSE`. Option is in high priority.

    - Written a package test to check support naming in [`tests/rowLogSumExps.R`](https://github.com/AngelPn/matrixStats/blob/develop/tests/rowLogSumExps.R#L170-L181)

    - The package passes `R CMD check` with all OKs
        ```sh
        ── R CMD check results ──────────────────────────── matrixStats 0.58.0-9000 ────
        Duration: 3m 19.4s

        ❯ checking installed package size ... NOTE
            installed size is 10.7Mb
            sub-directories of 1Mb or more:
            libs   9.9Mb

        ❯ checking top-level files ... NOTE
        Non-standard file/directory found at top level:
            ‘CONTRIBUTING.md’

        0 errors ✔ | 0 warnings ✔ | 2 notes ✖
        ```
- [ ] 6. Medium/Hard: _Implement in C code_
    - Implemented naming support for [`colLogSumExps()`](https://github.com/AngelPn/matrixStats/blob/develop/src/rowLogSumExp.c#L46-L65) in C code, according to [template](https://github.com/HenrikBengtsson/matrixStats/pull/197)

    - Have not validate correctness yet.

- [ ] 7. Hard: _Begin to work on the project._

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

## Contributing

To contribute to this package, please see [CONTRIBUTING.md](CONTRIBUTING.md).

## Software status

| Resource      | CRAN        | GitHub Actions      | Travis CI       | AppVeyor CI      |
| ------------- | ------------------- | ------------------- | --------------- | ---------------- |
| _Platforms:_  | _Multiple_          | _Multiple_          | _Linux & macOS_ | _Windows_        |
| R CMD check   | <a href="https://cran.r-project.org/web/checks/check_results_matrixStats.html"><img border="0" src="http://www.r-pkg.org/badges/version/matrixStats" alt="CRAN version"></a> | <a href="https://github.com/HenrikBengtsson/matrixStats/actions?query=workflow%3AR-CMD-check"><img src="https://github.com/HenrikBengtsson/matrixStats/workflows/R-CMD-check/badge.svg?branch=develop" alt="Build status"></a>       | <a href="https://travis-ci.org/HenrikBengtsson/matrixStats"><img src="https://travis-ci.org/HenrikBengtsson/matrixStats.svg" alt="Build status"></a>   | <a href="https://ci.appveyor.com/project/HenrikBengtsson/matrixstats"><img src="https://ci.appveyor.com/api/projects/status/github/HenrikBengtsson/matrixStats?svg=true" alt="Build status"></a> |
| Test coverage |                     |                     | <a href="https://codecov.io/gh/HenrikBengtsson/matrixStats"><img src="https://codecov.io/gh/HenrikBengtsson/matrixStats/branch/develop/graph/badge.svg" alt="Coverage Status"/></a>     |                  |


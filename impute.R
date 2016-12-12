library(Rcpp);

sourceCpp("impute.cpp");

x <- as.integer(c(1, 2, 5, 7, 9));
y <- c(1, 1, 2, 2, 3);

xx <- 2:10;
yy <- c(1, 1.5, 1.5, 2, 2, 2, 2.5, 3, 3);
yy_hat <- impute_nei(x, y, xx);

stopifnot(yy == yy_hat);

xx <- 0:5;
yy <- c(1, 1, 1, 1.5, 1.5, 2);
yy_hat <- impute_nei(x, y, xx);

stopifnot(yy == yy_hat);


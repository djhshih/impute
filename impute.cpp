#include <Rcpp.h>
using namespace Rcpp;

// TODO use weighted mean with distance to nearest neighbours as weights

/**
 * Impute from neighbour data points.
 * Assume that data points (x, y) are sorted by x.
 * @param x   x-values at observed data points
 * @param y   y-values at observed data points
 * @param xx  x-values at points to be imputed
 * @return    y-values imputed at xx
 */
// [[Rcpp::export]]
NumericVector impute_nei(IntegerVector x, NumericVector y, IntegerVector xx) {
	size_t n = x.size();
	size_t m = xx.size();

	if (y.size() != n) {
		stop("x and y must have equal size.");
	}

	NumericVector yy(m);

	size_t i = 0;
	for (size_t ii = 0; ii < m; ++ii) {
		// find first x s.t. x >= xx
		while (i < n && x[i] < xx[ii]) ++i;
		
		if (i == n) {
			// all x <= xx
			// impute from last observed data point
			yy[ii] = y[n - 1];
		} else if (x[i] == xx[ii]) {
			// y-value is observed: no need for imputation
			yy[ii] = y[i];
		} else {
			// x[i] > xx[ii]
			// impute from the two observed data points that flank xx[i]
			size_t j = 0;
			if (i > 0) j = i - 1;
			yy[ii] = (y[j] + y[i]) / 2;
		}
	}

	return yy;
}

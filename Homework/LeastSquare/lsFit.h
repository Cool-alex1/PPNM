#ifndef HAVE_LSFIT_H
#define HAVE_LSFIT_H

#include<functional>
#include<vector>
#include<tuple>
#include"matrix.h"
#include"QR.h"

std::tuple<matrix, matrix> lsfit(const std::vector<std::function<double(double)>>& f, const std::vector<double>&, const std::vector<double>&, const std::vector<double>&);

#endif
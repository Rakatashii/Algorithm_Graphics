#ifndef util_hpp
#define util_hpp

#include <stdio.h>
#include "ccc_shap.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <cstdio>

#include <ctime>
#include <unistd.h>

//#include "stdlib.h"
#include <cstdlib>

namespace HELPERS{
    extern int stringtoint(const std::string &s);
    extern void print_vector_points(std::vector<Point> vp);
    extern void print_vector_points(std::vector<Point> vp, int from, int to);
    extern void test_coords();
    extern void print_vector_coords(std::vector<Point> vp, int line_space = -40, int width = 140);
    extern std::vector<Point> get_subvector(std::vector<Point>& vp, int from, int to);
    // Big Trade Off w/ #sleep: #sleep actually works, but at the cost of delaying the output displayed by X11. The output is really there. If you repeatedly click the X11 screen during runtime, it will definitely appear more sequential. Since I can't think of another way to illustrate the binary search functions without ~#sleep, the best solution seems to be to use #sleep sparingly, and constantly click the X11 screen when output must appear continuous.
    extern bool sleep(double milliseconds);
    extern void display_total_time_sleeping();
};

#endif /* util_hpp */

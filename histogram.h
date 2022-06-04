
#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED
#include <vector>

using namespace std;

void find_minmax(const vector<double>& numbers, double& min, double& max);
struct Input {
    vector<double> numbers;
    size_t bin_count;
};

vector<size_t> make_histogramm(Input data);


void show_histogram_text(const vector<size_t>& bins);
#endif // HISTOGRAM_H_INCLUDED

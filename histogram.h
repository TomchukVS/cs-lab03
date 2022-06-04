
#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED
#include <vector>
#include <string>

using namespace std;

void find_minmax(const vector<double>& numbers, double& min, double& max);
struct Input {
    vector<double> numbers;
    size_t bin_count;
};

vector<size_t> make_histogramm(Input data);


void show_histogram_text(const vector<size_t>& bins);
Input
download(const string& address);
Input read_input(istream& in, bool prompt);

#endif // HISTOGRAM_H_INCLUDED

#include <iostream>
#include <vector>
using namespace std;
#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED

void svg_begin(double width, double height);

void svg_end();

size_t check_size(size_t text_size);

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black");

void svg_text(double left, double baseline, string text, size_t size = 12);

void show_histogram_svg(const vector<size_t>& bins);

#endif // SVG_H_INCLUDED

#include "svg.h"
#include <vector>
#include <iostream>
using namespace std;
void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}

void svg_rect (double x, double y, double width, double height, string stroke , string fill )
{
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "'>" << "</rect>\n" ;
}

void
svg_end()
{
    cout << "</svg>\n";
}
void
show_histogram_svg(const vector<size_t>& bins)

{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    double top = 0;
    svg_begin(IMAGE_WIDTH,IMAGE_HEIGHT);

    const auto MAX_BIN_WIDTH = IMAGE_WIDTH - TEXT_WIDTH;
    size_t max_bins_width = bins[0];
    for (size_t bin : bins)
    {
        if (bin > max_bins_width)
        {
            max_bins_width = bin;
        }
    }
    max_bins_width = max_bins_width * BLOCK_WIDTH;

    for (size_t bin : bins)
    {
        double bin_width = BLOCK_WIDTH * bin;
        if (max_bins_width >= MAX_BIN_WIDTH)
        {
            bin_width = MAX_BIN_WIDTH * (bin_width / max_bins_width) - 1;
        }


    svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bins[0]));
    svg_rect(TEXT_WIDTH, 0, bins[0] * BLOCK_WIDTH, BIN_HEIGHT);
     top += BIN_HEIGHT;
    }
    svg_end();
}

#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>

using namespace std;


vector<double>
input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for(size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}
Input read_input(istream& in, bool prompt)
{
    Input data;
    size_t number_count;
    if (prompt)
    {
        cerr << "Enter number count: ";
    }
    in >> number_count;

    if(prompt)
    {
        cerr << "Enter numbers: ";
    }
    data.numbers = input_numbers(in, number_count);

    if(prompt)
    {
        cerr << "Enter bin count: ";
    }
    in >> data.bin_count;

    return data;
}



void show_histogramm_text(const vector<size_t>& bins)
{
    size_t SCREEN_WIDTH = 80;
    const size_t max_asterix = SCREEN_WIDTH - 3 - 1;

    size_t max_bin = bins[0];
    for (size_t bin: bins)
    {
        if (max_bin < bin)
        {
            max_bin = bin;
        }
    }

    for(size_t bin: bins)
    {
        size_t height = bin;

//Проверка, нужно ли масштабировать столбцы
        if (max_bin > max_asterix)
        {
            height = max_asterix * (static_cast<double>(bin) / max_bin);
        }

        if (bin < 100)
        {
            cout << ' ';
        }
        if (bin < 10)
        {
            cout << ' ';
        }
        cout << bin << "|";
        for (size_t i = 0; i < height; i++)
        {
            cout << "*";
        }
        cout << endl;
    }
}



int main(int argc, char* argv[])
{
    if(argc > 1)
    {
        curl_global_init(CURL_GLOBAL_ALL);
        CURL *curl = curl_easy_init();
        if(curl)
        {
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            if (res)
            {
                cerr << curl_easy_strerror(res) << endl;
                exit(1);
            }
        }
        return 0;
    }
}

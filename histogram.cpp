#include "histogram.h"
#include <iostream>
#include <sstream>
#include <curl/curl.h>

using namespace std;

void find_minmax(const vector<double>& numbers, double& min, double& max)
{
    if(numbers.size() == 0)
    {
        return;
    }

    min = max = numbers[0];
    for(double number : numbers)
    {
        if (min > number)
        {
            min = number;
        }
        if (max < number)
        {
            max = number;
        }
    }
}
vector<size_t> make_histogramm(Input data)
{

    const vector<double>& numbers = data.numbers;
    size_t& bin_count = data.bin_count;


    double min, max;
    find_minmax(numbers, min, max);

    vector<size_t> bins(bin_count, 0);
    double bin_size = (max - min) / bin_count;
    for (size_t i = 0; i < numbers.size(); i++)
    {
        bool found = false;
        for(size_t j = 0; j < (bin_count - 1) && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if (lo <= numbers[i] && numbers[i] < hi)
            {
                bins[j]++;
                found = true;
            }
        }
        if (!found)
        {
            bins[bin_count - 1]++;
        }
    }
    return bins;
}

void show_histogram_text(const vector<size_t>& bins)
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
vector <double> input_numbers ( istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
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
size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{

    size_t data_size=item_size*item_count;
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(reinterpret_cast< const char*>(items), data_size);
    return data_size;
}

Input
download(const string& address)
{
stringstream buffer;


curl_global_init(CURL_GLOBAL_ALL);
CURL *curl = curl_easy_init();
if(curl)
{
    char *ip;
CURLcode res;
curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
res = curl_easy_perform(curl);
if((res == CURLE_OK) && !curl_easy_getinfo(curl, CURLINFO_PRIMARY_IP, &ip) && ip) cerr << "IP:" << ip << endl;
else {

cerr << curl_easy_strerror(res) << endl;
exit(1);
}

curl_easy_cleanup(curl);
}
return read_input(buffer, false);

}

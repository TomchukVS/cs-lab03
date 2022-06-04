#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>
#include <sstream>
#include <string>
#include <windows.h>
using namespace std;


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
buffer->write(reinterpret_cast<const char*>(items), data_size);
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



int
main(int argc, char* argv[])
{
    DWORD info = GetVersion();
    printf("System info: %u or 0x%x\n", info, info);
    DWORD mask =0x0000ffff;
    DWORD version = info & mask;
    DWORD version_major = version & 0x00ff;
    DWORD version_minor = version & 0xff00;
    printf("Windows v%u.%u", version_major, version_minor);

    if((info & 0x8000'0000) == 0)
    {
        DWORD build = info >> 16;
        printf(" (build %u)\n", build);
    }
    return 0;
Input input;
if (argc > 1)
{
input = download(argv[1]);
}
else
{
input = read_input(cin, true);
}

const auto bins = make_histogramm(input);
show_histogramm_svg(bins);
}


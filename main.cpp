#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>
#include <sstream>
#include <string>
#include <windows.h>
using namespace std;





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


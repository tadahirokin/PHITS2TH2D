
#include <vector>
#include <regex>
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

using namespace std;

#define FILENAME "test.out"

TH2D *outTH2D;
TCanvas *c1;

int CountSkipLines(const char *filename)
{
    int skipLineNum = 0;

    std::ifstream file(filename);

    if (!file.is_open())
    {
        cout << "The file is not exist!!" << filename << endl;
        return 0;
    }

    std::string line;

    while (std::getline(file, line))
    {
        skipLineNum++;
        if (line.find("hc: ") == 0)
        {
            // If starting with "hc: ," stop counting.
            break;
        }
    }

    file.close();
    return skipLineNum - 1;
}

vector<std::string> SplitString(const string &input, char delimiter)
{
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = input.find(delimiter);

    while (end != std::string::npos)
    {
        tokens.push_back(input.substr(start, end - start));
        start = end + 1;
        end = input.find(delimiter, start);
    }

    tokens.push_back(input.substr(start));
    return tokens;
}

void PHITS2TH2D()
{
    int skipLineNum = CountSkipLines(FILENAME);

    std::ifstream file(FILENAME);

    if (!file.is_open())
    {
        cout << "The file is not exist !!;: " << FILENAME << endl;
        return;
    }

    string dummy;

    for (int i = 0; i < skipLineNum; i++)
    {
        getline(file, dummy);
    }

    getline(file, dummy);

    std::regex pattern("\\s+");

    cout << dummy << endl;
    dummy = std::regex_replace(dummy, pattern, " ");

    vector<string> lineSeparated = SplitString(dummy, ' ');

    cout << lineSeparated[3] << ", " << lineSeparated[5] << ", " << lineSeparated[7] << ", " << lineSeparated[11] << ", " << lineSeparated[13] << ", " << lineSeparated[15] << endl;

    double ymax = stod(lineSeparated[3]);
    double ymin = stod(lineSeparated[5]);
    double ystep = stod(lineSeparated[7]);
    int ny = (int)((ymax - ymin) / ystep);

    double xmax = stod(lineSeparated[3]);
    double xmin = stod(lineSeparated[5]);
    double ystep = stod(lineSeparated[7]);
    int nx = (int)((xmax - xml::
                        : in) /
                   ystep);

    cout << "ny = " << ny << endl;
}

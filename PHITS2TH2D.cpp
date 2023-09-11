
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

void HistoDef()
{
    char hName[40];
    char hTitle[40];
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
    dummy = std::regex_replace(dummy, pattern, " "); // Merge blanks (because the delimiter is the blank)

    vector<string> lineSeparated = SplitString(dummy, ' ');

    cout << lineSeparated[3] << ", " << lineSeparated[5] << ", " << lineSeparated[7] << ", " << lineSeparated[11] << ", " << lineSeparated[13] << ", " << lineSeparated[15] << endl;

    double ymax = stod(lineSeparated[3]);
    double ymin = stod(lineSeparated[5]);
    double ystep = stod(lineSeparated[7]);
    if (ymax < ymin)
    {
        double temp = ymax;
        ymax = ymin;
        ymin = temp;
    }
    int ny = (int)((ymax - ymin) / ystep);

    double xmin = stod(lineSeparated[11]);
    double xmax = stod(lineSeparated[13]);
    double xstep = stod(lineSeparated[15]);
    if (xmax < xmin)
    {
        double temp = xmax;
        xmax = xmin;
        xmin = temp;
    }
    int nx = (int)((xmax - xmin) / xstep);

    cout << "ny = " << ny << ", nx = " << nx << endl;

    outTH2D = new TH2D(nx, xmin, xmax, ny, ymin, ymax);

    for (int i = 0; i < ny; i++)
    {
        for (int j = 0; j < nx; j++)
        {
            double x = nx * xstep + xmin;
            double y = ny * ystep + ymin;
            double temp;
            file >> temp;
            outTH2D.Fill(x, y, temp);
        }
    }
}


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

string Blanks2Blank(string str)
{
    std::regex pattern("\\s+");
    str = std::regex_replace(str, pattern, " ");
    return str;
}

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
    TFile *outFile = new TFile("output.root", "recreate");
    TTree *tree = new TTree("tree", "tree");
    tree->Branch("outTH2D", &outTH2D);

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
    dummy = Blanks2Blank(dummy);

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
    int ny = (int)(((ymax + ystep / 2.) - (ymin - ystep / 2.)) / ystep);

    double xmin = stod(lineSeparated[11]);
    double xmax = stod(lineSeparated[13]);
    double xstep = stod(lineSeparated[15]);
    if (xmax < xmin)
    {
        double temp = xmax;
        xmax = xmin;
        xmin = temp;
    }
    int nx = (int)(((xmax + xstep / 2.) - (xmin - xstep / 2.)) / xstep);

    cout << "ny = " << ny << ", nx = " << nx << endl;

    int totalDataNum = ny * nx;
    int totalLineNum = (int)(totalDataNum / 10); // PHITS output has 10 data in a single line.

    outTH2D = new TH2D("outHist", "outHist", nx, xmin - xstep / 2., xmax + xstep / 2., ny, ymin - ystep / 2., ymax + ystep / 2.);

    int numDataCount = 0;
    double data[totalDataNum];
    for (int i = 0; i < totalLineNum; i++)
    {
        getline(file, dummy);
        dummy = Blanks2Blank(dummy);
        istringstream iss(dummy);

        for (int j = 0; j < 10; j++)
        {
            double datum;
            if (iss >> datum)
            {
                // cout << datum << ", ";

                data[numDataCount] = datum;
                numDataCount++;
            }
        }
    }

    numDataCount = 0;
    for (int i = ny; i > 0; i--)
    {
        for (int j = 0; j < nx; j++)
        {
            double x = j * xstep + xmin;
            double y = i * ystep + ymin;
            outTH2D->Fill(x, y, data[numDataCount]);
            numDataCount++;
            // cout << "x: " << x << ", y: " << y << ", val: " << data[numDataCount - 1] << endl;
        }
    }

    tree->Fill();
    outFile->Write();

    c1 = new TCanvas("c1", "c1", 800, 600);
    outTH2D->Draw("colz");

    // outFile->Close();
}
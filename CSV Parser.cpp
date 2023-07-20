//
// Created by Ilya Belov on 7/12/23.
//

#include "iostream"
#include "fstream"
#include "sstream"
#include <vector>
#include <string>
#include <iterator>

using namespace std;

class CSVRange
{
    istream&   stream;
public:
    CSVRange(istream& str)
            : stream(str)
    {}
    CSVIterator begin() const {return CSVIterator{stream};}
    CSVIterator end()   const {return CSVIterator{};}
};

int main()
{
    ifstream       file("plop.csv");

    for(auto& row: CSVRange(file))
    {
        cout << "4th Element(" << row[3] << ")\n";
    }
}
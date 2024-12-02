#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;

class Reader{
    public:
        Reader(string);
        void read();
        void print();
        int getCount();
        void sortElements();
        bool findWord(string);
        int findOccurrence(string);

    private:
        string filename;
        vector<string> words;
        int count;
};

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;

class MappedReader {
    public:
        MappedReader(string);
        void readMap();
        void printMap();
        int getCount();
        int findWord(string);
        void clean();
        void findTop10Words();
        void cmp(std::vector<std::pair<std::string, int>> &sortedWords);
        void saveMapToFile(string);
        void loadMapFromFile(string);
        vector<string> getWordsWithMinOccurrences(int);
        vector<string> getWordsWithMaxOccurrences(int);
        vector<string> getWordsStartingWith(char);

    private:
        string filename;
        map<string, int> wordMap;
        int count;
};
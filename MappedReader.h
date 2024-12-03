#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <sstream>
#include <cctype>

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

        void readSubjects();
        void printSubjects();
        void countSubjectsOccurrences();

        void printSubjectsOccurrences();
        void findMaxOccurrences();

        void analyseChapter();
        string getAnalysisData();
    private:
        string filename;
        map<string, int> wordMap;
        map<string, vector<string>> subjectsMap;
        map<string, int> subjectsOccurrences;
        int count;
};
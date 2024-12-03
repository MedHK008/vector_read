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
        void printMap() const;
        int getCount() const;
        int findWord(const string&);
        void clean();
        void findTop10Words() const;

        static void cmp(std::vector<std::pair<std::string, int>> &sortedWords);
        void saveMapToFile(const string &outputFilename) const;
        void loadMapFromFile(const string &inputFilename);
        vector<string> getWordsWithMinOccurrences(int) const;
        vector<string> getWordsWithMaxOccurrences(int) const;
        vector<string> getWordsStartingWith(char) const;

        void readSubjects();
        void printSubjects() const;
        void countSubjectsOccurrences();

        void printSubjectsOccurrences() const;
        void findMaxOccurrences() const;

        void analyseChapter();
        string getAnalysisData();
    private:
        string filename;
        map<string, int> wordMap;
        map<string, vector<string>> subjectsMap;
        map<string, int> subjectsOccurrences;
        int count;
};
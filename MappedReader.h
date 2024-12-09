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
        MappedReader(string, string);
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

        void readWordsFromFile();
        void readPatternsFromFile();
        vector<int> computeKMPTable(const vector<string>&);
        int KMPSearch(const vector<string>&, const vector<string>&);
        void countPatternsOccurrences();
        void printPatternsOccurences() const;

    private:
        string filename;
        string subStringFile;
        map<string, int> wordMap;
        map<string, vector<string>> subjectsMap;
        map<string, int> subjectsOccurrences;
        vector<string> words;
        vector<vector<string>> patterns;
        map<vector<string>, int> PatternOccurrences;
        int count;
};
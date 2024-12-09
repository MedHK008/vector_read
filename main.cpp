#include "MappedReader.h"

using namespace std;

int main(int, char**) {
    ofstream csvFile("../files/analysis.csv");
    if (!csvFile.is_open()) {
        cerr << "Failed to open analysis.csv" << endl;
        return 1;
    }

    csvFile << "File Name,Top Word,Occurrences of Top Word,Top 10 Words,Top Subject Mentioned,Occurrences in Top Subject\n";

    string file = "../files/text.txt";
    string patternFile = "../files/patterns.txt";
    MappedReader reader(file, patternFile);
    reader.readWordsFromFile();
    reader.readPatternsFromFile();
    reader.countPatternsOccurrences();
    reader.printPatternsOccurences();
    return 0;
}


#include "MappedReader.h"

using namespace std;

int main(int, char**) {
    ofstream csvFile("../analysis.csv");
    if (!csvFile.is_open()) {
        cerr << "Failed to open analysis.csv" << endl;
        return 1;
    }

    csvFile << "File Name,Top Word,Occurrences of Top Word,Top 10 Words,Top Subject Mentioned,Occurrences in Top Subject\n";

    string file = "../files/trumpArticle.txt";
    MappedReader reader(file);
    reader.analyseChapter();
    csvFile << reader.getAnalysisData() << "\n";

    csvFile.close();
    return 0;
}


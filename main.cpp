#include "MappedReader.h"

using namespace std;
namespace fs = std::filesystem;

bool isNumber(const string& str) {
    for (char const &c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

void chapterSeparator() {
    ifstream file("../words.txt");
    if (!file.is_open()) {
        cerr << "Failed to open words.txt" << endl;
        return;
    }
    fs::create_directory("../chapters");
    string line;
    int chapter = 0;
    ofstream chapterFile;
    while (getline(file, line)) {
        if (isNumber(line)) {
            if (chapterFile.is_open()) {
                chapterFile.close();
            }
            chapter++;
            chapterFile.open("../chapters/chapter" + to_string(chapter) + ".txt");
            if (!chapterFile.is_open()) {
                cerr << "Failed to create chapter file" << endl;
                return;
            }
        }
        if (chapterFile.is_open()) {
            chapterFile << line << endl;
        }
    }

    if (chapterFile.is_open()) {
        chapterFile.close();
    }

    file.close();
}

int main(int, char**) {
    ofstream csvFile("../analysis.csv");
    if (!csvFile.is_open()) {
        cerr << "Failed to open analysis.csv" << endl;
        return 1;
    }

    csvFile << "File Name,Top Word,Occurrences of Top Word,Top 10 Words,Top Subject Mentioned,Occurrences in Top Subject\n";

        string file = "../text.txt";
        MappedReader reader(file);
        reader.analyseChapter();
        csvFile << reader.getAnalysisData() << "\n";

    csvFile.close();
    return 0;
}


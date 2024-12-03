#include "MappedReader.h"

MappedReader::MappedReader(string file) : filename(file), count(0) {}

void MappedReader::readMap() {
    ifstream file(filename);
    string word;
    while (file >> word) {
        for (char &c : word) {
            c = tolower(c);
        }
        wordMap[word]++;
        count++;
    }
    file.close();
}

void MappedReader::printMap() {
    for (const auto &pair : wordMap) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

int MappedReader::getCount() {
    return count;
}

int MappedReader::findWord(string word) {
    return wordMap[word];
}

void MappedReader::clean() {
    map<string, int> cleanedMap;
    for (auto &pair : wordMap) {
        string cleanedWord;
        for (char c : pair.first) {
            if (isalnum(c)) {
                cleanedWord += c;
            }
        }
        cleanedMap[cleanedWord] += pair.second;
    }
    wordMap = cleanedMap;
    map<string, int> cleanedMap2;
    for (const auto &pair : wordMap) {
        if (pair.first.size() > 4) {
            cleanedMap2[pair.first] = pair.second;
        }
    }
    wordMap = cleanedMap2;
}

void MappedReader::findTop10Words() {
    vector<pair<string, int>> sortedWords;
    for (auto pair : wordMap)
        sortedWords.push_back(pair);
    cmp(sortedWords);
    for (int i = 0; i < 10 && i < sortedWords.size(); i++)
        cout << sortedWords[i].first << " " << sortedWords[i].second << endl;
}

void MappedReader::cmp(std::vector<std::pair<std::string, int>> &sortedWords) {
    sort(sortedWords.begin(), sortedWords.end(), [](pair<string, int> a, pair<string, int> b) {
        return a.second > b.second;
    });
}

void MappedReader::saveMapToFile(string outputFilename) {
    ofstream outFile(outputFilename);
    for (const auto &pair : wordMap) {
        outFile << pair.first << " " << pair.second << endl;
    }
    outFile.close();
}

void MappedReader::loadMapFromFile(string inputFilename) {
    ifstream inFile(inputFilename);
    string word;
    int count;
    while (inFile >> word >> count) {
        wordMap[word] = count;
    }
    inFile.close();
}


vector<string> MappedReader::getWordsWithMinOccurrences(int minOccurrences) {
    vector<string> result;
    for (const auto &pair : wordMap) {
        if (pair.second >= minOccurrences) {
            result.push_back(pair.first);
        }
    }
    return result;
}

vector<string> MappedReader::getWordsWithMaxOccurrences(int maxOccurrences) {
    vector<string> result;
    for (const auto &pair : wordMap) {
        if (pair.second <= maxOccurrences) {
            result.push_back(pair.first);
        }
    }
    return result;
}

vector<string> MappedReader::getWordsStartingWith(char letter) {
    vector<string> result;
    for (const auto &pair : wordMap) {
        if (pair.first[0] == letter) {
            result.push_back(pair.first);
        }
    }
    return result;
}

void MappedReader::readSubjects()
{
    ifstream file("subject.txt");
    string word;
    vector<string> subjects;
    while (getline(file, word)) {
        istringstream iss(word);
        string subject;
        iss >> subject;
        vector<string> associatedWords;
        string associatedWord;
        for(char &c : subject)
        {
            c = tolower(c);
        }
        while (iss >> associatedWord) {
            for(char &c : associatedWord)
            {
                c = tolower(c);
            }
            associatedWords.push_back(associatedWord);
        }
        subjectsMap[subject] = associatedWords;
    }
}

void MappedReader::printSubjects()
{
    for (const auto &pair : subjectsMap) {
        cout << pair.first << ": ";
        for (const auto &word : pair.second)
            cout << word << " ";
        cout << endl;
    }
}

void MappedReader::countSubjectsOccurrences()
{
    int subjectCount = 0;
    for(const auto &subject : subjectsMap)
    {
        for(const auto &pair : wordMap)
            if(find(subject.second.begin(), subject.second.end(), pair.first) != subject.second.end())
                subjectCount++;
        subjectsOccurrences[subject.first] = subjectCount;
        subjectCount = 0;
    }
}

void MappedReader::printSubjectsOccurrences()
{
    for(const auto &pair : subjectsOccurrences)
        cout << pair.first << " mentionned : " << pair.second << endl;
}

void MappedReader::findMaxOccurrences()
{
    int max = 0;
    string maxSubject;
    for(const auto &pair : subjectsOccurrences)
    {
        if(pair.second > max)
        {
            max = pair.second;
            maxSubject = pair.first;
        }
    }
    cout << "The subject mentionned the most is " << maxSubject << " with " << max << " mentions." << endl;
}

string MappedReader::getAnalysisData() {
    vector<pair<string, int>> sortedWords;
    for (auto pair : wordMap)
        sortedWords.push_back(pair);
    cmp(sortedWords);

    string topWord = sortedWords.empty() ? "" : sortedWords[0].first;
    int topWordCount = sortedWords.empty() ? 0 : sortedWords[0].second;

    int max = 0;
    string maxSubject;
    for (const auto &pair : subjectsOccurrences) {
        if (pair.second > max) {
            max = pair.second;
            maxSubject = pair.first;
        }
    }

    stringstream ss;
    ss << filename << "," << topWord << "," << topWordCount << ",";
    for (int i = 0; i < 10 && i < sortedWords.size(); i++) {
        ss << sortedWords[i].first;
        if (i < 9 && i < sortedWords.size() - 1) {
            ss << ";";
        }
    }
    ss << "," << maxSubject << "," << max;
    return ss.str();
}

void MappedReader::analyseChapter() {
    readMap();
    clean();
    findTop10Words();
    saveMapToFile("output.txt");
    readSubjects();
    countSubjectsOccurrences();
    printSubjectsOccurrences();
    findMaxOccurrences();
}

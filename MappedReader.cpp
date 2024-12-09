#include "MappedReader.h"

#include <utility>

MappedReader::MappedReader(string file,string PatternFile) : filename(std::move(file)), count(0) {}

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

void MappedReader::printMap() const {
    for (const auto &[fst, snd] : wordMap) {
        cout << fst << ": " << snd << endl;
    }
}

int MappedReader::getCount() const {
    return count;
}

int MappedReader::findWord(const string& word) {
    return wordMap[word];
}

void MappedReader::clean() {
    map<string, int> cleanedMap;
    for (auto &[fst, snd] : wordMap) {
        string cleanedWord;
        for (const char c : fst) {
            if (isalpha(c)) {
                cleanedWord += c;
            }
        }
        cleanedMap[cleanedWord] += snd;
    }
    wordMap = cleanedMap;
    map<string, int> cleanedMap2;
    for (const auto &[fst, snd] : wordMap) {
        if (fst.size() > 4) {
            cleanedMap2[fst] = snd;
        }
    }
    wordMap = cleanedMap2;
}

void MappedReader::findTop10Words() const {
    vector<pair<string, int>> sortedWords;
    for (const auto& pair : wordMap)
        sortedWords.emplace_back(pair);
    cmp(sortedWords);
    for (int i = 0; i < 10 && i < sortedWords.size(); i++)
        cout << sortedWords[i].first << " " << sortedWords[i].second << endl;
}

void MappedReader::cmp(std::vector<std::pair<std::string, int>> &sortedWords) {
    sort(sortedWords.begin(), sortedWords.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });
}

void MappedReader::saveMapToFile(const string& outputFilename) const {
    ofstream outFile(outputFilename);
    for (const auto &[fst, snd] : wordMap) {
        outFile << fst << " " << snd << endl;
    }
    outFile.close();
}

void MappedReader::loadMapFromFile(const string& inputFilename) {
    ifstream inFile(inputFilename);
    string word;
    int count;
    while (inFile >> word >> count) {
        wordMap[word] = count;
    }
    inFile.close();
}

vector<string> MappedReader::getWordsWithMinOccurrences(int minOccurrences) const {
    vector<string> result;
    for (const auto &pair : wordMap) {
        if (pair.second >= minOccurrences) {
            result.push_back(pair.first);
        }
    }
    return result;
}

vector<string> MappedReader::getWordsWithMaxOccurrences(int maxOccurrences) const {
    vector<string> result;
    for (const auto &pair : wordMap) {
        if (pair.second <= maxOccurrences) {
            result.push_back(pair.first);
        }
    }
    return result;
}

vector<string> MappedReader::getWordsStartingWith(char letter) const {
    vector<string> result;
    for (const auto &[fst, snd] : wordMap) {
        if (fst[0] == letter) {
            result.push_back(fst);
        }
    }
    return result;
}

void MappedReader::readSubjects()
{
    ifstream file("../files/subject.txt");
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

void MappedReader::printSubjects() const {
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
                subjectCount+= pair.second;
        subjectsOccurrences[subject.first] = subjectCount;
        subjectCount = 0;
    }
}

void MappedReader::printSubjectsOccurrences() const {
    for(const auto &[fst, snd] : subjectsOccurrences)
        cout << fst << " mentioned : " << snd << endl;
}

void MappedReader::findMaxOccurrences() const {
    int max = 0;
    string maxSubject;
    for(const auto &[fst, snd] : subjectsOccurrences)
    {
        if(snd > max)
        {
            max = snd;
            maxSubject = fst;
        }
    }
    cout << "The subject mentioned the most is " << maxSubject << " with " << max << " mentions." << endl;
}

string MappedReader::getAnalysisData() {
    vector<pair<string, int>> sortedWords;
    sortedWords.reserve(wordMap.size());
    for (const auto& pair : wordMap)
            sortedWords.emplace_back(pair);
    cmp(sortedWords);

    string topWord = sortedWords.empty() ? "" : sortedWords[0].first;
    int topWordCount = sortedWords.empty() ? 0 : sortedWords[0].second;

    int max = 0;
    string maxSubject;
    for (const auto &[fst, snd] : subjectsOccurrences) {
        if (snd > max) {
            max = snd;
            maxSubject = fst;
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
    string outputFilename = "../files/"+filename+"output.txt";
    saveMapToFile(outputFilename);
    readSubjects();
    countSubjectsOccurrences();
    printSubjectsOccurrences();
    findMaxOccurrences();
}

void MappedReader::readWordsFromFile() {
    ifstream file(filename);
    string word;
    while (file >> word) {
        for (char &c : word) {
            c = tolower(c);
        }
        words.push_back(word);
    }
}

void MappedReader::readPatternsFromFile() {
    ifstream file(subStringFile);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string word;
        vector<string> pattern;
        while (iss >> word) {
            for (char &c : word) {
                c = tolower(c);
            }
            pattern.push_back(word);
        }
        patterns.push_back(pattern);
    }
}

vector<int> MappedReader::computeKMPTable(const vector<string>& pattern) {
    vector<int> table(pattern.size(), 0);
    int j = 0;
    for (int i = 1; i < pattern.size(); i++) {
        if (pattern[i] == pattern[j]) {
            j++;
            table[i] = j;
        } else {
            if (j != 0) {
                j = table[j - 1];
                i--;
            } else {
                table[i] = 0;
            }
        }
    }
    return table;
}

int MappedReader::KMPSearch(const vector<string>& text, const vector<string>& pattern) {
    vector<int> table = computeKMPTable(pattern);
    int i = 0, j = 0;
    int count = 0;
    while (i < text.size()) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == pattern.size()) {
            count++;
            j = table[j - 1];
        } else if (i < text.size() && pattern[j] != text[i]) {
            if (j != 0) {
                j = table[j - 1];
            } else {
                i++;
            }
        }
    }
    return count;
}

void MappedReader::countPatternsOccurrences() {
    map<vector<string>, int> patternOccurrences;
    for (const auto& pattern : patterns) {
        int count = KMPSearch(words, pattern);
        patternOccurrences[pattern] = count;
    }
}

void MappedReader::printPatternsOccurences() const {
    for (const auto& [fst, snd] : PatternOccurrences) {
        cout << "Pattern: ";
        for (const auto& word : fst) {
            cout << word << " ";
        }
        cout << "occurs " << snd << " times." << endl;
    }
}
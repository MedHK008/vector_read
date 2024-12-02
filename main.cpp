#include "Reader.h"
#include "MappedReader.h"
#include <chrono>

int main(int, char**){
    
    auto start = std::chrono::high_resolution_clock::now();
    // Reader reader("words.txt");
    // reader.read();

    // cout << "Number of words: " << reader.getCount() << endl;

    // reader.findWord("the");

    // cout << "Number of occurrences of 'the': " << reader.findOccurrence("the") << endl;

    MappedReader mappedReader("words.txt");
    mappedReader.readMap();
    mappedReader.clean();
    cout << "Number of words: " << mappedReader.getCount() << endl;
    cout << "Number of occurrences of 'the': " << mappedReader.findWord("the") << endl;


    mappedReader.findTop10Words();
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    cout << "Time taken by function: " << duration.count() << " milliseconds" << endl;

    mappedReader.saveMapToFile("word_map.txt");
    mappedReader.loadMapFromFile("word_map.txt");

    vector<string> minOccurrencesWords = mappedReader.getWordsWithMinOccurrences(5);
    cout << "Words with at least 5 occurrences: ";
    for (const auto &word : minOccurrencesWords) {
        cout << word << " ";
    }
    cout << endl;

    vector<string> maxOccurrencesWords = mappedReader.getWordsWithMaxOccurrences(2);
    cout << "Words with at most 2 occurrences: ";
    for (const auto &word : maxOccurrencesWords) {
        cout << word << " ";
    }
    cout << endl;

    vector<string> wordsStartingWithT = mappedReader.getWordsStartingWith('t');
    cout << "Words starting with 't': ";
    for (const auto &word : wordsStartingWithT) {
        cout << word << " ";
    }
    cout << endl;

    return 0;
}

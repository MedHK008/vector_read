#include "Reader.h"

Reader::Reader(string filename): filename(filename),count(0){}

void Reader::read()
{
    ifstream file(filename);
    string word;
    while(file >> word)
    {
        words.push_back(word);
        count++;
    }
    file.close();
}

void Reader::print()
{
    for(auto word: words)
    {
        cout << word << endl;
    }
}

void Reader::sortElements()
{
    sort(words.begin(), words.end());
}

bool Reader::findWord(string SearchWord)
{
    for(auto word: words)
    {
        if(word == SearchWord)
        {
            cout << "Found the word " << endl;
            return true;
        }
    }
    cout << "Word not found" << endl;
    return false;
}

int Reader::findOccurrence(string SearchWord)
{
    int count = 0;
    for(auto word: words)
    {
        if(word == SearchWord)
        {
            count++;
        }
    }
    return count;
}

int Reader::getCount()
{
    return count;
}


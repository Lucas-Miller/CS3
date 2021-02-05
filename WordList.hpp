#include<stdio.h>
#include<string>
#include<iostream>

class WordOccurrence {
public:
    WordOccurrence(const std::string& word="", int num=0);
    bool matchWord(const std::string &); // returns true if word matches stored
    void increment(); // increments number of occurrences
    std::string getWord() const; 
    int getNum() const;

private:
    std::string word_;
    int num_;
};

class WordList{
public:
    // add copy constructor, destructor, overloaded assignment
    WordList() {size_ = 0; wordArray_ = new WordOccurrence[size_];};
    ~WordList() {delete [] wordArray_;};
    WordList(const WordList&);
    WordList& operator=(WordList);

    // implement comparison as friend
    friend bool equal(const WordList&, const WordList&);

    void addWord(const std::string &);
    void print();
private:
    WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
                                // may or may not be sorted
    int size_;
};
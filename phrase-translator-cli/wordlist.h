#ifndef WORDLIST_H
#define WORDLIST_H

#include <string>
#include <vector>
#include "postag.h"

class Word
{
public:
    Word(const std::string &str, const POSTag &tag) : m_str(str), m_tag(tag) {};
    std::string const& getStr() const { return m_str; }
    void setTag(POSTagEnum tag) { m_tag.setTag(tag); }
    void setTag(std::string tag) { m_tag.setTag(tag); }
    POSTag const& getTag() const {return m_tag; }
private:
    std::string m_str;
    POSTag m_tag;
};

class WordList
{
public:
    WordList();
    void addWord(const std::string &s, const POSTag &tag);
    void readFromTxtFile(std::string filename);
    std::vector<Word> &vec() {return m_wvec; }
    std::vector<Word> const& vec() const {return m_wvec; }
private:
    std::vector<Word> m_wvec;
};

#endif // WORDLIST_H

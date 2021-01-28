#ifndef WORDLIST_H
#define WORDLIST_H

#include <string>
#include <vector>
#include <map>
#include "postag.h"

const size_t INVALID_WORD_ID = std::numeric_limits<size_t>::max();
using WordId = size_t;

class Word
{
public:
    Word() : m_str(""), m_tag(POSTag(POSTagEnum::UNK)) {};
    Word(const std::string &str, const POSTag &tag) : m_str(str), m_tag(tag) {};
    Word(const std::string &str) : m_str(str), m_tag(POSTag(POSTagEnum::UNK)) {};
    std::string const& getStr() const { return m_str; }
    void setTag(POSTagEnum tag) { m_tag.setTag(tag); }
    void setTag(std::string tag) { m_tag.setTag(tag); }
    POSTag const& getTag() const {return m_tag; }
    bool isWord() { return m_str != "" && m_str != "<s>" && m_str != "</s>"; }
    bool operator<(const Word& other) { return m_str < other.m_str; }
    WordId getId() { return m_id; }
    void setId(WordId id) { m_id = id; }
private:
    std::string m_str;
    WordId m_id = INVALID_WORD_ID;
    POSTag m_tag;
};

inline bool operator<(const Word& w1, const Word&w2)
{
    return w1.getStr() < w2.getStr();
}

inline bool operator==(const Word& w1, const Word&w2)
{
    return w1.getStr() == w2.getStr();
}

class WordList
{
public:
    WordList();
    void readFromTxtFile(std::string filename);
    std::vector<Word> &vec() {return m_wvec; }
    std::vector<Word> const& vec() const {return m_wvec; }
    std::map<WordId, std::map<WordId,double>> const& getNextWordOdds() const { return m_next_word_odds; }
private:
    void addWord(Word &word);
    std::vector<Word> m_wvec;
    std::map<WordId, std::map<WordId,double>> m_next_word_odds;
    void normalize_next_word_odds();
};

#endif // WORDLIST_H

#ifndef WORDLIST_H
#define WORDLIST_H

#include <string>
#include <QString>
#include <QVector>
#include <QDataStream>
#include <QMap>
#include "postag.h"

const int INVALID_WORD_ID = std::numeric_limits<int>::max();
using WordId = int;

class Word
{
public:
    Word() : m_str(""), m_tag(POSTag(POSTagEnum::UNK)) {};
    Word(const std::string &str, const POSTag &tag) : m_str(str), m_tag(tag) {};
    Word(const std::string &str) : m_str(str), m_tag(POSTag(POSTagEnum::UNK)) {};
    std::string const& getStr() const { return m_str; }
    void setStr(std::string &str) { m_str = str; }
    void setStr(QString &str) { m_str = str.toStdString(); }
    void setTag(POSTagEnum tag) { m_tag.setTag(tag); }
    void setTag(std::string tag) { m_tag.setTag(tag); }
    POSTag const& getTag() const {return m_tag; }
    bool isWord() { return m_str != "" && m_str != "<s>" && m_str != "</s>"; }
    bool operator<(const Word& other) { return m_str < other.m_str; }
    WordId getId() const { return m_id; }
    void setId(WordId id) { m_id = id; }
private:
    std::string m_str;
    WordId m_id = INVALID_WORD_ID;
    POSTag m_tag;
};

inline QDataStream &operator<<(QDataStream &stream, const Word &w)
{
    stream << QString::fromStdString(w.getStr());
    stream << w.getId();
    stream << QString::fromStdString(w.getTag().toStr());
    return stream;
}

inline QDataStream &operator>>(QDataStream &stream, Word &w)
{
    QString str;
    WordId id;
    QString tag;

    stream >> str;
    w.setStr(str);
    stream >> id;
    w.setId(id);
    stream >> tag;
    w.setTag(tag.toStdString());
    return stream;
}

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
    QVector<Word> &vec() {return m_wvec; }
    QVector<Word> const& vec() const {return m_wvec; }
    QMap<WordId, QMap<WordId,double>> const& getNextWordOdds() const { return m_next_word_odds; }
    void store(QString outfile);
    void load(QString infile);
private:
    void addWord(Word &word);
    QVector<Word> m_wvec;
    QMap<WordId, QMap<WordId,double>> m_next_word_odds;
    void normalize_next_word_odds();
};

#endif // WORDLIST_H

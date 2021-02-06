#include <QDebug>
#include <QFile>
#include <QDataStream>
#include "wordlist.h"
#include "meta/analyzers/analyzer.h"
#include "meta/analyzers/tokenizers/icu_tokenizer.h"
#include "meta/analyzers/filters/all.h"
#include "meta/io/filesystem.h"
#include "meta/parser/sr_parser.h"
#include "meta/sequence/io/ptb_parser.h"
#include <meta/sequence/perceptron.h>
#include <meta/sequence/sequence.h>

using namespace meta;

WordList::WordList()
{

}

void WordList::addWord(Word &word)
{
    WordId id;
    auto dup = std::find(m_wvec.begin(), m_wvec.end(), word);

    if (dup != m_wvec.end()) {
        id = dup->getId();
    } else {
        id = m_wvec.size();
    }
    word.setId(id);
    m_wvec.push_back(word);
}

void WordList::normalize_next_word_odds()
{
    for (auto & i : m_next_word_odds) {
        auto sum = 0.0;
        for (const auto &w : i) {
            sum += w;
        }
        for (auto &w : i) {
            w = w / sum;
        }
    }
}

void WordList::readFromTxtFile(std::string filename)
{
    WordId prev = 0;
    Word word;

    Q_ASSERT(m_wvec.empty());

    /* Construct the token filter chain */
    std::unique_ptr<analyzers::token_stream> stream
        = make_unique<analyzers::tokenizers::icu_tokenizer>();
    stream = make_unique<analyzers::filters::ptb_normalizer>(std::move(stream));

    stream->set_content(filesystem::file_text(filename));

    /* Add first word for 'prev' to be valid */
    word = Word(stream->next());
    addWord(word);

    while (*stream) {
        word = Word(stream->next());
        addWord(word);
        Q_ASSERT(word.getId() != INVALID_WORD_ID);
        if (m_wvec[prev].isWord()) {
            if (m_next_word_odds.count(prev) == 0) {
                m_next_word_odds[prev] = QMap<WordId,double>();
                m_next_word_odds[prev][word.getId()] = 1;
            } else {
                m_next_word_odds[prev][word.getId()] += 1;
            }
        }
        prev = word.getId();
    }
    normalize_next_word_odds();
}

void WordList::store(QString outfile)
{
   QFile file(outfile);
   file.open(QIODevice::WriteOnly);
   QDataStream out(&file);

   /* Magic number and version */
   out << (quint32)0x050B0A03;
   out << (quint32)0x01;

   out.setVersion(QDataStream::Qt_5_15);

   out << m_wvec;
   out << m_next_word_odds;
}

void WordList::load(QString infile)
{
   QFile file(infile);
   file.open(QIODevice::ReadOnly);
   QDataStream in(&file);

   quint32 magic, version;
   in >> magic;
   /* TODO: Replace with error code */
   assert(magic == 0x050B0A03);
   in >> version;
   assert(version == 0x01);

   in.setVersion(QDataStream::Qt_5_15);

   in >> m_wvec;
   in >> m_next_word_odds;
}

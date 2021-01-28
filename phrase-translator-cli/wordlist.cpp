#include <QDebug>
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

inline bool operator<(const Word& w1, const Word&w2)
{
    return w1.getStr() < w2.getStr();
}

inline bool operator==(const Word& w1, const Word&w2)
{
    return w1.getStr() == w2.getStr();
}

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

    while (*stream)
    {
        word = Word(stream->next());
        addWord(word);
        Q_ASSERT(word.getId() != INVALID_WORD_ID);
        if (m_wvec[prev].isWord()) {
            if (m_next_word_odds.count(prev) == 0) {
                m_next_word_odds[prev] = std::map<WordId,float>();
                m_next_word_odds[prev][word.getId()] = 1;
            } else {
                m_next_word_odds[prev][word.getId()] += 1;
            }
        }
        prev = word.getId();
    }
}

#include "postagger.h"
#include "meta/analyzers/analyzer.h"
#include "meta/analyzers/tokenizers/icu_tokenizer.h"
#include "meta/analyzers/filters/all.h"
#include "meta/io/filesystem.h"
#include "meta/parser/sr_parser.h"
#include "meta/sequence/io/ptb_parser.h"
#include <meta/sequence/sequence.h>

using namespace meta;

POSTagger::POSTagger(QObject *parent) : QObject(parent)
{
    std::string str = "/home/egor/src/meta/data/perceptron-tagger/";
    m_tagger = sequence::perceptron(str);
}

void POSTagger::doTagging(WordList &wlist)
{
    sequence::sequence seq;
    std::vector<Word *> sentence;

    for (auto &w : wlist.vec())
    {
        auto token = w.getStr();
        if (token == "<s>")
        {
            seq = {};
            sentence.clear();
        }
        else if (token == "</s>")
        {
            m_tagger.tag(seq);
            for (size_t i = 0; i < seq.size(); i++)
            {
                sentence[i]->setTag(seq[i].tag());
            }
        }
        else
        {
            seq.add_symbol(sequence::symbol_t{token});
            sentence.push_back(&w);
        }
    }
}


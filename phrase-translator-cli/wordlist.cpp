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

void WordList::addWord(const std::string &s, const POSTag &tag)
{
    m_wvec.push_back(Word(s, tag));
}

void WordList::readFromTxtFile(std::string filename)
{
    m_wvec.clear();

    // construct the token filter chain
    std::unique_ptr<analyzers::token_stream> stream
        = make_unique<analyzers::tokenizers::icu_tokenizer>();
    stream = make_unique<analyzers::filters::ptb_normalizer>(std::move(stream));

    stream->set_content(filesystem::file_text(filename));

    while (*stream)
    {
        addWord(std::string(stream->next()), POSTag(POSTagEnum::UNK));
    }
}

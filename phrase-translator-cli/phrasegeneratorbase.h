#ifndef PHRASEGENERATORBASE_H
#define PHRASEGENERATORBASE_H

#include "wordlist.h"
#include "phrasepattern.h"

class PhraseGeneratorBase
{
public:
    virtual std::string generatePhrase(WordList const& wlist, PhrasePattern const& pattern) = 0;
};

#endif // PHRASEGENERATORBASE_H

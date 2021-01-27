#ifndef PHRASEGENERATOR_H
#define PHRASEGENERATOR_H

#include "wordlist.h"
#include "phrasepattern.h"

class PhraseGenerator
{
public:
    PhraseGenerator();
    std::string generatePhrase(WordList const& wlist, PhrasePattern const& pattern);
};

#endif // PHRASEGENERATOR_H

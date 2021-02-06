#ifndef PHRASEGENERATORMARKOV_H
#define PHRASEGENERATORMARKOV_H

#include "phrasegeneratorbase.h"

class PhraseGeneratorMarkov : public PhraseGeneratorBase
{
public:
    PhraseGeneratorMarkov();
    std::string generatePhrase(WordList const& wlist, PhrasePattern const& pattern) override;
};

#endif // PHRASEGENERATORMARKOV_H

#ifndef PHRASEGENERATORRANDOM_H
#define PHRASEGENERATORRANDOM_H

#include "phrasegeneratorbase.h"

class PhraseGeneratorRandom : public PhraseGeneratorBase
{
public:
    PhraseGeneratorRandom();
    std::string generatePhrase(WordList const& wlist, PhrasePattern const& pattern) override;
};

#endif // PHRASEGENERATORRANDOM_H

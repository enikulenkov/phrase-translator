#ifndef PHRASEPATTERN_H
#define PHRASEPATTERN_H

#include <vector>
#include "postag.h"

class PhrasePattern
{
public:
    PhrasePattern(POSTag *tags, size_t tags_size);
    std::vector<POSTag> const& vec() const { return m_vec; }
private:
    std::vector<POSTag> m_vec;
};

#endif // PHRASEPATTERN_H

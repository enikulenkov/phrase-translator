#include "phrasepattern.h"

PhrasePattern::PhrasePattern(POSTag *tags, int tags_size)
{
    m_vec.reserve(tags_size);
    for (int i = 0; i < tags_size; i++) {
        m_vec.push_back(tags[i]);
    }
}

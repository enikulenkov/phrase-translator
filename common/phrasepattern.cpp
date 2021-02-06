#include "phrasepattern.h"

PhrasePattern::PhrasePattern(POSTag *tags, size_t tags_size)
{
    m_vec.reserve(tags_size);
    for (size_t i = 0; i < tags_size; i++) {
        m_vec.push_back(tags[i]);
    }
}

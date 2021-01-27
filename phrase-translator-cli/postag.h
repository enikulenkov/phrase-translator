#ifndef POSTAG_H
#define POSTAG_H

#include <map>

/* Part-of-speech (POS) tags from Wikipedia:
 * https://en.wikipedia.org/wiki/Brown_Corpus#Part-of-speech_tags_used.
 * The only change is "NP" (wiki) -> NNP (here). It seems MeTA toolkit
 * assigns "NNP" tag for proper nouns.
 *
 * MeTA documentation:
 * https://meta-toolkit.org/pos-tagging-tutorial.html
 */
typedef enum {
    NN   = 0x0000, /* singular or mass noun */
    NNP          , /* proper noun or part of name phrase */
    VB   = 0x0010, /* verb, base form */
    VBD          , /* verb, past tense */
    VBG          , /* verb, present participle/gerund */
    VBN          , /* verb, past participle */
    VBP          , /* verb, non 3rd person, singular, present */
    VBZ          , /* verb, 3rd. singular present */
    DT   = 0x0020, /* singular determiner/quantifier (this, that) */
    DTI          , /* singular or plural determiner/quantifier (some, any) */
    DTS          , /* plural determiner (these, those) */
    DTX          , /* determiner/double conjunction (either) */
    UNK  = 0xFFFF
} POSTagEnum;

class POSNames {
public:
    POSNames();
    std::map<std::string,POSTagEnum> m;
};

class POSTag {
public:
    POSTag(const POSTagEnum v) : m_value(v) {};
    POSTag(const std::string s);
    bool isNoun() const { return !!(m_value & 0x0F); }
    bool isVerb() const { return !!(m_value & 0xF0); }
    const char* toStr();
    void setTag(POSTagEnum v) { m_value = v; }
    void setTag(std::string s);
    POSTagEnum value(void) const {return m_value;}
private:
    POSTagEnum m_value;
};

#endif // POSTAG_H

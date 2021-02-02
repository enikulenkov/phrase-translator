#ifndef POSTAG_H
#define POSTAG_H

#include <map>

/* Part-of-speech (POS) tags from Wikipedia:
 * https://en.wikipedia.org/wiki/Brown_Corpus#Part-of-speech_tags_used.
 * The only change is "NP" (wiki) -> NNP (here). It seems MeTA toolkit
 * assigns "NNP" tag for proper nouns.
 *
 * Another tag set is Penn Treebank (probably used by meta):
 * https://www.ling.upenn.edu/courses/Fall_2003/ling001/penn_treebank_pos.html
 *
 * MeTA documentation:
 * https://meta-toolkit.org/pos-tagging-tutorial.html
 */
typedef enum {
    NN   = 0x0000, /* Noun, singular or mass */
    NNS          , /* noun, plural */
    NNP          , /* proper noun, singular */
    NNPS         , /* proper noun, plural */
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
    JJ   = 0x0030, /* adjective */
    JJR          , /* comparative adjective */
    JJS          , /* semantically superlative adjective (chief, top) */
    JJT          , /* morphologically superlative adjective (biggest) */
    PRP  = 0x0040, /* Personal pronoun */
    PRPP         , /* Possessive pronoun */
    RB   = 0x0050, /* Adverb */
    RBR          , /* Adverb, comparative */
    RBS          , /* Adverb, superlative */
    CC   = 0x0060, /* Coordinating conjunction */
    IN           , /* Preposition or subordinating conjunction */
    CD   = 0x0070, /* Cardinal number */
    EX   = 0x0080, /* Existential "there" */
    FW   = 0x0090, /* Foreign word */
    LS   = 0x0100, /* List item marker */
    MD   = 0x0110, /* Modal */
    PDT  = 0x0120, /* Predeterminer */
    POS  = 0x0130, /* Possessive ending */
    RP   = 0x0140, /* Particle */
    SYM  = 0x0150, /* Particle */
    TO   = 0x0160, /* To */
    UH   = 0x0170, /* Interjection */
    WDT  = 0x0180, /* Wh-determiner */
    WP           , /* Wh-pronoun */
    WPP          , /* Wh-pronoun, possesive */
    WRB          , /* Wh-adverb */
    DOT  = 0x0190, /* dot */
    CLN          , /* colon */
    COM          , /* comma */
    TCK          , /* backticks */
    SQT          , /* single quotes */
    UNK  = 0xFFFF
} POSTagEnum;

class POSNames {
public:
    POSNames();
    std::map<std::string,POSTagEnum> m;
    std::map<POSTagEnum,std::string> m_r; /* reverse map of 'm' */
};

class POSTag {
public:
    POSTag(const POSTagEnum v) : m_value(v) {};
    POSTag(const std::string s);
    bool isNoun() const { return !!(m_value & 0x0F); }
    bool isVerb() const { return !!(m_value & 0xF0); }
    bool operator==(const POSTag& other) { return m_value == other.m_value; }
    const std::string toStr() const;
    void setTag(POSTagEnum v) { m_value = v; }
    void setTag(std::string s);
    POSTagEnum value(void) const {return m_value;}
private:
    POSTagEnum m_value;
};

inline bool operator==(const POSTag& tag1, const POSTag& tag2)
{
    return tag1.value() == tag2.value();
}

#endif // POSTAG_H

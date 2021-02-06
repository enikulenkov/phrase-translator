#include <QDebug>
#include <random>
#include "phrasegeneratormarkov.h"

PhraseGeneratorMarkov::PhraseGeneratorMarkov()
{

}

static const Word *getFirstWord(std::mt19937 &gen, const WordList &wlist, const PhrasePattern &pattern)
{
    auto wlist_size = wlist.vec().size();
    std::uniform_int_distribution<int> distribution(1,wlist_size);
    const auto& p = pattern.vec().at(0);
    auto start_idx = distribution(gen);
    auto i = 0;
    auto found = false;
    const Word *res;

    while (i < wlist_size && !found) {
        res = &wlist.vec().at(start_idx);
        if (res->getTag() == p) {
            found = true;
        }
        start_idx = (start_idx + 1) % wlist_size;
        i++;
    }
    Q_ASSERT(found);
    return res;
}

std::string PhraseGeneratorMarkov::generatePhrase(const WordList &wlist, const PhrasePattern &pattern)
{
    std::string res = "";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<const Word*> res_words;
    const Word* curr_word;
    size_t pattern_idx = 0;

    while (pattern_idx < pattern.vec().size()) {
        std::uniform_real_distribution<> dis(0.0, 1.0);
        auto dice = dis(gen);
        auto sum = 0.0;
        const Word *match = NULL;
        auto nextWordOdds = wlist.getNextWordOdds();

        if (pattern_idx == 0) {
            curr_word = getFirstWord(gen, wlist, pattern);
            res_words.push_back(curr_word);
            pattern_idx++;
        } else {
            QMapIterator<WordId,double> it(nextWordOdds[curr_word->getId()]);
            while (it.hasNext()) {
                it.next();
                sum += it.value();
                const Word *w = &wlist.vec().at(it.key());
                bool tag_match = w->getTag() == pattern.vec()[pattern_idx];
                if (tag_match) {
                    match = w;
                    if (sum >= dice) {
                        break;
                    }
                }
            }
            if (match != NULL) {
                curr_word = match;
                res_words.push_back(curr_word);
                pattern_idx++;
            } else {
                /* Start the process over for simplicity */
                pattern_idx = 0;
                res_words.clear();
            }
        }
    }

    for (const Word* w : res_words) {
        res += w->getStr() + " ";
    }
    return res;
}

#include <QDebug>
#include <random>
#include "phrasegeneratormarkov.h"

PhraseGeneratorMarkov::PhraseGeneratorMarkov()
{

}

std::string PhraseGeneratorMarkov::generatePhrase(const WordList &wlist, const PhrasePattern &pattern)
{
    std::string res = "";
    auto wlist_size = wlist.vec().size();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> distribution(1,wlist_size);
    Word first_word, curr_word;

    /* Find first word of required POS randomly */
    const auto& p = pattern.vec().at(0);
    auto start_idx = distribution(gen);
    size_t i = 0;
    auto found = false;

    while (i < wlist_size && !found) {
        auto word = wlist.vec().at(start_idx);
        if (word.getTag() == p) {
            first_word = word;
            found = true;
        }
        start_idx = (start_idx + 1) % wlist_size;
        i++;
    }
    Q_ASSERT(found);

    res += first_word.getStr() + " ";
    curr_word = first_word;

    /* Find others according to probabilities */
    for (size_t i = 1; i < pattern.vec().size(); i++) {
        std::uniform_real_distribution<> dis(0.0, 1.0);
        auto dice = dis(gen);
        auto sum = 0.0;
        Word match;

        for (const auto& next_word : wlist.getNextWordOdds().at(curr_word.getId())) {
            sum += next_word.second;
            auto w = wlist.vec().at(next_word.first);
            bool tag_match = w.getTag() == pattern.vec()[i];
            if (tag_match) {
                match = w;
                if (sum >= dice) {
                    break;
                }
            }
        }
        /* TODO: Do one step back */
        Q_ASSERT(match.getStr() != "");
        res += match.getStr() + " ";
        curr_word = match;
    }
    return res;
}

#include <QDebug>
#include <random>
#include <assert.h>
#include "phrasegeneratorrandom.h"

PhraseGeneratorRandom::PhraseGeneratorRandom()
{

}

std::string PhraseGeneratorRandom::generatePhrase(const WordList &wlist, const PhrasePattern &pattern)
{
    std::string res = "";
    auto wlist_size = wlist.vec().size();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1,wlist_size);

    for (auto& p : pattern.vec()) {
        auto start_idx = distribution(gen);
        auto i = 0;
        auto found = false;

        while (i < wlist_size && !found) {
            auto word = wlist.vec().at(start_idx);
            if (word.getTag().value() == p.value()) {
                res += word.getStr() + " ";
                found = true;
            }
            start_idx = (start_idx + 1) % wlist_size;
            i++;
        }
        Q_ASSERT(found);
    }

    return res;
}

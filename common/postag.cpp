#include <QDebug>
#include <string>
#include <assert.h>
#include "postag.h"

static POSNames s_posNames;

POSTag::POSTag(const std::string s)
{
    m_value = s_posNames.m.find(s)->second;
}

const std::string POSTag::toStr() const
{
    return s_posNames.m_r[m_value];
}

void POSTag::setTag(std::string s)
{
    auto found = s_posNames.m.find(s);
    //Q_ASSERT(found != s_posNames.m.end());
    if (found == s_posNames.m.end()) {
        qWarning() << s.c_str();
        m_value = UNK;
    } else {
        m_value = found->second;
    }
}

POSNames::POSNames()
{
    m["NN"]   = NN;
    m["NNS"]  = NNS;
    m["NNP"]  = NNP;
    m["NNPS"] = NNPS;
    m["VB"]   = VB;
    m["VBD"]  = VBD;
    m["VBG"]  = VBG;
    m["VBN"]  = VBN;
    m["VBP"]  = VBP;
    m["VBZ"]  = VBZ;
    m["DT"]   = DT;
    m["DTI"]  = DTI;
    m["DTS"]  = DTS;
    m["DTX"]  = DTX;
    m["JJ"]   = JJ;
    m["JJR"]  = JJR;
    m["JJS"]  = JJS;
    m["JJT"]  = JJT;
    m["PRP"]  = PRP;
    m["PRP$"] = PRPP;
    m["RB"]   = RB;
    m["RBR"]  = RBR;
    m["RBS"]  = RBS;
    m["CC"]   = CC;
    m["IN"]   = IN;
    m["CD"]   = CD;
    m["DT"]   = DT;
    m["EX"]   = EX;
    m["FW"]   = FW;
    m["LS"]   = LS;
    m["MD"]   = MD;
    m["PDT"]  = PDT;
    m["POS"]  = POS;
    m["RP"]   = RP;
    m["SYM"]  = SYM;
    m["TO"]   = TO;
    m["UH"]   = UH;
    m["WDT"]  = WDT;
    m["WP"]   = WP;
    m["WP$"]  = WPP;
    m["WRB"]  = WRB;
    m["."]    = DOT;
    m[":"]    = CLN;
    m[","]    = COM;
    m["``"]   = TCK;
    m["''"]   = SQT;
    m["UNK"]  = UNK;

    for (const auto& kv : m) {
        m_r[kv.second] = kv.first;
    }
}

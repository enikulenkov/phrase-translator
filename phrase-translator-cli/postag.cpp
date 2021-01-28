#include <QDebug>
#include <string>
#include <assert.h>
#include "postag.h"

static POSNames s_posNames;

POSTag::POSTag(const std::string s)
{
    m_value = s_posNames.m.find(s)->second;
}

const char* POSTag::toStr()
{
    switch (m_value) {
    case NN:  return "NN";
    case NNP: return "NNP";
    case VB:  return "VB";
    case VBD: return "VB";
    case VBG: return "VBG";
    case VBN: return "VBN";
    case VBP: return "VBP";
    case VBZ: return "VBZ";
    case DT:  return "DT";
    case DTI: return "DTI";
    case DTS: return "DTS";
    case DTX: return "DTX";
    case JJ:  return "JJ";
    case JJR: return "JJR";
    case JJS: return "JJS";
    case JJT: return "JJT";
    case UNK: return "UNK";
    }
}

void POSTag::setTag(std::string s)
{
    auto found = s_posNames.m.find(s);
    //Q_ASSERT(found != s_posNames.m.end());
    if (found == s_posNames.m.end()) {
        qDebug() << s.c_str();
        m_value = UNK;
    } else {
        m_value = found->second;
    }
}

POSNames::POSNames()
{
    m["NN"]  = NN;
    m["NNP"] = NNP;
    m["VB"]  = VB;
    m["VBD"] = VBD;
    m["VBG"] = VBG;
    m["VBN"] = VBN;
    m["VBP"] = VBP;
    m["VBZ"] = VBZ;
    m["DT"]  = DT;
    m["DTI"] = DTI;
    m["DTS"] = DTS;
    m["DTX"] = DTX;
    m["JJ"]  = JJ;
    m["JJR"] = JJR;
    m["JJS"] = JJS;
    m["JJT"] = JJT;
    m["UNK"] = UNK;
}

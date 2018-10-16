#include "DBitOptor.h"


DBitOptor::DBitOptor()
{
}


DBitOptor::~DBitOptor()
{
}
void DBitOptor::setbitfun(int &nFlag, ELeadNum eLeadNum, bool bValve)
{
    if (bValve)
    {
        nFlag |= eLeadNum;
    }
    else
    {
        nFlag &= ~eLeadNum;
    }
}
void DBitOptor::setFun(int & nFlag, bool bArr[12], int nSize)
{
    setbitfun(nFlag, lead_I, bArr[0]);
    setbitfun(nFlag, lead_II, bArr[1]);
    setbitfun(nFlag, lead_III, bArr[2]);
    setbitfun(nFlag, lead_aVR, bArr[3]);
    setbitfun(nFlag, lead_aVL, bArr[4]);
    setbitfun(nFlag, lead_aVF, bArr[5]);
    setbitfun(nFlag, lead_V1, bArr[6]);
    setbitfun(nFlag, lead_V2, bArr[7]);
    setbitfun(nFlag, lead_V3, bArr[8]);
    setbitfun(nFlag, lead_V4, bArr[9]);
    setbitfun(nFlag, lead_V5, bArr[10]);
    setbitfun(nFlag, lead_V6, bArr[11]);
}
void DBitOptor::getbitfun(const int & nFlag, bool bArr[12], int nSize)
{
    bArr[0] = nFlag & lead_I;
    bArr[1] = nFlag & lead_II;
    bArr[2] = nFlag & lead_III;
    bArr[3] = nFlag & lead_aVR;
    bArr[4] = nFlag & lead_aVL;
    bArr[5] = nFlag & lead_aVF;
    bArr[6] = nFlag & lead_V1;
    bArr[7] = nFlag & lead_V2;
    bArr[8] = nFlag & lead_V3;
    bArr[9] = nFlag & lead_V4;
    bArr[10] = nFlag & lead_V5;
    bArr[11] = nFlag & lead_V6;
}
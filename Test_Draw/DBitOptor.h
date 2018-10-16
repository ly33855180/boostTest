#pragma once
class DBitOptor
{
public:
public:
    enum ELeadNum
    {
        lead_I = 0x1,
        lead_II = 0x2,
        lead_III = 0x4,
        lead_aVR = 0x8,
        lead_aVL = 0x10,
        lead_aVF = 0x20,
        lead_V1 = 0x40,
        lead_V2 = 0x80,
        lead_V3 = 0x100,
        lead_V4 = 0x200,
        lead_V5 = 0x400,
        lead_V6 = 0x800,
    };
    static void setbitfun(int &nFlag, ELeadNum eLeadNum, bool bValve);
    static void setFun(int & nFlag, bool bArr[12], int nSize = 12);
    static void getbitfun(const int & nFlag, bool bArr[12], int nSize = 12);
private:
    DBitOptor();
    ~DBitOptor();
};


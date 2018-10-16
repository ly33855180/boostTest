#include "dleaddatas.h"
#include <string>
#include <iostream>
#include <fstream>
#include <qDebug>
using namespace std;

DLeadDatas::DLeadDatas()
{
}

DLeadDatas::~DLeadDatas()
{

}
#define Path "F:\\test\\Test_Draw\\Test_Draw\\file_²Î¿¼\\lead"
void DLeadDatas::LoadLeadData(int nLeadNum)
{
    char str[25] = "";

    ifstream f;
    string strFilePath = string(Path) + string(itoa(nLeadNum, str,10)) + string(".txt");
    f.open(strFilePath, ios::in | ios::binary);
    if (f)
    {
        for (int i = 0; i < PtCount; i++)
        {
                char buffer[200] = "";
                f.getline(buffer, 200);
                string strTemp(buffer);
                int nlen = strTemp.length();
                size_t findPos0 = strTemp.rfind("\"");
                size_t findPos1 = strTemp.rfind("=");
                string strSub = strTemp.substr(findPos1 + 1, nlen - 1 -2 - findPos1);
                qDebug() << QString(strSub.c_str()) ;
                double d = atof(strSub.c_str());
                m_dLeadData[nLeadNum][i] = d;
        }
    }
    else
    {
        cout << "open file error!" << endl;
    }

}

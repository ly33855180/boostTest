#pragma once
#include <QString>
#include <string>
using namespace std;

class DCodeHelper
{
public:
    DCodeHelper();
    ~DCodeHelper();
};

QString str2qstr(const string str);

string qstr2str(const QString qstr);





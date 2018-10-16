#ifndef DLEADDATAS_H
#define DLEADDATAS_H

#include <vector>
using namespace std;
#define PtCount 1000
class DLeadDatas
{
 
public:
    DLeadDatas();
    ~DLeadDatas();
    void LoadLeadData(int nLeadNum);

    //double m_dLeadData[12][PtCount];

    vector<double> m_dLeadData[12];

	
    
};

#endif // DLEADDATAS_H

#ifndef LP_ONE_BY_ONE_FILTER_H
#define LP_ONE_BY_ONE_FILTER_H

// ÖðµãÂË²¨
class CLPOnebyOneFilter
{
public:
	CLPOnebyOneFilter();
	~CLPOnebyOneFilter();

	double Filter(double dbData, int nFilterPara);
private:
	double m_dbXn[3];
	double m_dbYn[3];	
};

#endif // !LP_ONE_BY_ONE_FILTER_H

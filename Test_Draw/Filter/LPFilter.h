#pragma once

#include "FilterOneByOneInterface.h"
// 一个点一个点的进行低频滤波；
// 连续进行低频滤波
template<class T>
class CLPFilter:public IFilterOneByOne<T>
{
public:	
	CLPFilter(int nLPHz);
	
	~CLPFilter() {};
	
	T Filter(T tOrgData);
private:
	void InitArr();
private:
	double m_dbB;
	double m_dbArr[2];
	double m_Xn[3];
	double m_Yn[3];
};

template<class T>
inline CLPFilter<T>::CLPFilter(int nLPHz)
{
	switch (nLPHz)
	{
	case 30:
		m_dbB = 0.78e-2;
		m_dbArr[0] = 1.7347;
		m_dbArr[1] = -0.7660;
		break;
	case 40:
		m_dbB = 1.34e-2;
		m_dbArr[0] = 1.6457;
		m_dbArr[1] = -0.7009;
		break;
	case 60:
		m_dbB = 2.79e-2;
		m_dbArr[0] = 1.4755;
		m_dbArr[1] = -0.5869;
		break;
	case 80:
		m_dbB = 4.61e-2;
		m_dbArr[0] = 1.3073;
		m_dbArr[1] = -0.4918;
		break;
	case 100:
		m_dbB = 6.75e-2;
		m_dbArr[0] = 1.1430;
		m_dbArr[1] = -0.4128;
		break;
	case 150:
		m_dbB = 9.13e-2;
		m_dbArr[0] = 0.9824;
		m_dbArr[1] = -0.3477;
		break;
	default:
		break;
	}
}

template<class T>
void CLPFilter<T>::InitArr()
{
    memset(this->m_dbArr, 0, sizeof(double) * 2);
    memset(this->m_Xn, 0, sizeof(double) * 3);
    memset(this->m_Yn, 0, sizeof(double) * 3);
}

template<class T>
T CLPFilter<T>::Filter(T tOrgData)
{
	double b, a[2];
	
	b = m_dbB;
	a[0] = m_dbArr[0];
	a[1] = m_dbArr[1];

	m_Xn[2] = m_Xn[1];
	m_Xn[1] = m_Xn[0];
	m_Xn[0] = tOrgData;
	m_Yn[2] = m_Yn[1];
	m_Yn[1] = m_Yn[0];
	m_Yn[0] = b * (m_Xn[0] + 2 * m_Xn[1] + m_Xn[2]) + a[0] * m_Yn[1] + a[1] * m_Yn[2];

	return static_cast<T>(m_Yn[0]);
}

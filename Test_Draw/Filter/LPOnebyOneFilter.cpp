//#include "StdAfx.h"
#include "LPOnebyOneFilter.h"
#include <string.h>

CLPOnebyOneFilter::CLPOnebyOneFilter()
{
	memset(m_dbXn, 0, sizeof(double) * 3);
	memset(m_dbYn, 0, sizeof(double) * 3);
}

CLPOnebyOneFilter::~CLPOnebyOneFilter()
{
}

double CLPOnebyOneFilter::Filter(double dbData, int nFilterPara)
{
	double dbRet = dbData;

	if (nFilterPara > 150)
	{
		return dbRet;
	}

	double b, a[2];

	// 根据滤波类型，选择相应的滤波参数
	switch (nFilterPara)
	{
	case 30:
		b = 0.78e-2;
		a[0] = 1.7347;
		a[1] = -0.7660;
		break;
	case 40:
		b = 1.34e-2;
		a[0] = 1.6457;
		a[1] = -0.7009;
		break;
	case 60:
		b = 2.79e-2;
		a[0] = 1.4755;
		a[1] = -0.5869;
		break;
	case 80:
		b = 4.61e-2;
		a[0] = 1.3073;
		a[1] = -0.4918;
		break;
	case 100:
		b = 6.75e-2;
		a[0] = 1.1430;
		a[1] = -0.4128;
		break;
	case 150:
		b = 9.13e-2;
		a[0] = 0.9824;
		a[1] = -0.3477;
		break;
	default:
		break;
	}

	m_dbXn[2] = m_dbXn[1];
	m_dbXn[1] = m_dbXn[0];
	m_dbXn[0] = dbData;
	m_dbYn[2] = m_dbYn[1];
	m_dbYn[1] = m_dbYn[0];
	m_dbYn[0] = b * (m_dbXn[0] + 2 * m_dbXn[1] + m_dbXn[2])
		+ a[0] * m_dbYn[1] + a[1] * m_dbYn[2];

	dbRet = m_dbYn[0];

	return dbRet;
}

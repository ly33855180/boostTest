#pragma once
#include "FilterOneByOneInterface.h"

#include "CutFilter.h"
#include "LPFilter.h"
#include "BaselineOneByOneFilter.h"
#include "StaticBPFilter.h"

// 滤波器类型
enum FilterType
{
    BaseLine_Filter = 0,
    LP_Filter = 1,
    Cut_Filter = 2,
    QRS_Filter = 3,
    Static_HP_Filter = 4,
    Old_Analysis_HP_Filter = 5,
    Static_BP_Filter = 6,
    Static_LP_Filter = 7,
};

// 对外提供单点滤波的滤波器；
template<class T>
class COnePointFilter:public IFilterOneByOne<T>
{
public:
	COnePointFilter():m_pIFilterOnePointDeal(nullptr) { };
	COnePointFilter(FilterType nFilterType,
		int nMultiple, int nFilterMode);
	virtual ~COnePointFilter() { ClearFilerDeal(); };

	// 设置不同滤波模式，创建不同滤波器对象；
	void CreatUsedFilter(FilterType nFilterType, int nMultiple, int nFilterMode);
	// 对外的滤波接口；
	virtual T Filter(T tOrgData);	
private:
	void ClearFilerDeal();// 释放滤波器指针；
	// 基线滤波
	CBaselineOneByOneFilter<T>* CreatBaseLineFilter(int nMultiple, int nFilterMode);
	// 低通滤波
	CLPFilter<T>* CreateLPFilter(int nFilterMode);
	// 带通滤波
	IFilterOneByOne<T>* CreateCutFilter(int nMultiple);
	// QRS-高通滤波
	IFilterOneByOne<T>* CreateQRSFilter(int nMultiple, int nFilterMode);
	// 静态心电用的高通滤波
	IFilterOneByOne<T>* CreateStaticHPFilter(int nMultiple, int nFilterMode);
	// 老静态心电工作站用的高通滤波
	IFilterOneByOne<T>* CreateOldAnalysisHPFilter(int nMultiple, int nFilterMode);
	// 静态心电带通滤波
	IFilterOneByOne<T>* CreateStaticBPFilter(int nMultiple);
	// 静态心电低通滤波（只设定频率）	
	// 静态心电低通滤波（设置滤波模式，采样率/50）
	IFilterOneByOne<T>* CreateStaticLPFilter(int nMultiple, int nFilterMode);
private:
	IFilterOneByOne<T> *m_pIFilterOnePointDeal;
};

template<class T>
inline T COnePointFilter<T>::Filter(T tOrgData)
{	
	T tResultValue;
	try
	{
		if (m_pIFilterOnePointDeal != nullptr)
		{
			tResultValue = m_pIFilterOnePointDeal->Filter(tOrgData);
		}
		else
		{
			tResultValue = tOrgData;
		}
	}
	catch (...)
	{
		return -1;
	}
	return tResultValue;
}

template<class T>
inline void COnePointFilter<T>::ClearFilerDeal()
{
	if (m_pIFilterOnePointDeal != nullptr)
	{
		delete m_pIFilterOnePointDeal;
	}
}

template<class T>
inline COnePointFilter<T>::COnePointFilter(FilterType nFilterType, int nMultiple, int nFilterMode)
	:m_pIFilterOnePointDeal(nullptr)
{
	CreatUsedFilter(nFilterType, nMultiple, nFilterMode);
}

template<class T>
inline void COnePointFilter<T>::CreatUsedFilter(FilterType nFilterType,
	int nMultiple, int nFilterMode)
{
	ClearFilerDeal();

	switch (nFilterType)
	{
	case BaseLine_Filter:
		m_pIFilterOnePointDeal = CreatBaseLineFilter(nMultiple, nFilterMode);
		break;
	case LP_Filter:
		m_pIFilterOnePointDeal = CreateLPFilter(nFilterMode);
		break;
	case Cut_Filter:
		m_pIFilterOnePointDeal = CreateCutFilter(nFilterMode);
		break;
	case QRS_Filter:
		m_pIFilterOnePointDeal = CreateQRSFilter(nMultiple, nFilterMode);
		break;
	case Static_HP_Filter:
		m_pIFilterOnePointDeal = CreateStaticHPFilter(nMultiple, nFilterMode);
		break;
	case Old_Analysis_HP_Filter:
		m_pIFilterOnePointDeal = CreateOldAnalysisHPFilter(nMultiple, nFilterMode);
		break;
	case Static_BP_Filter:
		m_pIFilterOnePointDeal = CreateStaticBPFilter(nMultiple);
		break;	
	case Static_LP_Filter:
		m_pIFilterOnePointDeal = CreateStaticLPFilter(nMultiple, nFilterMode);
		break;
	default:
		m_pIFilterOnePointDeal = nullptr;
		break;
	}
}

template<class T>
inline CLPFilter<T>* COnePointFilter<T>::CreateLPFilter(int nFilterMode)
{
	// 30,40,60,80,100,150;
	return new CLPFilter<T>(nFilterMode);	
}

template<class T>
inline IFilterOneByOne<T>* COnePointFilter<T>::CreateCutFilter(int nMultiple)
{
	IFilterOneByOne<T>* pReturnFilter = nullptr;
	pReturnFilter = new CCut50Filter<T>(nMultiple);	
	return pReturnFilter;
}

template<class T>
inline CBaselineOneByOneFilter<T>* COnePointFilter<T>::CreatBaseLineFilter(int nMultiple,
	int nFilterMode)
{
	switch (nFilterMode)
	{
	case 1:
		return new C003HzBaseLineFilter<T>(nMultiple);
	case 2:
		return new C007HzBaseLineFilter<T>(nMultiple);
	default:
		break;
	}
	return NULL;
}

template<class T>
inline IFilterOneByOne<T>* COnePointFilter<T>::CreateQRSFilter(int nMultiple, int nFilterMode)
{
	IFilterOneByOne<T>* pReturnFilter = nullptr;
	if (nFilterMode > 3 || nFilterMode < 0)
	{
		return pReturnFilter;
	}
	pReturnFilter = new CQRSFilter<T>(nMultiple, nFilterMode);
	return pReturnFilter;
}

template<class T>
inline IFilterOneByOne<T>* COnePointFilter<T>::CreateStaticHPFilter(int nMultiple, int nFilterMode)
{
	return CreateQRSFilter(nMultiple, nFilterMode);
}

template<class T>
inline IFilterOneByOne<T>* COnePointFilter<T>::CreateOldAnalysisHPFilter(int nMultiple, int nFilterMode)
{
	IFilterOneByOne<T>* pReturnFilter = nullptr;
	if (nFilterMode > 3 || nFilterMode < 0)
	{
		return pReturnFilter;
	}

	pReturnFilter = new CHPBaseLineFilter<T>(nMultiple, nFilterMode);
	return pReturnFilter;
}

template<class T>
inline IFilterOneByOne<T>* COnePointFilter<T>::CreateStaticBPFilter(int nMultiple)
{
	IFilterOneByOne<T>* pReturnFilter = nullptr;
	pReturnFilter = new CBPFilter<T>(nMultiple);
	return pReturnFilter;
}

template<class T>
inline IFilterOneByOne<T>* COnePointFilter<T>::CreateStaticLPFilter(int nMultiple,
	int nFilterMode)
{
	IFilterOneByOne<T>* pReturnFilter = nullptr;

	if (nFilterMode > 6 || nFilterMode < 0)
	{
		return pReturnFilter;
	}
	pReturnFilter = new CStaticLPFilter<T>(nMultiple, nFilterMode);
	return NULL;
}


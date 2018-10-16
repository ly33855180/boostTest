#pragma once

#include "Filter/COnePointFilterFactory.h"
#include "Filter/ComplexFilter.h"
#include "Filter/CSegDataFilter.h"
#include "Filter/FilterOneByOneInterface.h"
template<class T>
class CFilterService
{
public:	
	// 不同滤波方式，内部装配不同滤波器；
	// nSampleRate: 采样率；
	// bHPFilter: 是否启用HP滤波；
	// bBLRFilter： 是否启用基线滤波；
	// bLPFilter：是否启用低通滤波；
	// nHPFilterMode：高通滤波模式；
	// nMFNo：低通滤波的频率；
	// nHPType：HP滤波器类型；
	// nLPType：LP滤波器类型；
	CFilterService(int nSampleRate,
		bool bHPFilter, bool bBLRFilter, bool bLPFilter,
		int nHPFilterMode,
		int nMFNo,
		int nHPType,
		int nLPType);
	// 成段式滤波，可选择基线滤波或者
	CFilterService(SegPointsFilterType filterType, int nSampleRate);
	~CFilterService();	

	// 更改滤波方式；调整滤波器；
	bool SetFilterMode(bool bHPFilter, bool bBLRFilter, bool bLPFilter,
		int nHPFilterMode, int nMFNo, int nHPType, int nLPType);
	// 设置波形的采样率
	bool SetWaveSampleRate(int nSampleRate);

	T OnePointFilter(T dbDataValue);	// 逐点滤波；
	bool SegPointsFilter(T* pInBuf, T* pOutBuf, int nDataLength);// 使用逐点滤波来实现成段滤波；
private:
	bool InitFilterDeal();// 装配组合滤波器；
private:
	bool m_bIsOnePointOrSegPoints;// 区分逐点滤波还是成段滤波；true:逐点滤波；false:成段滤波；
	
	bool m_bHPFilter;	// 是否高通滤波；
	bool m_bBLRFilter;	// 是否基线滤波；
	bool m_bLPFilter;	// 是否低通滤波

	int m_nHPFilterMode;	// 高通滤波参数类型；
	int m_nMFNo;			// 低通滤波参数类型；
	int m_nHPType;			// 0:HP_BaseLineFilter;1:HPFilter;
	int m_nLPType;			// 0:LPFilter(只使用30Hz等参数），1：Static_LP_Two_Filter，采用2个参数的LP滤波，且内部
	
	int m_nSampleRate;
	// 指向逐点滤波器的指针；
	COnePointFilter<T>* m_OnePointFilter;
	// 指向段落滤波器的指针；
	CSegDataFilter<T>* m_SegPointsFilter;
};

template<class T>
inline CFilterService<T>::CFilterService(int nSampleRate,
	bool bHPFilter, bool bBLRFilter, bool bLPFilter,
	int nHPFilterMode, int nMFNo, int nHPType,int nLPType)
	:m_OnePointFilter(nullptr),
	m_SegPointsFilter(nullptr),
	m_nSampleRate(nSampleRate),
	m_bHPFilter(bHPFilter),
	m_bBLRFilter(bBLRFilter),
	m_bLPFilter(bLPFilter),
	m_nHPFilterMode(nHPFilterMode),
	m_nMFNo(nMFNo),
	m_nHPType(nHPType),
	m_nLPType(nLPType),
	m_bIsOnePointOrSegPoints(true)
{
	InitFilterDeal();
}

template<class T>
CFilterService<T>::CFilterService(SegPointsFilterType filterType, int nSampleRate)
	:m_OnePointFilter(nullptr),
	m_SegPointsFilter(nullptr),
	m_nSampleRate(nSampleRate),
	m_bIsOnePointOrSegPoints(false)
{
	m_SegPointsFilter = new CSegDataFilter<T>(filterType, nSampleRate);
}

template<class T>
inline CFilterService<T>::~CFilterService()
{
	if (nullptr != m_OnePointFilter)
	{
		delete m_OnePointFilter;
	}

	if (nullptr != m_SegPointsFilter)
	{
		delete m_SegPointsFilter;
	}
}

template<class T>
bool CFilterService<T>::SetFilterMode(bool bHPFilter, bool bBLRFilter, bool bLPFilter,
	int nHPFilterMode, int nMFNo, int nHPType, int nLPType)
{
	m_bHPFilter = bHPFilter;
	m_bBLRFilter = bBLRFilter;
	m_bLPFilter = bLPFilter;
	m_nHPFilterMode = nHPFilterMode;
	m_nMFNo = nMFNo;
	m_nHPType = nHPType;
	m_nLPType = nLPType;
	// 初始化滤波器，生成滤波器；
	InitFilterDeal();
	return true;
}

template<class T>
inline bool CFilterService<T>::SetWaveSampleRate(int nSampleRate)
{
	m_nSampleRate = nSampleRate;
	return true;
}

template<class T>
inline T CFilterService<T>::OnePointFilter(T dbDataValue)
{
	if (nullptr != m_OnePointFilter)
	{
		return m_OnePointFilter->Filter(dbDataValue);
	}
	else
	{
		return dbDataValue;
	}
}

template<class T>
inline bool CFilterService<T>::SegPointsFilter(T * pInBuf, T * pOutBuf, int nDataLength)
{
	if (m_bIsOnePointOrSegPoints)
	{
		for (int i = 0; i < nDataLength; i++)
		{
			pOutBuf[i] = OnePointFilter(pInBuf[i]);
		}
	}
	else
	{
		if (nullptr != m_SegPointsFilter)
		{
			return m_SegPointsFilter->Filter(pInBuf, pOutBuf, nDataLength);
		}
	}
	
	return true;
}

template<class T>
bool CFilterService<T>::InitFilterDeal()
{
	if (nullptr != m_OnePointFilter)
	{
		delete m_OnePointFilter;
	}
	// 装配HP滤波；
	if (m_bHPFilter)
	{
		if (m_nHPType == 0)
		{
			// SO中对应了HPFilter
            m_OnePointFilter = new COnePointFilter<T>(Static_HP_Filter,
				m_nSampleRate / 50, m_nHPFilterMode);
		}
		else if (m_nHPType == 1)
		{
			// SO中对应了HP_BaseLineFilter_Src
            m_OnePointFilter = new COnePointFilter<T>(Old_Analysis_HP_Filter,
				m_nSampleRate / 50, m_nHPFilterMode);
		}		
	}
	// 装配BaseLine滤波；
	if (m_bBLRFilter)
	{
        m_OnePointFilter = new CComplexOnePointFilter<T>(BaseLine_Filter,
			m_nSampleRate / 50, 2,m_OnePointFilter);
	}
	// 装配LP滤波；
	if (m_bLPFilter)
	{
		if (m_nLPType == 0)
		{
			// 
            m_OnePointFilter = new CComplexOnePointFilter<T>(LP_Filter,
				0, m_nMFNo, m_OnePointFilter);
		}
		else if (m_nLPType == 1)
		{
            m_OnePointFilter = new CComplexOnePointFilter<T>(Static_LP_Filter,
				3, 1, m_OnePointFilter);
		}
		
	}
	return false;
}

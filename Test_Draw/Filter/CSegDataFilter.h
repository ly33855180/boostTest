#pragma once
#include "Filter/BaseLineFilter.h"
#include "Filter/SOBPFilter.h"
enum SegPointsFilterType
{
	BPFilter = 1,
	BaseLineFilter = 2,
};
// 成段滤波的工厂类，支持基线滤波和带通滤波
template<class T>
class CSegDataFilter : public IFilterSegData<T>
{	
public:
	CSegDataFilter(){}
	CSegDataFilter(SegPointsFilterType filterType, int nSampleRate);
	~CSegDataFilter();
	virtual bool Filter(T* ptOrgData, T* ptDstData, int nSize);
private:
	IFilterSegData<T>* CreateBPFilter(int nSampleRate);
	IFilterSegData<T>* CreateBaseLineFilter(int nSampleRate);

	IFilterSegData<T>* m_pSegFilter;
};

template<class T>
inline CSegDataFilter<T>::CSegDataFilter(SegPointsFilterType filterType, int nSampleRate)
	:m_pSegFilter(nullptr)
{
	switch (filterType)
	{
	case BPFilter:// 带通滤波；
		m_pSegFilter = CreateBPFilter(nSampleRate);
		break;
	case BaseLineFilter:// 基线滤波；
		m_pSegFilter = CreateBaseLineFilter(nSampleRate);
		break;
	default:
		break;
	}
}

template<class T>
inline CSegDataFilter<T>::~CSegDataFilter()
{
	if (nullptr != m_pSegFilter)
	{
		delete m_pSegFilter;
	}
}

template<class T>
inline bool CSegDataFilter<T>::Filter(T * ptOrgData, T * ptDstData, int nSize)
{
	if (nullptr != m_pSegFilter)
	{
		return m_pSegFilter->Filter(ptOrgData, ptDstData, nSize);
	}
	else
	{
		return IFilterSegData<T>::Filter(ptOrgData, ptDstData, nSize);
	}
}

template<class T>
inline IFilterSegData<T>* CSegDataFilter<T>::CreateBPFilter(int nSampleRate)
{
	So_BPFilter<T>* pReturnFilter = nullptr;
	// 根据采样率，完成参数的选择
	if (250 == nSampleRate || 300 == nSampleRate || 500 == nSampleRate)
	{
		pReturnFilter = new So_BPFilter<T>(nSampleRate);
	}
	return pReturnFilter;
}

template<class T>
inline IFilterSegData<T>* CSegDataFilter<T>::CreateBaseLineFilter(int nSampleRate)
{
	return new CBaseLineFilter<T>(nSampleRate);
}

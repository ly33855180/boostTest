#pragma once
#include "Filter/COnePointFilterFactory.h"
template<class T>
class CComplexOnePointFilter :public COnePointFilter<T>
{
public:
    CComplexOnePointFilter(FilterType nFilterType,
		int nMultiple, int nFilterMode,
        COnePointFilter<T> *subOnePointFilter = nullptr) :COnePointFilter<T>(nFilterType,
			nMultiple, nFilterMode),
		m_subOnePointFilter(subOnePointFilter) {}

	virtual ~CComplexOnePointFilter()
	{
        if (this->m_subOnePointFilter != nullptr)
		{
            delete this->m_subOnePointFilter;
		}
	}
	virtual T Filter(T tOrgData)
	{
		T tMidValue = COnePointFilter<T>::Filter(tOrgData);
        if (nullptr != this->m_subOnePointFilter)
		{
            return this->m_subOnePointFilter->Filter(tMidValue);
		}
		return tMidValue;
	}
private:
    COnePointFilter<T> *m_subOnePointFilter;
};

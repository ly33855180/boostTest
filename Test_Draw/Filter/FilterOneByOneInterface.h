#pragma once
#include <string.h>
template<class T>
class IFilterOneByOne
{
public:
	IFilterOneByOne() {};
	virtual ~IFilterOneByOne() {};
	virtual T Filter(T tOrgData) { return tOrgData; };
private:
};

template<class T>
class IFilterSegData
{
public:	
	virtual ~IFilterSegData() {};
	virtual bool Filter(T* ptOrgData,T* ptDstData, int nSize)
	{
		for (int i = 0; i < nSize; i++)
		{
			ptDstData[i] = ptOrgData[i];
		}
		return true;
	};
private:
};

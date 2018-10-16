#pragma once
#include "Filter/FilterOneByOneInterface.h"
//临时数据缓存区
#define	HRBUF_TEMP_SIZE 20000	
#define NULL 0
template<class T>
class So_BPFilter:public IFilterSegData<T>
{
public:
	So_BPFilter() {};
	So_BPFilter(int nSampleRate)
	{
        memset(this->m_pdbParmA, 0, sizeof(double) * 4);
        memset(this->m_pdbParmB, 0, sizeof(double) * 5);
		double *pdbParmA = nullptr;
		double *pdbParmB = nullptr;
		// 参数数组ParmA
		double s_dbParmA1[4] = { -3.01829599695080, 3.47256995692139, -1.85050139600919, 0.398399411271445 };
		double s_dbParmA2[4] = { -3.19547805137387, 3.88199379511533, -2.15383021149884, 0.468430073003391 };
		double s_dbParmA3[4] = { -3.53295446971604, 4.71089617106857, -2.81743559432937, 0.639658147254532 };

		// 参数数组ParmB
		double s_dbParmB1[5] = { 0.0721477875066581, 0, -0.144295575013316, 0, 0.0721477875066581 };
		double s_dbParmB2[5] = { 0.0517551652464675, 0, -0.103510330492935, 0, 0.0517551652464675 };
		double s_dbParmB3[5] = { 0.0203004378180865, 0, -0.0406008756361731, 0, 0.0203004378180865 };
		switch (nSampleRate)
		{

		case 250:
			pdbParmA = s_dbParmA1;
			pdbParmB = s_dbParmB1;
			break;
		case 300:
			pdbParmA = s_dbParmA2;
			pdbParmB = s_dbParmB2;
			break;
		case 500:
			pdbParmA = s_dbParmA3;
			pdbParmB = s_dbParmB3;
			break;
		default:
			break;
		}
		if (nullptr != pdbParmB && nullptr != pdbParmA)
		{
            memcpy(this->m_pdbParmA, pdbParmA, sizeof(double) * 4);
            memcpy(this->m_pdbParmB, pdbParmB, sizeof(double) * 5);
		}
	}
	~So_BPFilter() {};

	bool Filter(T * pnInData, T * pdbOutData, int nDataLen);

	double m_pdbParmA[4];
	double m_pdbParmB[5];
};

/************************************************************************\
* 函数说明：3-30Hz带通滤波函数(只适用于采样率为250、300和500的情况)
* 参数说明：pInData     原ECG数据  int类型
*           pOutData    滤波后数据 int类型
*           nDataLen    数据长度
* 返 回 值：成功返回true,失败返回false
* 注意事项：无
* 编辑日期：2015-4-13
* 作    者：shenyn zhaogh
************************************************************************/
template<class T>
bool So_BPFilter<T>::Filter(T *pnInData, T *pdbOutData, int nDataLen)
{
	if (nDataLen < 4)
	{
		return false;
	}
	double *dbTemp = new double[nDataLen];
    memset(dbTemp, 0, nDataLen * sizeof(double));

	// pdbOutData前四个元素置零
	pdbOutData[0] = 0;
	pdbOutData[1] = 0;
	pdbOutData[2] = 0;
	pdbOutData[3] = 0;

	// pnInData前四个元素置零
	pnInData[0] = 0;
	pnInData[1] = 0;
	pnInData[2] = 0;
	pnInData[3] = 0;
	
	// 判断参数的有效性
	if ((nullptr == m_pdbParmA) || (nullptr == m_pdbParmB))
	{
		return false;
	}

	// 根据选择的参数,进行滤波操作
	for (int i = 4; i < nDataLen; i++)
	{

		dbTemp[i] = ((m_pdbParmB[0] * pnInData[i])
			+ (m_pdbParmB[2] * pnInData[(i - 2)])
			+ (m_pdbParmB[4] * pnInData[(i - 4)])
			- (m_pdbParmA[0] * dbTemp[i - 1])
			- (m_pdbParmA[1] * dbTemp[i - 2])
			- (m_pdbParmA[2] * dbTemp[i - 3])
			- (m_pdbParmA[3] * dbTemp[i - 4]));

		pdbOutData[i] = static_cast<T>(dbTemp[i]);
	}

	if (dbTemp != NULL)
	{
		delete dbTemp;
		dbTemp = NULL;
	}

	return true;
}



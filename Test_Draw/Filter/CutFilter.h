#pragma once

#include "FilterOneByOneInterface.h"

// 对单个点数据进行带通滤波；
template<class T, int NUM>
class CCutFilter :public IFilterOneByOne<T>
{
public:
	CCutFilter();


    ~CCutFilter() {};
	T Filter(T tOneData);
private:
	void Init();
protected:

    double m_dbA[2];
    double m_dbB[3];

	double	m_dbHPBufIn[NUM + 1];
	double	m_dbHPBufOut[NUM];
};
template<class T, int NUM>
void CCutFilter<T, NUM>::Init()
{
    memset(this->m_dbA, 0, sizeof(double) * 2);
    memset(this->m_dbB, 0, sizeof(double) * 3);

    memset(this->m_dbHPBufIn, 0, sizeof(double)*(NUM + 1));
    memset(this->m_dbHPBufOut, 0, sizeof(double)*NUM);
}
template<class T, int NUM>
CCutFilter<T, NUM>::CCutFilter()
{
	Init();
}

template<class T, int NUM>
// 将原函数中的起搏分离摘了出去；输入数据，应该是没有带起搏脉冲的数据；
T CCutFilter<T, NUM>::Filter(T tOneData)
{
	double temp = 0;

	int k;
	m_dbHPBufIn[NUM] = static_cast<double>(tOneData);
	temp = 0.0;

	for (k = 0; k < NUM; k++)
	{
		temp += m_dbB[k] * m_dbHPBufIn[NUM - k];
		temp -= m_dbA[k] * m_dbHPBufOut[NUM - 1 - k];
	}
	temp += m_dbB[NUM] * m_dbHPBufIn[0];
	for (k = 0; k < NUM - 1; k++)
	{
		m_dbHPBufIn[k] = m_dbHPBufIn[k + 1];
		m_dbHPBufOut[k] = m_dbHPBufOut[k + 1];
	}
	m_dbHPBufIn[NUM - 1] = m_dbHPBufIn[NUM];
	m_dbHPBufOut[NUM - 1] = temp;

	return static_cast<T>(temp);
}

// CUT50_ORDER使用的参数；
// #define CUT50_ORDER 2 需要将NUM设置为2；
// ECGAnalysisDLL 中QRS_Filter使用该类参数；
// MeCECGMeasurementLib 中HPFilter使用该类参数；
template<class T>
class CCut50Filter :public CCutFilter<T, 2>
{
public:
	CCut50Filter(int iMultiple)
	{
		if (iMultiple == 6)
		{
			// 300Hz
			//[b,a]=butter(1,[45,55]/150,'stop') // 50Hz
			//static double b_300[] = { 0.90489201659750,-0.90987641479972,0.90489201659750 };
			//static double a_300[] = { -0.90987641479972,0.80978403319501 };
			//[b,a]=butter(1,[35,65]/150,'stop') // 50Hz
			double a[] = { -0.79360449333484,0.50952544949443 };
			double b[] = { 0.75476272474721,-0.79360449333484,0.75476272474721 };
			//[b,a]=butter(1,[25,75]/150,'stop') // 50Hz
			//static double b_300[] = { 0.63397459621556,-0.73205080756888,0.63397459621556 };
			//static double a_300[] = { -0.73205080756888,0.26794919243112 };
            memcpy(this->m_dbA, a, sizeof(double) * 2);
            memcpy(this->m_dbB, b, sizeof(double) * 3);
		}
		else if (iMultiple == 10)
		{
			// 500Hz
			//[b,a]=butter(1,[35,65]/250,'stop') // 50Hz
			double a[] = { -1.38332689851758,0.67959929822453 };
			double b[] = { 0.83979964911226,-1.38332689851758,0.83979964911226 };
            memcpy(this->m_dbA, a, sizeof(double) * 2);
            memcpy(this->m_dbB, b, sizeof(double) * 3);
		}
		else if (iMultiple == 20)
		{
			// 1000Hz
			//[b,a]=butter(1,[35,65]/500,'stop') // 50Hz
			double a[] = { -1.74558586310929,0.82727194597248 };
			double b[] = { 0.91363597298624,-1.74558586310929,0.91363597298624 };
            memcpy(this->m_dbA, a, sizeof(double) * 2);
            memcpy(this->m_dbB, b, sizeof(double) * 3);
		}

	}
};

//-----------------------------------------------------------------------------------

// QRS使用的参数；
// NUM需要设置为2
// A数组一个参数，B数组两个参数；
template<class T>
class CQRSFilter :public CCutFilter<T, 2>
{
public:
	CQRSFilter(int nMultiple, int nFilterMode);
};
template<class T>
CQRSFilter<T>::CQRSFilter(int nMultiple, int QRS_FilterMode)

{
	double* pdbA = nullptr;
	double* pdbB = nullptr;

	if (nMultiple == 40)
	{
		// 2000Hz
		//[b,a]=butter(1,[2,35]/1000) // 2Hz
		double b_2[] = { 0.04932370687643,0,-0.04932370687643 };
		double a_2[] = { -1.90069523927247,0.90135258624715 };
		//[b,a]=butter(1,[4,35]/1000) // 4Hz
		double b_4[] = { 0.04646864427961,0,-0.04646864427961 };
		double a_4[] = { -1.90574428411133,0.90706271144077 };
		//[b,a]=butter(1,[6,35]/1000) // 6Hz
		double b_6[] = { 0.04359726343247,0,-0.04359726343247 };
		double a_6[] = { -1.91082218701366,0.91280547313506 };

		if (QRS_FilterMode == 1)
		{
			pdbA = a_2;
			pdbB = b_2;
		}
		else if (QRS_FilterMode == 2)
		{
			pdbA = a_4;
			pdbB = b_4;
		}
		else
		{
			pdbA = a_6;
			pdbB = b_6;
		}

	}
	else if (nMultiple == 20)
	{// 1000 Hz
	 // 1000Hz
	 //[b,a]=butter(1,[2,35]/500) // 2Hz
		double b_2[] = { 0.09424029851803,0,-0.09424029851803 };
		double a_2[] = { -1.80900791830758,0.81151940296394 };
		//[b,a]=butter(1,[4,35]/500) // 4Hz
		double b_4[] = { 0.08900299329633,0,-0.08900299329633 };
		double a_4[] = { -1.81694530073959,0.82199401340735 };
		//[b,a]=butter(1,[6,35]/500) // 6Hz
		double b_6[] = { 0.08371130785230,0,-0.08371130785230 };
		double a_6[] = { -1.82496509895663,0.83257738429540 };

		if (QRS_FilterMode == 1)
		{
			pdbA = a_2;
			pdbB = b_2;
		}
		else if (QRS_FilterMode == 2)
		{
			pdbA = a_4;
			pdbB = b_4;
		}
		else {
			pdbA = a_6;
			pdbB = b_6;
		}
	}
	else if (nMultiple == 10)
	{// 500 Hz
	 // 500Hz
	 //[b,a]=butter(1,[2,35]/250) // 2Hz
		double b_2[] = { 0.17380534106848,0,-0.17380534106848 };
		double a_2[] = { -1.64313198598908,0.65238931786305 };
		//[b,a]=butter(1,[4,35]/250) // 4Hz
		double b_4[] = { 0.16477343734338,0,-0.16477343734338 };
		double a_4[] = { -1.65178541250144,0.67045312531323 };
		//[b,a]=butter(1,[6,35]/250) // 6Hz
		double b_6[] = { 0.15558804183322,0,-0.15558804183322 };
		double a_6[] = { -1.66058589880570,0.68882391633355 };

		if (QRS_FilterMode == 1)
		{
			pdbA = a_2;
			pdbB = b_2;
		}
		else if (QRS_FilterMode == 2)
		{
			pdbA = a_4;
			pdbB = b_4;
		}
		else
		{
			pdbA = a_6;
			pdbB = b_6;
		}
	}
	else if (nMultiple == 6)
	{// 300 Hz
	 // 300Hz
	 //[b,a]=butter(1,[2,35]/150) // 2Hz
		double b_2[] = { 0.26471785939387,0,-0.26471785939387 };
		double a_2[] = { -1.44710387965525,0.47056428121225 };
		//[b,a]=butter(1,[4,35]/150) // 4Hz
		double b_4[] = { 0.25179784450632,0,-0.25179784450632 };
		double a_4[] = { -1.44901640928106,0.49640431098737 };
		//[b,a]=butter(1,[6,35]/150) // 6Hz
		double b_6[] = { 0.23860631689066,0,-0.23860631689066 };
		double a_6[] = { -1.45096913051196,0.52278736621869 };

		if (QRS_FilterMode == 1)
		{
			pdbA = a_2;
			pdbB = b_2;
		}
		else if (QRS_FilterMode == 2)
		{
			pdbA = a_4;
			pdbB = b_4;
		}
		else
		{
			pdbA = a_6;
			pdbB = b_6;
		}
	}
	else if (nMultiple == 4)
	{// 200 Hz
	 // 200Hz Sample
	 //[b,a]=butter(1,[2,35]/100) // 2Hz
		double b_2[] = { 0.36321547845888,0,-0.36321547845888 };
		double a_2[] = { -1.22544296830785,0.27356904308224 };
		//[b,a]=butter(1,[4,35]/100) // 4Hz
		double b_4[] = { 0.34617991517005,0,-0.34617991517005 };
		double a_4[] = { -1.21055334002239,0.30764016965990 };
		//[b,a]=butter(1,[6,35]/100) // 6Hz
		double b_6[] = { 0.32881173713566,0,-0.32881173713566 };
		double a_6[] = { -1.19537299578937,0.34237652572868 };

		if (QRS_FilterMode == 1)
		{
			pdbA = a_2;
			pdbB = b_2;
		}
		else if (QRS_FilterMode == 2)
		{
			pdbA = a_4;
			pdbB = b_4;
		}
		else
		{
			pdbA = a_6;
			pdbB = b_6;
		}
	}
	else
	{  // nothing
		double b[] = { 1, 0, 0 };
		double a[] = { 0, 0 };
		pdbA = a; pdbB = b;
	}
    memcpy(this->m_dbA, pdbA, sizeof(double) * 2);
    memcpy(this->m_dbB, pdbB, sizeof(double) * 3);
}

// ECGAnalysisDll中HP_BaseLineFilter中使用的参数为；
// A数组1个参数，B数组2个参数；
// NUM需要设置为1
template<class T>
class CHPBaseLineFilter :public CCutFilter<T, 1>
{
public:
	CHPBaseLineFilter(int nMultiple, int HPBASE_FilterMode);

	

};

template<class T>
CHPBaseLineFilter<T>::CHPBaseLineFilter(int nMultiple, int HPBASE_FilterMode)
{
	double *pdbA = nullptr;
	double *pdbB = nullptr;
	if (nMultiple == 40)
	{
		// 2000Hz
		//[b,a]=butter(1,0.03/1000,'high') // 1000Hz
		double b_1[] = { 0.99995287833072,  -0.99995287833072 };
		double a_1[] = { -0.99990575666144 };
		//[b,a]=butter(1,0.07/1000,'high') // 1000Hz
		double b_2[] = { 0.99989005634562,  -0.99989005634562 };
		double a_2[] = { -0.99978011269123 };
		//[b,a]=butter(1,0.1/1000,'high') // 1000Hz
		double b_3[] = { 0.99984294503616,  -0.99984294503616 };
		double a_3[] = { -0.99968589007233 };

		if (HPBASE_FilterMode == 1)
		{
			pdbA = a_1;
			pdbB = b_1;
		}
		else if (HPBASE_FilterMode == 2)
		{
			pdbA = a_2;
			pdbB = b_2;
		}
		else
		{
			pdbA = a_3;
			pdbB = b_3;
		}

	}
	else if (nMultiple == 20)
	{// 1000 Hz
	 // 1000Hz
	 //[b,a]=butter(1,0.03/500,'high') // 500Hz
		double b_1[] = { 0.99990576110192,  -0.99990576110192 };
		double a_1[] = { -0.99981152220384 };
		//[b,a]=butter(1,0.07/500,'high') // 500Hz
		double b_2[] = { 0.99978013686113,  -0.99978013686113 };
		double a_2[] = { -0.99956027372227 };
		//[b,a]=butter(1,0.1/500,'high') // 500Hz
		double b_3[] = { 0.99968593938936,  -0.99968593938936 };
		double a_3[] = { -0.99937187877872 };

		if (HPBASE_FilterMode == 1)
		{
			pdbA = a_1;
			pdbB = b_1;
		}
		else if (HPBASE_FilterMode == 2)
		{
			pdbA = a_2;
			pdbB = b_2;
		}
		else
		{
			pdbA = a_3;
			pdbB = b_3;
		}
	}
	else if (nMultiple == 12)
	{// 600 Hz
	 // 600Hz
	 //[b,a]=butter(1,0.03/300,'high') // 300Hz
		double b_1[] = { 0.99984294503616,  -0.99984294503616 };
		double a_1[] = { -0.99968589007233 };
		//[b,a]=butter(1,0.07/300,'high') // 300Hz
		double b_2[] = { 0.99963361512774,  -0.99963361512774 };
		double a_2[] = { -0.99926723025549 };
		//[b,a]=butter(1,0.1/300,'high') // 300Hz
		double b_3[] = { 0.99947667518881,  -0.99947667518881 };
		double a_3[] = { -0.99895335037762 };

		if (HPBASE_FilterMode == 0)
		{
			pdbA = a_1;
			pdbB = b_1;
		}
		else if (HPBASE_FilterMode == 1)
		{
			pdbA = a_2;
			pdbB = b_2;
		}
		else
		{
			pdbA = a_3;
			pdbB = b_3;
		}
	}
	else if (nMultiple == 10)
	{// 500 Hz
	 // 500Hz
	 //[b,a]=butter(1,0.03/250,'high') // 250Hz
		double b_1[] = { 0.99981153996243,  -0.99981153996243 };
		double a_1[] = { -0.99962307992487 };
		//[b,a]=butter(1,0.07/250,'high') // 250Hz
		double b_2[] = { 0.99956037035936,  -0.99956037035936 };
		double a_2[] = { -0.99912074071873 };
		//[b,a]=butter(1,0.1/250,'high') // 250Hz
		//static double b_3[] = { 0.99937207592298,  -0.99937207592298 };
		//static double a_3[] = { -0.99874415184597 };
		double b_3[] = { 0.999372075922984,-0.999372075922984 };
		double a_3[] = { -0.998744151845968 };
		//[b,a]=butter(1,0.3/250,'high') // 500Hz
		double b_4[] = { 0.998118588556613,-0.998118588556613 };
		double a_4[] = { -0.996237177113225 };

		if (HPBASE_FilterMode == 0)
		{
			pdbA = a_1;
			pdbB = b_1;
		}
		else if (HPBASE_FilterMode == 1)
		{
			pdbA = a_2;
			pdbB = b_2;
		}
		else if (HPBASE_FilterMode == 2)
		{
			pdbA = a_3;
			pdbB = b_3;
		}
		else if (HPBASE_FilterMode == 3)
		{
			pdbA = a_4;
			pdbB = b_4;
		}
	}
	else if (nMultiple == 6)
	{// 300 Hz
	 // 300Hz
	 // [b,a]=butter(1,0.02/150,'high') // 150Hz
		double b_0[] = { 0.99989529120958,  -0.99989529120958 };
		double a_0[] = { -0.99979058241915 };
		//[b,a]=butter(1,0.03/150,'high') // 150Hz
		double b_1[] = { 0.99968593938936,  -0.99968593938936 };
		double a_1[] = { -0.99937187877872 };
		//[b,a]=butter(1,0.07/150,'high') // 150Hz
		double b_2[] = { 0.99926749853458,  -0.99926749853458 };
		double a_2[] = { -0.99853499706916 };
		//[b,a]=butter(1,0.1/150,'high') // 150Hz
		double b_3[] = { 0.99895389754234,  -0.99895389754234 };
		double a_3[] = { -0.99790779508468 };

		if (HPBASE_FilterMode == 0)
		{
			pdbA = a_0;
			pdbB = b_0;
		}
		else if (HPBASE_FilterMode == 1)
		{
			pdbA = a_1;
			pdbB = b_1;
		}
		else if (HPBASE_FilterMode == 2)
		{
			pdbA = a_2;
			pdbB = b_2;
		}
		else
		{
			pdbA = a_3;
			pdbB = b_3;
		}
	}
	else if (nMultiple == 5)
	{
		// 250Hz
		//[b,a]=butter(1,0.001/150,'high') // 150Hz
		//static double b_1[] = { 0.99998743378730,  -0.99998743378730 };
		//static double a_1[] = { -0.99997486757459 };
		//[b,a]=butter(1,0.03/250,'high') // 250Hz
		double b_1[] = { 0.999623150932468,  -0.999623150932468 };
		double a_1[] = { -0.999246301864936 };
		//[b,a]=butter(1,0.07/150,'high') // 150Hz
		double b_2[] = { 0.99912112692744,  -0.99912112692744 };
		double a_2[] = { -0.99824225385489 };
		//[b,a]=butter(1,0.1/150,'high') // 150Hz
		double b_3[] = { 0.998744939433549,-0.998744939433549 };
		double a_3[] = { -0.997489878867098 };
		//[b,a]=butter(1,0.3/125,'high') // 250Hz
		double b_4[] = { 0.996244229942597,-0.996244229942597 };
		double a_4[] = { -0.992488459885195 };

		if (HPBASE_FilterMode == 0)
		{
			pdbA = a_1;
			pdbB = b_1;
		}
		else if (HPBASE_FilterMode == 1)
		{
			pdbA = a_2;
			pdbB = b_2;
		}
		else if (HPBASE_FilterMode == 2)
		{
			pdbA = a_3;
			pdbB = b_3;
		}
		else if (HPBASE_FilterMode == 3)
		{
			pdbA = a_4;
			pdbB = b_4;
		}
	}
	else if (nMultiple == 4)
	{// 200 Hz
	 // 200Hz Sample
	 //[b,a]=butter(1,0.03/100,'high') // 100Hz
		double b_1[] = { 0.99952898302861,  -0.99952898302861 };
		double a_1[] = { -0.99905796605723 };
		//[b,a]=butter(1,0.07/100,'high') // 100Hz
		double b_2[] = { 0.99890164982769,  -0.99890164982769 };
		double a_2[] = { -0.99780329965538 };
		//[b,a]=butter(1,0.1/100,'high') // 100Hz
		double b_3[] = { 0.99843166591672,  -0.99843166591672 };
		double a_3[] = { -0.99686333183344 };

		if (HPBASE_FilterMode == 1)
		{
			pdbA = a_1;
			pdbB = b_1;
		}
		else if (HPBASE_FilterMode == 2)
		{
			pdbA = a_2;
			pdbB = b_2;
		}
		else
		{
			pdbA = a_3;
			pdbB = b_3;
		}
	}
	else
	{  // nothing
		double b[] = { 1, 0, 0 };
		double a[] = { 0, 0 };
		pdbA = a;
		pdbB = b;
	}
    memcpy(this->m_dbA, pdbA, sizeof(double) * 1);
    memcpy(this->m_dbB, pdbB, sizeof(double) * 2);
}

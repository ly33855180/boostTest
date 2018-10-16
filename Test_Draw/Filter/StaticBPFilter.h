#pragma once

#include "FilterOneByOneInterface.h"
// 静态心电使用的带通滤波；
template<class T>
class CStaticBPFilter :public IFilterOneByOne<T>
{
public:
	CStaticBPFilter();
	virtual T Filter(T tOrgData);
private:
	void Init();
	
protected:
	enum constEnum
	{
		NUM = 2,
	};
	double	m_dbHPBufIn[NUM + 1];
	double	m_dbHPBufOut[NUM];

	double m_A[2];
	double m_B;
	bool m_Init;

};
template<class T>
void CStaticBPFilter<T>::Init()
{
	m_B = 0;
    memset(this->m_A, 0, sizeof(double) * 2);
    memset(this->m_dbHPBufIn, 0, sizeof(double)*(NUM + 1));
    memset(this->m_dbHPBufOut, 0, sizeof(double)*NUM);
}

template<class T>
inline CStaticBPFilter<T>::CStaticBPFilter()
	:m_Init(false)		
{	
	Init();
}

template<class T>
T CStaticBPFilter<T>::Filter(T tOrgData)
{	
	double dbCurValue = static_cast<double>(tOrgData);
	if (!m_Init)
	{
		for (int k = 0; k < NUM; k++)
		{
			m_dbHPBufIn[k] = dbCurValue;
			m_dbHPBufOut[k] = dbCurValue;
		}
	}

	double	temp = 0.0;

	m_dbHPBufIn[NUM] = dbCurValue;
	temp += m_B * (-m_dbHPBufIn[0] + m_dbHPBufIn[2]);

	for (int k = 0; k < NUM; k++)
	{
		temp -= m_A[k] * m_dbHPBufOut[NUM - 1 - k];
	}

	for (int k = 0; k < NUM - 1; k++)
	{
		m_dbHPBufIn[k] = m_dbHPBufIn[k + 1];
		m_dbHPBufOut[k] = m_dbHPBufOut[k + 1];
	}

	m_dbHPBufIn[NUM - 1] = m_dbHPBufIn[NUM];
	m_dbHPBufOut[NUM - 1] = temp;

	return	static_cast<T>(temp);
}

template<class T>
class CBPFilter :public CStaticBPFilter<T>
{
public:
	CBPFilter(int iMultiple)
	{
		double *pdbA = nullptr;
		if (iMultiple == 5)
		{// 250 Hz

			double b_40 = 0.020919120808648;
			double a_40[] = { -1.957790649033331, 0.958161758382704 };
            pdbA = a_40;
            this->m_B = b_40;
		}
		else if (iMultiple == 2)
		{// 100 Hz
			double b_40 = 0.050745179751877;
			double a_40[] = { -1.896259439855798, 0.898509640496245 };
            pdbA = a_40;
            this->m_B = b_40;
		}
		else
		{  // nothing
			double b = 1;
			double a[] = { 0, 0 };
            pdbA = a;
            this->m_B = b;
		}
        memcpy(this->m_A, pdbA, sizeof(double) * 2);
	};
};

template<class T>
class CStaticLPFilter :public CStaticBPFilter<T>
{
public:
	CStaticLPFilter(int nMultiple, int LowFilterMode);
	~CStaticLPFilter() {};
	virtual T Filter(T tOrgData);
};

template<class T>
CStaticLPFilter<T>::CStaticLPFilter(int nMultiple,int LowFilterMode)
{
	double *pdbA = nullptr;
	if (nMultiple == 40)
	{
		// 2000Hz
		//[b,a]=butter(2,15/1000) // 15Hz
		double b_15 = 0.00053716977481;
		double a_15[] = { -1.93338022587993,0.93552890497918 };
		//[b,a]=butter(2,35/1000) // 35Hz
		double b_35 = 0.00280209672777;
		double a_35[] = { -1.84477840502346,0.85598679193455 };
		//[b,a]=butter(2,70/1000) // 70Hz
		double b_70 = 0.01043241337109;
		double a_70[] = { -1.69099637688744,0.73272603037182 };
		//[b,a]=butter(2,100/1000) // 100Hz
		double b_100 = 0.02008336556421;
		double a_100[] = { -1.56101807580072,0.64135153805756 };
		//[b,a]=butter(2,150/1000) // 150Hz
		double b_150 = 0.04125353724172;
		double a_150[] = { -1.34896774525279,0.51398189421968 };

		if (LowFilterMode == 1)
		{
			pdbA = a_100;
            this->m_B = b_100;
		}
		else if (LowFilterMode == 2) 
		{
			pdbA = a_70;
            this->m_B = b_70;
		}
		else if (LowFilterMode == 3) 
		{
			pdbA = a_35;
            this->m_B = b_35;
		}
		else if (LowFilterMode == 4)
		{
			pdbA = a_15;
            this->m_B = b_15;
		}
		else
		{
			pdbA = a_150;	
            this->m_B = b_150;
		}
	}
	else if (nMultiple == 24)
	{// 1200 Hz
		// 1200Hz
		//[b,a]=butter(2,40/600) // 15Hz
		double b_40 = 0.00952576237620;
		double a_40[] = { -1.70555214554408,0.74365519504887 };
		//[b,a]=butter(2,70/600) // 70Hz
		double b_70 = 0.02649566776566;
		double a_70[] = { -1.48967152352787,0.59565419459052 };
		//[b,a]=butter(2,100/600) // 100Hz
		double b_100 = 0.04948995626868;
		double a_100[] = { -1.27963242499781,0.47759225007252 };
		//[b,a]=butter(2,150/600) // 150Hz
		double b_150 = 0.09763107293782;
		double a_150[] = { -0.94280904158206,0.33333333333333 };
		//[b,a]=butter(2,200/600) // 200Hz
		double b_200 = 0.15505102572168;
		double a_200[] = { -0.62020410288673,0.24040820577346 };
		//[b,a]=butter(2,300/600) // 200Hz
		double b_300 = 0.29289321881345;
		double a_300[] = { -0.00000000000000,0.17157287525381 };

		if (LowFilterMode == 1)
		{
			pdbA = a_150;
            this->m_B = b_150;
		}
		else if (LowFilterMode == 2)
		{
			pdbA = a_100;
            this->m_B = b_100;
		}
		else if (LowFilterMode == 3) 
		{
			pdbA = a_70;
            this->m_B = b_70;
		}
		else if (LowFilterMode == 4)
		{
			pdbA = a_40;
            this->m_B = b_40;
		}
		else
		{
			pdbA = a_200;
            this->m_B = b_200;
		}
	}
	else if (nMultiple == 20)
	{// 1000 Hz
		// 1000Hz
		//[b,a]=butter(2,15/500) // 15Hz
		double b_15 = 0.00208056713549;
		double a_15[] = { -1.86689227971171,0.87521454825368 };
		//[b,a]=butter(2,35/500) // 35Hz
		double b_35 = 0.01043241337109;
		double a_35[] = { -1.69099637688744,0.73272603037182 };
		//[b,a]=butter(2,70/500) // 70Hz
		double b_70 = 0.03657483584393;
		double a_70[] = { -1.39089528142539,0.53719462480110 };
		//[b,a]=butter(2,100/500) // 100Hz
		double b_100 = 0.06745527388907;
		double a_100[] = { -1.14298050253990,0.41280159809619 };
		//[b,a]=butter(2,150/500) // 150Hz
		double b_150 = 0.13110643991663;
		double a_150[] = { -0.74778917825850,0.27221493792501 };

		if (LowFilterMode == 1) 
		{
			pdbA = a_100;
            this->m_B = b_100;
		}
		else if (LowFilterMode == 2)
		{
			pdbA = a_70;
            this->m_B = b_70;
		}
		else if (LowFilterMode == 3) 
		{
			pdbA = a_35;
            this->m_B = b_35;
		}
		else if (LowFilterMode == 4)
		{
			pdbA = a_15;
            this->m_B = b_15;
		}
		else 
		{
			pdbA = a_150;
            this->m_B = b_150;
		}
	}
	else if (nMultiple == 12)
	{// 600 Hz
		// 600Hz
		//[b,a]=butter(2,40/300) // 40Hz
		double b_40 = 0.03357180936764;
		double a_40[] = { -1.41898265221812,  0.55326988968868 };
		//[b,a]=butter(2,70/300) // 70Hz
		double b_70 = 0.08717908371248;
		double a_70[] = { -1.00892162396499, 0.35763795881491 };
		//[b,a]=butter(2,100/300) // 100Hz
		double b_100 = 0.15505102572168;
		double a_100[] = { -0.62020410288673, 0.24040820577346 };
		//[b,a]=butter(2,150/300) // 150Hz
		double b_150 = 0.29289321881345;
		double a_150[] = { -0.00000000000000,  0.17157287525381 };
		//[b,a]=butter(2,200/300) // 200Hz
		double b_200 = 0.46515307716505;
		double a_200[] = { 0.62020410288673,  0.24040820577346 };

		if (LowFilterMode == 1)
		{
			pdbA = a_150;
            this->m_B = b_150;
		}
		else if (LowFilterMode == 2)
		{
			pdbA = a_100;
            this->m_B = b_100;
		}
		else if (LowFilterMode == 3)
		{
			pdbA = a_70;
            this->m_B = b_70;
		}
		else if (LowFilterMode == 4)
		{
			pdbA = a_40;
            this->m_B = b_40;
		}
		else 
		{
			pdbA = a_200;
            this->m_B = b_200;
		}

	}
	else if (nMultiple == 10)
	{// 500 Hz
		// 500Hz
		//[b,a]=butter(2,15/250) // 15Hz
		//static double b_15 = 0.00782020803350;
		//static double a_15[] = { -1.73472576880928,0.76600660094326 };
		//[b,a]=butter(2,35/250) // 35Hz
		static double b_35 = 0.03657483584393;
		static double a_35[] = { -1.39089528142539,  0.53719462480110 };
		//[b,a]=butter(2,70/250) // 70Hz
		static double b_70 = 0.11735103672461;
		static double a_70[] = { -0.82523238068948, 0.29463652758791 };
		//[b,a]=butter(2,100/250) // 100Hz
		static double b_100 = 0.20657208382615;
		static double a_100[] = { -0.36952737735124, 0.19581571265583 };
		//[b,a]=butter(2,150/250) // 150Hz
		static double b_150 = 0.39133577250177;
		static double a_150[] = { 0.36952737735124,  0.19581571265583 };
		//[b,a]=butter(2,150/250) // 200Hz
		static double b_200 = 0.63894552515902;
		static double a_200[] = { 1.14298050253990,  0.41280159809619 };

		if (LowFilterMode == 1)
		{
			pdbA = a_150;
            this->m_B = b_150;
		}
		else if (LowFilterMode == 2)
		{
			pdbA = a_100;
            this->m_B = b_100;
		}
		else if (LowFilterMode == 3)
		{
			pdbA = a_70;
            this->m_B = b_70;
		}
		else if (LowFilterMode == 4) 
		{
			pdbA = a_35;
            this->m_B = b_35;
		}
		else
		{
			pdbA = a_200;
            this->m_B = b_200;
		}

	}
	else if (nMultiple == 6)
	{// 300 Hz
		// 300Hz
		//[b,a]=butter(2,15/150) // 35Hz
		double b_15 = 0.02008336556421;
		double a_15[] = { -1.56101807580072,0.64135153805756 };
		//[b,a]=butter(2,35/150) // 35Hz
		double b_35 = 0.08717908371248;
		double a_35[] = { -1.00892162396499, 0.35763795881491 };
		//[b,a]=butter(2,70/150) // 70Hz
		double b_70 = 0.26287402958593;
		double a_70[] = { -0.12274122501252, 0.17423734335624 };
		//[b,a]=butter(2,100/150) // 100Hz
		double b_100 = 0.46515307716505;
		double a_100[] = { 0.62020410288673, 0.24040820577346 };
		//[b,a]=butter(2,120/150) // 120Hz
		double b_120 = 0.63894552515902;
		double a_120[] = { 1.14298050253990, 0.41280159809619 };

		if (LowFilterMode == 1) 
		{
			pdbA = a_100;
            this->m_B = b_100;
		}
		else if (LowFilterMode == 2) 
		{
			pdbA = a_70;
            this->m_B = b_70;
		}
		else if (LowFilterMode == 3) 
		{
			pdbA = a_35;
            this->m_B = b_35;
		}
		else if (LowFilterMode == 4)
		{
			pdbA = a_15;
            this->m_B = b_15;
		}
		else {
			pdbA = a_120;
            this->m_B = b_120;
		}

	}
	else if (nMultiple == 5)
	{// 250 Hz
		// 250Hz
		//[b,a]=butter(2,15/125) // 15Hz
		double b_15 = 0.02785976611714;
		double a_15[] = { -1.47548044359265,0.58691950806119 };
		//[b,a]=butter(2,30/125) // 30Hz
		double b_30 = 0.091314900435832;
		double a_30[] = { -0.982405793108395, 0.347665394851723 };
		//[b,a]=butter(2,35/125) // 35Hz
		double b_35 = 0.11735103672461;
		double a_35[] = { -0.82523238068948, 0.29463652758791 };
		//[b,a]=butter(2,40/125) // 40Hz
		double b_40 = 0.145323883877042;
		double a_40[] = { -0.671029090774096, 0.252324626282266 };
		//[b,a]=butter(2,70/150) // 70Hz
		double b_70 = 0.35034637785541;
		double a_70[] = { 0.22115343752331, 0.18023207389835 };
		//[b,a]=butter(2,100/150) // 100Hz
		double b_100 = 0.63894552515902;
		double a_100[] = { 1.14298050253990, 0.41280159809619 };
		// 30HZ低通滤波
		if (1 == LowFilterMode)
		{
			pdbA = a_30;
            this->m_B = b_30;
		}
		else if (2 == LowFilterMode)
		{
			pdbA = a_70;
            this->m_B = b_70;
		}
		// zucs[2015/3/10] 修改增加40Hz低通滤波-开始
		else if (3 == LowFilterMode)
		{
			pdbA = a_40;
            this->m_B = b_40;
		}
		// zucs[2015/3/10] 修改增加40Hz低通滤波-结束
		else if (4 == LowFilterMode)
		{
			pdbA = a_35;
            this->m_B = b_35;
		}
		else if (5 == LowFilterMode)
		{
			pdbA = a_15;
            this->m_B = b_15;
		}
		else
		{
			pdbA = a_100;
            this->m_B = b_100;
		}

	}
	else if (nMultiple == 4)
	{// 200 Hz
		// 200Hz Sample
		//[b,a]=butter(2,15/100) // 15Hz
		static double b_15 = 0.04125353724172;
		static double a_15[] = { -1.34896774525279,0.51398189421968 };
		//[b,a]=butter(2,35/100) // 35Hz
		static double b_35 = 0.16748380012702;
		static double a_35[] = { -0.55703099731175, 0.22696619781982 };
		//[b,a]=butter(2,70/100) // 70Hz
		static double b_70 = 0.50500102904588;
		static double a_70[] = { 0.74778917825850, 0.27221493792501 };
		if (LowFilterMode == 3) 
		{
			pdbA = a_35;
            this->m_B = b_35;
		}
		else
		{
			pdbA = a_70;
            this->m_B = b_70;
		}

	}
	else if (nMultiple == 2)
	{// 100 Hz

		// 100Hz Sample
		//[b,a]=butter(2,30/50) // 30Hz
		double b_30 = 0.391335772501769;
		double a_30[] = { 0.369527377351241,0.195815712655833 };
		//[b,a]=butter(2,40/50) // 40Hz
		double b_40 = 0.638945525159022;
		double a_40[] = { 1.142980502539901, 0.412801598096189 };
		// zucs[2015/3/25] 支持采样率100HZ
		if (1 == LowFilterMode)
		{
			pdbA = a_30;
            this->m_B = b_30;
		}
		else if (2 == LowFilterMode)
		{
			pdbA = a_40;
            this->m_B = b_40;
		}
	}
	else
	{  // nothing
		double b = 1;
		double a[] = { 0, 0 };

		pdbA = a;
        this->m_B = b;
	}
	
    memcpy(this->m_A, pdbA, sizeof(double) * 2);
}

template<class T>
T CStaticLPFilter<T>::Filter(T tOrgData)
{
	double	temp = 0.0;		
    this->m_dbHPBufIn[this->NUM] = static_cast<double>(tOrgData);
	
    temp += this->m_B * (this->m_dbHPBufIn[0] + 2 * this->m_dbHPBufIn[1] + this->m_dbHPBufIn[2]);
    for (int k = 0; k < this->NUM; k++)
	{
        temp -= this->m_A[k] * this->m_dbHPBufOut[this->NUM - 1 - k];
	}

    for (int k = 0; k < this->NUM - 1; k++)
	{
        this->m_dbHPBufIn[k] = this->m_dbHPBufIn[k + 1];
        this->m_dbHPBufOut[k] = this->m_dbHPBufOut[k + 1];
	}

    this->m_dbHPBufIn[this->NUM - 1] = this->m_dbHPBufIn[this->NUM];
    this->m_dbHPBufOut[this->NUM - 1] = temp;

	return	static_cast<T>(temp);
}


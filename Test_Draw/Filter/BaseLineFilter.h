#ifndef BASE_LINE_FILTER_H
#define BASE_LINE_FILTER_H
#define FIR_TRAP_LEN 80
#include "FilterOneByOneInterface.h"
//#include "CommonFun.h"
//#include "Shell.h"

// 基线滤波；// 该滤波采用了窗口式的滤波；
// 新添0.07Hz基线漂移滤波器
// 滤除工频干扰(IF)并抑制基线(BL)漂移
// h_07滤波器在f = 0Hz, 50Hz, 100Hz, 150Hz...处构成3Hz宽的陷波
template<class T>
class CBaseLineFilter:public IFilterSegData<T>
{
public:	
	CBaseLineFilter(int nSampleRate);
	~CBaseLineFilter();

	bool Filter(T * pDealedData, T* ptDstData, int nDataLength);
private:
	// 80阶滤波器；
	static double m_h_07[FIR_TRAP_LEN + 1];

	int m_nSampleRate;	// 采样率；
};
template<class T>
double CBaseLineFilter<T>::m_h_07[FIR_TRAP_LEN + 1] =
{  // 0.8Hz
	-0.00174172605455,-0.00183191994101,-0.00190674124767,-0.00196413224584,-0.00200212801611,-0.00201888668406,
	-0.00201271959284,-0.00198212104135,-0.00192579720961,-0.00184269389037,-0.00173202264784,-0.00159328503144,
	-0.00142629448351,-0.00123119559638,-0.00100848039474,-0.00075900134459,-0.00048398081934,-0.00018501678722,
	0.00013591547873,0.00047646582644,0.00083391590126,0.00120519014239,0.00158687112062,0.00197521918988,
	0.00236619637489,0.00275549436705,0.00313856645086,0.00351066313394,0.00386687120648,0.00420215591028,
	0.00451140585506,0.00478948028001,0.00503125822305,0.00523168912840,0.00538584439659,0.00548896935903,
	0.00553653514295,0.00552428988189,0.00544830872202,0.00530504207608,0.00509136158385,0.00480460325188,
	0.00444260726479,0.00400375398589,0.00348699569651,0.00289188366005,0.00221859013872,0.00146792503773,
	0.00064134690258,-0.00025903195031,-0.00123044633144,-0.00226948520587,-0.00337210488996,-0.00453364839260,
	-0.00574887081250,-0.00701197063902,-0.00831662674124,-0.00965604076811,-0.01102298462392,-0.01240985262676,
	-0.01380871790538,-0.01521139254139,-0.01660949092044,-0.01799449571771,-0.01935782591085,-0.02069090618725,
	-0.02198523709287,-0.02323246525701,-0.02442445302158,-0.02555334680451,-0.02661164353510,-0.02759225451473,
	-0.02848856607812,-0.02929449645959,-0.03000454830387,-0.03061385630230,-0.03111822948240,-0.03151418773059,
	-0.03179899218466,-0.03197066919290,0.96799913092711
};

template<class T>
CBaseLineFilter<T>::CBaseLineFilter(int nSampleRate)
	:m_nSampleRate(nSampleRate)
{
}

template<class T>
CBaseLineFilter<T>::~CBaseLineFilter()
{
}

template<class T>
bool CBaseLineFilter<T>::Filter(T * pDealedData, T* ptDstData, int nDataLength)
{
	int Index, SubIndex, ForwardLen, BackwardLen;
	unsigned char Step;
	double Sum;
    //Step = (int)TIME_TO_POINTS(0.02, this->m_nSampleRate);
    Step = int(0.02 * this->m_nSampleRate + 0.5);
	//int *pTempDataStart = new int[nDataLength];

	for (Index = 0; Index < nDataLength; Index++)
	{
		ForwardLen = (Index < (nDataLength - 1 - FIR_TRAP_LEN*Step))
			? FIR_TRAP_LEN : ((nDataLength - 1 - Index) / Step);
		BackwardLen = (Index > FIR_TRAP_LEN*Step) ? FIR_TRAP_LEN : (Index / Step);

		Sum = m_h_07[FIR_TRAP_LEN] * pDealedData[Index];

		for (SubIndex = 1; SubIndex <= FIR_TRAP_LEN; SubIndex++)
		{
			if (SubIndex <= ForwardLen)
			{
				Sum += m_h_07[FIR_TRAP_LEN - SubIndex] * pDealedData[Index + SubIndex*Step];
			}
			else
			{
				Sum += m_h_07[FIR_TRAP_LEN - SubIndex] * pDealedData[nDataLength - 1];
			}

			if (SubIndex <= BackwardLen)
			{
				Sum += m_h_07[FIR_TRAP_LEN - SubIndex] * pDealedData[Index - SubIndex*Step];
			}
			else
			{
				Sum += m_h_07[FIR_TRAP_LEN - SubIndex] * pDealedData[0];
			}
		}
		//pTempDataStart[Index] = (int)Sum;
		ptDstData[Index] = (int)Sum;
	}

	//for (Index = 0; Index < nDataLength; Index++)
	//{
	//	ptDstData[Index] = pTempDataStart[Index];
	//}
	//delete[] pTempDataStart;
	return true;
}
#endif // !BASE_LINE_FILTER_H

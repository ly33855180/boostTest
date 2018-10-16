/*++
Module Name:
    FilterType.h
Abstract:
	Normally there are four types of noise: baseline drift, EMG, industry frequency and
	high frequency noise. To reduce those noise, we use four kinds of filter. All information 
	related to filter must be send to ECGAnalysis.dll where the signal is filtered. All those 
	Information are defined here.
Author:
	Ma Yaquan
Revision History:
	Ma Yaquan			3/20/2003	1.00	Initial Version
--*/

#ifndef _FILTER_TYPE_
#define _FILTER_TYPE_
//#include "ECGReader/ECGParameter.h"
enum FILTER_TYPE
{
	FT_NULL,
	FT_1,
	FT_2,
	FT_3,
	FT_4,
	FT_5,
	FT_6
}; // low pass filter

struct FILTER_INFO
{
	FILTER_TYPE ftIndustryFreq;
    FILTER_TYPE ftEMG;
    FILTER_TYPE ftBaseline;
    FILTER_TYPE ftLowpass;
};

enum
{
	ECG,
	VCG,
	VLP,
	HRV
};

/*******************************************************************
≤Ó÷µÀ„∑®
*******************************************************************/
#define TARGET_RESOLUTION   10       // 5-millisecond target resolution
//#define CHANNELNUM_IN 12
//#define CHANNELNUM_OUT 19
#define B_SPLINE_HALF_LENGTH 20
#define B_SPLINE_ORDER 5
#define INDRIECT_HALF_LENGTH 5

#define FIR_TRAP_LEN 80
#define  IniFileName                  "MEViewer.ini"
#define TOTAL_LEAD V6
#endif


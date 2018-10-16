/*
 * Public.h
 *
 *  Created on: 2015-2-12
 *      Author: MedEx_YD
 */

#ifndef PUBLIC_H_
#define PUBLIC_H_

//#include<android/log.h>


//#define TAG "SampleMIH_SO" // 这个是自定义的LOG的标识
//#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
//#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
//#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
//#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
//#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

#include <stdio.h>

#define TAG "SampleMIH_SO" // 这个是自定义的LOG的标识
//#define LOGD(fmt,...) printf(fmt, ##__VA_ARGS__,"\n") // 定义LOGD类型
//#define LOGI(fmt,...) printf(fmt,  ##__VA_ARGS__,"\n") // 定义LOGI类型
//#define LOGW(fmt,...) printf(fmt,  ##__VA_ARGS__,"\n") // 定义LOGW类型
//#define LOGE(fmt,...) printf(fmt,  ##__VA_ARGS__,"\n") // 定义LOGE类型
//#define LOGF(fmt,...) printf(fmt,  ##__VA_ARGS__,"\n") // 定义LOGF类型

#define LOGD(fmt,...) printf("[DEBUG] [%s(%d)<%s>] : " fmt"\n",(__FILE__),__LINE__,__FUNCTION__,##__VA_ARGS__) // 定义LOGD类型
#define LOGI(fmt,...) printf("[INFO ] [%s(%d)<%s>] : " fmt"\n",(__FILE__),__LINE__,__FUNCTION__,##__VA_ARGS__) // 定义LOGI类型
#define LOGW(fmt,...) printf("[WARN ] [%s(%d)<%s>] : " fmt"\n",(__FILE__),__LINE__,__FUNCTION__,##__VA_ARGS__) // 定义LOGW类型
#define LOGE(fmt,...) printf("[ERROR] [%s(%d)<%s>] : " fmt"\n",(__FILE__),__LINE__,__FUNCTION__,##__VA_ARGS__) // 定义LOGE类型
#define LOGF(fmt,...) printf(fmt,  ##__VA_ARGS__) // 定义LOGF类型

//最大原始数据写入长度 写入 80秒 500点 60包长    80秒
//#define		MAX_ORIG_WRITE_NUM  			80 * 500 * 60

//修改为可以存储5分钟的数据
#define		MAX_ORIG_WRITE_NUM  			5 * 60 * 500 * 60

//最大原始数据写入长度 写入2分钟数据  60秒 250点 12通道   大约占用2.7M内存空间
//#define		MAX_WRITE_NUM  80 * 500 * 18
#define		MAX_WRITE_NUM  					5 * 60 * 500 * 18

/////////////////////////
//处理数据的宏定义
#define CHANNELNUM           18
#define CHANNELNUM_IN        18
#define CHANNELNUM_OUT       18
#define RA                   Data[0]
#define LA                   Data[1]
#define V1                   Data[2]
#define V2                   Data[3]
#define V3                   Data[4]
#define V4                   Data[5]
#define V5                   Data[6]
#define V6                   Data[7]
#define VH                   Data[7]
#define VIA                  Data[8]      // 右侧中线第5肋间
#define VEA                  Data[9]      // 前中线第5肋间
#define VCA                  Data[5]
#define VAA                  Data[7]
#define VMA                  Data[10]     // 背
#define VHA                  Data[11]     // 颈
#define V7                   Data[8]
#define V8                   Data[9]
#define V9                   Data[10]
#define V3R                  Data[11]
#define V4R                  Data[12]
#define V5R                  Data[13]
#define V6R                  Data[14]
#define MFT                  Data[15]
/////////////////////////

typedef unsigned char BYTE;

#endif /* PUBLIC_H_ */

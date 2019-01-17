#pragma once
/*****************************************************************************
* 名称: APO_SeedSize.h
* 模块: XXX
* 描述: 用于返回种子大小比较的函数接口
*
* 作者: ParticularJ
* 日期: 2018.12.24
* 版本: 1.0
*
* Copyright (c) 2018.
* All rights reserved.
*****************************************************************************
*
* @change:
* @change:
*
*****************************************************************************/

#ifdef SEEDSIZEDLL_EXPORTS
#define SEEDSIZEDLL  _declspec(dllexport)
#else
#define SEEDSIZEDLL  _declspec(dllimport)
#endif 

#include"API_SeedSize.h"

typedef unsigned char uchar;
/*****************************************************************
** 函数功能：输出种子排序图
** 输入参数：src:种子的二值图， dst:种子的原图 //图像文件
** 输出结果：Mat 排序完成图 //检测线和对照线颜色深浅的比值
** 创建作者：ParticularJ
** 函数版本：1.0  2018.12.24
** 修改说明:
******************************************************************/

extern "C" __declspec(dllexport) int __stdcall simuStr(SeedInfo* seedInfo);

extern "C" __declspec(dllexport) int __stdcall getImage(int seedNum, bool sortByHeightOrWidth, uchar* src_data, int src_width, int src_height, int src_step, uchar* dst_data, int dst_width, int dst_height, int dst_step, uchar* pfinal_pic, SeedInfo* seedInfo);


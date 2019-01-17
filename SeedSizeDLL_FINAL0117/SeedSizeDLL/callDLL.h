#pragma once
/*****************************************************************************
* ����: APO_SeedSize.h
* ģ��: XXX
* ����: ���ڷ������Ӵ�С�Ƚϵĺ����ӿ�
*
* ����: ParticularJ
* ����: 2018.12.24
* �汾: 1.0
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
** �������ܣ������������ͼ
** ���������src:���ӵĶ�ֵͼ�� dst:���ӵ�ԭͼ //ͼ���ļ�
** ��������Mat �������ͼ //����ߺͶ�������ɫ��ǳ�ı�ֵ
** �������ߣ�ParticularJ
** �����汾��1.0  2018.12.24
** �޸�˵��:
******************************************************************/

extern "C" __declspec(dllexport) int __stdcall simuStr(SeedInfo* seedInfo);

extern "C" __declspec(dllexport) int __stdcall getImage(int seedNum, bool sortByHeightOrWidth, uchar* src_data, int src_width, int src_height, int src_step, uchar* dst_data, int dst_width, int dst_height, int dst_step, uchar* pfinal_pic, SeedInfo* seedInfo);


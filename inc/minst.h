<<<<<<< HEAD
#ifndef __MINST_
#define __MINST_
/*
MINST���ݿ���һ����дͼ�����ݿ⣬����
*/
=======
/******************************************************************************
   Copyright 2018-2028 @
   All Rights Reserved
   FileName:    minst.h
   Description:
   Author:		meimaokui@126.com
   Date:		$(Time)
   Modification History: <version>      <time>      <author>        <desc>
   a)					  v1.0.0	   $(time)	  meimaokui@126.com	 Creat
******************************************************************************/
#ifndef _MMK_MINST_H_
#define _MMK_MINST_H_

#ifdef __cplusplus
extern "C" {
#endif
	/*
	   MINST���ݿ���һ����дͼ�����ݿ⣬����
	   */
>>>>>>> init files

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
<<<<<<< HEAD
#include <random>
#include <time.h>

typedef struct MinstImg{
	int c;           // ͼ���
	int r;           // ͼ���
	float** ImgData; // ͼ�����ݶ�ά��̬����
}MinstImg;

typedef struct MinstImgArr{
	int ImgNum;        // �洢ͼ�����Ŀ
	MinstImg* ImgPtr;  // �洢ͼ������ָ��
}*ImgArr;              // �洢ͼ�����ݵ�����

typedef struct MinstLabel{
	int len;            // �����ǵĳ�
	float* LabelData; // ����������
}MinstLabel;

typedef struct MinstLabelArr{
	int LabelNum;
	MinstLabel* LabelPtr;
}*LabelArr;              // �洢ͼ���ǵ�����

LabelArr read_Lable(const char* filename); // ����ͼ����

ImgArr read_Img(const char* filename); // ����ͼ��

void save_Img(ImgArr imgarr, char* filedir); // ��ͼ�����ݱ�����ļ�

#endif
=======
	/* #include <random.h> */
#include <time.h>
#include "../inc/com_type_def.h"

	typedef struct MinstImg
	{
		int c;           /* ͼ��� */
		int r;           /* ͼ��� */
		float **ImgData; /* ͼ�����ݶ�ά��̬���� */
	} MinstImg;

	typedef struct MinstImgArr
	{
		int ImgNum;        /* �洢ͼ�����Ŀ */
		MinstImg *ImgPtr;  /* �洢ͼ������ָ�� */
	} MinstImgArr;              /* �洢ͼ�����ݵ����� */

	typedef struct MinstLabel
	{
		int len;            /* �����ǵĳ� */
		float *LabelData; /* ���������� */
	} MinstLabel;

	typedef struct MinstLabelArr
	{
		int LabelNum;
		MinstLabel *LabelPtr;
	} MinstLabelArr;              /* �洢ͼ���ǵ����� */

	MinstLabelArr * read_Lable(const char *filename); /* ����ͼ���� */
	int minstReadLable(MinstLabelArr *labArr, const char *filename);
	/* ����ͼ�� */
	int ReadMinstImg(MinstImgArr * imgArr, const char *filename);
	MinstImgArr * read_Img(const char *filename); /* ����ͼ�� */

	void save_Img(MinstImgArr* imgarr, char *filedir); /* ��ͼ�����ݱ�����ļ� */


#ifdef __cplusplus
}
#endif

#endif
>>>>>>> init files

// ������ļ���Ҫ���ڹ��ڶ�ά��������Ĳ���
<<<<<<< HEAD
#ifndef __MAT_
#define __MAT_
=======
#ifndef _MMK_MAT_H_
#define _MMK_MAT_H_

#ifdef __cplusplus
extern "C" {
#endif
>>>>>>> init files

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
<<<<<<< HEAD
#include <random>
=======
	//#include <random>
>>>>>>> init files
#include <time.h>

#define full 0
#define same 1
#define COV_VALID 2

<<<<<<< HEAD
typedef struct Mat2DSize{
	unsigned int c; // �У���
	unsigned int r; // �У��ߣ�
}nSize;


float ** ppMat2dMalloc_Float(unsigned int width, unsigned int height);

void ppMat2dFree_Float(float ** ppMat, unsigned int width, unsigned int height);

float** rotate180(float** mat, nSize matSize);// ����ת180��
void Mat2dRotate_180(float** matIn, float** matOut, nSize matSize);
	
void addmat(float** res, float** mat1, nSize matSize1, float** mat2, nSize matSize2);// �������

float** correlation(float** map,nSize mapSize,float** inputData,nSize inSize,int type);// �����
//mapsize �����ͬ
void MatCorrelation_Valid(float** srcMat, nSize srcSize, float** mapMat, nSize mapSize, float** dstMat, nSize dstSize);

float** cov(float** map,nSize mapSize,float** inputData,nSize inSize,int type); // �������

// ����Ǿ�����ϲ�������ֵ�ڲ壩��upc��upr���ڲ屶��
float** UpSample(float** mat,nSize matSize,int upc,int upr);
void Mat2dUpSample(float** matIn, nSize matInSize, float** matOut, nSize matOutSize);

// ����ά�����Ե��������addw��С��0ֵ��
float** matEdgeExpand(float** mat,nSize matSize,int addc,int addr);
void Mat2dEdgeExpand(float** matIn, nSize matSize, float** matOut, int addc, int addr);

// ����ά�����Ե��С������shrinkc��С�ı�
float** matEdgeShrink(float** mat,nSize matSize,int shrinkc,int shrinkr);
void Mat2dEdgeShrink(float** matIn, nSize matSize, float** matOut, int shrinkc, int shrinkr);

void savemat(float** mat,nSize matSize,const char* filename);// �����������

void multifactor(float** res, float** mat, nSize matSize, float factor);// �������ϵ��

float Mat2dSum(float** mat,nSize matSize);// �����Ԫ�صĺ�

char * combine_strings(char *a, char *b);

char* intTochar(int i);
=======
	typedef struct Mat2DSize{
		unsigned int c; // �У���
		unsigned int r; // �У��ߣ�
	}nSize;


	float ** ppMat2dMalloc_Float(unsigned int width, unsigned int height);

	void ppMat2dFree_Float(float ** ppMat, unsigned int width, unsigned int height);

	float** rotate180(float** mat, nSize matSize);// ����ת180��
	void Mat2dRotate_180(float* matIn, float* matOut, nSize matSize);

	void addmat(float** res, float** mat1, nSize matSize1, float** mat2, nSize matSize2);// �������
	void Mat2D_Add(float* res, float* mat1, float* mat2, nSize matSize);

	float** correlation(float** map, nSize mapSize, float** inputData, nSize inSize, int type);// �����
	float** MatCorrelation(float** map, nSize mapSize, float** inputData, nSize inSize, int type);
	//mapsize �����ͬ
	void Mat2dCorrelation_Valid(float *srcMat, nSize srcSize, float *mapMat, nSize mapSize, float *dstMat, nSize dstSize);
	void MatCorrelation_Valid(float** srcMat, nSize srcSize, float** mapMat, nSize mapSize, float** dstMat, nSize dstSize);
	void Mat2dCorrelation_Full(float* srcMat, nSize srcSize, float* mapMat, nSize mapSize, float* dstMat, nSize dstSize);
	float** cov(float** map, nSize mapSize, float** inputData, nSize inSize, int type); // �������

	// ����Ǿ�����ϲ�������ֵ�ڲ壩��upc��upr���ڲ屶��
	float** UpSample(float** mat, nSize matSize, int upc, int upr);
	//void Mat2dUpSample(float** matIn, nSize matInSize, float** matOut, nSize matOutSize);
	void Mat2dUpSample(float* srcMat, nSize srcSize, float* dstMat, nSize dstSize);
	// ����ά�����Ե��������addw��С��0ֵ��
	float** matEdgeExpand(float** mat, nSize matSize, int addc, int addr);
	void Mat2dEdgeExpand(float** matIn, nSize matSize, float** matOut, int addc, int addr);
	void Mat2dEdgeExpand_2(float* matIn, nSize matSize, float* matOut, int addc, int addr);
	// ����ά�����Ե��С������shrinkc��С�ı�
	float** matEdgeShrink(float** mat, nSize matSize, int shrinkc, int shrinkr);
	void Mat2dEdgeShrink(float** matIn, nSize matSize, float** matOut, int shrinkc, int shrinkr);
	/*******************************************************************************
	Function:		Mat2dEdgeShrink_w
	Description:
	Input:
	Output:		N/A
	Return:		0:			Successful
	ohters:		Failed
	*******************************************************************************/
	void Mat2dEdgeShrink_w(float *matIn, nSize matSize, float *matOut, int shrinkc, int shrinkr);

	void savemat(float** mat, nSize matSize, const char* filename);// �����������

	void multifactor(float** res, float** mat, nSize matSize, float factor);// �������ϵ��
	void Mat2dMultiFactor(float* res, float* mat, nSize matSize, float factor);
	float Mat2dSum(float** mat, nSize matSize);// �����Ԫ�صĺ�
	float Mat2dSum_float(float *mat, nSize matSize);
	char * combine_strings(char *a, char *b);

	char* intTochar(int i);


#ifdef __cplusplus
}
#endif
>>>>>>> init files

#endif
<<<<<<< HEAD
#ifndef __CNN_
#define __CNN_
=======
/******************************************************************************
Copyright 2018-2028 @
All Rights Reserved
FileName:    cnn.h
Description:
Author:		meimaokui@126.com
Date:		$(Time)
Modification History: <version>      <time>      <author>        <desc>
a)					  v1.0.0	   $(time)	  meimaokui@126.com	 Creat
******************************************************************************/
#ifndef _MMK_CNN_H_
#define _MMK_CNN_H_

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
#include <time.h>
#include "mat.h"
=======
	//#include <random>
#include <time.h>
#include "mat.h"
#include "../inc/com_type_def.h"
#include "../inc/common.h"
>>>>>>> init files
#include "minst.h"

#define AvePool 0
#define MaxPool 1
#define MinPool 2

<<<<<<< HEAD
#define CNN_AVE_POOL 0
#define CNN_MAX_POOL 1
#define CNN_MIN_POOL 2

#define CNN_DATA_FILE_DIR "D:\\Embedded Work\\Machine Learning\\CNN\\demoCnn\\PicTrans\\CNNData\\"

// �����
typedef struct convolutional_layer{
	int inputWidth;   //����ͼ��Ŀ�
	int inputHeight;  //����ͼ��ĳ�
	int mapSize;      //����ģ��Ĵ�С��ģ��һ�㶼��������

	int inChannels;   //����ͼ�����Ŀ
	int outChannels;  //���ͼ�����Ŀ

	/* 
	��������ģ���Ȩ�طֲ���������һ����ά����,���СΪinChannels*outChannels*mapSize*mapSize��С
	��������ά���飬��Ҫ��Ϊ�˱���ȫ���ӵ���ʽ��ʵ���Ͼ���㲢û���õ�ȫ���ӵ���ʽ
	�����������DeapLearningToolboox���CNN���ӣ����õ�����ȫ����
	*/
	float**** mapData;     //�������ģ�������
	float**** dmapData;    //�������ģ������ݵľֲ��ݶ�

	float* basicData;   //ƫ�ã�ƫ�õĴ�С��ΪoutChannels
	bool isFullConnect; //�Ƿ�Ϊȫ����
	bool* connectModel; //����ģʽ��Ĭ��Ϊȫ���ӣ�

	// �������ߵĴ�Сͬ�����ά����ͬ
	float*** v; // ���뼤���������ֵ
	float*** y; // ���������Ԫ�����

	// ������صľֲ��ݶ�
	float*** d; // ����ľֲ��ݶ�,��ֵ  
}CovLayer;

// ������ pooling
typedef struct pooling_layer{
	int inputWidth;   //����ͼ��Ŀ�
	int inputHeight;  //����ͼ��ĳ�
	int mapSize;      //����ģ��Ĵ�С

	int inChannels;   //����ͼ�����Ŀ
	int outChannels;  //���ͼ�����Ŀ

	int poolType;     //Pooling�ķ���
	float* basicData;   //ƫ��

	float*** y; // ������������Ԫ�����,�޼����
	float*** d; // ����ľֲ��ݶ�,��ֵ
}PoolLayer;

// ����� ȫ���ӵ�������
typedef struct nn_layer{
	int 	inputNum;   //�������ݵ���Ŀ
	int 	outputNum;  //������ݵ���Ŀ

	float** wData; // Ȩ�����ݣ�Ϊһ��inputNum*outputNum��С
	float* 	basicData;   //ƫ�ã���СΪoutputNum��С

	// �������ߵĴ�Сͬ�����ά����ͬ
	float* 	v; // ���뼤���������ֵ
	float* 	y; // ���������Ԫ�����
	float* 	d; // ����ľֲ��ݶ�,��ֵ

	bool 	isFullConnect; //�Ƿ�Ϊȫ����
}OutLayer;

typedef struct cnn_network{
	int 		layerNum;
	CovLayer* 	C1;
	PoolLayer* 	S2;
	CovLayer* 	C3;
	PoolLayer* 	S4;
	OutLayer* 	O5;

	float* 		e; // ѵ�����
	float* 		L; // ˲ʱ�������
}CNN;

typedef struct _CNN_NET_STR_{
	int 		layerNum;
	int 		res[3];
	CovLayer 	C1;
	PoolLayer 	S2;
	CovLayer 	C3;
	PoolLayer 	S4;
	OutLayer 	O5;

	float* 		e; // ѵ�����
	float* 		L; // ˲ʱ�������
}CNN_NET_STR;


typedef struct train_opts{
	int 		numepochs; // ѵ���ĵ�������
	float 		alpha; // ѧϰ����
}CNNOpts;

void cnnsetup(CNN* cnn,nSize inputSize,int outputSize);
/*	
	CNN�����ѵ������
	inputData��outputData�ֱ����ѵ������
	dataNum����������Ŀ
*/
void cnnTrain(CNN* cnn,	ImgArr inputData,LabelArr outputData,CNNOpts opts,int trainNum);
// ����cnn����
float cnnTest(CNN* cnn, ImgArr inputData, LabelArr outputData, unsigned int testNum);
// ����cnn
void savecnn(CNN* cnn, const char* filename);
// ����cnn������
int importcnn(CNN* cnn, const char* filename);

// ��ʼ�������
CovLayer* initCovLayer(int inputWidth,int inputHeight,int mapSize,int inChannels,int outChannels);
void CovLayerConnect(CovLayer* covL,bool* connectModel);
// ��ʼ��������
PoolLayer* initPoolLayer(int inputWidth,int inputHeigh,int mapSize,int inChannels,int outChannels,int poolType);
void PoolLayerConnect(PoolLayer* poolL,bool* connectModel);
// ��ʼ�������
OutLayer* initOutLayer(int inputNum,int outputNum);

// ����� input�����ݣ�inputNum˵��������Ŀ��bas����ƫ��
float activation_Sigma(float input,float bas); // sigma�����
float CnnActiv_Sigma(float input, float bas);

void cnnff(CNN* cnn,float** inputData); // �����ǰ�򴫲�
void cnnbp(CNN* cnn,float* outputData); // ����ĺ��򴫲�
void cnnapplygrads(CNN* cnn,CNNOpts opts,float** inputData);
void cnnclear(CNN* cnn); // ������vyd����

/*
=======
#define CNN_AVE_POOL	0
#define CNN_MAX_POOL	1
#define CNN_MIN_POOL	2

#define CNN_LAYER_NUM 5

#define CNN_LAYER1_IN_SIZE			28
#define CNN_MAP_SIZE				5
#define CNN_LAYER1_MAP_SIZE			5
#define CNN_LAYER1_IN_CHANNEL_NUM	1
#define CNN_LAYER1_OUT_CHANNEL_NUM	6
#define CNN_LAYER1_OUT_SIZE			24

#define CNN_LAYER2_IN_CHANNEL_NUM 6
#define CNN_LAYER2_OUT_CHANNEL_NUM 6
#define CNN_LAYER2_OUT_SIZE 12


#define CNN_LAYER3_IN_SIZE 12
#define CNN_LAYER3_MAP_SIZE 5
#define CNN_LAYER3_IN_CHANNEL_NUM 6
#define CNN_LAYER3_OUT_CHANNEL_NUM 12
#define CNN_LAYER3_OUT_SIZE 8

#define CNN_LAYER4_IN_CHANNEL_NUM 12
#define CNN_LAYER4_OUT_CHANNEL_NUM 12
#define CNN_LAYER4_OUT_SIZE 4

#define CNN_LAYER5_IN_CHANNEL_NUM 12
#define CNN_LAYER5_OUT_CHANNEL_NUM 10
#define CNN_LAYER5_IN_DATA_NUM (CNN_LAYER5_IN_CHANNEL_NUM * CNN_LAYER4_OUT_SIZE * CNN_LAYER4_OUT_SIZE)

#define CNN_DATA_FILE_DIR "/mnt/hgfs/share/cnnDemo/PicTrans/CNNData"


	/* ����� */
	typedef struct convolutional_layer
	{
		int inputWidth;   /* ����ͼ��Ŀ� */
		int inputHeight;  /* ����ͼ��ĳ� */
		int mapSize;      /* ����ģ��Ĵ�С��ģ��һ�㶼�������� */

		int inChannels;   /* ����ͼ�����Ŀ */
		int outChannels;  /* ���ͼ�����Ŀ */

		/*
		��������ģ���Ȩ�طֲ���������һ����ά����,���СΪinChannels*outChannels*mapSize*mapSize��С
		��������ά���飬��Ҫ��Ϊ�˱���ȫ���ӵ���ʽ��ʵ���Ͼ���㲢û���õ�ȫ���ӵ���ʽ
		�����������DeapLearningToolboox���CNN���ӣ����õ�����ȫ����
		*/
		float ****mapData;     /* �������ģ������� */
		float ****dmapData;    /* �������ģ������ݵľֲ��ݶ� */

		float *basicData;   /* ƫ�ã�ƫ�õĴ�С��ΪoutChannels */
		BOOL isFullConnect; /* �Ƿ�Ϊȫ���� */
		BOOL *connectModel; /* ����ģʽ��Ĭ��Ϊȫ���ӣ� */

		/* �������ߵĴ�Сͬ�����ά����ͬ */
		float ***v; /* ���뼤���������ֵ */
		float ***y; /* ���������Ԫ����� */

		/* ������صľֲ��ݶ� */
		float ***d; /* ����ľֲ��ݶ�,��ֵ */
	} CovLayer;

	// �����
	typedef struct _CNN_COV_LAYER_L1_{
		int inputWidth;   //����ͼ��Ŀ� 28
		int inputHeight;  //����ͼ��ĳ� 28
		int mapSize;      //����ģ��Ĵ�С��ģ��һ�㶼�������� 5*5

		int inChannels;   //����ͼ�����Ŀ 1
		int outChannels;  //���ͼ�����Ŀ 6

		BOOL isFullConnect; //�Ƿ�Ϊȫ����
		BOOL* connectModel; //����ģʽ��Ĭ��Ϊȫ���ӣ�

		/*
		��������ģ���Ȩ�طֲ���������һ����ά����,���СΪinChannels*outChannels*mapSize*mapSize��С
		��������ά���飬��Ҫ��Ϊ�˱���ȫ���ӵ���ʽ��ʵ���Ͼ���㲢û���õ�ȫ���ӵ���ʽ
		�����������DeapLearningToolboox���CNN���ӣ����õ�����ȫ����
		*/
		//�������ģ�������
		float mapData[CNN_LAYER1_IN_CHANNEL_NUM][CNN_LAYER1_OUT_CHANNEL_NUM][CNN_LAYER1_MAP_SIZE][CNN_LAYER1_MAP_SIZE];
		//�������ģ������ݵľֲ��ݶ�
		float dMapData[CNN_LAYER1_IN_CHANNEL_NUM][CNN_LAYER1_OUT_CHANNEL_NUM][CNN_LAYER1_MAP_SIZE][CNN_LAYER1_MAP_SIZE];
		//ƫ�ã�ƫ�õĴ�С��ΪoutChannels
		float basicData[CNN_LAYER1_OUT_CHANNEL_NUM];

		// �������ߵĴ�Сͬ�����ά����ͬ
		// ���뼤���������ֵ
		float v[CNN_LAYER1_OUT_CHANNEL_NUM][CNN_LAYER1_OUT_SIZE][CNN_LAYER1_OUT_SIZE];
		// ���������Ԫ�����
		float y[CNN_LAYER1_OUT_CHANNEL_NUM][CNN_LAYER1_OUT_SIZE][CNN_LAYER1_OUT_SIZE];
		// ������صľֲ��ݶ�, ����ľֲ��ݶ�,��ֵ  
		float d[CNN_LAYER1_OUT_CHANNEL_NUM][CNN_LAYER1_OUT_SIZE][CNN_LAYER1_OUT_SIZE];

		float mapOut[CNN_LAYER1_OUT_SIZE][CNN_LAYER1_OUT_SIZE]; //��ž�������ʱ����

		//GPU
		float *vDev[CNN_LAYER1_OUT_CHANNEL_NUM];
		float *yDev[CNN_LAYER1_OUT_CHANNEL_NUM];
		float *dDev[CNN_LAYER1_OUT_CHANNEL_NUM];
		float *mapOutDev;
		float* basicDev;
	}CNN_COV_LAYER_L1;

	// ������ pooling �ػ�
	typedef struct _CNN_POOLING_LAYER_L2_{
		int inputWidth;   //����ͼ��Ŀ� 24
		int inputHeight;  //����ͼ��ĳ� 24
		int mapSize;      //����ģ��Ĵ�С 2*2

		int inChannels;   //����ͼ�����Ŀ 6
		int outChannels;  //���ͼ�����Ŀ 6

		int poolType;     //Pooling�ķ���
		float basicData[CNN_LAYER2_OUT_CHANNEL_NUM];   //ƫ��

		float y[CNN_LAYER2_OUT_CHANNEL_NUM][CNN_LAYER2_OUT_SIZE][CNN_LAYER2_OUT_SIZE]; // ������������Ԫ�����,�޼����
		float d[CNN_LAYER2_OUT_CHANNEL_NUM][CNN_LAYER2_OUT_SIZE][CNN_LAYER2_OUT_SIZE]; // ����ľֲ��ݶ�,��ֵ

		//##############################GPU###########################################//
		float * basicDev;
		float * yDev[CNN_LAYER2_OUT_CHANNEL_NUM];
		float * dDev;

	}CNN_POOLING_LAYER_L2;

	typedef struct _CNN_COV_LAYER_L3_{
		int inputWidth;   //����ͼ��Ŀ� 12
		int inputHeight;  //����ͼ��ĳ� 12
		int mapSize;      //����ģ��Ĵ�С��ģ��һ�㶼�������� 5*5

		int inChannels;   //����ͼ�����Ŀ 6
		int outChannels;  //���ͼ�����Ŀ 12

		BOOL isFullConnect; //�Ƿ�Ϊȫ����
		BOOL* connectModel; //����ģʽ��Ĭ��Ϊȫ���ӣ�
		//##############################CPU###########################################//
		/*
		��������ģ���Ȩ�طֲ���������һ����ά����,���СΪinChannels*outChannels*mapSize*mapSize��С
		��������ά���飬��Ҫ��Ϊ�˱���ȫ���ӵ���ʽ��ʵ���Ͼ���㲢û���õ�ȫ���ӵ���ʽ
		�����������DeapLearningToolboox���CNN���ӣ����õ�����ȫ����
		*/
		//�������ģ�������
		float mapData[CNN_LAYER3_IN_CHANNEL_NUM][CNN_LAYER3_OUT_CHANNEL_NUM][CNN_LAYER3_MAP_SIZE][CNN_LAYER3_MAP_SIZE];
		//�������ģ������ݵľֲ��ݶ�
		float dMapData[CNN_LAYER3_IN_CHANNEL_NUM][CNN_LAYER3_OUT_CHANNEL_NUM][CNN_LAYER3_MAP_SIZE][CNN_LAYER3_MAP_SIZE];
		//ƫ�ã�ƫ�õĴ�С��ΪoutChannels
		float basicData[CNN_LAYER3_OUT_CHANNEL_NUM];

		// �������ߵĴ�Сͬ�����ά����ͬ
		// ���뼤���������ֵ
		float v[CNN_LAYER3_OUT_CHANNEL_NUM][CNN_LAYER3_OUT_SIZE][CNN_LAYER3_OUT_SIZE];
		// ���������Ԫ�����
		float y[CNN_LAYER3_OUT_CHANNEL_NUM][CNN_LAYER3_OUT_SIZE][CNN_LAYER3_OUT_SIZE];
		// ������صľֲ��ݶ�, ����ľֲ��ݶ�,��ֵ  
		float d[CNN_LAYER3_OUT_CHANNEL_NUM][CNN_LAYER3_OUT_SIZE][CNN_LAYER3_OUT_SIZE];

		float mapOut[CNN_LAYER3_OUT_SIZE][CNN_LAYER3_OUT_SIZE]; //��ž�������ʱ����

		//##############################GPU###########################################//
		float *	basicDev;   //ƫ�ã���СΪoutputNum��С
		float *mapOutDev;
		float *vDev[CNN_LAYER3_OUT_CHANNEL_NUM];
		float *yDev[CNN_LAYER3_OUT_CHANNEL_NUM];
		float *dDev[CNN_LAYER3_OUT_CHANNEL_NUM];


	}CNN_COV_LAYER_L3;


	// ������ pooling �ػ�
	typedef struct _CNN_POOLING_LAYER_L4_{
		int inputWidth;   //����ͼ��Ŀ� 8
		int inputHeight;  //����ͼ��ĳ� 8
		int mapSize;      //����ģ��Ĵ�С 2*2

		int inChannels;   //����ͼ�����Ŀ 12
		int outChannels;  //���ͼ�����Ŀ 12

		int poolType;     //Pooling�ķ���
		//##############################CPU###########################################//
		float basicData[CNN_LAYER4_OUT_CHANNEL_NUM];   //ƫ��

		float y[CNN_LAYER4_OUT_CHANNEL_NUM][CNN_LAYER4_OUT_SIZE][CNN_LAYER4_OUT_SIZE]; // ������������Ԫ�����,�޼����
		float d[CNN_LAYER4_OUT_CHANNEL_NUM][CNN_LAYER4_OUT_SIZE][CNN_LAYER4_OUT_SIZE]; // ����ľֲ��ݶ�,��ֵ

		//##############################GPU###########################################//
		float * basicDev;
		float * yDev;
		float * dDev;

	}CNN_POOLING_LAYER_L4;

	// ������ pooling
	typedef struct pooling_layer{
		int inputWidth;   //����ͼ��Ŀ�
		int inputHeight;  //����ͼ��ĳ�
		int mapSize;      //����ģ��Ĵ�С

		int inChannels;   /* ����ͼ�����Ŀ */
		int outChannels;  /* ���ͼ�����Ŀ */

		int poolType;     /* Pooling�ķ��� */
		float *basicData;   /* ƫ�� */

		float ***y; /* ������������Ԫ�����,�޼���� */
		float ***d; /* ����ľֲ��ݶ�,��ֵ */
	} PoolLayer;

	/* ����� ȫ���ӵ������� */
	typedef struct nn_layer
	{
		int	inputNum;       /* �������ݵ���Ŀ */
		int	outputNum;      /* ������ݵ���Ŀ */

		float **wData; /* Ȩ�����ݣ�Ϊһ��inputNum*outputNum��С */
		float *basicData;    /* ƫ�ã���СΪoutputNum��С */

		/* �������ߵĴ�Сͬ�����ά����ͬ */
		float *v;  /* ���뼤���������ֵ */
		float *y;  /* ���������Ԫ����� */
		float *d;  /* ����ľֲ��ݶ�,��ֵ */

		BOOL isFullConnect;    /* �Ƿ�Ϊȫ���� */
	} OutLayer;

	// ����� ȫ���ӵ�������
	typedef struct _CNN_OUT_LAYER_L5_{
		int 	inputNum;   //�������ݵ���Ŀ 192
		int 	outputNum;  //������ݵ���Ŀ 10
		BOOL 	isFullConnect; //�Ƿ�Ϊȫ����
		//##############################CPU###########################################//
		float	inData[CNN_LAYER5_IN_DATA_NUM];//ǰ������תΪһά����
		float 	wData[CNN_LAYER5_OUT_CHANNEL_NUM][CNN_LAYER5_IN_DATA_NUM]; // Ȩ�����ݣ�Ϊһ��inputNum*outputNum��С
		float 	basicData[CNN_LAYER5_OUT_CHANNEL_NUM];   //ƫ�ã���СΪoutputNum��С

		// �������ߵĴ�Сͬ�����ά����ͬ
		float 	v[CNN_LAYER5_OUT_CHANNEL_NUM]; // ���뼤���������ֵ
		float 	y[CNN_LAYER5_OUT_CHANNEL_NUM]; // ���������Ԫ�����
		float 	d[CNN_LAYER5_OUT_CHANNEL_NUM]; // ����ľֲ��ݶ�,��ֵ

		//##############################GPU###########################################//
		float * inDev;//ǰ������תΪһά����
		float * wDev;
		float *	basicDev;   //ƫ�ã���СΪoutputNum��С
		float *	vDev; // ���뼤���������ֵ
		float *	yDev; // ���������Ԫ�����
		float *	dDev; // ����ľֲ��ݶ�,��ֵ	
	}CNN_OUT_LAYER_L5;


	typedef struct cnn_net{
		int 		layerNum;
		CovLayer* 	C1;
		PoolLayer* 	S2;
		CovLayer* 	C3;
		PoolLayer* 	S4;
		OutLayer* 	O5;

		float *e;      /* ѵ����� */
		float *L;      /* ˲ʱ������� */
	} CNN;

	typedef struct _CNN_NET_STR_{
		int 		layerNum;
		float * pInDataDev;
		int 		res[2];
		CNN_COV_LAYER_L1 		stCovL1;
		CNN_POOLING_LAYER_L2 	stPoolL2;
		CNN_COV_LAYER_L3		stCovL3;
		CNN_POOLING_LAYER_L4	stPoolL4;
		CNN_OUT_LAYER_L5		stOutL5;

		float e[CNN_LAYER5_OUT_CHANNEL_NUM];      /* ѵ����� */
		float L[CNN_PIC_TRAIN_NUM];      /* ˲ʱ������� */
	} CNN_NET_STR;


	typedef struct train_opts
	{
		int	numepochs;         /* ѵ���ĵ������� */
		float alpha;       /* ѧϰ���� */
	} CNNOpts;

	void cnnsetup(CNN *cnn, nSize inputSize, int outputSize);
	void CnnSetUp(CNN_NET_STR* stCnnNet);
	/*******************************************************************************
	Function:		CnnTrainProc
	Description:
	Input:
	Output:		N/A
	Return:		0:			Successful
	ohters:		Failed
	*******************************************************************************/
	void CnnTrainProc(CNN_NET_STR *pCnnNet, MinstImgArr *inputData, MinstLabelArr *outputData, CNNOpts opts, int trainNum);
	/*
	CNN�����ѵ������
	inputData��outputData�ֱ����ѵ������
	dataNum����������Ŀ
	*/
	void cnnTrain(CNN *cnn, MinstImgArr* inputData, MinstLabelArr* outputData, CNNOpts opts, int trainNum);

	/* ����cnn���� */
	float cnnTest(CNN *cnn, MinstImgArr* inputData, MinstLabelArr* outputData, unsigned int testNum);

	/* ����cnn */
	void savecnn(CNN *cnn, const char *filename);
	/* ����cnn������ */
	int importcnn(CNN *cnn, const char *filename);


	void SaveCnnModelFile(CNN_NET_STR* pCnnNet, const char* fileName);



	/* ��ʼ������� */
	CovLayer *initCovLayer(int inputWidth, int inputHeight, int mapSize, int inChannels, int outChannels);
	void CovLayerConnect(CovLayer *covL, BOOL *connectModel);

	/* ��ʼ�������� */
	PoolLayer *initPoolLayer(int inputWidth, int inputHeigh, int mapSize, int inChannels, int outChannels, int poolType);
	void PoolLayerConnect(PoolLayer *poolL, BOOL *connectModel);

	/* ��ʼ������� */
	OutLayer *initOutLayer(int inputNum, int outputNum);

	/* ����� input�����ݣ�inputNum˵��������Ŀ��bas����ƫ�� */
	float activation_Sigma(float input, float bas); /* sigma����� */
	float SigmaActiveFun(float input, float bas); // sigma�����


	void cnnff(CNN *cnn, float **inputData); /* �����ǰ�򴫲� */
	void CnnForwardPass(CNN_NET_STR* pCnnNet, float* inputData);
	void CnnBackPass(CNN_NET_STR *pCnnNet, float *outputData); /* ����ĺ��򴫲� */

	void cnnbp(CNN *cnn, float *outputData); /* ����ĺ��򴫲� */
	void cnnapplygrads(CNN *cnn, CNNOpts opts, float **inputData);
	void CnnApplyGrads(CNN_NET_STR *pCnnNet, CNNOpts opts, float *inputData); /* ����Ȩ�� */

	void cnnclear(CNN *cnn); /* ������vyd���� */
	/*******************************************************************************
	Function:		CnnParamClear
	Description:
	Input:
	Output:		N/A
	Return:		0:			Successful
	ohters:		Failed
	*******************************************************************************/
	void CnnParamClear(CNN_NET_STR *pCnnNet);

	/*
>>>>>>> init files
	Pooling Function
	input ��������
	inputNum ����������Ŀ
	mapSize ��ƽ����ģ������
<<<<<<< HEAD
*/
void avgPooling(float** output,nSize outputSize,float** input,nSize inputSize,int mapSize); // ��ƽ��ֵ

/* 
	����ȫ����������Ĵ���
	nnSize������Ĵ�С
*/
void nnff(float* output,float* input,float** wdata,float* bas,nSize nnSize); // ����ȫ�����������ǰ�򴫲�

void saveCnnData(CNN* cnn, const char* filename, float** inputdata); // ����CNN�����е��������

void CNNOptsPrint(CNNOpts *pCNNOpts);
void CovLayerPrint(CovLayer *pCovLayer);
void PoolLayerPrint(PoolLayer *pPoolLayer);
void OutLayerPrint(OutLayer *pOutLayer);
=======
	*/
	void avgPooling(float **output, nSize outputSize, float **input, nSize inputSize, int mapSize); /* ��ƽ��ֵ */
	void PoolingAverage(float* output, nSize outputSize, float* input, nSize inputSize, int mapSize);

	/*
	����ȫ����������Ĵ���
	nnSize������Ĵ�С
	*/
	void nnff(float *output, float *input, float **wdata, float *bas, nSize nnSize); /* ����ȫ�����������ǰ�򴫲� */
	void nn2f(float* output, float* input, float* wdata, float* bas, nSize nnSize);

	void saveCnnData(CNN *cnn, const char *filename, float **inputdata); /* ����CNN�����е�������� */
	void SaveCnnMidData(CNN_NET_STR *pCnnNet, const char *filename, float **inputdata);

	/*******************************************************************************
	Function:		CNNOptsPrint
	Description:
	Input:
	Output:		N/A
	Return:		0:			Successful
	ohters:		Failed
	*******************************************************************************/
	void CNNOptsPrint(CNNOpts *pCNNOpts);

	void CovLayerPrint(CovLayer *pCovLayer);
	void PoolLayerPrint(PoolLayer *pPoolLayer);
	void OutLayerPrint(OutLayer *pOutLayer);
	INT32 vecMaxIndex(PFLOAT vec, UINT32 veclength);

#ifdef __cplusplus
}
#endif
>>>>>>> init files

#endif

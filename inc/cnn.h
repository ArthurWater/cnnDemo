#ifndef __CNN_
#define __CNN_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <random>
#include <time.h>
#include "mat.h"
#include "minst.h"

#define AvePool 0
#define MaxPool 1
#define MinPool 2

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
	Pooling Function
	input ��������
	inputNum ����������Ŀ
	mapSize ��ƽ����ģ������
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

#endif

/******************************************************************************
   Copyright 2018-2028 @
   All Rights Reserved
   FileName:    mat.c
   Description:
   Author:		meimaokui@126.com
   Date:		$(Time)
   Modification History: <version>      <time>      <author>        <desc>
   a)					  v1.0.0	   $(time)	  meimaokui@126.com	 Creat
******************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
/* #include <random> */
#include <time.h>
#include "../inc/common.h"
#include "../inc/mat.h"


/* ����һ����ά����ռ�,����ʼ��Ϊ0 */
float **ppMat2dMalloc_Float(unsigned int width, unsigned int height)
{
    unsigned int i = 0;

    if (!width || !height)
    {
        return NULL;
    }

    float **outputSpace = (float **)malloc(height * sizeof(float *));
    for (i = 0; i < height; i++)
    {
        outputSpace[i] = (float *)malloc(width * sizeof(float));
        if (outputSpace[i])
        {
            memset(outputSpace[i], 0, width * sizeof(float));
        }
        else
        {
            PRT_ERR("malloc failed !\n");
        }
    }

    return outputSpace;
}

/*******************************************************************************
   Function:		ppMat2dFree_Float
   Description:
   Input:
   Output:		N/A
   Return:		0:			Successful
                    ohters:		Failed
*******************************************************************************/
void ppMat2dFree_Float(float **ppMat, unsigned int width, unsigned int height)
{
    unsigned int i = 0;

    if (!height || !width)
    {
        return;
    }

    for (i = 0; i < height; i++)
    {
        free(ppMat[i]);
    }

    free(ppMat);
}

/* ����ת180�� */
float **rotate180(float **mat, nSize matSize)
{
    int i, c, r;
    int outSizeW = matSize.c;
    int outSizeH = matSize.r;
    float **outputData = (float **)malloc(outSizeH * sizeof(float *));

    for (i = 0; i < outSizeH; i++)
        outputData[i] = (float *)malloc(outSizeW * sizeof(float));

    for (r = 0; r < outSizeH; r++)
        for (c = 0; c < outSizeW; c++)
            outputData[r][c] = mat[outSizeH - r - 1][outSizeW - c - 1];

    return outputData;
}

/*������ת180��*/
void Mat2dRotate_180(float *matIn, float *matOut, nSize matSize)
{
    int i, j;
    int outSizeW = matSize.c;
    int outSizeH = matSize.r;

    if (!matIn || !matOut || !matSize.c || !matSize.r)
    {
        return;
    }

    for (i = 0; i < outSizeH; i++)
    {
        for (j = 0; j < outSizeW; j++)
        {
            matOut[i * outSizeW + j] = matIn[(outSizeH - i - 1) * outSizeW + outSizeW - j - 1];
        }
    }
}

/*
   ���ھ������ز��������ѡ��
   ���ﹲ������ѡ��full��same��valid���ֱ��ʾ
   fullָ��ȫ�����������Ĵ�СΪinSize+(mapSize-1)
   sameָͬ������ͬ��С
   validָ��ȫ������Ĵ�С��һ��ΪinSize-(mapSize-1)��С���䲻��Ҫ��������0����
 */
float **correlation(float **map, nSize mapSize, float **inputData, nSize inSize, int type)/* ����� */
{
    /* ����Ļ�������ں��򴫲�ʱ���ã������ڽ�Map��ת180���پ�� */
    /* Ϊ�˷�����㣬�����Ƚ�ͼ������һȦ */
    /* ����ľ��Ҫ�ֳ�������ż��ģ��ͬ����ģ�� */
    unsigned int i, j, c, r;
    int halfmapsizew;
    int halfmapsizeh;

    if (mapSize.r % 2 == 0 && mapSize.c % 2 == 0) /* ģ���СΪż�� */
    {
        halfmapsizew = (mapSize.c) / 2; /* ���ģ��İ���С */
        halfmapsizeh = (mapSize.r) / 2;
    }
    else
    {
        halfmapsizew = (mapSize.c - 1) / 2; /* ���ģ��İ���С */
        halfmapsizeh = (mapSize.r - 1) / 2;
    }

    /* ������Ĭ�Ͻ���fullģʽ�Ĳ�����fullģʽ�������СΪinSize+(mapSize-1) */
    int outSizeW = inSize.c + (mapSize.c - 1); /* ������������һ���� */
    int outSizeH = inSize.r + (mapSize.r - 1);
    float **outputData = (float **)malloc(outSizeH * sizeof(float *)); /* ����صĽ�������� */
    for (i = 0; i < outSizeH; i++)
        outputData[i] = (float *)calloc(outSizeW, sizeof(float));

    /* Ϊ�˷�����㣬��inputData����һȦ */
    float **exInputData = matEdgeExpand(inputData, inSize, mapSize.c - 1, mapSize.r - 1);

    for (j = 0; j < outSizeH; j++)
        for (i = 0; i < outSizeW; i++)
            for (r = 0; r < mapSize.r; r++)
                for (c = 0; c < mapSize.c; c++)
                {
                    outputData[j][i] = outputData[j][i] + map[r][c] * exInputData[j + r][i + c];
                }

    for (i = 0; i < inSize.r + 2 * (mapSize.r - 1); i++)
        free(exInputData[i]);

    free(exInputData);

    nSize outSize = {outSizeW, outSizeH};
    switch (type) /* ���ݲ�ͬ����������ز�ͬ�Ľ�� */
    {
        case full: /* ��ȫ��С����� */
            return outputData;
        case same: {
            float **sameres = matEdgeShrink(outputData, outSize, halfmapsizew, halfmapsizeh);
            for (i = 0; i < outSize.r; i++)
                free(outputData[i]);

            free(outputData);
            return sameres;
        }
        case COV_VALID: {
            float **validres;
            if (mapSize.r % 2 == 0 && mapSize.c % 2 == 0)
                validres = matEdgeShrink(outputData, outSize, halfmapsizew * 2 - 1, halfmapsizeh * 2 - 1);
            else
                validres = matEdgeShrink(outputData, outSize, halfmapsizew * 2, halfmapsizeh * 2);

            for (i = 0; i < outSize.r; i++)
                free(outputData[i]);

            free(outputData);
            return validres;
        }
        default:
            return outputData;
    }
}

/*
   �����
   ���ھ������ز��������ѡ��
   ���ﹲ������ѡ��full��same��valid���ֱ��ʾ
   fullָ��ȫ�����������Ĵ�СΪinSize+(mapSize-1)
   sameָͬ������ͬ��С
   validָ��ȫ������Ĵ�С��һ��ΪinSize-(mapSize-1)��С���䲻��Ҫ��������0����

    ����Ļ�������ں��򴫲�ʱ���ã������ڽ�Map��ת180���پ��,Ϊ�˷�����㣬�����Ƚ�ͼ������һȦ
    ����ľ��Ҫ�ֳ�������ż��ģ��ͬ����ģ�塣
 */
float **MatCorrelation(float **map, nSize mapSize, float **inputData, nSize inSize, int type)
{
	unsigned int i, j, c, r;
    int halfmapsizew;
    int halfmapsizeh;

    if (!inputData || !map)
    {
        PRT_ERR("param error !\n");
        return NULL;
    }

    if (mapSize.r % 2 == 0 && mapSize.c % 2 == 0)/* ģ���СΪż�� */
    {
        halfmapsizew = (mapSize.c) / 2; /* ���ģ��İ���С */
        halfmapsizeh = (mapSize.r) / 2;
    }
    else
    {
        halfmapsizew = (mapSize.c - 1) / 2; /* ���ģ��İ���С */
        halfmapsizeh = (mapSize.r - 1) / 2;
    }

    /* ������Ĭ�Ͻ���fullģʽ�Ĳ�����fullģʽ�������СΪinSize+(mapSize-1) */
    int outSizeW = inSize.c + (mapSize.c - 1); /* ������������һ���� */
    int outSizeH = inSize.r + (mapSize.r - 1);

    /*
       float** outputData=(float**)malloc(outSizeH*sizeof(float*)); // ����صĽ��������
       for(i=0;i<outSizeH;i++)
        outputData[i]=(float*)calloc(outSizeW,sizeof(float));
     */
    float **outputData = ppMat2dMalloc_Float(outSizeW, outSizeH);



    /* Ϊ�˷�����㣬��inputData����һȦ */
/*	float** exInputData = matEdgeExpand(inputData, inSize, mapSize.c-1, mapSize.r-1); */

    float **exInputData = ppMat2dMalloc_Float(inSize.c + 2 * (mapSize.c - 1), inSize.r + 2 * (mapSize.r - 1));

    Mat2dEdgeExpand(inputData, inSize, exInputData, mapSize.c - 1, mapSize.r - 1);

    /* ���ֵ���� */
    for (j = 0; j < outSizeH; j++)
    {
        for (i = 0; i < outSizeW; i++)
        {/* �����������ÿ��λ�õ�ֵ */
            for (r = 0; r < mapSize.r; r++)
                for (c = 0; c < mapSize.c; c++)
                {
                    outputData[j][i] = outputData[j][i] + map[r][c] * exInputData[j + r][i + c];
                }
        }
    }

    ppMat2dFree_Float(exInputData, inSize.c + 2 * (mapSize.c - 1), inSize.r + 2 * (mapSize.r - 1));

    nSize outSize = {outSizeW, outSizeH};
    switch (type) /* ���ݲ�ͬ����������ز�ͬ�Ľ�� */
    {
        case full: /* ��ȫ��С����� */
            return outputData;
        case same: {
/*		float** sameres = matEdgeShrink(outputData, outSize, halfmapsizew, halfmapsizeh); */
            float **sameres = ppMat2dMalloc_Float(inSize.c, inSize.r);
            Mat2dEdgeShrink(outputData, outSize, sameres, halfmapsizew, halfmapsizeh);
            ppMat2dFree_Float(outputData, outSizeW, outSizeH);

            return sameres;
        }
        case COV_VALID: {
            float **validres;
        #if 0
            if (mapSize.r % 2 == 0 && mapSize.c % 2 == 0)
                validres = matEdgeShrink(outputData, outSize, halfmapsizew * 2 - 1, halfmapsizeh * 2 - 1);
            else
                validres = matEdgeShrink(outputData, outSize, halfmapsizew * 2, halfmapsizeh * 2);

        #endif
            if (mapSize.r % 2 == 0 && mapSize.c % 2 == 0)/* ż�� */
            {
                validres = ppMat2dMalloc_Float(inSize.c + 3 - mapSize.c, inSize.r + 3 - mapSize.r);
                Mat2dEdgeShrink(outputData, outSize, validres, halfmapsizew * 2 - 1, halfmapsizeh * 2 - 1);
            }
            else/* ���� */
            {
                validres = ppMat2dMalloc_Float(inSize.c + 1 - mapSize.c, inSize.r + 1 - mapSize.r);
                Mat2dEdgeShrink(outputData, outSize, validres, halfmapsizew * 2, halfmapsizeh * 2);
            }

            ppMat2dFree_Float(outputData, outSizeW, outSizeH);

            return validres;
        }
        default:
            return outputData;
    }
}

/*******************************************************************************
   Function:		MatCorrelation_Full
   Description:
   Input:
   Output:		N/A
   Return:		0:			Successful
                    ohters:		Failed
*******************************************************************************/
void MatCorrelation_Full(float **srcMat, nSize srcSize, float **mapMat, nSize mapSize, float **dstMat, nSize dstSize)
{
	unsigned int i, j, c, r;
    float tmp = 0.0;
    nSize exSize = {0, 0};

    if (!srcMat || !mapMat || !dstMat)
    {
        PRT_ERR("param error !\n");
        return;
    }

    PRT("--map size--[%d-%d]\n", mapSize.r, mapSize.c);

    /* ������Ĭ�Ͻ���fullģʽ�Ĳ�����fullģʽ�������СΪinSize+(mapSize-1) */
    int outSizeW = srcSize.c + (mapSize.c - 1); /* ������������һ���� */
    int outSizeH = srcSize.r + (mapSize.r - 1);

    /* ��������С�Ƿ����Ҫ�� */
    if (outSizeW != dstSize.c || outSizeH != dstSize.r)
    {
        PRT_ERR("param error !\n");
        return;
    }

    /* Ϊ�˷�����㣬��inputData����һȦ */
    exSize.c = srcSize.c + 2 * (mapSize.c - 1);
    exSize.r = srcSize.r + 2 * (mapSize.r - 1);
    float **exInputData = ppMat2dMalloc_Float(exSize.c, exSize.r);
    if (!exInputData)
    {
        PRT_ERR("malloc error !\n");
        return;
    }

    Mat2dEdgeExpand(srcMat, srcSize, exInputData, mapSize.c - 1, mapSize.r - 1);
    PRT_ERR("--debug--[%d-%d]--[%d-%d]\n", outSizeW, outSizeH, dstSize.r, dstSize.c);

    /* ���ֵ���� */
    for (j = 0; j < outSizeH; j++)
    {
        for (i = 0; i < outSizeW; i++)
        {/* �����������ÿ��λ�õ�ֵ */
            for (r = 0; r < mapSize.r; r++)
            {
                for (c = 0; c < mapSize.c; c++)
                {
                    dstMat[j][i] = dstMat[j][i] + mapMat[r][c] * exInputData[j + r][i + c];
                }
            }
        }
    }

    PRT_ERR("--debug--\n");
    ppMat2dFree_Float(exInputData, exSize.c, exSize.r);
}

/* ��Ҫȷ���ڴ����� */
void Mat2dCorrelation_Full(float *srcMat, nSize srcSize, float *mapMat, nSize mapSize, float *dstMat, nSize dstSize)
{
	unsigned int i, j, c, r;
    float tmp = 0.0;
    float *pTmpData = NULL;
    nSize exSize = {0, 0};

    if (!srcMat || !mapMat || !dstMat)
    {
        PRT_ERR("param error !\n");
        return;
    }

    /* ������Ĭ�Ͻ���fullģʽ�Ĳ�����fullģʽ�������СΪinSize+(mapSize-1) */
    int outSizeW = srcSize.c + (mapSize.c - 1); /* ������������һ���� */
    int outSizeH = srcSize.r + (mapSize.r - 1);

    /* ��������С�Ƿ����Ҫ�� */
    if (outSizeW != dstSize.c || outSizeH != dstSize.r)
    {
        PRT_ERR("param error !\n");
        return;
    }

    /* Ϊ�˷�����㣬��inputData����һȦ */
    exSize.c = srcSize.c + 2 * (mapSize.c - 1);
    exSize.r = srcSize.r + 2 * (mapSize.r - 1);

    pTmpData = (float *)malloc(exSize.c * exSize.r * sizeof(float));
    memset(pTmpData, 0, exSize.c * exSize.r * sizeof(float));

    Mat2dEdgeExpand_2(srcMat, srcSize, pTmpData, mapSize.c - 1, mapSize.r - 1);
/*	PRT_ERR("--debug--[%d-%d]--[%d-%d]\n", outSizeW, outSizeH, dstSize.r, dstSize.c); */

    /* ���ֵ���� */
    for (j = 0; j < outSizeH; j++)
    {
        for (i = 0; i < outSizeW; i++)
        {/* �����������ÿ��λ�õ�ֵ */
            for (r = 0; r < mapSize.r; r++)
            {
                for (c = 0; c < mapSize.c; c++)
                {
                    dstMat[j * outSizeW + i] = dstMat[j * outSizeW + i] + mapMat[r * mapSize.c + c] * pTmpData[(j + r) * exSize.c + i + c];
                }
            }
        }
    }

    free(pTmpData);
}

/* mapsize �����ͬ,��ʱmapsize�Ŀ�����Ϊ�����������������ûָ�Ϊԭ���Ĵ�С���������ƫ�� */
void MatCorrelation_Same(float **srcMat, nSize srcSize, float **mapMat, nSize mapSize, float **dstMat, nSize dstSize)
{
    int halfmapsizew;
    int halfmapsizeh;

    if (!srcMat || !mapMat || !dstMat)
    {
        PRT_ERR("param error !\n");
        return;
    }

    if (mapSize.r % 2 == 0 && mapSize.c % 2 == 0)/* ģ���СΪż�� */
    {
        halfmapsizew = (mapSize.c) / 2; /* ���ģ��İ���С */
        halfmapsizeh = (mapSize.r) / 2;
    }
    else
    {
        halfmapsizew = (mapSize.c - 1) / 2; /* ���ģ��İ���С */
        halfmapsizeh = (mapSize.r - 1) / 2;
    }

    if (srcSize.c != dstSize.c || srcSize.r != dstSize.r)
    {
        PRT_ERR("param error !\n");
        return;
    }

    /* ������Ĭ�Ͻ���fullģʽ�Ĳ�����fullģʽ�������СΪinSize+(mapSize-1) */
    int outSizeW = srcSize.c + (mapSize.c - 1); /* ������������һ���� */
    int outSizeH = srcSize.r + (mapSize.r - 1);
    nSize outSize = { outSizeW, outSizeH };

    float **outputData = ppMat2dMalloc_Float(outSizeW, outSizeH);

    MatCorrelation_Full(srcMat, srcSize, mapMat, mapSize, outputData, outSize);

    Mat2dEdgeShrink(outputData, outSize, dstMat, halfmapsizew, halfmapsizeh);

    ppMat2dFree_Float(outputData, outSizeW, outSizeH);
}

/* mapsize �����ͬ */
void MatCorrelation_Valid(float **srcMat, nSize srcSize, float **mapMat, nSize mapSize, float **dstMat, nSize dstSize)
{
    int halfmapsizew;
    int halfmapsizeh;

    if (!srcMat || !mapMat || !dstMat)
    {
        PRT_ERR("param error !\n");
        return;
    }

    if (mapSize.r % 2 == 0 && mapSize.c % 2 == 0)/* ģ���СΪż�� */
    {
        halfmapsizew = (mapSize.c) / 2; /* ���ģ��İ���С */
        halfmapsizeh = (mapSize.r) / 2;
    }
    else
    {
        halfmapsizew = (mapSize.c - 1) / 2; /* ���ģ��İ���С */
        halfmapsizeh = (mapSize.r - 1) / 2;
    }

    /* ������Ĭ�Ͻ���fullģʽ�Ĳ�����fullģʽ�������СΪinSize+(mapSize-1) */
    int outSizeW = srcSize.c + (mapSize.c - 1); /* ������������һ���� */
    int outSizeH = srcSize.r + (mapSize.r - 1);
    nSize outSize = { outSizeW, outSizeH };

    float **outputData = ppMat2dMalloc_Float(outSizeW, outSizeH);

    PRT_ERR("--debug-%f-[%d-%d]\n", mapMat[0][0], outSizeW, outSizeH);

    MatCorrelation_Full(srcMat, srcSize, mapMat, mapSize, outputData, outSize);
    PRT_ERR("--debug--[%d-%d]\n", dstSize.c, dstSize.r);

    if (mapSize.r % 2 == 0 && mapSize.c % 2 == 0)/* ģ���СΪż�� */
    {
        Mat2dEdgeShrink(outputData, outSize, dstMat, halfmapsizew * 2 - 1, halfmapsizeh * 2 - 1);
    }
    else
    {
        Mat2dEdgeShrink(outputData, outSize, dstMat, halfmapsizew * 2, halfmapsizeh * 2);
    }

    ppMat2dFree_Float(outputData, outSizeW, outSizeH);
}

/*******************************************************************************
   Function:		Mat2dCorrelation_Valid
   Description:
   Input:
   Output:		N/A
   Return:		0:			Successful
                    ohters:		Failed
*******************************************************************************/
void Mat2dCorrelation_Valid(float *srcMat, nSize srcSize, float *mapMat, nSize mapSize, float *dstMat, nSize dstSize)
{
    int i, j, c, r;
    float *pTmpData = NULL;
    nSize exSize = {0, 0};
    int halfmapsizew;
    int halfmapsizeh;

    if (!srcMat || !mapMat || !dstMat)
    {
        PRT_ERR("param error !\n");
        return;
    }

    if (mapSize.r % 2 == 0 && mapSize.c % 2 == 0)/* ģ���СΪż�� */
    {
        halfmapsizew = (mapSize.c) / 2; /* ���ģ��İ���С */
        halfmapsizeh = (mapSize.r) / 2;
    }
    else
    {
        halfmapsizew = (mapSize.c - 1) / 2; /* ���ģ��İ���С */
        halfmapsizeh = (mapSize.r - 1) / 2;
    }

    /* ������Ĭ�Ͻ���fullģʽ�Ĳ�����fullģʽ�������СΪinSize+(mapSize-1) */
    int outSizeW = srcSize.c + (mapSize.c - 1); /* ������������һ���� */
    int outSizeH = srcSize.r + (mapSize.r - 1);
    nSize outSize = { outSizeW, outSizeH };

    float *outputData = malloc(outSizeW * outSizeH * sizeof(float));
    memset(outputData, 0, outSizeW * outSizeH * sizeof(float));

/*	Mat2dCorrelation_Full(srcMat, srcSize, mapMat, mapSize, outputData, outSize); */

    /* ������Ĭ�Ͻ���fullģʽ�Ĳ�����fullģʽ�������СΪinSize+(mapSize-1) */
    /* Ϊ�˷�����㣬��inputData����һȦ */
    exSize.c = srcSize.c + 2 * (mapSize.c - 1);
    exSize.r = srcSize.r + 2 * (mapSize.r - 1);

    pTmpData = (float *)malloc(exSize.c * exSize.r * sizeof(float));
    memset(pTmpData, 0, exSize.c * exSize.r * sizeof(float));

    Mat2dEdgeExpand_2(srcMat, srcSize, pTmpData, mapSize.c - 1, mapSize.r - 1);

    /* ���ֵ���� */
    for (j = 0; j < outSizeH; j++)
    {
        for (i = 0; i < outSizeW; i++)
        {/* �����������ÿ��λ�õ�ֵ */
            for (r = 0; r < mapSize.r; r++)
            {
                for (c = 0; c < mapSize.c; c++)
                {
                    outputData[j * outSizeW + i] += mapMat[r * mapSize.c + c] * pTmpData[(j + r) * exSize.c + i + c];
                }
            }
        }
    }

    free(pTmpData);

    if (mapSize.r % 2 == 0 && mapSize.c % 2 == 0)/* ģ���СΪż�� */
    {
        Mat2dEdgeShrink_w(outputData, outSize, dstMat, halfmapsizew * 2 - 1, halfmapsizeh * 2 - 1);
    }
    else
    {
        Mat2dEdgeShrink_w(outputData, outSize, dstMat, halfmapsizew * 2, halfmapsizeh * 2);
    }

    free(outputData);
}

/*
   ���������������ת180�ȵ�����ģ���������
 */
float **cov(float **map, nSize mapSize, float **inputData, nSize inSize, int type) /* ������� */
{
    nSize dstMatSize;
    float **dstMat = NULL;

    if (!map || !inputData)
    {
        PRT_ERR("param error !\n");
        return NULL;
    }

    /*
       int i = 0;

       float** flipmap = (float**)malloc(mapSize.r*sizeof(float*));
       for(i = 0; i < mapSize.r; i++)
        flipmap[i] = (float*)malloc(mapSize.c*sizeof(float));
     */

    /*
       float** flipmap = ppMat2dMalloc_Float(mapSize.c, mapSize.r);
       if(!flipmap)
       {
        return NULL;
       }
     */
    float **flipmap = rotate180(map, mapSize); /* ��ת180�ȵ�����ģ�� */

/*	Mat2dRotate_180(map, flipmap, mapSize); */

    /* ������������С */
#if 0
    if (COV_VALID == type)
    {
        dstMatSize.c = inSize.c - (mapSize.c - 1);
        dstMatSize.r = inSize.r - (mapSize.r - 1);
        dstMat = ppMat2dMalloc_Float(dstMatSize.c, dstMatSize.r);
        MatCorrelation_Valid(inputData, inSize, map, mapSize, dstMat, dstMatSize);
    }
    else
    {
        dstMat = correlation(flipmap, mapSize, inputData, inSize, type);
        PRT_ERR("param error !\n");
    }

#else
    dstMat = correlation(flipmap, mapSize, inputData, inSize, type);


#endif

    /*

       ppMat2dFree_Float(flipmap, mapSize.c, mapSize.r);

       for (i = 0; i < mapSize.r; i++)
       {
        free(flipmap[i]);
       }
       free(flipmap);
     */
    return dstMat;
}

/* ����Ǿ�����ϲ�������ֵ�ڲ壩��upc��upr���ڲ屶�� */
float **UpSample(float **mat, nSize matSize, int upc, int upr)
{
    int i, j, m, n;
    int c = matSize.c;
    int r = matSize.r;
    float **res = (float **)malloc((r * upr) * sizeof(float *)); /* ����ĳ�ʼ�� */

    for (i = 0; i < (r * upr); i++)
        res[i] = (float *)malloc((c * upc) * sizeof(float));

    for (j = 0; j < r * upr; j = j + upr)
    {
        for (i = 0; i < c * upc; i = i + upc) /* ������� */
            for (m = 0; m < upc; m++)
                res[j][i + m] = mat[j / upr][i / upc];

        for (n = 1; n < upr; n++) /*  �ߵ����� */
            for (i = 0; i < c * upc; i++)
                res[j + n][i] = res[j][i];
    }

    return res;
}

/*******************************************************************************
   Function:		Mat2dUpSample
   Description:
   Input:
   Output:		N/A
   Return:		0:			Successful
                    ohters:		Failed
*******************************************************************************/
void Mat2dUpSample(float *srcMat, nSize srcSize, float *dstMat, nSize dstSize)
{
    int i, j, m, n;
    int upc = 1;
    int upr = 1;

    if (!srcMat || !dstMat || srcSize.c==0 || srcSize.r==0 || srcSize.c<dstSize.c || srcSize.r<dstSize.r)
    {
        return;
    }

    memset(dstMat, 0, (dstSize.c * dstSize.r));
    upc = dstSize.c / srcSize.c;
    upr = dstSize.r / srcSize.r;

    for (j = 0; j < dstSize.r; j = j + upr)
    {
        for (i = 0; i < dstSize.c; i = i + upc)/* ������� */
        {
            for (m = 0; m < upc; m++)
                dstMat[j * dstSize.c + i + m] = srcMat[(j / upr) * srcSize.c + i / upc];
        }

        for (n = 1; n < upr; n++)      /*  �ߵ����� */
        {
//        	memcpy();
            for (i = 0; i < dstSize.c; i++)
                dstMat[(j + n) * dstSize.c + i] = dstMat[j * dstSize.c + i];
        }
    }
}

/*
   ����Ǿ�����ϲ�������ֵ�ڲ壩��upc��upr���ڲ屶��
   matInSize ��ֵǰ�Ĵ�С
   matOutSize��ֵ��Ĵ�С���ú���Ҫ�������С(��͸�)�����������������
   �������Ͻǵĵ�
 */

/*
   void Mat2dUpSample(float** matIn, nSize matInSize, float** matOut, nSize matOutSize)
   {
    int i,j,m,n;
    unsigned int wUp = 1;
    unsigned int hUp = 1;
    if(!matInSize.c || !matInSize.r)
    {
        return;
    }

    //��ֵ����������������
    if(!(matOutSize.c%matInSize.c) || !(matOutSize.r%matInSize.r))
    {
        return;
    }
    //��ֵ����
    wUp = matOutSize.c / matInSize.c;
    hUp = matOutSize.r / matInSize.r;

    for(j=0; j<matOutSize.r; j=j+hUp)
    {
        for(i=0; i<matOutSize.c; i=i+wUp)// �������
        {
            for(m=0; m<wUp; m++)
                matOut[j][i+m] = matIn[j/hUp][i/wUp];
        }

        for(n=1; n<hUp; n++)      //  �ߵ�����
        for (i = 0; i<matOutSize.c; i++)
                matOut[j+n][i] = matOut[j][i];
    }
   }
 */
/* ����ά�����Ե��������addw��С��0ֵ�� */
float **matEdgeExpand(float **mat, nSize matSize, int addc, int addr)
{ /* ������Ե���� */
    int i, j;
    int c = matSize.c;
    int r = matSize.r;
    float **res = (float **)malloc((r + 2 * addr) * sizeof(float *)); /* ����ĳ�ʼ�� */

    for (i = 0; i < (r + 2 * addr); i++)
        res[i] = (float *)malloc((c + 2 * addc) * sizeof(float));

    for (j = 0; j < r + 2 * addr; j++)
    {
        for (i = 0; i < c + 2 * addc; i++)
        {
            if (j < addr || i < addc || j >= (r + addr) || i >= (c + addc))
                res[j][i] = (float)0.0;
            else
                res[j][i] = mat[j - addr][i - addc]; /* ����ԭ���������� */

        }
    }

    return res;
}

/*
   ����ά�����Ե��������addw��С��0ֵ��
 */
void Mat2dEdgeExpand(float **matIn, nSize matSize, float **matOut, int addc, int addr)
{
    int i, j;
    int c = matSize.c;
    int r = matSize.r;

    if (!matIn || !matOut)
    {
        return;
    }

    for (i = 0; i < (r + 2 * addr); i++)
    {
        memset((float *)matOut[i], 0, (c + 2 * addc) * sizeof(float));
    }

    for (j = 0; j < (r + 2 * addr); j++)
    {
        for (i = 0; i < (c + 2 * addc); i++)
        {
            if (j < addr || j >= (r + addr) || i < addc || i >= (c + addc))
                matOut[j][i] = (float)0.0;
            else
                matOut[j][i] = matIn[j - addr][i - addc]; /* ����ԭ���������� */

        }
    }
}

/*******************************************************************************
   Function:		Mat2dEdgeExpand_2
   Description:
   Input:
   Output:		N/A
   Return:		0:			Successful
                    ohters:		Failed
*******************************************************************************/
void Mat2dEdgeExpand_2(float *matIn, nSize matSize, float *matOut, int addc, int addr)
{
    int i, j;
    int c = matSize.c;
    int r = matSize.r;

    if (!matIn || !matOut)
    {
        return;
    }

    for (j = 0; j < (r + 2 * addr); j++)
    {
        for (i = 0; i < (c + 2 * addc); i++)
        {
            if (j < addr || j >= (r + addr) || i < addc || i >= (c + addc))
                matOut[j * (c + 2 * addc) + i] = (float)0.0;
            else
                matOut[j * (c + 2 * addc) + i] = matIn[(j - addr) * c + i - addc]; /* ����ԭ���������� */

        }
    }
}

/*
   ����ά�����Ե��С������shrinkc��С�ı�
 */
float **matEdgeShrink(float **mat, nSize matSize, int shrinkc, int shrinkr)
{ /* ��������С������Сaddw������Сaddh */
    int i, j;
    int c = matSize.c;
    int r = matSize.r;
    float **res = (float **)malloc((r - 2 * shrinkr) * sizeof(float *)); /* �������ĳ�ʼ�� */

    for (i = 0; i < (r - 2 * shrinkr); i++)
        res[i] = (float *)malloc((c - 2 * shrinkc) * sizeof(float));

    for (j = 0; j < r; j++)
    {
        for (i = 0; i < c; i++)
        {
            if (j >= shrinkr && i >= shrinkc && j < (r - shrinkr) && i < (c - shrinkc))
                res[j - shrinkr][i - shrinkc] = mat[j][i]; /* ����ԭ���������� */

        }
    }

    return res;
}

/*
   ����ά�����Ե��С������shrinkc��С�ı�
   �����Ҷ���Сshrinkc��
   �����¶���Сshrinkr
   ��ע���������ռ��ⲿ����ã����ִ��Ч��
 */
void Mat2dEdgeShrink(float **matIn, nSize matSize, float **matOut, int shrinkc, int shrinkr)
{
    int i, j;
    int c = matSize.c;
    int r = matSize.r;

    if (!matIn || !matOut || (shrinkc > (matSize.c / 2)) || (shrinkr > (matSize.r / 2)))
    {
        return;
    }

    for (j = 0; j < r; j++)
    {
        for (i = 0; i < c; i++)
        {
            if ((j >= shrinkr) && (i >= shrinkc) && (j < (r - shrinkr)) && (i < (c - shrinkc)))
            {
                matOut[j - shrinkr][i - shrinkc] = matIn[j][i]; /* ����ԭ���������� */
            }
        }
    }
}

/*******************************************************************************
   Function:		Mat2dEdgeShrink_w
   Description:
   Input:
   Output:		N/A
   Return:		0:			Successful
                    ohters:		Failed
*******************************************************************************/
void Mat2dEdgeShrink_w(float *matIn, nSize matSize, float *matOut, int shrinkc, int shrinkr)
{
    int i, j;
    int w = matSize.c;
    int h = matSize.r;

    if (!matIn || !matOut || (shrinkc > (matSize.c / 2)) || (shrinkr > (matSize.r / 2)))
    {
        return;
    }

    for (j = 0; j < h; j++)
    {
        for (i = 0; i < w; i++)
        {
            if ((j >= shrinkr) && (i >= shrinkc) && (j < (h - shrinkr)) && (i < (w - shrinkc)))
            {
                matOut[(j - shrinkr) * (w - 2 * shrinkc) + i - shrinkc] = matIn[j * w + i]; /* ����ԭ���������� */
            }
        }
    }
}

/*******************************************************************************
   Function:		savemat
   Description:
   Input:
   Output:		N/A
   Return:		0:			Successful
                    ohters:		Failed
*******************************************************************************/
void savemat(float **mat, nSize matSize, const char *filename)
{
    int i = 0;
    FILE *fp = NULL;

    fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        printf("write file failed\n");
        return;
    }

    for (i = 0; i < matSize.r; i++)
        fwrite(mat[i], sizeof(float), matSize.c, fp);

    fclose(fp);
}

/* ������� */
void addmat(float **res, float **mat1, nSize matSize1, float **mat2, nSize matSize2)
{
    int i, j;

    if (matSize1.c != matSize2.c || matSize1.r != matSize2.r)
        printf("ERROR: Size is not same!");

    for (i = 0; i < matSize1.r; i++)
    {
        for (j = 0; j < matSize1.c; j++)
        {
            res[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

/*******************************************************************************
   Function:		Mat2D_Add
   Description:
   Input:
   Output:		N/A
   Return:		0:			Successful
                    ohters:		Failed
*******************************************************************************/
void Mat2D_Add(float *res, float *mat1, float *mat2, nSize matSize)
{
    int i, j;

    if (matSize.c == 0 || matSize.r == 0)
    {
        printf("ERROR: Size error!");
    }

    for (i = 0; i < matSize.r; i++)
    {
        for (j = 0; j < matSize.c; j++)
        {
            res[i * matSize.c + j] = mat1[i * matSize.c + j] + mat2[i * matSize.c + j];
        }
    }
}

/* �������ϵ�� */
void multifactor(float **res, float **mat, nSize matSize, float factor)
{
    int i, j;

    for (i = 0; i < matSize.r; i++)
    {
        for (j = 0; j < matSize.c; j++)
            res[i][j] = mat[i][j] * factor;
    }
}

/*******************************************************************************
   Function:		Mat2dMultiFactor
   Description:
   Input:
   Output:		N/A
   Return:		0:			Successful
                    ohters:		Failed
*******************************************************************************/
void Mat2dMultiFactor(float *res, float *mat, nSize matSize, float factor)
{
    int i, j;

    for (i = 0; i < matSize.r; i++)
    {
        for (j = 0; j < matSize.c; j++)
            res[i * matSize.c + j] = mat[i * matSize.c + j] * factor;
    }
}

/* �����Ԫ�صĺ� */
float Mat2dSum(float **mat, nSize matSize)
{
    int i, j;
    float sum = 0.0;

    for (i = 0; i < matSize.r; i++)
    {
        for (j = 0; j < matSize.c; j++)
            sum = sum + mat[i][j];
    }

    return sum;
}
float Mat2dSum_float(float *mat, nSize matSize)
{
    int i = 0;
    float sum = 0.0;

    for (i = 0; i < (matSize.r*matSize.c); i++)
    {
        sum += mat[i];
    }

    return sum;
}



#ifndef _CU_CNN_H_
#define _CU_CNN_H_

#define CUDA_BLOCK_SIZE 64

void cuCnnSetUp(CNN_NET_STR *stCnnNet);
void cuCnnDestroy(CNN_NET_STR *stCnnNet);
/*******************************************************************************
Function:		cuCnnTrainProc
Description:
Input:
Output:		N/A
Return:		0:			Successful
ohters:		Failed
*******************************************************************************/
void cuCnnTrainProc(CNN_NET_STR *pCnnNet, MinstImgArr *inputData, MinstLabelArr *outputData, CNNOpts opts, int trainNum);

/* ����InputData��ͼ�����ݣ�inputData[r][c],r��c�У��������Ȩ��ģ����һ�µ� */
void cuCnnForwardPass(CNN_NET_STR *pCnnNet, float *inputData);

#endif

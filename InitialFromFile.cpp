#include <stdio.h>
#include <stdlib.h>

void initialfromfile(struct Ray , int Radius[], int Distance[], int Re_Index[])
{
	int k,i;
	i = 0;

	char Inputdatas[200];
	scanf("%s",&Inputdatas);						//��������ļ����ݴ���Inputdatas

	FILE *fw = fopen(Inputdatas, "r");

	fscanf(fw,"%f",&Ray.L0);						//�����ʼ���
	fscanf(fw,"%f",&Ray.U0_D0);						//�����ʼ�﷽��׾���U0����ֱͫ��D0
	fscanf(fw,"%f",&Ray.Y0_W0);						//�����ʼ���Y0����ӳ���W

	fscanf(fw,"%d",&k);

	for (i = 0; i < k; i++)							//���ζ������е�rֵ����k����
	{
		fscanf(fw, "%f", &Radius[i]);
	}

	for (i = 0; i < k-1; i++)						//���ζ������е�dֵ����k-1����
	{
		fscanf(fw, "%f", &Distance[i]);
	}

	for (i = 0; i <=k; i++)							//���ζ������е�nֵ����k+1����
	{
		fscanf(fw, "%f", &Re_Index[i]);
	}

}

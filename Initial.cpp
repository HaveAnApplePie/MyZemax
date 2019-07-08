#include "Ray_Point.h"
#include<stdlib.h>
#include<stdio.h>

void InitialFromFile(struct Ray*Ray0 , double Radius[], double Distance[], double Re_Index[])
{
	int k,i;
	i = 0;

	Ray0->now_surface_number = -1;
	Ray0->Wavelen = D_RAY;

	char Inputdatas[200];
	printf("������Ҫ�򿪵��ļ�����\n");
	scanf("%s",&Inputdatas);							//��������ļ����ݴ���Inputdatas

	FILE *fw = fopen(Inputdatas, "r");

	fscanf(fw,"%lf",&Ray0->L0);							//�����ʼ���
	if (Ray0->L0 <= 0 && -Ray0->L0 < INFINITE)			//�ж��Ƿ�Ϊ����Զ��
		Ray0->IsInfinite = false;
	else Ray0->IsInfinite = true;

	fscanf(fw,"%lf",&Ray0->U0_D0);						//�����ʼ�﷽��׾���U0����ֱͫ��D0
	fscanf(fw,"%lf",&Ray0->Y0_W0);						//�����ʼ���Y0����ӳ���W

	fscanf(fw,"%d",&k);
	Ray0->all_surface_number = k - 1;

	for (i = 0; i < k; i++)								//���ζ������е�rֵ����k����
	{
		fscanf(fw, "%lf", &Radius[i]);
	}

	for (i = 0; i < k-1; i++)							//���ζ������е�dֵ����k-1����
	{
		fscanf(fw, "%lf", &Distance[i]);
	}

	for (i = 0; i <=k; i++)								//���ζ������е�nֵ����k+1����
	{
		fscanf(fw, "%lf", &Re_Index[i]);
	}

	fscanf(fw, "%lf", &Ray0->A0);
}

void InitialFromScreen(struct Ray*Ray0, double Radius[], double Distance[], double Re_Index[])
{
	int k, i;

	Ray0->now_surface_number = -1;

	Ray0->Wavelen = D_RAY;

	scanf("%lf", &Ray0->L0);			//��ʼ���

	if (Ray0->L0 <= 0 && -Ray0->L0 < INFINITE)
		Ray0->IsInfinite = false;
	else 
		Ray0->IsInfinite = true;

	scanf("%lf", &Ray0->U0_D0);		//��ʼ�﷽�뾶��U0 ��ֱͫ��D0 

	scanf("%lf", &Ray0->Y0_W0);		//��ʼ���Y0 �뾶��W 

	scanf("%d", &k);
	Ray0->all_surface_number = k-1;

	for (i = 0;i<k;i++) {
		scanf("%lf", &Radius[i]);
	}
	for (i = 0;i<k - 1;i++) {
		scanf("%lf", &Distance[i]);
	}
	for (i = 0;i<k + 1;i++) {
		scanf("%lf", &Re_Index[i]);
	}

	scanf("%lf", &Ray0->A0);
}


void Initial(struct Ray*Ray0, double Radius[], double Distance[], double Re_Index[]) {
	int i;
	printf("������ȡ��\n1.����1���ļ��ж�ȡ\n2.����2����Ļ�ж�ȡ\n");
	scanf("%d", &i);
	if (i == 1)
		InitialFromFile(Ray0, Radius, Distance, Re_Index);
	else if (i == 2)
		InitialFromScreen(Ray0, Radius, Distance, Re_Index);
	else
		printf("Error!");
}
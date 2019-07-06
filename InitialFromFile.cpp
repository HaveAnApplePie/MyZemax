#include <stdio.h>
#include <stdlib.h>

void initial(struct Ray*Ray0 , double Radius[], double Distance[], double Re_Index[])
{
	int k,i;
	i = 0;

	Ray0->surface_number = -1;
	Ray0->Wavelen = D_RAY;

	char Inputdatas[200];
	scanf("%s",&Inputdatas);							//��������ļ����ݴ���Inputdatas

	FILE *fw = fopen(Inputdatas, "r");

	fscanf(fw,"%f",&Ray0->L0);							//�����ʼ���
	if (Ray0->L0 < INFINITE)							//�ж��Ƿ�Ϊ����Զ��
		Ray0->IsInfinite = false;
	else Ray0->IsInfinite = true;

	fscanf(fw,"%f",&Ray0->U0_D0);						//�����ʼ�﷽��׾���U0����ֱͫ��D0
	fscanf(fw,"%f",&Ray0->Y0_W0);						//�����ʼ���Y0����ӳ���W

	fscanf(fw,"%d",&k);

	for (i = 0; i < k; i++)								//���ζ������е�rֵ����k����
	{
		fscanf(fw, "%f", &Radius[i]);
	}

	for (i = 0; i < k-1; i++)							//���ζ������е�dֵ����k-1����
	{
		fscanf(fw, "%f", &Distance[i]);
	}

	for (i = 0; i <=k; i++)								//���ζ������е�nֵ����k+1����
	{
		fscanf(fw, "%f", &Re_Index[i]);
	}

}

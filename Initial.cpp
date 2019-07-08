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
	printf("请输入要打开的文件名：\n");
	scanf("%s",&Inputdatas);							//将输入的文件名暂存在Inputdatas

	FILE *fw = fopen(Inputdatas, "r");

	fscanf(fw,"%lf",&Ray0->L0);							//读入初始物距
	if (Ray0->L0 <= 0 && -Ray0->L0 < INFINITE)			//判断是否为无穷远物
		Ray0->IsInfinite = false;
	else Ray0->IsInfinite = true;

	fscanf(fw,"%lf",&Ray0->U0_D0);						//读入初始物方半孔径角U0或入瞳直径D0
	fscanf(fw,"%lf",&Ray0->Y0_W0);						//读入初始物高Y0或半视场角W

	fscanf(fw,"%d",&k);
	Ray0->all_surface_number = k - 1;

	for (i = 0; i < k; i++)								//依次读入所有的r值（共k个）
	{
		fscanf(fw, "%lf", &Radius[i]);
	}

	for (i = 0; i < k-1; i++)							//依次读入所有的d值（共k-1个）
	{
		fscanf(fw, "%lf", &Distance[i]);
	}

	for (i = 0; i <=k; i++)								//依次读入所有的n值（共k+1个）
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

	scanf("%lf", &Ray0->L0);			//初始物距

	if (Ray0->L0 <= 0 && -Ray0->L0 < INFINITE)
		Ray0->IsInfinite = false;
	else 
		Ray0->IsInfinite = true;

	scanf("%lf", &Ray0->U0_D0);		//初始物方半径角U0 入瞳直径D0 

	scanf("%lf", &Ray0->Y0_W0);		//初始物高Y0 半径角W 

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
	printf("参数读取：\n1.输入1从文件中读取\n2.输入2从屏幕中读取\n");
	scanf("%d", &i);
	if (i == 1)
		InitialFromFile(Ray0, Radius, Distance, Re_Index);
	else if (i == 2)
		InitialFromScreen(Ray0, Radius, Distance, Re_Index);
	else
		printf("Error!");
}
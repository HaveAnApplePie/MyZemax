#include <stdio.h>
#include <stdlib.h>

void initial(struct Ray*Ray0 , double Radius[], double Distance[], double Re_Index[])
{
	int k,i;
	i = 0;

	Ray0->now_surface_number = -1;
	Ray0->Wavelen = D_RAY;

	char Inputdatas[200];
	scanf("%s",&Inputdatas);							//将输入的文件名暂存在Inputdatas

	FILE *fw = fopen(Inputdatas, "r");

	fscanf(fw,"%f",&Ray0->L0);							//读入初始物距
	if (Ray0->L0 < INFINITE)							//判断是否为无穷远物
		Ray0->IsInfinite = false;
	else Ray0->IsInfinite = true;

	fscanf(fw,"%f",&Ray0->U0_D0);						//读入初始物方半孔径角U0或入瞳直径D0
	fscanf(fw,"%f",&Ray0->Y0_W0);						//读入初始物高Y0或半视场角W

	fscanf(fw,"%d",&k);
	Ray0->all_surface_number = k - 1;

	for (i = 0; i < k; i++)								//依次读入所有的r值（共k个）
	{
		fscanf(fw, "%f", &Radius[i]);
	}

	for (i = 0; i < k-1; i++)							//依次读入所有的d值（共k-1个）
	{
		fscanf(fw, "%f", &Distance[i]);
	}

	for (i = 0; i <=k; i++)								//依次读入所有的n值（共k+1个）
	{
		fscanf(fw, "%f", &Re_Index[i]);
	}

}

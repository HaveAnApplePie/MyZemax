#include <stdio.h>
#include <stdlib.h>

void initialfromfile(struct Ray , int Radius[], int Distance[], int Re_Index[])
{
	int k,i;
	i = 0;

	char Inputdatas[200];
	scanf("%s",&Inputdatas);						//将输入的文件名暂存在Inputdatas

	FILE *fw = fopen(Inputdatas, "r");

	fscanf(fw,"%f",&Ray.L0);						//读入初始物距
	fscanf(fw,"%f",&Ray.U0_D0);						//读入初始物方半孔径角U0或入瞳直径D0
	fscanf(fw,"%f",&Ray.Y0_W0);						//读入初始物高Y0或半视场角W

	fscanf(fw,"%d",&k);

	for (i = 0; i < k; i++)							//依次读入所有的r值（共k个）
	{
		fscanf(fw, "%f", &Radius[i]);
	}

	for (i = 0; i < k-1; i++)						//依次读入所有的d值（共k-1个）
	{
		fscanf(fw, "%f", &Distance[i]);
	}

	for (i = 0; i <=k; i++)							//依次读入所有的n值（共k+1个）
	{
		fscanf(fw, "%f", &Re_Index[i]);
	}

}

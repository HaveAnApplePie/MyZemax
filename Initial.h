#ifndef	INITIAL_H
#define	INITIAL_H


void InitialFromFile(struct Ray*Ray0, double Radius[], double Distance[], double Re_Index[]);	//从文件中读取

void InitialFromScreen(struct Ray*Ray0, double Radius[], double Distance[], double Re_Index[]);	//从屏幕中读取

void Initial(struct Ray*Ray0, double Radius[], double Distance[], double Re_Index[]);			//初始化函数
	

#endif
#ifndef	CALCULTION_H
#define	CALCULTION_H

#include"Ray_Point.h"

//近轴光
Ray FirstParaxialLight(struct Ray*Ray0);	//第一近轴光线
Ray SencondParaxialLight(struct Ray*Ray0);	//第二近轴光线
Ray* Paraxial_single_surface(struct Ray *ray_in, double Radius[], double Distance[], double Re_Index[]);	//单个面计算
void Paraxial_calculation(struct Ray *ray0, double Radius[], double Distance[], double Re_Index[]);			//所有面计算


#endif
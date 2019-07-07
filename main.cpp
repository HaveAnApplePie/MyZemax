#include<stdio.h>
#include<stdlib.h>

#include"Ray_Point.h"
#include"Initial.h"
#include"Calcultion.h"


int main(void) {

	struct Ray ray0;
	double Radius[100], Distance[100], Re_Index[100];

	//初始化
	Initial(&ray0,Radius,Distance,Re_Index);
	//近轴光计算
	Paraxial_calculation(&ray0, Radius, Distance, Re_Index);
	//实际光计算
	RealRay_calculation(&ray0, Radius, Distance, Re_Index);
	return 0;
}
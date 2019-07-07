#ifndef	RAYPOINT_H
#define	RAYPOINT_H

#define	D_RAY		0
#define	C_RAY		1
#define	F_RAY		2
#define INFINITE 	1E12
#define PI			3.1415927

struct Ray
{
	bool	IsInfinite;			//物距是否无穷远
	int 	now_surface_number;	//已经过的面
	int		all_surface_number;	//总的面数
	int 	Wavelen;			//波长
	double	A0;					//入瞳半径
	double  S;					//弧矢距
	double  T;					//子午距
	double	L0;					//初始物距
	double 	U0_D0;				//初始物方半孔径角或入瞳直径
	double	Y0_W0;				//物高或半视场角   
	double	Ln;					//当前物距，相对于surface_number
	double 	Un;					//当前角度
};


struct Point					//相对于最后一个面与主轴的交点
{
	double 	X;
	double 	Y;
};

#endif
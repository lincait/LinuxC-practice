#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
一个水分子质量3.0e-23g,一夸脱水的质量是950g,编写程序，要求从输入端输入水的夸脱数，输出包含的水分子数
*/
#define MOLECULE_MASS 3.0e-23
#define QUARTER_MASS 950
void water(void)
{
	float num_quart;
	float sum;

	printf("请输入夸脱数：");
    scanf("%f",&num_quart);
	sum = num_quart * QUARTER_MASS / MOLECULE_MASS;
	printf("水分子数量为：%e\n",sum);	//使用科学计数法输出
	return ;	
}

/*
从终端输入a,b,c的值，计算并输出二次方程ax^2+bx+c=0的根
*/
void root(void)
{
	float a,b,c;
	float x1,x2;

	printf("enter abc:");
	scanf("%f%f%f",&a,&b,&c);

	if((b*b - 4*a*c) < 0)
		printf("error\n");
	else
	{
		x1 = (-b + sqrt(b*b - 4*a*c)) / (2*a);
		x2 = (-b - sqrt(b*b - 4*a*c)) / (2*a);
		printf("root is x1 = %f, x2 = %f\n",x1,x2);
	}

	return;
}

int main()
{
	//water();
	root();

	return 0;
}

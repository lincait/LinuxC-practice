#include <stdio.h>
#include <stdlib.h>


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

int main()
{
	water();

	return 0;
}

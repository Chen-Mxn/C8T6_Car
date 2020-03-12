
#include "pch.h"
#include <stdio.h>
#include <malloc.h>
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996);
void bubble_sort(int *a, int len)
{
	int i, j, temp;
	for (i = 0; i < len; i++)
	{
		for (j = 0; j < len - 1 - i; j++)
			if (a[j] > a[j + 1])
			{

				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
	}
}
int main()
{
	int n, i, flag;
	int *data = NULL;
	printf("请输入数组元素的个数：");
	flag = scanf("%d", &n);
	while ((getchar()) != '\n');
	while (!flag)
	{
		printf("输入格式有误，请重新输入：\n请输入数组元素的个数：");
		flag = scanf("%d", &n);
		while ((getchar()) != '\n');
	}
	data = (int*)malloc(sizeof(int) * n);
	if (data != NULL)
		printf("内存分配成功！\n");
		
	printf("请在下方输入数组的数据: ↓↓↓\n");
	for (i = 0; i < n; i++)
	{
		printf("请输入第%d个数：", i + 1);
		flag = scanf("%d", &data[i]);
		while ((getchar()) != '\n');
		while (!flag)
		{
			printf("输入格式有误，请重新输入：\n请输入第%d个数：", i + 1);
			flag = scanf("%d", &data[i]);
			while ((getchar()) != '\n');
		}
	}
	printf("输入数据为：");
	for (i = 0; i < n; i++)
	{
		printf("%4d", data[i]);
	}
	printf("\n\n");
	bubble_sort(data, n);
	printf("正确排序为：");
	for (i = 0; i < n; i++)
	{
		printf("%4d", data[i]);
	}
	printf("\n\n");
	free(data);
	printf("输入任意键结束进程");
	getchar();
	//getchar();
	return 0;
}
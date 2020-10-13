#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inputFunc.h"

// 根据标题完成字符串输入交互
char *inputCharWithTitle(const char *title)
{
	static char str[20];
	char temp[20];
	printf("请输入 %s 的内容\n", title);
	scanf("%s", temp);
	fflush(stdin);
	strcpy(str, temp);
	printf("项目: %s 的内容是 %s\n", title, str);
	return str;
}

// 输入年龄
int inputAge()
{
	int age = 0;
	printf("请输入年龄\n");
	scanf("%d", &age);
	fflush(stdin);
	// 年龄检查
	while (age < 1 || age > 150)
	{
		printf("输入有误，请重试\n");
		scanf("%d", &age);
		fflush(stdin);
	}
	printf("年龄: %d\n", age);
	return age;
}

// 输入ID
int inputID(const char *title)
{
	int id = 0;
	printf("请输入 %s\n", title);
	scanf("%d", &id);
	fflush(stdin);
	printf("输入成功 %s: %d\n", title, id);
	return id;
}

// 医生上班
int *inputWork()
{
	int work[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //TODO: static问题，已删
	int totalDays = 0;
	// 设置总天数
	do
	{
		printf("请输入该医生一周上班总天数:\n");
		scanf("%d", &totalDays);
	} while (totalDays > 7 || totalDays < 1);
	work[0] = totalDays;
	fflush(stdin);
	// 哪一天上班
	for (int i = 1; i <= totalDays; i++)
	{
		int tempWork = 0;
		// 周几上班
		printf("医生在一周中第 %d 天上班是周几？ (1-7)\n", i);
		scanf("%d", &tempWork);

		// 检查异常
		fflush(stdin);
		while (tempWork >= 8 || tempWork < 1 || work[tempWork] == 1)
		{
			printf("输入有误，请重试\n");
			scanf("%d", &tempWork);
			fflush(stdin);
		}
		// 标记上班
		work[tempWork] = 1;
	}

	// debug： 输出上班数组
	// printf("work DEBUG: ");
	// for (int i = 0; i <= 7; i++)
	// {
	//     printf("[%d]", work[i]);
	// }

	return work;
}

// 输入价钱
int inputPrice(int isPrint)
{

	double price = 0;
	int valueAsFen = -1;
	printf("请输入金额,（例如：12.34 元）\n");
	scanf("%lf", &price);
	fflush(stdin);
	printf("输入的金额:%.2lf\n", price);
	int isContinue = isNextInput("输入的金额是否无误，确认请输入 1，重新输入请输入 0\n");
	fflush(stdin);
	if (isContinue == 1)
	{
		valueAsFen = money_double_yjf(price, isPrint);
		return valueAsFen;
	}
	return 0;
}

// 输入数量
int inputAmount()
{
	int amount = 0;
	printf("请输入数量\n");
	scanf("%d", &amount);
	fflush(stdin);
	printf("输入成功，数量: %d\n", amount);
	return amount;
}

// 01 判断是否继续输入
int isNextInput(const char *title)
{
	int result = -1;
	char temp[256];
	//int decision = -1;

	strcpy(temp, title);

	printf("%s\n", temp);

	while (result != 1 && result != 0)
	{
		int decision = -1;
		scanf("%d", &decision);
		fflush(stdin);
		switch (decision)
		{
		case 1:
			result = 1;
			break;
		case 0:
			result = 0;
			break;
		default:
			printf("输入有误，请重试\n");
			break;
		}
		//printf("result:%d\n", result);
	}

	return result;
}

// 金钱处理：输入double金额，计算元角分，返回总份
int money_double_yjf(double money, int isPrint)
{
	double rawValue = money;
	int yuan = 0;
	int jiao = 0;
	int fen = 0;
	int totalFen = 0;

	int tempValue = 0;
	int Value1 = -1;
	int Value2 = -1;

	/* code */
	/*==================================*/
	// rawValue = 4354543.345678; // 1234.56
	// printf("RAW: %f\n", rawValue);
	Value1 = rawValue * 100; // 123456
	yuan = (int)rawValue;	 // 1234

	// 123456 - 123400 = 56
	tempValue = yuan * 100;
	Value1 = Value1 - tempValue;
	jiao = Value1 / 10.0;

	// 56 - 50 = 6
	tempValue = jiao * 10;
	Value2 = Value1 - tempValue;
	fen = Value2 / 1.0;
	/*=======================*/
	totalFen = 100 * yuan + 10 * jiao + fen;

	switch (isPrint)
	{
	case 1:
		printf("金额: %d元 %d角 %d分\n", yuan, jiao, fen);
		break;
	default:
		break;
	}

	return totalFen;
}

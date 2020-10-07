#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inputFunc.h"

// ���ݱ�������ַ������뽻��
char *inputCharWithTitle(const char *title)
{
	static char str[20];
	char temp[20];
	printf("������ %s ������\n", title);
	scanf("%s", temp);
	fflush(stdin);
	strcpy(str, temp);
	printf("��Ŀ: %s �������� %s\n", title, str);
	return str;
}

// ��������
int inputAge()
{
	int age = 0;
	printf("����������\n");
	scanf("%d", &age);
	fflush(stdin);
	// ������
	while (age < 1 || age > 150)
	{
		printf("��������������\n");
		scanf("%d", &age);
		fflush(stdin);
	}
	printf("����: %d\n", age);
	return age;
}

// ����ID
int inputID(const char *title)
{
	int id = 0;
	printf("������ %s\n", title);
	scanf("%d", &id);
	fflush(stdin);
	printf("����ɹ� %s: %d\n", title, id);
	return id;
}

// ҽ���ϰ�
int *inputWork()
{
	static int work[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int totalDays = 0;
	// ����������
	do {
		printf("�������ҽ��һ���ϰ�������:\n");
		scanf("%d", &totalDays);
	} while (totalDays > 7 || totalDays < 1);
	work[0] = totalDays;
	fflush(stdin);
	// ��һ���ϰ�
	for (int i = 1; i <= totalDays; i++)
	{
		int tempWork = 0;
		// �ܼ��ϰ�
		printf("ҽ����һ���е� %d ���ϰ����ܼ��� (1-7)\n", i);
		scanf("%d", &tempWork);

		// ����쳣
		fflush(stdin);
		while (tempWork >= 8 || tempWork < 1 || work[tempWork] == 1)
		{
			printf("��������������\n");
			scanf("%d", &tempWork);
			fflush(stdin);
		}
		// ����ϰ�
		work[tempWork] = 1;
	}

	// debug�� ����ϰ�����
	// printf("work DEBUG: ");
	// for (int i = 0; i <= 7; i++)
	// {
	//     printf("[%d]", work[i]);
	// }

	return work;
}

// �����Ǯ
int inputPrice(int isPrint)
{
	/* Old Version
	int price = 0;
	printf("��������\n");
	scanf("%d", &price);
	fflush(stdin);
	printf("����ɹ������: %d\n", price);
	return price;
	*/

	double price = 0;
	int valueAsFen = -1;
	printf("��������,�����磺12.34 Ԫ��\n");
	scanf("%lf", &price);
	valueAsFen = money_double_yjf(price, isPrint);
	return valueAsFen;
}

// ��������
int inputAmount()
{
	int amount = 0;
	printf("����������\n");
	scanf("%d", &amount);
	fflush(stdin);
	printf("����ɹ�������: %d\n", amount);
	return amount;
}

// 01 �ж��Ƿ��������
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
			printf("��������������\n");
			break;
		}
		//printf("result:%d\n", result);
	}

	return result;
}

// ��Ǯ��������double������Ԫ�Ƿ֣������ܷ�
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
	yuan = (int)rawValue;    // 1234

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
		printf("���: %dԪ %d�� %d��\n", yuan, jiao, fen);
		break;
	default:
		break;
	}

	return totalFen;
}
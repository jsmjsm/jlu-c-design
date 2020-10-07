#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"treatment.h"
#include"fileFunction.h"

void readin_medicine(char** result)//传进来存储medicine信息的数组名
{
	FILE* fileread;
	fileread = fopen("txt\\medicine.txt", "r");
	char buf[20] = { 0 };
	if (fileread == NULL)
		printf("读入文件指针为空！\n");
	else
	{
		int i = 0;
		char* cp;
		while (fgets(buf, 20, fileread) != NULL)
		{
			if ((cp = strchr(buf, '\n')) != NULL)
				*cp = '\0';//手动将\n位置处的值变为0
			strcpy(result[i], buf);
			i++;
		}
		fclose(fileread);
	}
}

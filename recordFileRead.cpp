#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include"record.h"
#include<string.h>
#include"treatment.h"
#include"fileFunction.h"

void readin_record(char** result)//�������洢record��Ϣ��������
{
	FILE* fileread;
	fileread = fopen("txt\\record.txt", "r");
	char buf[20] = { 0 };
	if (fileread == NULL)
		printf("�����ļ�ָ��Ϊ�գ�\n");
	else
	{
		int i = 0;
		char* cp;
		while (fgets(buf, 20, fileread) != NULL)
		{
			if ((cp = strchr(buf, '\n')) != NULL)
				*cp = '\0';//�ֶ���\nλ�ô���ֵ��Ϊ0
			strcpy(result[i], buf);
			i++;
		}
	}
	fclose(fileread);
}


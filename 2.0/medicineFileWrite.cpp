#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"treatment.h"
#include"fileFunction.h"

void writeout_medicine(struct medicine_list ml)
{
	struct medicine* temp_md = ml.head;//������ʱ���浱ǰrecordָ��
	if (temp_md == NULL)//�ж�ͷָ��
	{
		printf("medicine����ͷָ��Ϊ�գ�");
		return;
	}
	else {
		FILE* filewrite = fopen("txt\\medicine.txt", "w");
		char intTOchar[16] = { 0 };//���ڽ�int����ת��Ϊchar*
		if (filewrite == NULL)
		{
			printf("д���ļ�ָ��Ϊ�գ�\n");
			return;
		}
		else {
			while (1)
			{
				fputs(temp_md->name, filewrite); fputs("\n", filewrite);//����
				itoa(temp_md->unit_Price, intTOchar, 10);//intתchar*
				fputs(intTOchar, filewrite); //����

				if (temp_md->next != NULL)
				{
					fputs("\n", filewrite);
					temp_md = temp_md->next;
				}
				else
					return;
			}
		}
		fclose(filewrite);
	}
}
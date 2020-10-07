#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"treatment.h"
#include"fileFunction.h"

void writeout_medicine(struct medicine_list ml)
{
	struct medicine* temp_md = ml.head;//用于暂时保存当前record指针
	if (temp_md == NULL)//判断头指针
	{
		printf("medicine链表头指针为空！");
		return;
	}
	else {
		FILE* filewrite = fopen("txt\\medicine.txt", "w");
		char intTOchar[16] = { 0 };//用于将int类型转换为char*
		if (filewrite == NULL)
		{
			printf("写出文件指针为空！\n");
			return;
		}
		else {
			while (1)
			{
				fputs(temp_md->name, filewrite); fputs("\n", filewrite);//名字
				itoa(temp_md->unit_Price, intTOchar, 10);//int转char*
				fputs(intTOchar, filewrite); //单价

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
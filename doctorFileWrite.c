#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"doctor.h"
#include"fileFunction.h"

void writeout_doctor(struct doctor_list dl)
{
	struct doctor* temp_dt = dl.head;//用于暂时保存当前record指针
	if (temp_dt == NULL)//判断头指针
	{
		printf("doctor链表头指针为空！");
		return;
	}
	else {
		FILE* filewrite = fopen("txt\\doctor.txt", "w");
		char intTOchar[16] = { 0 };//用于将int类型转换为char*
		if (filewrite == NULL)
		{
			printf("写出文件指针为空！\n");
			return;
		}
		else {
			while (1)
			{
				fputs(temp_dt->name, filewrite); fputs("\n", filewrite);//名字
				fputs(temp_dt->level, filewrite); fputs("\n", filewrite);//level
				fputs(temp_dt->department, filewrite); fputs("\n", filewrite);//科室
				//itoa(temp_dt->worker_id, intTOchar, 10);//int转char*
				sprintf(intTOchar, "%d", temp_dt->worker_id);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//工号

				for (int i = 0; i < 8; i++) {//写入visit数组
					//itoa(temp_dt->visit[i], intTOchar, 10);//int转char*
					sprintf(intTOchar, "%d", temp_dt->visit[i]);
					fputs(intTOchar, filewrite);
					if (i < 7)
						fputs("\n", filewrite);//visit
				}

				if (temp_dt->next != NULL)
				{
					fputs("\n", filewrite);
					temp_dt = temp_dt->next;
				}
				else {
					fclose(filewrite);
					return;
				}
			}
		}
		fclose(filewrite);
	}
}
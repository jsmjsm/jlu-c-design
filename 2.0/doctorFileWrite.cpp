#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"doctor.h"
#include"fileFunction.h"

void writeout_doctor(struct doctor_list dl)
{
	struct doctor* temp_dt = dl.head;//������ʱ���浱ǰrecordָ��
	if (temp_dt == NULL)//�ж�ͷָ��
	{
		printf("doctor����ͷָ��Ϊ�գ�");
		return;
	}
	else {
		FILE* filewrite = fopen("txt\\doctor.txt", "w");
		char intTOchar[16] = { 0 };//���ڽ�int����ת��Ϊchar*
		if (filewrite == NULL)
		{
			printf("д���ļ�ָ��Ϊ�գ�\n");
			return;
		}
		else {
			while (1)
			{
				fputs(temp_dt->name, filewrite); fputs("\n", filewrite);//����
				fputs(temp_dt->level, filewrite); fputs("\n", filewrite);//level
				fputs(temp_dt->department, filewrite); fputs("\n", filewrite);//����
				itoa(temp_dt->worker_id, intTOchar, 10);//intתchar*
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//����

				for (int i = 0; i < 8; i++) {//д��visit����
					itoa(temp_dt->visit[i], intTOchar, 10);//intתchar*
					fputs(intTOchar, filewrite);
					if (i < 7)
						fputs("\n", filewrite);//visit
				}

				if (temp_dt->next != NULL)
				{
					fputs("\n", filewrite);
					temp_dt = temp_dt->next;
				}
				else
					return;
			}
		}
		fclose(filewrite);
	}
}
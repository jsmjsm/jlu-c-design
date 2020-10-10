#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include"record.h"
#include<string.h>
#include"treatment.h"
#include"fileFunction.h"

void writeout_record(struct record* head)
{
	struct record* temp_record = head;//用于暂时保存当前record指针
	if (head == NULL)//判断头指针
	{
		printf("record链表头指针为空！");
		return;
	}
	else {
		FILE* filewrite = fopen("txt\\record.txt", "w");
		char intTOchar[16] = { 0 };//用于将int类型转换为char*
		char buf[128] = { 0 };
		if (filewrite == NULL)
		{
			printf("写出文件指针为空！\n");
			return;
		}
		else {
			while (1)
			{
				struct body_Check* temp_bc = temp_record->tm.bc;//用于暂时存放当前bc指针
				struct used_Medicine* temp_um = temp_record->tm.um;//用于暂时存放当前um指针
				fputs(temp_record->pa.name, filewrite); fputs("\n", filewrite);//名字
				//itoa(temp_record->pa.age, intTOchar, 10);
				sprintf(intTOchar, "%d", temp_record->pa.age);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//age
				//itoa(temp_record->pa.register_id, intTOchar, 10);
				sprintf(intTOchar, "%d", temp_record->pa.register_id);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//挂号
				fputs(temp_record->doc->name, filewrite); fputs("\n", filewrite);//医生name
				fputs(temp_record->doc->level, filewrite); fputs("\n", filewrite);//等级
				fputs(temp_record->doc->department, filewrite); fputs("\n", filewrite);//医生科室
				//itoa(temp_record->doc->worker_id, intTOchar, 10);
				sprintf(intTOchar, "%d", temp_record->doc->worker_id);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//医生工号
				//itoa(temp_record->doc->visit[0], intTOchar, 10);
				sprintf(intTOchar, "%d", temp_record->doc->visit[0]);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//医生上班天数
				//检查流程
				//itoa(temp_record->tm.check_num, intTOchar, 10);
				sprintf(intTOchar, "%d", temp_record->tm.check_num);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//检查数量
				for (int i = 0; i < temp_record->tm.check_num; i++)
				{
					fputs(temp_bc->name, filewrite); fputs("\n", filewrite);
					//itoa(temp_bc->price, intTOchar, 10);
					sprintf(intTOchar, "%d", temp_bc->price);
					fputs(intTOchar, filewrite); fputs("\n", filewrite);//检查价格
					if (temp_bc->next != NULL)
						temp_bc = temp_bc->next;
				}
				//开药流程
				//itoa(temp_record->tm.medicine_num, intTOchar, 10);
				sprintf(intTOchar, "%d", temp_record->tm.medicine_num);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//开药数量
				for (int i = 0; i < temp_record->tm.medicine_num; i++)
				{
					fputs(temp_um->use_m->name, filewrite); fputs("\n", filewrite);
					//itoa(temp_um->use_m->unit_Price, intTOchar, 10);
					sprintf(intTOchar, "%d", temp_um->use_m->unit_Price);
					fputs(intTOchar, filewrite); fputs("\n", filewrite);//药品单价
					//itoa(temp_um->amount, intTOchar, 10);
					sprintf(intTOchar, "%d", temp_um->amount);
					fputs(intTOchar, filewrite); fputs("\n", filewrite);//药品数量
					if (temp_um->next != NULL)
						temp_um = temp_um->next;
				}
				//住院信息
				//itoa(temp_record->tm.lh->in_time.month, intTOchar, 10);
				sprintf(intTOchar, "%d", temp_record->tm.lh->in_time.month);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//月
				//itoa(temp_record->tm.lh->in_time.day, intTOchar, 10);
				sprintf(intTOchar, "%d", temp_record->tm.lh->in_time.day);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//日
				//itoa(temp_record->tm.lh->in_time.hour, intTOchar, 10);
				sprintf(intTOchar, "%d", temp_record->tm.lh->in_time.hour);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//时
				//itoa(temp_record->tm.lh->in_time.minute, intTOchar, 10);
				sprintf(intTOchar, "%d", temp_record->tm.lh->in_time.minute);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//分
				//出院信息
				//itoa(temp_record->tm.lh->out_time.month, intTOchar, 10);
				sprintf(intTOchar, "%d", temp_record->tm.lh->out_time.month);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//月
				//itoa(temp_record->tm.lh->out_time.day, intTOchar, 10);
				sprintf(intTOchar, "%d", temp_record->tm.lh->out_time.day);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//日
				//itoa(temp_record->tm.lh->out_time.hour, intTOchar, 10);
				sprintf(intTOchar, "%d", temp_record->tm.lh->out_time.hour);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//时
				//itoa(temp_record->tm.lh->out_time.minute, intTOchar, 10);
				sprintf(intTOchar, "%d", temp_record->tm.lh->out_time.minute);
				fputs(intTOchar, filewrite); //分
				//打印完毕
				if (temp_record->next == NULL) {
					fclose(filewrite);
					return;
				}
				else
				{
					fputs("\n", filewrite);
					temp_record = temp_record->next;
				}
			}
		}
		fclose(filewrite);
	}
}


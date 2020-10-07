#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include"record.h"
#include<string.h>
#include"treatment.h"
#include"fileFunction.h"

void writeout_record(struct record* head)
{
	struct record* temp_record = head;//������ʱ���浱ǰrecordָ��
	if (head == NULL)//�ж�ͷָ��
	{
		printf("record����ͷָ��Ϊ�գ�");
		return;
	}
	else {
		FILE* filewrite = fopen("txt\\record.txt", "w");
		char intTOchar[16] = { 0 };//���ڽ�int����ת��Ϊchar*
		char buf[128] = { 0 };
		if (filewrite == NULL)
		{
			printf("д���ļ�ָ��Ϊ�գ�\n");
			return;
		}
		else {
			while (1)
			{
				struct body_Check* temp_bc = temp_record->tm.bc;//������ʱ��ŵ�ǰbcָ��
				struct used_Medicine* temp_um = temp_record->tm.um;//������ʱ��ŵ�ǰumָ��
				fputs(temp_record->pa.name, filewrite); fputs("\n", filewrite);//����
				itoa(temp_record->pa.age, intTOchar, 10);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//age
				itoa(temp_record->pa.register_id, intTOchar, 10);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//�Һ�
				fputs(temp_record->doc->name, filewrite); fputs("\n", filewrite);//ҽ��name
				fputs(temp_record->doc->level, filewrite); fputs("\n", filewrite);//�ȼ�
				fputs(temp_record->doc->department, filewrite); fputs("\n", filewrite);//ҽ������
				itoa(temp_record->doc->worker_id, intTOchar, 10);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//ҽ������
				itoa(temp_record->doc->visit[0], intTOchar, 10);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//ҽ���ϰ�����
				//�������
				itoa(temp_record->tm.check_num, intTOchar, 10);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//�������
				for (int i = 0; i < temp_record->tm.check_num; i++)
				{
					fputs(temp_bc->name, filewrite); fputs("\n", filewrite);
					itoa(temp_bc->price, intTOchar, 10);
					fputs(intTOchar, filewrite); fputs("\n", filewrite);//���۸�
					if (temp_bc->next != NULL)
						temp_bc = temp_bc->next;
				}
				//��ҩ����
				itoa(temp_record->tm.medicine_num, intTOchar, 10);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//��ҩ����
				for (int i = 0; i < temp_record->tm.medicine_num; i++)
				{
					fputs(temp_um->use_m->name, filewrite); fputs("\n", filewrite);
					itoa(temp_um->use_m->unit_Price, intTOchar, 10);
					fputs(intTOchar, filewrite); fputs("\n", filewrite);//ҩƷ����
					itoa(temp_um->amount, intTOchar, 10);
					fputs(intTOchar, filewrite); fputs("\n", filewrite);//ҩƷ����
					if (temp_um->next != NULL)
						temp_um = temp_um->next;
				}
				//סԺ��Ϣ
				itoa(temp_record->tm.lh->in_time.month, intTOchar, 10);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//��
				itoa(temp_record->tm.lh->in_time.day, intTOchar, 10);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//��
				itoa(temp_record->tm.lh->in_time.hour, intTOchar, 10);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//ʱ
				itoa(temp_record->tm.lh->in_time.minute, intTOchar, 10);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//��
				//��Ժ��Ϣ
				itoa(temp_record->tm.lh->out_time.month, intTOchar, 10);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//��
				itoa(temp_record->tm.lh->out_time.day, intTOchar, 10);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//��
				itoa(temp_record->tm.lh->out_time.hour, intTOchar, 10);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//ʱ
				itoa(temp_record->tm.lh->out_time.minute, intTOchar, 10);
				fputs(intTOchar, filewrite); fputs("\n", filewrite);//��
				//��ӡ���
				if (temp_record->next == NULL)
					return;
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


#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inputFunc.h"
#include "function.h"

// ������ƣ����滼����Ϣ������һ�� patient �ṹ�壬Ȼ����� create_patient(,,,) ����
struct patient inter_craate_patient()
{
	// ���߽ṹ��
	struct patient pa;
	pa.age = -1;
	pa.register_id = -1;
	strcpy(pa.name, inputCharWithTitle("��������"));
	pa.age = inputAge();
	pa.register_id = inputID("�Һ�");
	return pa;
}

// �������: ����ҽ����Ϣ, ����һ��ҽ���ṹ��
struct doctor inter_create_doctor()
{
	struct doctor oneDoctor;
	strcpy(oneDoctor.name, inputCharWithTitle("ҽ������"));
	strcpy(oneDoctor.level, inputCharWithTitle("ҽ��ְ��"));
	strcpy(oneDoctor.department, inputCharWithTitle("ҽ������"));
	oneDoctor.worker_id = inputID("����");
	// һ���ϰ������
	int *p;
	p = inputWork();
	for (int i = 0; i <= 7; i++)
	{
		oneDoctor.visit[i] = p[i];
	}
	// // debug
	// printf("\nDEBUG!!\n");
	// printf("%s\n", oneDoctor.name);
	// printf("%s\n", oneDoctor.level);
	// printf("%s\n", oneDoctor.department);
	// printf("%d\n", oneDoctor.worker_id);

	// for (int j = 0; j <= 7; j++)
	// {
	//     printf("[%d]", oneDoctor.visit[j]);
	// }
	return oneDoctor;
}

// ������ƣ�������������Ϣ�����������������ͷָ��
struct body_Check *inter_create_check()
{
	// var
	int isNext = 1; // flag
	char temp_name[20];
	int temp_price = 0;
	// Input name
	strcpy(temp_name, inputCharWithTitle("�����Ŀ����"));
	// Input price
	temp_price = inputPrice(1);

	// ������ʽ ����
	struct body_Check *check_head, *node, *end; // return the head, use the head can visit the whole list

	// insert
	check_head = (struct body_Check *)malloc(sizeof(struct body_Check));
	end = check_head;

	strcpy((end->name), temp_name);
	end->price = temp_price;
	end->next = NULL;
	// insert including previous

	while (isNext == 1)
	{
		// check isNext
		isNext = isNextInput("�Ƿ������������Ŀ���������� 1���������� 0");
		/*
		printf("�Ƿ������������Ŀ���������� 1���������� 0\n");
		scanf("%d", &isNext);
		fflush(stdin);
		while (isNext != 1 && isNext != 0)
		{
			printf("�������������ԣ�\n");
			scanf("%d", &isNext);
			fflush(stdin);
		}
		*/
		// next
		if (isNext == 0)
		{
			end->next = NULL;

			// DEBUG
			// printf("DEBUG NOW!!\n");
			// struct body_Check *debug_visit;
			// debug_visit = check_head;
			// while (debug_visit != NULL)
			// {
			//     printf("%s\n", debug_visit->name);
			//     printf("%d\n", debug_visit->price);
			//     debug_visit = debug_visit->next;
			// }
			// printf("DEBUG DONE!!\n");
			return check_head;
		}
		else if (isNext == 1)
		{
			// Input name
			strcpy(temp_name, inputCharWithTitle("�����Ŀ����"));
			// Input price
			temp_price = inputPrice(1);
			// insert new
			node = (struct body_Check *)malloc(sizeof(struct body_Check));
			strcpy((node->name), temp_name);
			node->price = temp_price;
			end->next = node;
			end = node;
		}
		else
		{
			printf("ERR!");
		}
	}
	return 0;
}

// ������ƣ�����һ�� medicine list
struct medicine_list *inter_create_medicine_list()
{
	// init
	struct medicine_list *m_list;
	m_list = (struct medicine_list *)malloc(sizeof(struct medicine_list));
	m_list->head = NULL;
	struct medicine *m_head = m_list->head;
	// temp var
	int isNext = 1;
	char temp_name[20];
	int temp_price = 0;

	// create the list
	strcpy(temp_name, inputCharWithTitle("ҩƷ����"));
	temp_price = inputPrice(1);
	add_to_medicine_list(m_list, temp_name, temp_price);

	// loop
	while (isNext == 1)
	{
		// check isNext
		isNext = isNextInput("�Ƿ�������ҩƷ���������� 1���������� 0");
		/*
		printf("�Ƿ�������ҩƷ���������� 1���������� 0\n");
		scanf("%d", &isNext);
		fflush(stdin);
		while (isNext != 1 && isNext != 0)
		{
			printf("�������������ԣ�\n");
			scanf("%d", &isNext);
			fflush(stdin);
		}
		*/

		if (isNext == 0) // û������ҩ��
		{
			return m_list;
		}
		else if (isNext == 1) // ������ҩ��
		{
			strcpy(temp_name, inputCharWithTitle("ҩƷ����"));
			temp_price = inputPrice(1);
			add_to_medicine_list(m_list, temp_name, temp_price);
		}
		else
		{
			printf("ERR!");
		}
	}
	return 0;
}

// ������ƣ���������ҩ��û��
struct medicine *inter_search_medicine(struct medicine_list *m_list)
{
	struct medicine *result;
	char temp_name[20];
	strcpy(temp_name, inputCharWithTitle("����ѯ��ҩ������"));
	result = search_medicine(m_list, temp_name);
	if (result == NULL)
	{
		printf("�鲻������Ҫ��ҩƷ��\n");
	}
	else
	{
		printf("��ѯ�ɹ���ҩ�����ƣ�%s\n", result->name);
	}
	return result;
}

// ������ƣ���������ҩ������һ����ҩ�б�����ͷָ��
struct used_Medicine *inter_create_used_medicine(struct medicine_list *m_list)
{
	// var
	struct medicine *temp_medicine;
	char temp_name[20];
	int temp_amount;
	int isNext = 1;

	// create the link list
	struct used_Medicine *u_medicine_head, *node, *end;
	u_medicine_head = (struct used_Medicine *)malloc(sizeof(struct used_Medicine));
	u_medicine_head->amount = 0;
	u_medicine_head->next = NULL;
	u_medicine_head->use_m = NULL;
	end = u_medicine_head;

	// body
	while (isNext == 1)
	{
		temp_medicine = inter_search_medicine(m_list);

		if (temp_medicine == NULL)
		{
			// �Ҳ���ҩ��Ĵ���
			// �Ƿ������
			isNext = isNextInput("�Ƿ�������ҩƷ���������� 1���������� 0");
			/*
			printf("�Ƿ�������ҩƷ���������� 1���������� 0\n");
			scanf("%d", &isNext);
			isNext = isNext * 1;
			fflush(stdin);
			while (isNext != 1 && isNext != 0)
			{
				printf("�������������ԣ�\n");
				scanf("%d", &isNext);
				fflush(stdin);
			}
			*/
		}
		else
		{
			// �ҵ�ҩ��
			// ��ӵ���
			temp_amount = inputAmount();
			end->use_m = temp_medicine;
			end->amount = temp_amount;
			end->next = NULL;
			// next��
			isNext = isNextInput("�Ƿ�������ҩƷ���������� 1���������� 0");
			/*
			printf("�Ƿ�������ҩƷ���������� 1���������� 0\n");
			scanf("%d", &isNext);
			fflush(stdin);
			while (isNext != 1 && isNext != 0)
			{
				printf("�������������ԣ�\n");
				scanf("%d", &isNext);
				fflush(stdin);
			}
			*/
		}
	}
	return u_medicine_head;
}

// ������ƣ�סԺ��¼
// TODO: δ���Կ�����
struct live_hospital inter_create_live_hospital()
{
	struct live_hospital live;
	int in_month;
	int in_day;
	int in_hour;
	int in_minute;
	int out_month;
	int out_day;
	int out_hour;
	int out_minute;
	int finalCheck = 0;

	while (finalCheck == 0)
	{
		// > in
		// ��
		printf("������Ժ���·ݣ�month��:\n");
		scanf("%d", &in_month);
		fflush(stdin);
		in_month = (int)in_month;
		while (in_month > 12 || in_month < 1)
		{
			printf("�·�������������ԣ�\n");
			scanf("%d", &in_month);
			fflush(stdin);
		}

		// ��
		printf("������Ժ�����ڣ�day��:\n");
		scanf("%d", &in_day);
		fflush(stdin);
		in_day = (int)in_day;
		while (in_day > 31 || in_day < 1)
		{
			printf("����������������ԣ�\n");
			scanf("%d", &in_day);
			fflush(stdin);
		}

		// ʱ
		printf("������Ժ��ʱ�䣨24Сʱ�ƣ���hour��:\n");
		scanf("%d", &in_hour);
		fflush(stdin);
		in_hour = (int)in_hour;
		while (in_hour > 31 || in_hour < 1)
		{
			printf("ʱ��������������ԣ�\n");
			scanf("%d", &in_hour);
			fflush(stdin);
		}

		// min
		printf("������Ժ�ķ��ӣ�minute��:\n");
		scanf("%d", &in_minute);
		fflush(stdin);
		in_minute = (int)in_minute;
		while (in_minute > 60 || in_minute < 0)
		{
			printf("����������������ԣ�\n");
			scanf("%d", &in_minute);
			fflush(stdin);
		}

		// > out
		// ��
		printf("�����Ժ���·ݣ�month��:\n");
		scanf("%d", &out_month);
		fflush(stdin);
		out_month = (int)out_month;
		while (out_month > 12 || out_month < 1)
		{
			printf("�·�������������ԣ�\n");
			scanf("%d", &out_month);
			fflush(stdin);
		}

		// ��
		printf("�����Ժ�����ڣ�day��:\n");
		scanf("%d", &out_day);
		fflush(stdin);
		out_day = (int)out_day;
		while (out_day > 31 || out_day < 1)
		{
			printf("����������������ԣ�\n");
			scanf("%d", &out_day);
			fflush(stdin);
		}

		// ʱ
		printf("�����Ժ��ʱ�䣨24Сʱ�ƣ���hour��:\n");
		scanf("%d", &out_hour);
		fflush(stdin);
		out_hour = (int)out_hour;
		while (out_hour > 31 || out_hour < 1)
		{
			printf("ʱ��������������ԣ�\n");
			scanf("%d", &out_hour);
			fflush(stdin);
		}

		// min
		printf("�����Ժ�ķ��ӣ�minute��:\n");
		scanf("%d", &out_minute);
		fflush(stdin);
		out_minute = (int)out_minute;
		while (out_minute > 60 || out_minute < 0)
		{
			printf("����������������ԣ�\n");
			scanf("%d", &out_minute);
			fflush(stdin);
		}

		// final check
		printf("��Ժʱ��: %d�� %d�� %dʱ %d�� \n", in_month, in_day, in_hour, in_minute);
		printf("��Ժʱ��: %d�� %d�� %dʱ %d�� \n", out_month, out_day, out_hour, out_minute);

		finalCheck = isNextInput("������Ϣ�Ƿ���ȷ����ȷ������ 1������������Ϣ������ 0");

		// printf("������Ϣ�Ƿ���ȷ����ȷ������ 1������������Ϣ������ 0\n");
		// scanf("%d", &finalCheck);
		// fflush(stdin);
		// while ((finalCheck * 1) != 1 || (finalCheck * 1) != 0)
		// {
		//     printf("��������������\n");
		//     scanf("%d", &finalCheck);
		//     fflush(stdin);
		// }

		if (finalCheck == 1)
		{
			live = create_live_hospital(in_month, in_day, in_hour, in_minute, out_month, out_day, out_hour, out_minute);

			return live;
		}
		else
		{
			printf("��������סԺ��Ϣ\n");
		}
	}
	return create_live_hospital(0, 0, 0, 0, 0, 0, 0, 0);
}

// �������: ���Ƽ�¼ ��װ���� ��Ҫһ��ҩ���б�
// TODO: δ���Կ�����
struct treatment inter_create_treatment(struct medicine_list *m_list)
{
	struct treatment t;
	// temp struct
	struct body_Check *temp_body_check;
	struct used_Medicine *temp_used_medicine;
	struct live_hospital temp_live_hospital;

	printf("��������һ�� treatment!\n");

	// ��������
	temp_body_check = inter_create_check();
	temp_used_medicine = inter_create_used_medicine(m_list);
	temp_live_hospital = inter_create_live_hospital();

	//  ����ҽ�Ƽ�¼
	t = create_treatment(temp_body_check, temp_used_medicine, &temp_live_hospital);
	printf("treatment �����ɹ�!\n");

	return t;
}

// ������ƣ����һ����¼
// TODO: δ���Կ�����
int inter_add_one_record(struct record_list *r_list, struct medicine_list *m_list)
{
	struct patient temp_patient;
	struct doctor temp_doctor;
	struct treatment temp_treatment;

	printf("��������һ�� redcord!\n");
	temp_patient = inter_craate_patient();
	temp_doctor = inter_create_doctor();
	temp_treatment = inter_create_treatment(m_list);

	addOneRecord(r_list, temp_patient, &(temp_doctor), temp_treatment);
	printf("record �����ɹ�!\n");
	return 0;
}

#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inputFunc.h"
#include "function.h"

// 交互设计：保存患者信息，返回一个 patient 结构体，然后调用 create_patient(,,,) 函数
struct patient inter_craate_patient()
{
	// 患者结构体
	struct patient pa;
	pa.age = -1;
	pa.register_id = -1;
	strcpy(pa.name, inputCharWithTitle("患者姓名"));
	pa.age = inputAge();
	pa.register_id = inputID("挂号");
	return pa;
}

// 交互设计: 保存医生信息, 返回一个医生结构体
struct doctor inter_create_doctor()
{
	struct doctor oneDoctor;
	strcpy(oneDoctor.name, inputCharWithTitle("医生姓名"));
	strcpy(oneDoctor.level, inputCharWithTitle("医生职称"));
	strcpy(oneDoctor.department, inputCharWithTitle("医生科室"));
	oneDoctor.worker_id = inputID("工号");
	// 一周上班多少天
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

// 交互设计：保存身体检查信息，返回身体检查链表的头指针
struct body_Check *inter_create_check()
{
	// var
	int isNext = 1; // flag
	char temp_name[20];
	int temp_price = 0;
	// Input name
	strcpy(temp_name, inputCharWithTitle("检查项目名称"));
	// Input price
	temp_price = inputPrice(1);

	// 链表形式 插入
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
		isNext = isNextInput("是否还有其他检查项目，是则输入 1，否则输入 0");
		/*
		printf("是否还有其他检查项目，是则输入 1，否则输入 0\n");
		scanf("%d", &isNext);
		fflush(stdin);
		while (isNext != 1 && isNext != 0)
		{
			printf("输入有误，请重试！\n");
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
			strcpy(temp_name, inputCharWithTitle("检查项目名称"));
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

// 交互设计：创建一个 medicine list
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
	strcpy(temp_name, inputCharWithTitle("药品名称"));
	temp_price = inputPrice(1);
	add_to_medicine_list(m_list, temp_name, temp_price);

	// loop
	while (isNext == 1)
	{
		// check isNext
		isNext = isNextInput("是否还有其他药品，是则输入 1，否则输入 0");
		/*
		printf("是否还有其他药品，是则输入 1，否则输入 0\n");
		scanf("%d", &isNext);
		fflush(stdin);
		while (isNext != 1 && isNext != 0)
		{
			printf("输入有误，请重试！\n");
			scanf("%d", &isNext);
			fflush(stdin);
		}
		*/

		if (isNext == 0) // 没有其他药物
		{
			return m_list;
		}
		else if (isNext == 1) // 有其他药物
		{
			strcpy(temp_name, inputCharWithTitle("药品名称"));
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

// 交互设计：查找这种药有没有
struct medicine *inter_search_medicine(struct medicine_list *m_list)
{
	struct medicine *result;
	char temp_name[20];
	strcpy(temp_name, inputCharWithTitle("欲查询的药物名称"));
	result = search_medicine(m_list, temp_name);
	if (result == NULL)
	{
		printf("查不到您需要的药品！\n");
	}
	else
	{
		printf("查询成功，药物名称：%s\n", result->name);
	}
	return result;
}

// 交互设计：给患者用药，创建一个用药列表，返回头指针
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
			// 找不到药物的处理
			// 是否继续找
			isNext = isNextInput("是否还有其他药品，是则输入 1，否则输入 0");
			/*
			printf("是否还有其他药品，是则输入 1，否则输入 0\n");
			scanf("%d", &isNext);
			isNext = isNext * 1;
			fflush(stdin);
			while (isNext != 1 && isNext != 0)
			{
				printf("输入有误，请重试！\n");
				scanf("%d", &isNext);
				fflush(stdin);
			}
			*/
		}
		else
		{
			// 找到药物
			// 添加到表
			temp_amount = inputAmount();
			end->use_m = temp_medicine;
			end->amount = temp_amount;
			end->next = NULL;
			// next？
			isNext = isNextInput("是否还有其他药品，是则输入 1，否则输入 0");
			/*
			printf("是否还有其他药品，是则输入 1，否则输入 0\n");
			scanf("%d", &isNext);
			fflush(stdin);
			while (isNext != 1 && isNext != 0)
			{
				printf("输入有误，请重试！\n");
				scanf("%d", &isNext);
				fflush(stdin);
			}
			*/
		}
	}
	return u_medicine_head;
}

// 交互设计：住院记录
// TODO: 未测试可行性
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
		// 月
		printf("请输入院的月份（month）:\n");
		scanf("%d", &in_month);
		fflush(stdin);
		in_month = (int)in_month;
		while (in_month > 12 || in_month < 1)
		{
			printf("月份输入错误！请重试！\n");
			scanf("%d", &in_month);
			fflush(stdin);
		}

		// 日
		printf("请输入院的日期（day）:\n");
		scanf("%d", &in_day);
		fflush(stdin);
		in_day = (int)in_day;
		while (in_day > 31 || in_day < 1)
		{
			printf("日期输入错误！请重试！\n");
			scanf("%d", &in_day);
			fflush(stdin);
		}

		// 时
		printf("请输入院的时间（24小时制）（hour）:\n");
		scanf("%d", &in_hour);
		fflush(stdin);
		in_hour = (int)in_hour;
		while (in_hour > 31 || in_hour < 1)
		{
			printf("时间输入错误！请重试！\n");
			scanf("%d", &in_hour);
			fflush(stdin);
		}

		// min
		printf("请输入院的分钟（minute）:\n");
		scanf("%d", &in_minute);
		fflush(stdin);
		in_minute = (int)in_minute;
		while (in_minute > 60 || in_minute < 0)
		{
			printf("分钟输入错误！请重试！\n");
			scanf("%d", &in_minute);
			fflush(stdin);
		}

		// > out
		// 月
		printf("请输出院的月份（month）:\n");
		scanf("%d", &out_month);
		fflush(stdin);
		out_month = (int)out_month;
		while (out_month > 12 || out_month < 1)
		{
			printf("月份输入错误！请重试！\n");
			scanf("%d", &out_month);
			fflush(stdin);
		}

		// 日
		printf("请输出院的日期（day）:\n");
		scanf("%d", &out_day);
		fflush(stdin);
		out_day = (int)out_day;
		while (out_day > 31 || out_day < 1)
		{
			printf("日期输入错误！请重试！\n");
			scanf("%d", &out_day);
			fflush(stdin);
		}

		// 时
		printf("请输出院的时间（24小时制）（hour）:\n");
		scanf("%d", &out_hour);
		fflush(stdin);
		out_hour = (int)out_hour;
		while (out_hour > 31 || out_hour < 1)
		{
			printf("时间输入错误！请重试！\n");
			scanf("%d", &out_hour);
			fflush(stdin);
		}

		// min
		printf("请输出院的分钟（minute）:\n");
		scanf("%d", &out_minute);
		fflush(stdin);
		out_minute = (int)out_minute;
		while (out_minute > 60 || out_minute < 0)
		{
			printf("分钟输入错误！请重试！\n");
			scanf("%d", &out_minute);
			fflush(stdin);
		}

		// final check
		printf("入院时间: %d月 %d日 %d时 %d分 \n", in_month, in_day, in_hour, in_minute);
		printf("出院时间: %d月 %d日 %d时 %d分 \n", out_month, out_day, out_hour, out_minute);

		finalCheck = isNextInput("以上信息是否正确，正确请输入 1，重新输入信息请输入 0");

		// printf("以上信息是否正确，正确请输入 1，重新输入信息请输入 0\n");
		// scanf("%d", &finalCheck);
		// fflush(stdin);
		// while ((finalCheck * 1) != 1 || (finalCheck * 1) != 0)
		// {
		//     printf("输入有误，请重试\n");
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
			printf("重新输入住院信息\n");
		}
	}
	return create_live_hospital(0, 0, 0, 0, 0, 0, 0, 0);
}

// 交互设计: 诊疗记录 组装起来 需要一个药物列表
// TODO: 未测试可行性
struct treatment inter_create_treatment(struct medicine_list *m_list)
{
	struct treatment t;
	// temp struct
	struct body_Check *temp_body_check;
	struct used_Medicine *temp_used_medicine;
	struct live_hospital temp_live_hospital;

	printf("即将创建一条 treatment!\n");

	// 交互创建
	temp_body_check = inter_create_check();
	temp_used_medicine = inter_create_used_medicine(m_list);
	temp_live_hospital = inter_create_live_hospital();

	//  创建医疗记录
	t = create_treatment(temp_body_check, temp_used_medicine, &temp_live_hospital);
	printf("treatment 创建成功!\n");

	return t;
}

// 交互设计：添加一条记录
// TODO: 未测试可行性
int inter_add_one_record(struct record_list *r_list, struct medicine_list *m_list)
{
	struct patient temp_patient;
	struct doctor temp_doctor;
	struct treatment temp_treatment;

	printf("即将创建一条 redcord!\n");
	temp_patient = inter_craate_patient();
	temp_doctor = inter_create_doctor();
	temp_treatment = inter_create_treatment(m_list);

	addOneRecord(r_list, temp_patient, &(temp_doctor), temp_treatment);
	printf("record 创建成功!\n");
	return 0;
}

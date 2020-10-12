#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

int deleteOneRecord(struct record_list *list, int register_id)
{ //删除挂号为xxx的记录
	struct record *temp;
	struct record *previous = NULL;
	temp = list->head;
	if (temp == NULL)
		return 0;
	while (temp != NULL)
	{
		if (temp->pa.register_id == register_id)
		{ //发现要删除的记录
			if (temp == list->head)
			{
				list->head = list->head->next;
			}
			else
			{
				previous->next = temp->next;
			}
			//加入内存释放
			return 1;
		}
		previous = temp;
		temp = temp->next;
	}
	return 0;
}

int modifyOneRecord(struct record_list *list, struct patient pa, struct doctor *doc, struct treatment tm, int register_id)
{
	deleteOneRecord(list, register_id);
	addOneRecord(list, pa, doc, tm);
	return 1;
}

int searchByDepartment(struct record_list *list, const char department[20])
{
	struct record *temp;
	temp = list->head;
	while (temp != NULL)
	{
		if (strcmp(temp->doc->department, department) == 0)
		{
			print_record(temp);
		}
		temp = temp->next;
	}
	return 1;
}

int searchByDoctor(struct record_list *list, int worker_id)
{
	struct record *temp;
	temp = list->head;
	while (temp != NULL)
	{
		if (temp->doc->worker_id == worker_id)
		{
			print_record(temp);
		}
		temp = temp->next;
	}
	return 1;
}

int searchByPatient(struct record_list *list, const char name[20], int age)
{
	struct record *temp;
	temp = list->head;
	while (temp != NULL)
	{
		if (strcmp(temp->pa.name, name) == 0 && temp->pa.age == age)
		{
			print_record(temp);
		}
		temp = temp->next;
	}
	return 1;
}

int printRecordDuringTime(struct record_list *list, int start_m, int start_d, int end_m, int end_d)
{
	struct record *temp;
	temp = list->head;
	if (temp != NULL)
	{
		int time = temp->pa.register_id / 1000;
		int start_time = start_m * 100 + start_d;
		int end_time = end_m * 100 + end_d;
		while (temp != NULL)
		{
			if (start_time <= time && end_time >= time)
			{
				print_record(temp);
			}
			temp = temp->next;
		}
	}
	return 1;
}

int calcDoctorBusy(struct record_list *r_list, struct doctor_list d_list)
{
	int working[30] = {0}; //记录三十个医生
	int i = 0;
	struct doctor *temp_d;
	struct record *temp_t;
	temp_d = d_list.head;
	printf("各医生出诊情况：\n");
	while (temp_d != NULL)
	{
		temp_t = r_list->head;
		while (temp_t != NULL)
		{
			if (temp_t->doc->worker_id == temp_d->worker_id)
				working[i]++;
			temp_t = temp_t->next;
		}
		printf("%s%s（工号：%d）在今年出诊了%d次\n", temp_d->level, temp_d->name, temp_d->worker_id, working[i]);
		i++;
		temp_d = temp_d->next;
	}
	printf("\n");

	return 1;
}

int createLiveInHospital(struct record_list *list, struct time now)
{
	struct record *temp;
	struct time temp_t;
	int start_time;
	int end_time;
	int now_time;
	now_time = now.month * 1000000 + now.day * 10000 + now.hour * 100 + now.minute;
	printf("当前时间:%d月%d日%d时%d分\n", now.month, now.day, now.hour, now.minute);
	printf("当前住院患者：\n\n");
	temp = list->head;
	while (temp != NULL)
	{
		temp_t = temp->tm.lh->in_time;
		start_time = temp_t.month * 1000000 + temp_t.day * 10000 + temp_t.hour * 100 + temp_t.minute;
		temp_t = temp->tm.lh->out_time;
		end_time = temp_t.month * 1000000 + temp_t.day * 10000 + temp_t.hour * 100 + temp_t.minute;
		if (now_time >= start_time && now_time <= end_time)
		{
			printf("患者姓名：%s   ", temp->pa.name);
			printf("患者年龄：%d\n", temp->pa.age);
			printf("住院时间：%d月%d日%d时%d分\n", temp->tm.lh->in_time.month, temp->tm.lh->in_time.day, temp->tm.lh->in_time.hour, temp->tm.lh->in_time.minute);
			printf("预期出院时间：%d月%d日%d时%d分\n", temp->tm.lh->out_time.month, temp->tm.lh->out_time.day, temp->tm.lh->out_time.hour, temp->tm.lh->out_time.minute);
			printf("押金：%.2f元\n", temp->tm.lh->pledge * 1.0 / 100);
			printf("\n");
		}
		temp = temp->next;
	}
	return 1;
}

double deduct_expenses(struct record_list *list, struct time now)
{ //根据当前时间扣除当前住院患者的费用
	struct record *temp;
	struct time temp_t;
	int start_time;
	int end_time;
	int now_time;
	int expense = 0; //收费
	now_time = now.month * 1000000 + now.day * 10000 + now.hour * 100 + now.minute;
	temp = list->head;
	while (temp != NULL)
	{
		temp_t = temp->tm.lh->in_time;
		start_time = temp_t.month * 1000000 + temp_t.day * 10000 + temp_t.hour * 100 + temp_t.minute;
		temp_t = temp->tm.lh->out_time;
		end_time = temp_t.month * 1000000 + temp_t.day * 10000 + temp_t.hour * 100 + temp_t.minute;
		if (now_time >= start_time && now_time <= end_time)
		{
			if (temp->tm.lh->pledge >= 120000)
			{ //扣除押金
				temp->tm.lh->pledge -= 20000;
			}
			else if (temp->tm.lh->pledge < 120000 && temp->tm.lh->pledge >= 100000)
			{ //押金小于1000
				temp->tm.lh->pledge = 100000;
			}
			expense += 20000;
		}
		temp = temp->next;
	}
	return expense * 1.0 / 100;
}

int day_count(int month, int day)
{
	int days = 0;
	switch (month)
	{
	case 1:
		days += 0;
	case 2:
		days += 31;
	case 3:
		days += 29;
	case 4:
		days += 31;
	case 5:
		days += 30;
	case 6:
		days += 31;
	case 7:
		days += 30;
	case 8:
		days += 31;
	case 9:
		days += 31;
	case 10:
		days += 30;
	case 11:
		days += 31;
	case 12:
		days += 30;
	}
	days += (day - 1);
	return days;
}

int day_minus(int month1, int day1, int month2, int day2)
{ //计算日期差
	int days1 = day_count(month1, day1);
	int days2 = day_count(month2, day2);
	return days2 - days1;
}

double calcCurrentTurnover(struct record_list *list, struct time now)
{ //计算体检费用和药物费用，住院费用另外计算
	int now_time;
	int in_time;
	int out_time;
	struct record *temp;
	temp = list->head;
	now_time = now.month * 1000000 + now.day * 10000 + now.hour * 100 + now.minute;
	double total_money = 0;
	while (temp != NULL)
	{
		in_time = temp->tm.lh->in_time.month * 1000000 + temp->tm.lh->in_time.day * 10000 + temp->tm.lh->in_time.hour * 100 + temp->tm.lh->in_time.minute;
		if (in_time < now_time)
		{ //在日期之前看病，计入检查费、药费
			total_money += temp->tm.check_total_price;
			total_money += temp->tm.medicine_total_price;
			out_time = temp->tm.lh->out_time.month * 1000000 + temp->tm.lh->out_time.day * 10000 + temp->tm.lh->out_time.hour * 100 + temp->tm.lh->out_time.minute;
			if (out_time > now_time)
			{ //未出院
				total_money += day_minus(temp->tm.lh->in_time.month, temp->tm.lh->in_time.day, now.month, now.day) * 20000;
				if (now.hour < 8)
					total_money -= 20000;
			}
			else
			{ //已出院
				total_money += day_minus(temp->tm.lh->in_time.month, temp->tm.lh->in_time.day, temp->tm.lh->out_time.month, temp->tm.lh->out_time.day) * 20000;
				if (temp->tm.lh->out_time.hour < 8)
					total_money -= 20000;
			}
		}
		temp = temp->next;
	}
	return total_money * 1.0 / 100;
}

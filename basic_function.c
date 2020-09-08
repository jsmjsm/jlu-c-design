#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basic_function.h"

struct patient create_patient(const char name[20], int age, int register_id)
{ //保存患者信息
	struct patient pa;
	strcpy(pa.name, name);
	pa.age = age;
	pa.register_id = register_id; //挂号为日期（4位）+当天顺序号（3位）
	return pa;
}

struct doctor *create_doctor(const char name[20], const char level[20], const char department[20], int worker_id, int visit[8], struct doctor_list *list)
{ //添加新医生
	struct doctor *dc;
	struct doctor *temp;
	int i;
	//生成新结点
	dc = (struct doctor *)malloc(sizeof(struct doctor));
	strcpy(dc->name, name);
	strcpy(dc->level, level);
	strcpy(dc->department, department);
	dc->worker_id = worker_id;
	dc->next = NULL;
	for (i = 0; i < 8; i++)
	{
		dc->visit[i] = visit[i];
	}
	//添加到doctor_list
	temp = list->head;
	if (temp == NULL)
	{
		list->head = dc;
	}
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = dc;
	}
	return dc;
}

struct doctor *find_doctor(int worker_id, struct doctor_list list)
{ //根据工号搜寻医生
	struct doctor *temp;
	temp = list.head;
	while (temp != NULL)
	{
		if (temp->worker_id == worker_id)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

struct treatment create_treatment(struct body_Check *bc, struct used_Medicine *um, struct live_hospital *lh)
{ //体检、用药、住院
	struct treatment tm;
	struct body_Check *temp1;
	struct used_Medicine *temp2;
	int num_c = 0;
	int cost_c = 0;
	int num_m = 0;
	int cost_m = 0;
	tm.bc = bc;
	tm.um = um;
	tm.lh = lh;
	temp1 = bc;
	while (bc != NULL)
	{
		num_c++;
		cost_c += bc->price;
		bc = bc->next;
	}
	tm.check_num = num_c;
	tm.check_total_price = cost_c;
	temp2 = um;
	while (um != NULL)
	{
		num_m++;
		cost_m += um->amount * um->use_m->unit_Price;
		um = um->next;
	}
	tm.medicine_num = num_m;
	tm.medicine_total_price = cost_m;
	return tm;
}

struct body_Check *create_check(struct body_Check *previous, const char name[30], int price)
{ //增加体检项目
	struct body_Check *check;
	check = (struct body_Check *)malloc(sizeof(struct body_Check));
	strcpy(check->name, name);
	check->price = price;
	check->next = NULL;
	if (previous != NULL)
		previous->next = check;
	return check;
}

void add_to_medicine_list(struct medicine_list *list, const char name[30], int price)
{ //增加药物种类
	struct medicine *temp;
	struct medicine *m;
	m = (struct medicine *)malloc(sizeof(struct medicine));
	strcpy(m->name, name);
	m->unit_Price = price;
	m->next = NULL;
	temp = list->head;
	if (temp == NULL)
	{
		list->head = m;
	}
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = m;
	}
}

struct medicine *search_medicine(struct medicine_list *list, const char name[30])
{ //根据药名搜索药
	struct medicine *temp;
	temp = list->head;
	while (temp != NULL)
	{
		if (strcmp(temp->name, name) == 0) //相等
			return temp;
		temp = temp->next;
	}
	return NULL;
}

struct used_Medicine *create_use_m(struct used_Medicine *previous, struct medicine *m, int amount)
{ //增加用药
	struct used_Medicine *use;
	use = (struct used_Medicine *)malloc(sizeof(struct used_Medicine));
	use->use_m = m;
	use->amount = amount;
	use->next = NULL;
	if (previous != NULL)
		previous->next = use;
	return use;
}

struct time create_time(int month, int day, int hour, int minute)
{ //创建时刻
	struct time new_time;
	new_time.month = month;
	new_time.day = day;
	new_time.hour = hour;
	new_time.minute = minute;
	return new_time;
}

struct live_hospital create_live_hospital(int in_month, int in_day, int in_hour, int in_minute, int out_month, int out_day, int out_hour, int out_minute)
{ //添加住院信息
	struct live_hospital new_live;
	struct time in_time;
	struct time out_time;
	in_time = create_time(in_month, in_day, in_hour, in_minute);
	out_time = create_time(out_month, out_day, out_hour, out_minute);
	new_live.in_time = in_time;
	new_live.out_time = out_time;
	new_live.predict_days = ((out_month - in_month) * 30 + (out_day - in_day));
	if (out_hour < 8)
		new_live.predict_days++;
	new_live.pledge = 20000 * new_live.predict_days;
	if (new_live.pledge < 100000)
		new_live.pledge = 100000;
	return new_live;
}

int addOneRecord(struct record_list *list, struct patient pa, struct doctor *doc, struct treatment tm)
{ //添加一条信息，在此之前需要添加其他判断函数
	struct record *temp;
	struct record *new_record;
	//生成新结点
	new_record = (struct record *)malloc(sizeof(struct record));
	new_record->pa = pa;
	new_record->doc = doc;
	new_record->tm = tm;
	new_record->next = NULL;
	//添加到record_list
	temp = list->head;
	if (temp == NULL)
	{
		list->head = new_record;
	}
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new_record;
	}
	return 1;
}

void print_record(struct record *temp)
{
	struct body_Check *temp_c;
	struct used_Medicine *temp_m;
	int j;
	printf("患者姓名：%s   ", temp->pa.name);
	printf("患者年龄：%d\n", temp->pa.age);
	printf("挂号:%d\n", temp->pa.register_id);
	printf("医生姓名：%s   ", temp->doc->name);
	printf("医生等级：%s   ", temp->doc->level);
	printf("医生科室：%s\n", temp->doc->department);
	printf("医生工号：%d   ", temp->doc->worker_id);
	printf("医生一周上班天数：%d\n", temp->doc->visit[0]);
	j = 1;
	temp_c = temp->tm.bc;
	printf("检查流程数：%d\n", temp->tm.check_num);
	while (temp_c != NULL)
	{
		printf("检查流程%d：%s   ", j, temp_c->name);
		printf("价格：%.2f元\n", float(temp_c->price) / 100);
		j++;
		temp_c = temp_c->next;
	}
	printf("检查总价格：%.2f元\n", float(temp->tm.check_total_price) / 100);
	j = 1;
	temp_m = temp->tm.um;
	printf("药品种类数：%d\n", temp->tm.medicine_num);
	while (temp_m != NULL)
	{
		printf("药品%d：%s   ", j, temp_m->use_m->name);
		printf("单价：%.2f元   ", float(temp_m->use_m->unit_Price) / 100);
		printf("数量：%d\n", temp_m->amount);
		j++;
		temp_m = temp_m->next;
	}
	printf("药品总价格：%.2f元\n", float(temp->tm.medicine_total_price) / 100);
	printf("住院时间：%d月%d日%d时%d分\n", temp->tm.lh->in_time.month, temp->tm.lh->in_time.day, temp->tm.lh->in_time.hour, temp->tm.lh->in_time.minute);
	printf("预期出院时间：%d月%d日%d时%d分\n", temp->tm.lh->out_time.month, temp->tm.lh->out_time.day, temp->tm.lh->out_time.hour, temp->tm.lh->out_time.minute);
	printf("预期住院天数：%d   ", temp->tm.lh->predict_days);
	printf("押金：%.2f元\n", float(temp->tm.lh->pledge) / 100);
	printf("\n");
}

void print_all(struct record_list *list)
{ //输出全部信息，测试用
	struct record *temp;
	int i;
	i = 1;
	temp = list->head;
	while (temp != NULL)
	{
		printf("第%d条记录\n", i);
		print_record(temp);
		i++;
		temp = temp->next;
		printf("\n");
	}
}

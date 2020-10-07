#ifndef DOCTOR_H
#define DOCTOR_H

struct doctor
{
	char name[20];
	char level[20];
	char department[20]; //科室
	int worker_id;
	int visit[8]; //第0位表示一周上班天数（1-7天），第1位到第7位代表周一到周日是否上班，上班则为1，否则为0
	struct doctor * next;
};

struct doctor_list
{
	struct doctor *head;
};


#endif
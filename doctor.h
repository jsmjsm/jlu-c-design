#ifndef DOCTOR_H
#define DOCTOR_H

struct doctor
{
	char name[20];
	char level[20];
	char department[20]; //����
	int worker_id;
	int visit[8]; //��0λ��ʾһ���ϰ�������1-7�죩����1λ����7λ������һ�������Ƿ��ϰ࣬�ϰ���Ϊ1������Ϊ0
	struct doctor * next;
};

struct doctor_list
{
	struct doctor *head;
};


#endif
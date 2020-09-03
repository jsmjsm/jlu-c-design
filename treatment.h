#ifndef TREATMENT_H
#define TREATMENT_H

//Ǯ�Է�Ϊ��λ

struct treatment;
struct body_Check;
struct medicine;
struct medicine_list;
struct used_Medicine;
struct time;
struct live_hospital;

struct treatment { //��ָ��head
	struct body_Check * bc;
	int check_num; //�����
	int check_total_price; //����ܼ۸�
	struct used_Medicine * um; 
	int medicine_num; //ҩƷ������
	int medicine_total_price; //ҩƷ�ܼ۸�
	struct live_hospital * lh;
};

struct body_Check { //���
	char name[30];
	int price;
	struct body_Check * next;
};

struct medicine { //ҩƷ��Ϣ
	char name[30];
	int unit_Price; //����
	struct medicine * next;
};

struct medicine_list { //��¼ȫ��ҩƷ��Ϣ
	struct medicine * head;
};

struct used_Medicine { //��ҩ
	struct medicine * use_m;
	int amount;
	struct used_Medicine * next;
};

struct time { //ʱ��
	int month;
	int day;
	int hour;
	int minute;
};

struct live_hospital {
	struct time in_time; //סԺ����
	struct time out_time; //Ԥ�Ƴ�Ժ����
	int predict_days; //Ԥ��סԺ����
	int pledge;//ʣ��Ѻ��
};

#endif
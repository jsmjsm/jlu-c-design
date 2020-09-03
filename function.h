#ifndef FUNCTINO_H
#define FUNCTINO_H

#include "patient.h"
#include "doctor.h"
#include "treatment.h"
#include "record.h"

struct patient create_patient(const char name[20], int age, int register_id); //���滼����Ϣ

struct doctor * create_doctor(const char name[20], const char level[20], const char department[20], int worker_id, int visit[8], struct doctor_list * list); //�����ҽ��

struct doctor * find_doctor(int worker_id, struct doctor_list list);//���ݹ�����Ѱҽ��

struct treatment create_treatment(struct body_Check * bc, struct used_Medicine * um, struct live_hospital * lh); //��졢��ҩ��סԺ

struct body_Check * create_check(struct body_Check * previous, const char name[30], int price); //���������Ŀ

void add_to_medicine_list(struct medicine_list * list, const char name[30], int price); //����ҩ������

struct medicine * search_medicine(struct medicine_list * list, const char name[30]); //����ҩ������ҩ

struct used_Medicine * create_use_m(struct used_Medicine * previous, struct medicine * m, int amount); //������ҩ

struct time create_time(int month, int day, int hour, int minute);//����ʱ��

struct live_hospital create_live_hospital(int in_month, int in_day, int in_hour, int in_minute, int out_month, int out_day, int out_hour, int out_minute); //���סԺ��Ϣ

int addOneRecord(struct record_list * list, struct patient pa, struct doctor * doc, struct treatment tm); //���һ����Ϣ���ڴ�֮ǰ��Ҫ��������жϺ���

void print_all(struct record_list * list);//���ȫ����Ϣ��������

#endif
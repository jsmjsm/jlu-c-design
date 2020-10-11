#ifndef BASIC_FUNCTION_H
#define BASIC_FUNCTION_H

#include "patient.h"
#include "doctor.h"
#include "treatment.h"
#include "record.h"

struct patient create_patient(const char name[20], int age, int register_id); //保存患者信息

struct doctor *create_doctor(const char name[20], const char level[20], const char department[20], int worker_id, int visit[8], struct doctor_list *list); //添加新医生

struct doctor *find_doctor(int worker_id, struct doctor_list list); //根据工号搜寻医生

void show_doctor_list(struct doctor_list *list); //根据工号搜寻医生

struct treatment create_treatment(struct body_Check *bc, struct used_Medicine *um, struct live_hospital *lh); //体检、用药、住院

struct body_Check *create_check(struct body_Check *previous, const char name[30], int price); //增加体检项目

void add_to_medicine_list(struct medicine_list *list, const char name[30], int price); //增加药物种类

struct medicine *search_medicine(struct medicine_list *list, const char name[30]); //根据药名搜索药

void show_medicine_list(struct medicine_list *list); //显示全部药

struct used_Medicine *create_use_m(struct used_Medicine *previous, struct medicine *m, int amount); //增加用药

struct time create_time(int month, int day, int hour, int minute); //创建时刻

struct live_hospital *create_live_hospital(int in_month, int in_day, int in_hour, int in_minute, int out_month, int out_day, int out_hour, int out_minute); //添加住院信息

int addOneRecord(struct record_list *list, struct patient pa, struct doctor *doc, struct treatment tm); //添加一条信息，在此之前需要添加其他判断函数

void print_all(struct record_list *list); //输出全部信息，测试用

void print_record(struct record *temp);

int register_id_valid(struct record_list *list, int id); //检查是否已有此挂号

#endif
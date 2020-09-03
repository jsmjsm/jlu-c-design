﻿#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basic_function.h"
#include "function.h"

int main()
{
	struct patient p1, p2, p3;
	p1 = create_patient("小明", 20, 803001);
	p2 = create_patient("小刚", 18, 803002);
	p3 = create_patient("小红", 22, 803003);

	struct doctor * d1, *d2, *d3;
	struct doctor_list dc_list;
	dc_list.head = NULL;
	int work[8] = { 7,1,1,1,1,1,1,1 };
	d1 = create_doctor("小李", "副主任医师", "牙科", 10001, work, &dc_list);
	d2 = create_doctor("小王", "主任医师", "眼科", 10002, work, &dc_list);
	d3 = create_doctor("小张", "主任医师", "肠胃科", 10003, work, &dc_list);

	struct body_Check * c1, *c2, *c3, *c4, *c5;
	c1 = create_check(NULL, "验血", 3001);
	c2 = create_check(c1, "体温", 501);
	c3 = create_check(NULL, "验血", 3500);
	c4 = create_check(c3, "体温", 700);
	c5 = create_check(NULL, "胃镜", 50000);

	struct medicine * m1;
	struct medicine_list * m_list;
	struct used_Medicine * u_m1, *u_m2, *u_m3, *u_m4, *u_m5, *u_m6;
	m_list = (struct medicine_list *)malloc(sizeof(struct medicine_list));
	m_list->head = NULL;
	add_to_medicine_list(m_list, "双黄连", 3001);
	add_to_medicine_list(m_list, "板蓝根", 2501);
	add_to_medicine_list(m_list, "XX药片", 8000);
	add_to_medicine_list(m_list, "XY药片", 10000);
	add_to_medicine_list(m_list, "XZ药片", 15000);
	m1 = search_medicine(m_list, "双黄连");
	u_m1 = create_use_m(NULL, m1, 2);
	m1 = search_medicine(m_list, "板蓝根");
	u_m2 = create_use_m(u_m1, m1, 2);
	m1 = search_medicine(m_list, "板蓝根");
	u_m3 = create_use_m(NULL, m1, 4);
	m1 = search_medicine(m_list, "XX药片");
	u_m4 = create_use_m(u_m3, m1, 3);
	m1 = search_medicine(m_list, "XY药片");
	u_m5 = create_use_m(NULL, m1, 1);
	m1 = search_medicine(m_list, "XZ药片");
	u_m6 = create_use_m(u_m5, m1, 1);
	

	struct live_hospital live1, live2, live3;
	live1 = create_live_hospital(8, 3, 12, 0, 9, 3, 12, 0);
	live2 = create_live_hospital(8, 3, 12, 0, 8, 5, 7, 0);
	live3 = create_live_hospital(8, 3, 12, 0, 8, 8, 12, 0);

	struct treatment t1, t2, t3;
	t1 = create_treatment(c1, u_m1, &live1);
	t2 = create_treatment(c3, u_m3, &live2);
	t3 = create_treatment(c5, u_m5, &live3);

	struct record_list * r_list;
	r_list = (struct record_list *)malloc(sizeof(struct record_list));
	r_list->head = NULL;
	addOneRecord(r_list, p1, d2, t1);
	addOneRecord(r_list, p2, d1, t2);
	addOneRecord(r_list, p3, d3, t3);

	struct time time1 = create_time(8, 8, 8, 0);
	float lh_cost = 0;

	//deleteOneRecord(r_list, 803003);
	//modifyOneRecord(r_list, p3, d3, t3, 803002);
	//searchByDepartment(r_list, "眼科");
	//searchByDoctor(r_list, 10001);
	//searchByPatient(r_list, "小明", 20);
	//printRecordDuringTime(r_list, 7, 1, 9, 1); //7.1-9.1
	//calcDoctorBusy(r_list, dc_list);
	//print_all(r_list);

	createLiveInHospital(r_list, time1);

	print_all(r_list);
	lh_cost = deduct_expenses(r_list, time1); //扣钱
	print_all(r_list);

	printf("总收入：%.2f元", calcCurrentTurnover(r_list, lh_cost));

}

#ifndef FUNCTION_H
#define FUNCTION_H

#include "basic_function.h"

// 删记录
int deleteOneRecord(struct record_list *list, int register_id);

int modifyOneRecord(struct record_list *list, struct patient pa, struct doctor *doc, struct treatment tm, int register_id);

int searchByDepartment(struct record_list *list, const char department[20]);

int searchByDoctor(struct record_list *list, int worker_id);

int searchByPatient(struct record_list *list, const char name[20], int age);

int printRecordDuringTime(struct record_list *list, int start_m, int start_d, int end_m, int end_d);

int calcDoctorBusy(struct record_list *r_list, struct doctor_list d_list);

int createLiveInHospital(struct record_list *list, struct time now); //打印当前住院信息

double calcCurrentTurnover(struct record_list *list, double live_hospital); //计算体检费用和药物费用，住院费用另外计算

double deduct_expenses(struct record_list *list, struct time now); //根据当前时间扣除当前住院患者的费用

#endif

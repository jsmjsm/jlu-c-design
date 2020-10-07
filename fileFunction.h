#ifndef FILEFUNCTION_H
#define FILEFUNCTION_H
void readin_record(char ** result);//传进来存储record信息的数组名
void writeout_record(struct record* head);
void readin_medicine(char ** result);//传进来存储record信息的数组名
void writeout_medicine(struct medicine_list ml);
void readin_doctor(char ** result);//传进来存储record信息的数组名
void writeout_doctor(struct doctor_list dl);
#endif
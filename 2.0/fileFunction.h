#ifndef FILEFUNCTION_H
#define FILEFUNCTION_H
void readin_record(char ** result);//�������洢record��Ϣ��������
void writeout_record(struct record* head);
void readin_medicine(char ** result);//�������洢record��Ϣ��������
void writeout_medicine(struct medicine_list ml);
void readin_doctor(char ** result);//�������洢record��Ϣ��������
void writeout_doctor(struct doctor_list dl);
#endif
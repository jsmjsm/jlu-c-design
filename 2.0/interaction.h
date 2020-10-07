#ifndef INTERACTION_H
#define INTERACTION_H

/*  �������
	function ����ֱ�Ӳ�����ȱ�ٶ��������ݵļ��
	��ҪһЩ��麯��
*/
#include "function.h"

// ������ƣ����滼����Ϣ������һ�� patient �ṹ�壬Ȼ����� create_patient(,,,) ����
struct patient inter_craate_patient();

// �������: ����ҽ����Ϣ, ����һ��ҽ���ṹ��
struct doctor inter_create_doctor();

// ������ƣ�������������Ϣ�����������������ͷָ��
struct body_Check *inter_create_check();

// ������ƣ�����һ�� medicine list
struct medicine_list *inter_create_medicine_list();

// ������ƣ���������ҩ��û��
struct medicine *inter_search_medicine(struct medicine_list *m_list);

// ������ƣ���������ҩ������һ����ҩ�б�����ͷָ��
struct used_Medicine *inter_create_used_medicine(struct medicine_list *m_list);

// ������ƣ�סԺ��¼
struct live_hospital inter_create_live_hospital();

// �������: ���Ƽ�¼
struct treatment inter_create_treatment(struct medicine_list *m_list);

// ������ƣ����һ����¼
int inter_add_one_record(struct record_list *r_list, struct medicine_list *m_list);

#endif

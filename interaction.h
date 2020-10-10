#ifndef INTERACTION_H
#define INTERACTION_H

/*  交互设计
	function 都是直接操作，缺少对输入内容的检查
	需要一些检查函数
*/
#include "function.h"

// 交互设计: 保存药品信息（新加）
struct medicine inter_create_medicine(struct medicine_list *m_list);

// 交互设计：保存患者信息，返回一个 patient 结构体，然后调用 create_patient(,,,) 函数
struct patient inter_create_patient();

// 交互设计: 保存医生信息, 返回一个医生结构体
struct doctor inter_create_doctor(struct doctor_list *);

// 交互设计：保存身体检查信息，返回身体检查链表的头指针
struct body_Check *inter_create_check();

// 交互设计：创建一个 medicine list
struct medicine_list *inter_create_medicine_list();

// 交互设计：查找这种药有没有
struct medicine *inter_search_medicine(struct medicine_list *m_list);

// 交互设计：给患者用药，创建一个用药列表，返回头指针
struct used_Medicine *inter_create_used_medicine(struct medicine_list *m_list);

// 交互设计：住院记录
struct live_hospital inter_create_live_hospital();

// 交互设计: 诊疗记录
struct treatment inter_create_treatment(struct medicine_list *m_list);

// 交互设计：添加一条记录
int inter_add_one_record(struct record_list *r_list, struct medicine_list *m_list, struct doctor_list *);

// 交互设计： 删除一条诊疗记录
int inter_delete_one_record(struct record_list *list);

// 交互设计：修改一条诊疗记录
int inter_modify_one_record(struct record_list *list, struct medicine_list *m_list, struct doctor_list *d_list);

#endif

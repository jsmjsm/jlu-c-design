#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#include "interaction.h"

int main()
{
    struct patient p1, p2, p3;
    /* 交互 */
    // p1 = inter_craate_patient();
    // p1 = create_patient(p1.name, p1.age, p1.register_id);
    p1 = create_patient("小明", 20, 80301);
    p2 = create_patient("小刚", 18, 80302);
    p3 = create_patient("小红", 22, 80303);

    struct doctor *d1, *d2, *d3;
    struct doctor_list dc_list;
    dc_list.head = NULL;
    int work[8] = {7, 1, 1, 1, 1, 1, 1, 1};

    /* 交互 */
    // d1 = inter_create_doctor() ; 错误 ❌
    // 正确：
    //struct doctor tempDoctor = inter_create_doctor();
    // d1 = &(tempDoctor);

    d1 = create_doctor("小李", "副主任医师", "牙科", 10001, work, &dc_list);
    d2 = create_doctor("小王", "主任医师", "眼科", 10002, work, &dc_list);
    d3 = create_doctor("小张", "主任医师", "肠胃科", 10003, work, &dc_list);

    struct body_Check *c1, *c2, *c3, *c4, *c5;
    /* 交互 */
    // c1 = inter_create_check();
    c1 = create_check(NULL, "验血", 3000);
    c2 = create_check(c1, "体温", 500);
    c3 = create_check(NULL, "验血", 3500);
    c4 = create_check(c3, "体温", 700);
    c5 = create_check(NULL, "胃镜", 50000);

    struct medicine *m1;
    struct medicine_list *m_list;
    struct used_Medicine *u_m1, *u_m2, *u_m3, *u_m4, *u_m5, *u_m6;
    m_list = (struct medicine_list *)malloc(sizeof(struct medicine_list));
    m_list->head = NULL;

    add_to_medicine_list(m_list, "双黄连", 3000);
    add_to_medicine_list(m_list, "板蓝根", 2500);
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

    struct record_list *r_list;
    r_list = (struct record_list *)malloc(sizeof(struct record_list));
    r_list->head = NULL;
    addOneRecord(r_list, p1, d2, t1);
    addOneRecord(r_list, p2, d1, t2);
    addOneRecord(r_list, p3, d3, t3);

    print_all(r_list);
}

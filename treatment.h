#ifndef TREATMENT_H
#define TREATMENT_H

//钱以分为单位

struct treatment;
struct body_Check;
struct medicine;
struct medicine_list;
struct used_Medicine;
struct time;
struct live_hospital;

struct treatment { //均指向head
	struct body_Check * bc;
	int check_num; //检查数
	int check_total_price; //检查总价格
	struct used_Medicine * um;
	int medicine_num; //药品种类数
	int medicine_total_price; //药品总价格
	struct live_hospital * lh;
};

struct body_Check { //体检
	char name[30];
	int price;
	struct body_Check * next;
};

struct medicine { //药品信息
	char name[30];
	int unit_Price; //单价
	struct medicine * next;
};

struct medicine_list { //记录全部药品信息
	struct medicine * head;
};

struct used_Medicine { //用药
	struct medicine * use_m;
	int amount;
	struct used_Medicine * next;
};

struct time { //时间
	int month;
	int day;
	int hour;
	int minute;
};

struct live_hospital {
	struct time in_time; //住院日期
	struct time out_time; //预计出院日期
	int predict_days; //预计住院天数
	int pledge;//剩余押金
};

#endif
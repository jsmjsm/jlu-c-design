//Ǯ�Է�Ϊ��λ

struct treatment {
	struct body_Check;
	struct used_medicine;
	struct live_hospital
};

struct body_Check { //���
	char name[30];
	int price;
	struct body_Check * next;
};

struct medicine { //ҩƷ��Ϣ
	char name[30];
	int unit_Price; //����
};

struct medicine_list { //��¼ȫ��ҩƷ��Ϣ
	struct * medicine[30];
};

struct used_Medicine { //��ҩ
	struct medicine * use_m;
	int amount;
	struct used_Medicine * next;
};

struct time { //ʱ��
	int month;
	int day;
	int hour;
	int minute;
};

struct live_hospital {
	struct time in_time; //סԺ����
	struct time out_time; //Ԥ�Ƴ�Ժ����
	int predict_days; //Ԥ��סԺ����
	int pledge;//ʣ��Ѻ��
	int cost;//��֧��סԺ����
};
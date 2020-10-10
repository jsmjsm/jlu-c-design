#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controlPanel.h"
#include "basic_function.h"
#include "function.h"
#include "fileFunction.h"
#include "interaction.h"
#pragma warning(disable : 4996)

//定义记录record的链表
struct record_list rl = {NULL};
struct record_list *rlp = &rl;
//定义记录doctor的链表
struct doctor_list dl = {NULL};
struct doctor_list *dlp = &dl;
//定义记录record时需要用到的doctor链表，无用，只是用来凑成函数所需参数
struct doctor_list useless_dl = {NULL};
struct doctor_list *useless_dlp = &useless_dl;
//定义记录medicine的链表
struct medicine_list ml = {NULL};
struct medicine_list *mlp = &ml;

void mainControl() // 主界面
{

	int isEnterMenu = -1;
	int isExit = 0;

	// -1024 退出
	while (isExit != -1024)
	{
		int menuDecision = -1;
		fflush(stdin);

		isExit = spaceWelcome();
		printf("\n");

		if (isExit == -1024)
		{
			continue;
		}

		while (menuDecision != 0)
		{
			menuDecision = spaceMenu();
			printf("\n");

			if (menuDecision == 0)
			{
				break;
			}
			operateMenu(menuDecision);
		}

		fflush(stdin);
	}
	printf("再见!\n");
}

// 欢迎界面s
int spaceWelcome()
{
	char decision[1] = "";
	int isEnterMenu = 0;
	printf("-----------------------------\n");
	printf("    欢迎使用诊疗管理系统    \n");
	printf("作者：201818xx-xxx\n");
	printf("-----------------------------\n");
	printf("\n");

	printf("摁任意键进入功能菜单，输入 q 退出系统\n");

	scanf("%c", &decision[0]);

	switch (decision[0])
	{
	case 'q':
		/* code */
		return -1024;
		break;
	default:
		isEnterMenu = 1;
		printf("跳转到菜单中....\n");
		break;
	}
	return isEnterMenu;
}

// 菜单
int spaceMenu()
{
	int decision = -1;
	printf("-----------------------------\n");
	printf("           功能菜单 \n");
	printf("作者：201818xx-xxx\n");
	printf("-----------------------------\n");
	printf("\n");

	printf("请输入你想使用的功能序号\n");
	printf("\n");

	printf("> 1. 从文件导入诊疗记录\n");
	printf("> 2. 录入一条诊疗记录\n");
	printf("> 3. 修改一条诊疗记录\n");
	printf("> 4. 删除一条诊疗记录\n");
	printf("> 5. 打印一位医生的诊疗信息\n");
	printf("> 6. 打印患者的历史诊疗信息\n");
	printf("> 7. 统计医院目前营业额\n");
	printf("> 8. 生成当前住院 报表\n");
	printf("> 9. 统计医生出诊情况及繁忙程度\n");
	printf("> 10. 输出某时间段的诊疗信息\n");
	printf("> 11. 录入医生信息\n");
	printf("> 12. 录入药品信息\n");
	printf("> 13. 查看全部医生信息（姓名、级别、科室、工号）\n");
	printf("> 14. 查看全部药品信息（名称、单价）\n");
	printf("> 15. 保存系统信息文件\n");
	printf("> 0. 返回欢迎界面\n");

	scanf("%d", &decision);
	decision = (int)decision;
	while (decision < 0 || decision > 15)
	{
		printf("输入错误！请重试！\n");
		fflush(stdin); //清空缓冲区
		scanf("%d", &decision);
	}
	printf(">> debug: 决定:  %d\n", decision);
	return decision;
}

// 根据menu决定操作
int operateMenu(int menuDecision)
{
	char **record_array = (char **)malloc(10000 * sizeof(char *));
	for (int i = 0; i < 10000; i++)
	{
		record_array[i] = (char *)malloc(20 * sizeof(char));
	}
	for (int i = 0; i < 10000; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			record_array[i][j] = 0;
		}
	}
	char **doctor_array = (char **)malloc(10000 * sizeof(char *));
	for (int i = 0; i < 10000; i++)
	{
		doctor_array[i] = (char *)malloc(20 * sizeof(char));
	}
	for (int i = 0; i < 10000; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			doctor_array[i][j] = 0;
		}
	}
	char **medicine_array = (char **)malloc(10000 * sizeof(char *));
	for (int i = 0; i < 10000; i++)
	{
		medicine_array[i] = (char *)malloc(20 * sizeof(char));
	}
	for (int i = 0; i < 10000; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			medicine_array[i][j] = 0;
		}
	}
	int flag = 0;
	int posi = 0;

	switch (menuDecision)
	{
	case 0:
		fflush(stdin); // 清空缓冲区
		break;
	case 1:
		printf("1. 从文件导入诊疗记录\n");
		/*TODO: 接口接入*/

		//*************************record记录************************
		readin_record(record_array);
		flag = 1; //判断值
		posi = 0; //用于确定当前在数组的哪一行
		while (flag)
		{
			flag = 0;
			struct patient pa = create_patient(record_array[posi], atoi(record_array[posi + 1]), atoi(record_array[posi + 2])); //病人
			posi += 3;																											//数组行数+3

			int temp_visit[8] = {0}; //医生
			temp_visit[0] = atoi(record_array[posi + 4]);
			struct doctor *dop = create_doctor(record_array[posi], record_array[posi + 1], record_array[posi + 2], atoi(record_array[posi + 3]), temp_visit, useless_dlp);
			posi += 5; //数组行数+5

			int numOFbodycheck = atoi(record_array[posi]); //体检数量
			struct body_Check *bc_cur = NULL;			   //当前体检节点
			struct body_Check *bc_pre = NULL;			   //体检前驱节点
			struct body_Check *bc_head = NULL;			   //头结点
			for (int i = 0; i < numOFbodycheck; i++)	   //体检
			{
				if (i == 0) //创建体检链表头
				{
					bc_cur = create_check(bc_pre, record_array[posi + 1], atoi(record_array[posi + 2]));
					bc_head = bc_cur; //确定头结点
					posi += 3;
				}
				else //非表头
				{
					bc_pre = bc_cur;
					bc_cur = create_check(bc_pre, record_array[posi], atoi(record_array[posi + 1]));
					posi += 2;
				}
			}

			int numOFusemedicine = atoi(record_array[posi]); //用药数量
			struct used_Medicine *um_cur = NULL;			 //当前用药节点
			struct used_Medicine *um_pre = NULL;			 //用药前驱节点
			struct used_Medicine *um_head = NULL;			 //头结点
			for (int i = 0; i < numOFusemedicine; i++)		 //用药
			{
				if (i == 0) //创建用药链表头
				{
					struct medicine *m;
					m = (struct medicine *)malloc(sizeof(struct medicine)); //生成药品
					strcpy(m->name, record_array[posi + 1]);				//药品名称
					m->unit_Price = atoi(record_array[posi + 2]);
					m->next = NULL;
					um_cur = create_use_m(um_pre, m, atoi(record_array[posi + 3]));
					um_head = um_cur;
					posi += 4;
				}
				else //非表头
				{
					um_pre = um_cur;
					struct medicine *m;
					m = (struct medicine *)malloc(sizeof(struct medicine)); //生成药品
					strcpy(m->name, record_array[posi]);					//药品名称
					m->unit_Price = atoi(record_array[posi + 1]);
					m->next = NULL;
					um_cur = create_use_m(um_pre, m, atoi(record_array[posi + 2]));
					posi += 3;
				}
			}

			//住院信息
			struct live_hospital *lhp = create_live_hospital(atoi(record_array[posi]), atoi(record_array[posi + 1]), atoi(record_array[posi + 2]), atoi(record_array[posi + 3]),
															 atoi(record_array[posi + 4]), atoi(record_array[posi + 5]), atoi(record_array[posi + 6]), atoi(record_array[posi + 7]));
			posi += 8;
			//struct live_hospital* lhp = &lh;

			//生成treatment
			struct treatment tm;
			tm = create_treatment(bc_head, um_head, lhp);

			//生成record
			addOneRecord(rlp, pa, dop, tm);

			if (strlen(record_array[posi]) > 0) //判断是否当前record是否为最后一条
				flag = 1;
		}

		//******************doctor信息******************
		readin_doctor(doctor_array);
		flag = 1; //判断值
		posi = 0; //用于确定当前在数组的哪一行
		while (flag)
		{
			flag = 0;
			int temp_visit[8];
			for (int i = 0; i < 8; i++)
				temp_visit[i] = atoi(doctor_array[posi + i + 4]);
			create_doctor(doctor_array[posi], doctor_array[posi + 1], doctor_array[posi + 2], atoi(doctor_array[posi + 3]), temp_visit, dlp);
			posi += 12;

			if (strlen(doctor_array[posi]) > 0) //判断是否当前record是否为最后一条
				flag = 1;
		}

		//******************medicine_list信息******************
		readin_medicine(medicine_array);
		flag = 1; //判断值
		posi = 0; //用于确定当前在数组的哪一行
		while (flag)
		{
			flag = 0;
			add_to_medicine_list(mlp, medicine_array[posi], atoi(medicine_array[posi + 1]));
			posi += 2;

			if (strlen(medicine_array[posi]) > 0) //判断是否当前record是否为最后一条
				flag = 1;
		}

		break;
	case 2:
		printf("2. 录入一条诊疗记录\n");
		inter_add_one_record(rlp, mlp, dlp);
		break;
	case 3:
		printf("3. 修改一条诊疗记录\n");
		inter_modify_one_record(rlp, mlp, dlp);
		break;
	case 4:
		printf("4. 删除一条诊疗记录\n");
		inter_delete_one_record(rlp);
		break;
	case 5:
		printf("5. 打印一位医生的诊疗信息\n");
		inter_print_one_doctor(rlp, dl);
		break;
	case 6:
		printf("6. 打印患者的历史诊疗信息\n");
		print_all(rlp); //仅用于调试
		break;
	case 7:
		printf("7. 统计医院目前营业额\n");
		inter_calc_hospital_current_turnover(rlp);
		break;
	case 8:
		printf("8. 生成当前住院的报表\n");
		inter_create_live_in_hospital(rlp);
		break;
	case 9:
		printf("9. 统计医生出诊情况及繁忙程度\n");
		calcDoctorBusy(rlp, dl);
		break;
	case 10:
		printf("10. 输出某时间段的诊疗信息\n");
		inter_print_record_during_time(rlp);
		break;
	case 11:
		printf("11. 录入医生信息\n");
		inter_create_doctor(dlp);
		break;

	case 12:
		printf("12. 录入药品信息\n");
		inter_create_medicine(mlp);
		break;

	case 13:
		printf("> 13. 查看全部医生信息（姓名、级别、科室、工号）\n");
		show_doctor_list(dlp);
		break;

	case 14:
		printf("> 14. 查看全部药品信息（名称、单价）\n");
		show_medicine_list(mlp);
		break;

	case 15:
		printf("15. 保存系统信息文件\n");
		//***********************保存record***********************
		writeout_record(rlp->head);

		//***********************保存doctor***********************
		writeout_doctor(dl);

		//***********************保存medicine***********************
		writeout_medicine(ml);

		break;
	default:
		printf("debug:ERR: 传参错误\n");
		break;
	}
	return 0;
}

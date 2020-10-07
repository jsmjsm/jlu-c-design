#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controlPanel.h"
#include "basic_function.h"
#include "fileFunction.h"
#include "interaction.h"
#pragma warning (disable:4996)

//�����¼record������
struct record_list rl = { NULL };
struct record_list* rlp = &rl;
//�����¼doctor������
struct doctor_list dl = { NULL };
struct doctor_list* dlp = &dl;
//�����¼recordʱ��Ҫ�õ���doctor�������ã�ֻ�������ճɺ����������
struct doctor_list useless_dl = { NULL };
struct doctor_list* useless_dlp = &useless_dl;
//�����¼medicine������
struct medicine_list ml = { NULL };
struct medicine_list* mlp = &ml;

void mainControl() // ������
{
	// TODO��Init!

	/*��Ҫ����ʼ��*/

	/*��Ҫ�� ��¼װ��*/

	int isEnterMenu = -1;
	int isExit = 0;

	// -1024 �˳�
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
	printf("�ټ�!\n");
}

// ��ӭ����s
int spaceWelcome()
{
	char decision[1] = "";
	int isEnterMenu = 0;
	printf("-----------------------------\n");
	printf("    ��ӭʹ�����ƹ���ϵͳ    \n");
	printf("���ߣ�201818xx-xxx\n");
	printf("-----------------------------\n");
	printf("\n");

	printf("����������빦�ܲ˵������� q �˳�ϵͳ\n");

	scanf("%c", &decision[0]);

	switch (decision[0])
	{
	case 'q':
		/* code */
		return -1024;
		break;
	default:
		isEnterMenu = 1;
		printf("��ת���˵���....\n");
		break;
	}
	return isEnterMenu;
}

// �˵�
int spaceMenu()
{
	int decision = -1;
	printf("-----------------------------\n");
	printf("           ���ܲ˵� \n");
	printf("���ߣ�201818xx-xxx\n");
	printf("-----------------------------\n");
	printf("\n");

	printf("����������ʹ�õĹ������\n");
	printf("\n");

	printf("> 1. ���ļ��������Ƽ�¼\n");
	printf("> 2. ¼��һ�����Ƽ�¼\n");
	printf("> 3. �޸�һ�����Ƽ�¼\n");
	printf("> 4. ɾ��һ�����Ƽ�¼\n");
	printf("> 5. ��ӡһλҽ����������Ϣ\n");
	printf("> 6. ��ӡ���ߵ���ʷ������Ϣ\n");
	printf("> 7. ͳ��ҽԺĿǰӪҵ��\n");
	printf("> 8. ���ɵ�ǰסԺ ����\n");
	printf("> 9. ͳ��ҽ�������������æ�̶�\n");
	printf("> 10. ���ĳʱ��ε�������Ϣ\n");
	printf("> 11. ����ϵͳ��Ϣ�ļ�\n");
	printf("> 0. ���ػ�ӭ����\n");

	scanf("%d", &decision);
	decision = (int)decision;
	while (decision < 0 || decision > 11)
	{
		printf("������������ԣ�\n");
		fflush(stdin); //��ջ�����
		scanf("%d", &decision);
	}
	printf(">> debug: ����:  %d\n", decision);
	return decision;
}

// ����menu��������
int operateMenu(int menuDecision)
{
	char ** record_array = (char**)malloc(10000 * sizeof(char*));
	for (int i = 0; i < 10000; i++) {
		record_array[i] = (char*)malloc(20 * sizeof(char));
	}
	for (int i = 0; i < 10000; i++) {
		for (int j = 0; j < 20; j++) {
			record_array[i][j] = 0;
		}
	}
	char ** doctor_array = (char**)malloc(10000 * sizeof(char*));
	for (int i = 0; i < 10000; i++) {
		doctor_array[i] = (char*)malloc(20 * sizeof(char));
	}
	for (int i = 0; i < 10000; i++) {
		for (int j = 0; j < 20; j++) {
			doctor_array[i][j] = 0;
		}
	}
	char ** medicine_array = (char**)malloc(10000 * sizeof(char*));
	for (int i = 0; i < 10000; i++) {
		medicine_array[i] = (char*)malloc(20 * sizeof(char));
	}
	for (int i = 0; i < 10000; i++) {
		for (int j = 0; j < 20; j++) {
			medicine_array[i][j] = 0;
		}
	}
	int flag = 0;
	int posi = 0;

	switch (menuDecision)
	{
	case 0:
		fflush(stdin); // ��ջ�����
		break;
	case 1:
		printf("1. ���ļ��������Ƽ�¼\n");
		/*TODO: �ӿڽ���*/

		  //*************************record��¼************************
		readin_record(record_array);
		flag = 1;//�ж�ֵ
		posi = 0;//����ȷ����ǰ���������һ��
		while (flag) {
			flag = 0;
			struct patient pa = create_patient(record_array[posi], atoi(record_array[posi + 1]), atoi(record_array[posi + 2]));//����
			posi += 3;//��������+3

			int temp_visit[8] = { 0 };//ҽ��
			temp_visit[0] = atoi(record_array[posi + 4]);
			struct doctor* dop = create_doctor(record_array[posi], record_array[posi + 1], record_array[posi + 2], atoi(record_array[posi + 3]), temp_visit, useless_dlp);
			posi += 5;//��������+5

			int numOFbodycheck = atoi(record_array[posi]);//�������
			struct body_Check* bc_cur = NULL;//��ǰ���ڵ�
			struct body_Check* bc_pre = NULL;//���ǰ���ڵ�
			struct body_Check* bc_head = NULL;//ͷ���
			for (int i = 0; i < numOFbodycheck; i++)//���
			{
				if (i == 0)//�����������ͷ
				{
					bc_cur = create_check(bc_pre, record_array[posi + 1], atoi(record_array[posi + 2]));
					bc_head = bc_cur;//ȷ��ͷ���
					posi += 3;
				}
				else//�Ǳ�ͷ
				{
					bc_pre = bc_cur;
					bc_cur = create_check(bc_pre, record_array[posi], atoi(record_array[posi + 1]));
					posi += 2;
				}
			}

			int numOFusemedicine = atoi(record_array[posi]);//��ҩ����
			struct used_Medicine* um_cur = NULL;//��ǰ��ҩ�ڵ�
			struct used_Medicine* um_pre = NULL;//��ҩǰ���ڵ�
			struct used_Medicine* um_head = NULL;//ͷ���
			for (int i = 0; i < numOFusemedicine; i++)//��ҩ
			{
				if (i == 0)//������ҩ����ͷ
				{
					struct medicine* m;
					m = (struct medicine*)malloc(sizeof(struct medicine));//����ҩƷ
					strcpy(m->name, record_array[posi + 1]);//ҩƷ����
					m->unit_Price = atoi(record_array[posi + 2]);
					m->next = NULL;
					um_cur = create_use_m(um_pre, m, atoi(record_array[posi + 3]));
					um_head = um_cur;
					posi += 4;
				}
				else//�Ǳ�ͷ
				{
					um_pre = um_cur;
					struct medicine* m;
					m = (struct medicine*)malloc(sizeof(struct medicine));//����ҩƷ
					strcpy(m->name, record_array[posi]);//ҩƷ����
					m->unit_Price = atoi(record_array[posi + 1]);
					m->next = NULL;
					um_cur = create_use_m(um_pre, m, atoi(record_array[posi + 2]));
					posi += 3;
				}
			}

			//סԺ��Ϣ
			struct live_hospital lh = create_live_hospital(atoi(record_array[posi]), atoi(record_array[posi + 1]), atoi(record_array[posi + 2]), atoi(record_array[posi + 3]),
				atoi(record_array[posi + 4]), atoi(record_array[posi + 5]), atoi(record_array[posi + 6]), atoi(record_array[posi + 7]));
			posi += 8;
			struct live_hospital* lhp = &lh;

			//����treatment
			struct treatment tm;
			tm = create_treatment(bc_head, um_head, lhp);

			//����record
			addOneRecord(rlp, pa, dop, tm);

			if (strlen(record_array[posi]) > 0)//�ж��Ƿ�ǰrecord�Ƿ�Ϊ���һ��
				flag = 1;
		}

		//******************doctor��Ϣ******************
		readin_doctor(doctor_array);
		flag = 1;//�ж�ֵ
		posi = 0;//����ȷ����ǰ���������һ��
		while (flag) {
			flag = 0;
			int temp_visit[8];
			for (int i = 0; i < 8; i++)
				temp_visit[i] = atoi(doctor_array[posi + i + 4]);
			create_doctor(doctor_array[posi], doctor_array[posi + 1], doctor_array[posi + 2], atoi(doctor_array[posi + 3]), temp_visit, dlp);
			posi += 12;

			if (strlen(doctor_array[posi]) > 0)//�ж��Ƿ�ǰrecord�Ƿ�Ϊ���һ��
				flag = 1;
		}

		//******************medicine_list��Ϣ******************
		readin_medicine(medicine_array);
		flag = 1;//�ж�ֵ
		posi = 0;//����ȷ����ǰ���������һ��
		while (flag) {
			flag = 0;
			add_to_medicine_list(mlp, medicine_array[posi], atoi(medicine_array[posi + 1]));
			posi += 2;

			if (strlen(medicine_array[posi]) > 0)//�ж��Ƿ�ǰrecord�Ƿ�Ϊ���һ��
				flag = 1;
		}

		break;
	case 2:
		printf("2. ¼��һ�����Ƽ�¼\n");
		/*TODO: �ӿڽ���*/
		inter_add_one_record(rlp, mlp);
		break;
	case 3:
		printf("3. �޸�һ�����Ƽ�¼\n");
		/*TODO: �ӿڽ���*/

		break;
	case 4:
		printf("4. ɾ��һ�����Ƽ�¼\n");
		/*TODO: �ӿڽ���*/

		break;
	case 5:
		printf("5. ��ӡһλҽ����������Ϣ\n");
		/*TODO: �ӿڽ���*/
		break;
	case 6:
		printf("6. ��ӡ���ߵ���ʷ������Ϣ\n");
		searchByPatient(rlp, "С��", 20);
		break;
	case 7:
		printf("7. ͳ��ҽԺĿǰӪҵ��\n");
		/*TODO: �ӿڽ���*/

		break;
	case 8:
		printf("8. ���ɵ�ǰסԺ ����\n");
		/*TODO: �ӿڽ���*/

		break;
	case 9:
		printf("9. ͳ��ҽ�������������æ�̶�\n");
		/*TODO: �ӿڽ���*/

		break;
	case 10:
		printf("10. ���ĳʱ��ε�������Ϣ\n");
		/*TODO: �ӿڽ���*/

		break;
	case 11:
		printf("11. ����ϵͳ��Ϣ�ļ�\n");
		/*TODO: �ӿڽ���*/


		//***********************����record***********************
		writeout_record(rlp->head);

		//***********************����doctor***********************
		writeout_doctor(dl);

		//***********************����medicine***********************
		writeout_medicine(ml);

		break;
	default:
		printf("debug:ERR: ���δ���\n");
		break;
	}
	return 0;
}
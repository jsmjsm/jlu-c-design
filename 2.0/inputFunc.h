#ifndef INPUTFUNC_H
#define INPUTFUNC_H

// ���ݱ�������ַ������뽻��
char *inputCharWithTitle(const char *title);

// ��������
int inputAge();

// ����ID with title
int inputID(const char *title);

// ҽ���ϰ�����
int *inputWork();

// ������
int inputPrice(int isPrint);

// ��������
int inputAmount();

// ����Int
// TODO����Ҫ���������쳣���
//int inputInt(const char *title);

// 01 �ж��Ƿ��������
int isNextInput(const char *title);

// ��Ǯ��������double������Ԫ�Ƿ֣������ܷ֣� isPrint ����1 �����ӡԪ�Ƿ�
int money_double_yjf(double money, int isPrint);

#endif
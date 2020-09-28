#ifndef INPUTFUNC_H
#define INPUTFUNC_H

// 根据标题完成字符串输入交互
char *inputCharWithTitle(char *title);

// 输入年龄
int inputAge();

// 输入ID with title
int inputID(char *title);

// 医生上班数组
int *inputWork();

// 输入金额
int inputPrice(int isPrint);

// 输入数量
int inputAmount();

// 输入Int
// TODO：需要用它来做异常检查
int inputInt(char *title);

// 01 判断是否继续输入
int isNextInput(char *title);

// 金钱处理：输入double金额，计算元角分，返回总分， isPrint 传入1 代表打印元角分
int money_double_yjf(double money, int isPrint);

#endif

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
int inputPrice();

// 输入数量
int inputAmount();

// 输入Int
// TODO：需要用它来做异常检查
int inputInt(char *title);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inputFunc.h"

// 根据标题完成字符串输入交互
char *inputCharWithTitle(char *title)
{
    static char str[20];
    char temp[20];
    printf("请输入 %s 的内容\n", title);
    scanf("%s", temp);
    fflush(stdin);
    strcpy(str, temp);
    printf("项目: %s 的内容是 %s\n", title, str);
    return str;
}

// 输入年龄
int inputAge()
{
    int age = 0;
    printf("请输入年龄\n");
    scanf("%d", &age);
    fflush(stdin);
    // 年龄检查
    while (age < 1 || age > 150)
    {
        printf("输入有误，请重试\n");
        scanf("%d", &age);
        fflush(stdin);
    }
    printf("年龄: %d\n", age);
    return age;
}

// 输入ID
int inputID(char *title)
{
    int id = 0;
    printf("请输入 %s\n", title);
    scanf("%d", &id);
    fflush(stdin);
    printf("输入成功 %s: %d\n", title, id);
    return id;
}

// 医生上班
int *inputWork()
{
    static int work[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int totalDays = 0;
    // 设置总天数
    printf("请输入该医生一周上班总天数:\n");
    scanf("%d", &totalDays);
    work[0] = totalDays;
    fflush(stdin);
    // 哪一天上班
    for (int i = 1; i <= totalDays; i++)
    {
        int tempWork = 0;
        // 周几上班
        printf("医生在一周中第 %d 天上班是周几？ (1-7)\n", i);
        scanf("%d", &tempWork);

        // 检查异常
        fflush(stdin);
        while (tempWork >= 8 || tempWork < 1 || work[tempWork] == 1)
        {
            printf("输入有误，请重试\n");
            scanf("%d", &tempWork);
            fflush(stdin);
        }
        // 标记上班
        work[tempWork] = 1;
    }

    // debug： 输出上班数组
    // printf("work DEBUG: ");
    // for (int i = 0; i <= 7; i++)
    // {
    //     printf("[%d]", work[i]);
    // }

    return work;
}

// 输入价钱
int inputPrice()
{
    int price = 0;
    printf("请输入金额\n");
    scanf("%d", &price);
    fflush(stdin);
    printf("输入成功，金额: %d\n", price);
    return price;
}

// 输入数量
int inputAmount()
{
    int amount = 0;
    printf("请输入数量\n");
    scanf("%d", &amount);
    fflush(stdin);
    printf("输入成功，数量: %d\n", amount);
    return amount;
}

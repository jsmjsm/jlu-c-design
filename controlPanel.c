#include <stdio.h>
#include <unistd.h>
#include "controlPanel.h"

void mainControl() // 主界面
{
    // TODO；Init!

    /*需要：初始化*/

    /*需要： 记录装载*/

    int isEnterMenu = -1;
    int isExit = 0;

    // -1024 退出
    while (isExit != -1024)
    {
        int menuDecision = -1;
        fflush(stdin);

        isExit = spaceWelcome();
        printf("\n");
        sleep(1);

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
    printf("> 11. 保存系统信息文件\n");
    printf("> 0. 返回欢迎界面\n");

    scanf("%d", &decision);
    decision = (int)decision;
    while (decision < 0 || decision > 11)
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
    switch (menuDecision)
    {
    case 0:
        fflush(stdin); // 清空缓冲区
        break;
    case 1:
        printf("1. 从文件导入诊疗记录\n");
        /*TODO: 接口接入*/
        break;
    case 2:
        printf("2. 录入一条诊疗记录\n");
        /*TODO: 接口接入*/

        break;
    case 3:
        printf("3. 修改一条诊疗记录\n");
        /*TODO: 接口接入*/

        break;
    case 4:
        printf("4. 删除一条诊疗记录\n");
        /*TODO: 接口接入*/

        break;
    case 5:
        printf("5. 打印一位医生的诊疗信息\n");
        /*TODO: 接口接入*/

        break;
    case 6:
        printf("6. 打印患者的历史诊疗信息\n");

        break;
    case 7:
        printf("7. 统计医院目前营业额\n");
        /*TODO: 接口接入*/

        break;
    case 8:
        printf("8. 生成当前住院 报表\n");
        /*TODO: 接口接入*/

        break;
    case 9:
        printf("9. 统计医生出诊情况及繁忙程度\n");
        /*TODO: 接口接入*/

        break;
    case 10:
        printf("10. 输出某时间段的诊疗信息\n");
        /*TODO: 接口接入*/

        break;
    case 11:
        printf("11. 保存系统信息文件\n");
        /*TODO: 接口接入*/

        break;
    default:
        printf("debug:ERR: 传参错误\n");
        break;
    }
    return 0;
}

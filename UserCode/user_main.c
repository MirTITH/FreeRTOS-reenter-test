#include "user_main.h"
#include <stdio.h>
#include <stdlib.h>

void ThreadEntry(void const *argument)
{
    float delta = *(float*)argument;
    float num = 0;
    char str_buff[25];
    for (;;)
    {
        sprintf(str_buff, "%f", num);
        sprintf(str_buff, "num = %lf\n", atof(str_buff));
        num += delta;
        osDelay(1);
    }
}

void StartDefaultTask(void const *argument)
{
    // 如果没有在 FreeRTOSConfig.h 中 #define configUSE_NEWLIB_REENTRANT 1，几乎必进 HardFault_Handler
    // 因为 malloc 等函数默认不可重入，不是线程安全的，而 sprintf, printf 等会调用这些函数
    // 开启那个宏定义后就可以使它们线程安全

    float delta[8] = {0.1, 0.2, -0.1, -0.2, 1.5, -1, 0.5, -0.5};

    osThreadDef(Normal1, ThreadEntry, osPriorityNormal, 0, 128);
    osThreadCreate(osThread(Normal1), &delta[0]);
    osThreadDef(Normal2, ThreadEntry, osPriorityNormal, 0, 128);
    osThreadCreate(osThread(Normal2), &delta[1]);
    osThreadDef(Normal3, ThreadEntry, osPriorityNormal, 0, 128);
    osThreadCreate(osThread(Normal3), &delta[2]);
    osThreadDef(Normal4, ThreadEntry, osPriorityNormal, 0, 128);
    osThreadCreate(osThread(Normal4), &delta[3]);

    osThreadDef(ANormal1, ThreadEntry, osPriorityAboveNormal, 0, 128);
    osThreadCreate(osThread(ANormal1), &delta[4]);
    osThreadDef(ANormal2, ThreadEntry, osPriorityAboveNormal, 0, 128);
    osThreadCreate(osThread(ANormal2), &delta[5]);
    osThreadDef(ANormal3, ThreadEntry, osPriorityAboveNormal, 0, 128);
    osThreadCreate(osThread(ANormal3), &delta[6]);
    osThreadDef(ANormal4, ThreadEntry, osPriorityAboveNormal, 0, 128);
    osThreadCreate(osThread(ANormal4), &delta[7]);
    
    for (;;)
    {
        osDelay(1);
    }
}

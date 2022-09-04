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

    osThreadDef(Normal1, ThreadEntry, osPriorityNormal, 0, 128);
    osThreadCreate(osThread(Normal1), NULL);
    osThreadDef(Normal2, ThreadEntry, osPriorityNormal, 0, 128);
    osThreadCreate(osThread(Normal2), NULL);
    osThreadDef(Normal3, ThreadEntry, osPriorityNormal, 0, 128);
    osThreadCreate(osThread(Normal3), NULL);
    osThreadDef(Normal4, ThreadEntry, osPriorityNormal, 0, 128);
    osThreadCreate(osThread(Normal4), NULL);

    osThreadDef(ANormal1, ThreadEntry, osPriorityAboveNormal, 0, 128);
    osThreadCreate(osThread(ANormal1), NULL);
    osThreadDef(ANormal2, ThreadEntry, osPriorityAboveNormal, 0, 128);
    osThreadCreate(osThread(ANormal2), NULL);
    osThreadDef(ANormal3, ThreadEntry, osPriorityAboveNormal, 0, 128);
    osThreadCreate(osThread(ANormal3), NULL);
    osThreadDef(ANormal4, ThreadEntry, osPriorityAboveNormal, 0, 128);
    osThreadCreate(osThread(ANormal4), NULL);
    
    for (;;)
    {
        osDelay(1);
    }
}

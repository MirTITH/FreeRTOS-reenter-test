# FreeRTOS 可重入测试

使用 FreeRTOS 时，一定要开启 `#define configUSE_NEWLIB_REENTRANT 1`

否则如果使用 mallo, printf 等函数，有概率进入 HardFault_Handler

除非你永远不使用这些函数

本工程实现了与此有关的测试，在开启 `configUSE_NEWLIB_REENTRANT` 后程序才能正常运行。

具体可见 [user_main.c](UserCode/user_main.c)
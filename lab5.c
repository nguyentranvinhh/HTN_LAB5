#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

#define TIMER0_ID  0
#define TIMER1_ID 100

TimerHandle_t xTimer0, xTimer1;

const uint32_t timePrint0 = 10;
const uint32_t timePrint1 =  5;

uint32_t count0, count1;

void vTimerCallback(TimerHandle_t xTimer) {
    uint32_t xTimerID;
    xTimerID  = (uint32_t)pvTimerGetTimerID(xTimer);
    if (xTimerID == TIMER0_ID) {
        count0++;
        if (count0 >= timePrint0) {
            xTimerStop(xTimer, 0);
        }

        printf("%ds: ahihi\n", pdTICKS_TO_MS(xTaskGetTickCount())/1000);
    } else if (xTimerID == TIMER1_ID) {
        count1++;
        if (count1 >= timePrint1) {
            xTimerStop(xTimer, 0);
        }

        printf("%ds: ihaha\n", pdTICKS_TO_MS(xTaskGetTickCount())/1000);
    }
}


void app_main(void)
{
    xTimer0 = xTimerCreate("Timer0", pdMS_TO_TICKS(2000), pdTRUE, (void *)TIMER0_ID, vTimerCallback);
    xTimer1 = xTimerCreate("Timer1", pdMS_TO_TICKS(3000), pdTRUE, (void *)TIMER1_ID, vTimerCallback);
    xTimerStart(xTimer0, 0);
    xTimerStart(xTimer1, 0);

}
#include "irq_handler.h"
#include "stm32f446xx.h"
#include "tim.h"

// This function is called by HAL when the timer period elapses
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6) {
        // Handle timer 6 interrupt
    }

    /* Timer 3 timeout*/
    else if (htim->Instance == TIM3) {
        /* Check if current state is SLEEP*/
        if(GetCurrentState() == SLEEP) {
            while (sleep_wakeup_count < sleep_wakeup_limit) {
                sleep_wakeup_count++;
                printf("Sleep wakeup count: %lu\n", sleep_wakeup_count);
            }
            sleep_wakeup_count = 0; // Reset the wakeup count after reaching the limit
            HAL_TIM_Base_Stop_IT(htim);
            HandleEvent(SLEEP_TIMEOUT_EVENT);
        }
    }
}

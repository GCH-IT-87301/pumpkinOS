/*
 * status_led.c
 *
 *  Created on: Oct 25, 2026
 *      Author: crvhoover
 */

#include "status_led.h"
#include "main.h"

void Heartbeat_Update(void)
{
    static uint32_t lastHeartbeat = 0;

    if (HAL_GetTick() - lastHeartbeat >= 1000)
    {
        lastHeartbeat = HAL_GetTick();

        HAL_GPIO_TogglePin(
            STATUS_LED_GPIO_Port,
            STATUS_LED_Pin
        );
    }
}

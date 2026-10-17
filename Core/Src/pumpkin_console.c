/*
 * pumpkin_console.c
 *
 *  Created on: Oct 17, 2026
 *      Author: crvhoover
 */

#include "pumpkin_console.h"
#include "st7796.h"

static uint16_t cursorX = 5;
static uint16_t cursorY = 5;

void PumpkinConsole_Clear(void)
{
	ST7796_FillScreen(ST7796_BLACK);

	cursorX = 5;
    cursorY = 5;
}

void PumpkinConsole_Print(const char *text)
{
    while(*text)
    {
        if(*text == '\n')
        {
            cursorX = 5;
            cursorY += 10;

            text++;
            continue;
        }

        ST7796_DrawChar(
            cursorX,
            cursorY,
            *text,
            ST7796_GREEN,
            1);

        cursorX += 6;

        if(cursorX > 470)
        {
            cursorX = 5;
            cursorY += 10;
        }

        text++;
    }
}

void PumpkinConsole_Print_Large(const char *text)
{
    while(*text)
    {
        if(*text == '\n')
        {
            cursorX = 5;
            cursorY += 10;

            text++;
            continue;
        }

        ST7796_DrawChar(
            cursorX,
            cursorY,
            *text,
            ST7796_GREEN,
            2);

        cursorX += 6;

        if(cursorX > 470)
        {
            cursorX = 5;
            cursorY += 10;
        }

        text++;
    }
}


void PumpkinConsole_Prompt(void)
{
    PumpkinConsole_Print(
        "root@pumpkin:~# ");
}

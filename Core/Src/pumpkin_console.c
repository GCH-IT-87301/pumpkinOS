/*
 * pumpkin_console.c
 *
 *  Created on: Oct 17, 2026
 *      Author: crvhoover
 */

#include "pumpkin_os.h"
#include "pumpkin_console.h"
#include "main.h"
#include "ascii_art.h"
#include "st7796.h"
#include <stdlib.h>

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


void PumpkinConsole_Prompt(void)
{
    PumpkinConsole_Print(
        "root@pumpkin:~# ");
}

void ShortDelay(void)
{
	HAL_Delay(500 + (rand() % 1000));
}

void LongDelay(void)
{
	HAL_Delay(2000 + (rand() % 1000));
}

void MicroDelay(void)
{
	HAL_Delay(15 + (rand() % 35));
}

static void PumpkinConsole_PutChar(char character)
{
    /*
     * Handle an explicit newline character.
     */
    if (character == '\n')
    {
        cursorX = 0;
        cursorY += 10;
        return;
    }

    /*
     * Wrap before drawing if the next character
     * would extend beyond the display.
     */
    if (cursorX + 5 > 470)
    {
        cursorX = 0;
        cursorY += 10;
    }

    ST7796_DrawChar(
        cursorX,
        cursorY,
        character,
        ST7796_GREEN,
        1);

    /*
     * Glyph width is 5 pixels, followed by
     * one pixel of character spacing.
     */
    cursorX += 6;
}

void TypeText(const char *text)
{
    while (*text != '\0')
    {
        PumpkinConsole_PutChar(*text);

        /*
         * Random delay from 20 through 69 milliseconds.
         */
        HAL_Delay(20 + (rand() % 50));

        text++;
    }

    /*
     * Move to the beginning of the next console line
     * when the complete string has been typed.
     */
    cursorX = 5;
    cursorY += 10;
}

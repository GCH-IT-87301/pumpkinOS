/*
 * pumpkin_os.c
 *
 *  Created on: Oct 17, 2026
 *      Author: crvhoover
 */


#include "pumpkin_os.h"
#include "pumpkin_console.h"

void DisplayText(const char *text)
{
    PumpkinConsole_Print(text);
    PumpkinConsole_Print("\n");
}

void PromptText(void)
{
    PumpkinConsole_Prompt();
}

void Separator(void)
{
    PumpkinConsole_Print("\n");
}

void PumpkinOS_Start(void)
{
    PumpkinConsole_Clear();

    DisplayText("PumpkinOS 6.66");
    Separator();

    DisplayText("[ OK ] Candy Filesystem");
    DisplayText("[ OK ] Ghost Service");    DisplayText("[ OK ] Skeleton Daemon");
    DisplayText("[FAIL] Printer Service");

    Separator();
    DisplayText("Reason:");
    DisplayText("Yellow toner empty");

    Separator();
    PromptText();
}


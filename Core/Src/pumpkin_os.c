/*
 * pumpkin_os.c
 *
 *  Created on: Oct 17, 2026
 *      Author: crvhoover
 */


#include "pumpkin_os.h"
#include "pumpkin_console.h"
#include "main.h"
#include "ascii_art.h"

void ShowBootScreen(void);
void ShowGhostScreen(void);
void ShowPrinterScreen(void);
void ShowTicketScreen(void);

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
	ShowBootScreen();
}

void ShowBootScreen(void)
{
    PumpkinConsole_Clear();

    Separator();
    Separator();
    Separator();

    DisplayText("Booting PumpkinOS 6.66...");
    HAL_Delay(1000);

    Separator();

    DisplayText("[ OK ] Candy Filesystem");
    HAL_Delay(500);

    DisplayText("[ OK ] Ghost Service");
    HAL_Delay(500);

    DisplayText("[ OK ] Skeleton Daemon");
    HAL_Delay(500);

    DisplayText("[FAIL] Printer Service");
    HAL_Delay(1000);

    Separator();

    DisplayText("Reason:");
    DisplayText("Yellow toner empty");

    HAL_Delay(500);

    DisplayText("Attempting bypass...");
    HAL_Delay(1000);

    DisplayText("Attempting bypass...FAILED");
    HAL_Delay(500);

    DisplayText("Attempting grayscale mode...");
    HAL_Delay(1000);

    DisplayText("Attempting grayscale mode...FAILED");
    HAL_Delay(500);

    DisplayText(
        "KERNEL PANIC: Color dependency "
        "violation; forcing system reboot");

    HAL_Delay(3000);

    Separator();
    Separator();
    Separator();

    DisplayText("NEED TO CODE IN THE REPEAT BOOTS HERE");

    //repeat sequences

    HAL_Delay(3000);

    ShowGhostScreen();
}


void ShowGhostScreen(void)
{
    PumpkinConsole_Clear();
    DisplayText(ghostASCII);
    HAL_Delay(3000);

    PumpkinConsole_Clear();
    PumpkinConsole_Print_Large(batASCII);
    HAL_Delay(3000);

    PumpkinConsole_Clear();
    PumpkinConsole_Print_Large(catASCII);
    HAL_Delay(3000);

    PumpkinConsole_Clear();
    DisplayText(pumpkinASCII);
    HAL_Delay(3000);

    PumpkinConsole_Clear();
    DisplayText(witchASCII);
    HAL_Delay(3000);

    PumpkinConsole_Clear();
    DisplayText(skeletonASCII);
    HAL_Delay(3000);

    PumpkinConsole_Clear();
    DisplayText(pumpkinOSASCII);
    HAL_Delay(3000);

    ShowPrinterScreen();
}

void ShowPrinterScreen(void)
{
	PumpkinConsole_Clear();
	DisplayText("PRINTER SCENE");
	HAL_Delay(5000);

	ShowTicketScreen();
}

void ShowTicketScreen(void)
{
	PumpkinConsole_Clear();
	DisplayText("TICKET SCREEN");
	HAL_Delay(5000);

	ShowBootScreen();
}

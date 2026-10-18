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
#include "st7796.h"

void ShowBIOSScreen(void);
void ShowBootScreen(void);
void ShowGhostScreen(void);
void ShowPrinterScreen(void);
void ShowTicketScreen(void);
void ShowJokeScreen(void);

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
	//FOR DEBUG TESTING PUT DESIRED START SCREEN HERE
	ShowPrinterScreen();
}

void ShowBIOSScreen(void)
{
	  /* create the pumpkin */

	  /* Pumpkin body */
	  ST7796_FillRectangle(
	      140,
	      50,
	      200,
	      140,
	      ST7796_ORANGE);

	  /* Stem */
	  ST7796_FillRectangle(
	      220,
	      20,
	      40,
	      40,
	      ST7796_GREEN);

	  /* Left eye */
	  ST7796_FillRectangle(
	      180,
	      85,
	      25,
	      25,
	      ST7796_BLACK);

	  /* Right eye */
	  ST7796_FillRectangle(
	      275,
	      85,
	      25,
	      25,
	      ST7796_BLACK);

	  /* Nose */
	  ST7796_FillRectangle(
	      230,
	      120,
	      20,
	      20,
	      ST7796_BLACK);

	  /* Mouth left */
	  ST7796_FillRectangle(
	      180,
	      155,
	      45,
	      15,
	      ST7796_BLACK);

	  /* Mouth center */
	  ST7796_FillRectangle(
	      225,
	      170,
	      30,
	      15,
	      ST7796_BLACK);

	  /* Mouth right */
	  ST7796_FillRectangle(
	      255,
	      155,
	      45,
	      15,
	      ST7796_BLACK);

	  ST7796_DrawHelloPumpkin();

	  HAL_Delay(3000);

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
	PromptText();
	LongDelay();
    DisplayText("cat ghostASCII");
    ShortDelay();
    DisplayText("\n");
    DisplayText(ghostASCII);
    Separator();
    ShortDelay();
    PromptText();
    LongDelay();
    DisplayText("clear");
    PumpkinConsole_Clear();

	PromptText();
	LongDelay();
    DisplayText("cat pumpkinASCII");
    ShortDelay();
    DisplayText("\n");
    DisplayText(pumpkinASCII);
    Separator();
    ShortDelay();
    PromptText();
    LongDelay();
    DisplayText("clear");
    PumpkinConsole_Clear();

	PromptText();
	LongDelay();
    DisplayText("cat batASCII");
    ShortDelay();
    DisplayText("\n");
    DisplayText(batASCII);
    Separator();
    ShortDelay();
    PromptText();
    LongDelay();
    DisplayText("clear");
    PumpkinConsole_Clear();

	PromptText();
	LongDelay();
    DisplayText("cat witchASCII");
    ShortDelay();
    DisplayText("\n");
    DisplayText(witchASCII);
    Separator();
    ShortDelay();
    PromptText();
    LongDelay();
    DisplayText("clear");
    PumpkinConsole_Clear();

	PromptText();
	LongDelay();
    DisplayText("cat skeletonASCII");
    ShortDelay();
    DisplayText("\n");
    DisplayText(skeletonASCII);
    Separator();
    ShortDelay();
    PromptText();
    LongDelay();
    DisplayText("clear");
    PumpkinConsole_Clear();

	PromptText();
	LongDelay();
    DisplayText("echo 'Happy Halloween!'");
    ShortDelay();
    DisplayText("\n");
    DisplayText(pumpkinOSASCII);
    Separator();
    ShortDelay();
    PromptText();
    LongDelay();
    DisplayText("clear");
    PumpkinConsole_Clear();

    ShowPrinterScreen();
}

void ShowPrinterScreen(void)
{

	// yellow toner joke
	PumpkinConsole_Clear();
	DisplayText("PumpkinOS 6.66 Recovery Console v0.1");
	Separator();

	//ifconfig joke
	PromptText();
	LongDelay();
	TypeText("ifconfig");
	ShortDelay();
	DisplayText("eth0        UP");
	DisplayText("            IP: 10.0.0.666");
	Separator();
	DisplayText("printer0    FAIL");
	DisplayText("            IP: invalid driver");

	//test-netconnection joke
	PromptText();
	LongDelay();
	TypeText("test-NetConnection printer0.local -p 8080");
	ShortDelay();
	DisplayText("bash: test-NetConnection:");
	ShortDelay();
	DisplayText("command not found");
	LongDelay();

	//printer ping joke
	PromptText();
	LongDelay();
	TypeText("ping printer0.local");
	LongDelay();
	DisplayText("PING printer0 (10.0.0.667)");
	Separator();
	LongDelay();
	DisplayText("Destination unreachable:");
	ShortDelay();
	DisplayText("Yellow toner empty");
	LongDelay();

	//printer status joke
	PromptText();
	LongDelay();
	TypeText("systemctl status printer");
	LongDelay();
	DisplayText("printer.service");
	Separator();
	LongDelay();
	DisplayText("Driver daemon: PASS");
	LongDelay();
	DisplayText("Service Active: FAIL");
	Separator();
	LongDelay();
	DisplayText("Reason:");
	LongDelay();
	DisplayText("Please replace yellow toner");
	LongDelay();
	PromptText();
	LongDelay();
	TypeText("sudo systemctl restart printer");
	LongDelay();
	DisplayText("Restarting printer service...");
	LongDelay();
	DisplayText("Restart successful");
	LongDelay();
	DisplayText("printer.service FAILED");
	ShortDelay();
	DisplayText("This problem survived reboot.");
	LongDelay();

	//just clear the goddamn screen and ask for help
	PromptText();
	LongDelay();
	TypeText("clear");
	ShortDelay();
	PumpkinConsole_Clear();
	ShortDelay();
	PromptText(); LongDelay(); DisplayText(""); ShortDelay();
	PromptText(); DisplayText(""); ShortDelay();
	PromptText(); DisplayText(""); ShortDelay();
	PromptText();
	LongDelay();
	TypeText("printers-suck --help");
	ShortDelay();
	DisplayText("bash: printers-suck:");
	ShortDelay();
	DisplayText("command found but there's nothing you can do about it");
	ShortDelay();
	PromptText();

	HAL_Delay(3000);

	ShowPrinterScreen();
}

void ShowTicketScreen(void)
{
	PumpkinConsole_Clear();
	DisplayText("TICKET SCREEN");
	HAL_Delay(5000);

	ShowTicketScreen();
}

void ShowJokeScreen(void)
{
	PumpkinConsole_Clear();
	DisplayText("JOKE SCREEN");
	HAL_Delay(5000);

	ShowJokeScreen();
}

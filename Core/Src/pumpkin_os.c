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
	ShowJokeScreen();
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

    ShowTicketScreen();
}

void ShowTicketScreen(void)
{
	PumpkinConsole_Clear();

    // Open Desk365 CLI
    PromptText();
    TypeText("desk365 tickets --status unresolved");
    ShortDelay();
    DisplayText("Connecting to GCH Help Desk...");
    ShortDelay();
    DisplayText("Authenticating root@pumpkin...");
    ShortDelay();
    DisplayText("[ OK ] Authentication successful");
    LongDelay();

    DisplayText("Loading unresolved tickets...");
    LongDelay();
    DisplayText("13 tickets found");
    LongDelay();

    Separator();

    // Ticket 1379: Printer for billing
    DisplayText("#1379  PRINTER FOR BILLING");
    DisplayText("Priority: HIGH");
    DisplayText("Status:  ESCALATED");
    ShortDelay();

    DisplayText("");
    DisplayText("Issue:");
    DisplayText("Printer says Replace Yellow Toner");
    ShortDelay();

    DisplayText("Work performed:");
    DisplayText("[ OK ] Replaced yellow toner");
    DisplayText("[ OK ] Restarted printer");
    DisplayText("[ OK ] Reinstalled driver");
    DisplayText("[ OK ] Performed ritual cleansing");
    ShortDelay();

    DisplayText("Result:");
    DisplayText("[FAIL] Replace Yellow Toner");
    ShortDelay();

    DisplayText("Assigned to:");
    DisplayText("Sinners");
    LongDelay();

    Separator();
    LongDelay();

    // Ticket 1343: New hire setup
    DisplayText("#1343  NEW HIRE SETUP");
    DisplayText("Priority: NORMAL");
    DisplayText("Status:  IN PROGRESS");
    ShortDelay();

    DisplayText("");
    DisplayText("Checklist:");
    DisplayText("[ OK ] Create user account");
    DisplayText("[ OK ] Assign Microsoft 365 license");
    DisplayText("[ OK ] Configure MFA");
    DisplayText("[ OK ] Prepare workstation");
    DisplayText("[FAIL] User has not started yet");
    ShortDelay();

    DisplayText("Waiting on:");
    DisplayText("The linear passage of time");
    LongDelay();

    Separator();
    LongDelay();

    // SPF and DNS joke
    DisplayText("#24259  EMAIL SPF CONFIGURATION");
    DisplayText("Priority: MEDIUM");
    DisplayText("Status:  RESOLVED");
    ShortDelay();

    DisplayText("");
    DisplayText("Original suspected cause:");
    DisplayText("DNS");
    ShortDelay();

    DisplayText("Actual cause:");
    DisplayText("DNS");
    ShortDelay();

    DisplayText("Final root cause:");
    DisplayText("It was DNS");
    LongDelay();

    Separator();
    LongDelay();

    // Keyboard in drawer
    DisplayText("#0031  KEYBOARD NOT WORKING");
    DisplayText("Priority: URGENT");
    DisplayText("Status:  CLOSED");
    ShortDelay();

    DisplayText("");
    DisplayText("Issue:");
    DisplayText("User has no keyboard");
    ShortDelay();

    DisplayText("Resolution:");
    DisplayText("Keyboard discovered in desk drawer");
    ShortDelay();

    DisplayText("Root cause:");
    DisplayText("Desk drawer was closed");
    LongDelay();

    Separator();
	LongDelay();

    // Haunted workstation
    DisplayText("#0666  WORKSTATION TURNS ON AT 3:00 AM");
    DisplayText("Priority: CRITICAL");
    DisplayText("Status:  ESCALATED");
    ShortDelay();

    DisplayText("");
    DisplayText("Troubleshooting:");
    DisplayText("[ OK ] Disabled Wake-on-LAN");
    DisplayText("[ OK ] Disabled scheduled tasks");
    DisplayText("[ OK ] Unplugged workstation");
    ShortDelay();

    DisplayText("Result:");
    DisplayText("Workstation still turns itself on");
    ShortDelay();

    DisplayText("Assigned service:");
    DisplayText("ghostd.service");
    LongDelay();

    Separator();
    LongDelay();

    // Password reset
    DisplayText("#1024  PASSWORD RESET");
    DisplayText("Priority: HIGH");
    DisplayText("Status:  CLOSED");
    ShortDelay();

    DisplayText("");
    DisplayText("User statement:");
    DisplayText("\"I never changed my password.\"");
    ShortDelay();

    DisplayText("Audit log:");
    DisplayText("Password changed 17 times today");
    ShortDelay();

    DisplayText("Resolution:");
    DisplayText("Password changed again");
    LongDelay();

    Separator();
    LongDelay();

    // Missing monitor
    DisplayText("#0404  MISSING MONITOR");
    DisplayText("Priority: NORMAL");
    DisplayText("Status:  OPEN");
    ShortDelay();

    DisplayText("");
    DisplayText("Description:");
    DisplayText("Monitor not found");
    ShortDelay();

    DisplayText("Troubleshooting:");
    DisplayText("Asked user to turn monitor on");
    ShortDelay();

    DisplayText("Response:");
    DisplayText("\"Which one is the monitor?\"");
    ShortDelay();

    DisplayText("Technician notes:");
    DisplayText("Monitor located in drawer next to missing keyboard");
    LongDelay();

    Separator();
    LongDelay();

    // Coffee machine
    DisplayText("#0500  COFFEE MACHINE OFFLINE");
    DisplayText("Priority: CATASTROPHIC");
    DisplayText("Status:  ALL HANDS");
    ShortDelay();

    DisplayText("");
    DisplayText("Ping result:");
    DisplayText("Destination host unreachable");
    ShortDelay();

    DisplayText("Business impact:");
    DisplayText("Entire IT department");
    ShortDelay();

    DisplayText("Temporary workaround:");
    DisplayText("Nobody speak to IT before 09:00");
    LongDelay();

    Separator();
    LongDelay();
    DisplayText("End of ticket status command.");
	Separator();

    PromptText();

    LongDelay();

	ShowJokeScreen();
}

void ShowJokeScreen(void)
{
	PumpkinConsole_Clear();

    DisplayText("PumpkinOS Joke Module v1.666 - Halloween Edition");
    DisplayText("Loading dad-joke database...");
    LongDelay();

    DisplayText("[ OK ] Skeleton jokes");
    ShortDelay();
    DisplayText("[ OK ] Ghost jokes");
    ShortDelay();
    DisplayText("[ OK ] Vampire jokes");
    ShortDelay();
    DisplayText("[ OK ] Eye roll module");
    LongDelay();

    Separator();

    PromptText(); LongDelay();
    TypeText("echo Why don't skeletons fight each other?");
    LongDelay();
    DisplayText("Because they don't have the guts.");
    LongDelay();

    Separator();

    PromptText(); LongDelay();
    TypeText("echo What room does a ghost avoid?");
    LongDelay();
    DisplayText("The living room.");
    LongDelay();

    Separator();

    PromptText(); LongDelay();
    TypeText("echo What is the witch's favorite subject in school?");
    LongDelay();
    DisplayText("Spelling.");
    LongDelay();

    Separator();

    PromptText(); LongDelay();
    TypeText("echo What is a ghost's favorite Linux command?");
    LongDelay();
    DisplayText("ps -ef");
    LongDelay();

    Separator();

    PromptText(); LongDelay();
    TypeText("echo Why was the haunted server always busy?");
    LongDelay();
    DisplayText("Too many ghost processes.");
    LongDelay();

    Separator();

    PromptText(); LongDelay();
    TypeText("echo Why did the pumpkin get promoted?");
    LongDelay();
    DisplayText("Because it was out standing in its field.");
    LongDelay();

    Separator();

    PromptText(); LongDelay();
    TypeText("echo Why was the ghost bad at lying?");
    LongDelay();
    DisplayText("You could see right through him.");
    LongDelay();

    Separator();

    PromptText(); LongDelay();
    TypeText("echo What was the bat's favorite thing to study in school?");
    LongDelay();
    DisplayText("The alpha-bat.");
    LongDelay();

    Separator();

    PromptText(); LongDelay();
    TypeText("echo Why did the skeleton skip the party?");
    LongDelay();
    DisplayText("He had no body to go with.");
    LongDelay();

    Separator();

    PromptText(); LongDelay();
    TypeText("echo What do you get when you divide a pumpkin's circumference by its diameter?");
    LongDelay();
    DisplayText("Pumpkin Pi.");
    LongDelay();

    Separator();

    PromptText(); LongDelay();
    TypeText("echo Why are graveyards so noisy?");
    LongDelay();
    DisplayText("Because of all the coffin.");
    LongDelay();

    Separator();

    PromptText(); LongDelay();
    TypeText("echo What does a vegetarian zombie eat?");
    LongDelay();
    DisplayText("GRAAAAAINS!");
    LongDelay();

    Separator();

    PromptText(); LongDelay();
    TypeText("echo Why did the ghost go to the doctor?");
    LongDelay();
    DisplayText("He was feeling a little boo-hoo.");
    LongDelay();

    Separator();

    PromptText(); LongDelay();
    TypeText("echo What kind of music do mummies like?");
    LongDelay();
    DisplayText("Wrap music.");
    LongDelay();

    Separator();

    PromptText(); LongDelay();
    TypeText("echo Initializing final joke...");
    LongDelay();
    DisplayText("ERROR: joke quality threshold exceeded");
    DisplayText("WARNING: spouse terminal eyeroll detected");
    LongDelay();

    Separator();

    PromptText(); LongDelay();
    TypeText("exit");
    LongDelay();

    DisplayText("ERROR: Dad jokes are a protected system service.");
    ShortDelay();
    DisplayText("Refusing shutdown request.");
    LongDelay();

    Separator();

    DisplayText("PumpkinOS Joke Module Complete. User may stop rolling eyes in:");
    ShortDelay();
    DisplayText("5");
    ShortDelay();
    DisplayText("4");
    ShortDelay();
    DisplayText("3");
    ShortDelay();
    DisplayText("2");
    LongDelay();
    DisplayText("1");

    LongDelay();


	ShowJokeScreen();
}

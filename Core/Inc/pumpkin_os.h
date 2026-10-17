/*
 * pumpkin_os.h
 *
 *  Created on: Oct 17, 2026
 *      Author: crvhoover
 */

#ifndef PUMPKIN_OS_H
#define PUMPKIN_OS_H

void PumpkinOS_Start(void);
void ShowBootScreen(void);

void DisplayText(const char *text);
void PromptText(void);
void Separator(void);

#endif

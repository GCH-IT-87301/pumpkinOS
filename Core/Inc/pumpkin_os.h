/*
 * pumpkin_os.h
 *
 *  Created on: Oct 17, 2026
 *      Author: crvhoover
 */

#ifndef PUMPKIN_OS_H
#define PUMPKIN_OS_H

void PumpkinOS_Start(void);
void PumpkinOS_Update(void);
void ShowBootScreen(void);

void DisplayText(const char *text);
void PromptText(void);
void Separator(void);

typedef enum
{
    SCENE_BIOS,
    SCENE_BOOT,
    SCENE_PRINTER,
    SCENE_GHOST,
    SCENE_TICKET,
    SCENE_JOKE
} PumpkinScene_t;

#endif

#ifndef ST7796_H
#define ST7796_H

#include <stdint.h>

void ST7796_Init(void);
void ST7796_FillScreen(uint16_t color);
void ST7796_FillRectangle(
    uint16_t x,
    uint16_t y,
    uint16_t width,
    uint16_t height,
    uint16_t color);

#define ST7796_RED    0xF800
#define ST7796_GREEN  0x07E0
#define ST7796_BLUE   0x001F
#define ST7796_BLACK  0x0000
#define ST7796_WHITE  0xFFFF

#endif

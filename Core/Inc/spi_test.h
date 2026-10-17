#ifndef SPI_TEST_H
#define SPI_TEST_H

#include <stdint.h>

void SPI_Test(void);
void LCD_WriteCommand(uint8_t cmd);
void LCD_WriteData(uint8_t data);

#endif

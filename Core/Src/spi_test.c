#include "main.h"
#include "spi_test.h"

extern SPI_HandleTypeDef hspi1;

void SPI_Test(void)
{
    uint8_t byte = 0xAA;

    HAL_GPIO_WritePin(
        LCD_CS_GPIO_Port,
        LCD_CS_Pin,
        GPIO_PIN_RESET);

    HAL_SPI_Transmit(
        &hspi1,
        &byte,
        1,
        100);

    HAL_GPIO_WritePin(
        LCD_CS_GPIO_Port,
        LCD_CS_Pin,
        GPIO_PIN_SET);
}

void LCD_WriteCommand(uint8_t cmd)
{
    HAL_GPIO_WritePin(
        LCD_CS_GPIO_Port,
        LCD_CS_Pin,
        GPIO_PIN_RESET);

    /* RS/DC low means command */
    HAL_GPIO_WritePin(
        LCD_RS_GPIO_Port,
        LCD_RS_Pin,
        GPIO_PIN_RESET);

    HAL_SPI_Transmit(
        &hspi1,
        &cmd,
        1,
        100);

    HAL_GPIO_WritePin(
        LCD_CS_GPIO_Port,
        LCD_CS_Pin,
        GPIO_PIN_SET);
}

void LCD_WriteData(uint8_t data)
{
    HAL_GPIO_WritePin(
        LCD_CS_GPIO_Port,
        LCD_CS_Pin,
        GPIO_PIN_RESET);

    /* RS/DC high means data */
    HAL_GPIO_WritePin(
        LCD_RS_GPIO_Port,
        LCD_RS_Pin,
        GPIO_PIN_SET);

    HAL_SPI_Transmit(
        &hspi1,
        &data,
        1,
        100);

    HAL_GPIO_WritePin(
        LCD_CS_GPIO_Port,
        LCD_CS_Pin,
        GPIO_PIN_SET);
}

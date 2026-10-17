#include "main.h"
#include "spi_test.h"
#include "st7796.h"

extern SPI_HandleTypeDef hspi1;

void ST7796_Init(void)
{
    /* Hardware reset */
    HAL_GPIO_WritePin(
        LCD_RST_GPIO_Port,
        LCD_RST_Pin,
        GPIO_PIN_RESET);

    HAL_Delay(20);

    HAL_GPIO_WritePin(
        LCD_RST_GPIO_Port,
        LCD_RST_Pin,
        GPIO_PIN_SET);

    HAL_Delay(120);

    /* Software reset */
    LCD_WriteCommand(0x01);
    HAL_Delay(120);

    /* Sleep out */
    LCD_WriteCommand(0x11);
    HAL_Delay(120);

    /* Enable extension command set, part 1 */
    LCD_WriteCommand(0xF0);
    LCD_WriteData(0xC3);

    /* Enable extension command set, part 2 */
    LCD_WriteCommand(0xF0);
    LCD_WriteData(0x96);

    /* Memory access control */
    LCD_WriteCommand(0x36);
    LCD_WriteData(0x48);

    /* RGB565, 16-bit pixel format */
    LCD_WriteCommand(0x3A);
    LCD_WriteData(0x55);

    /* Column inversion */
    LCD_WriteCommand(0xB4);
    LCD_WriteData(0x01);

    /* Display function control */
    LCD_WriteCommand(0xB6);
    LCD_WriteData(0x80);
    LCD_WriteData(0x02);
    LCD_WriteData(0x3B);

    /* Display output control adjustment */
    LCD_WriteCommand(0xE8);
    LCD_WriteData(0x40);
    LCD_WriteData(0x8A);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x29);
    LCD_WriteData(0x19);
    LCD_WriteData(0xA5);
    LCD_WriteData(0x33);

    /* Power control 2 */
    LCD_WriteCommand(0xC1);
    LCD_WriteData(0x06);

    /* Power control 3 */
    LCD_WriteCommand(0xC2);
    LCD_WriteData(0xA7);

    /* VCOM control */
    LCD_WriteCommand(0xC5);
    LCD_WriteData(0x18);

    HAL_Delay(120);

    /* Positive gamma */
    LCD_WriteCommand(0xE0);
    LCD_WriteData(0xF0);
    LCD_WriteData(0x09);
    LCD_WriteData(0x0B);
    LCD_WriteData(0x06);
    LCD_WriteData(0x04);
    LCD_WriteData(0x15);
    LCD_WriteData(0x2F);
    LCD_WriteData(0x54);
    LCD_WriteData(0x42);
    LCD_WriteData(0x3C);
    LCD_WriteData(0x17);
    LCD_WriteData(0x14);
    LCD_WriteData(0x18);
    LCD_WriteData(0x1B);

    /* Negative gamma */
    LCD_WriteCommand(0xE1);
    LCD_WriteData(0xE0);
    LCD_WriteData(0x09);
    LCD_WriteData(0x0B);
    LCD_WriteData(0x06);
    LCD_WriteData(0x04);
    LCD_WriteData(0x03);
    LCD_WriteData(0x2B);
    LCD_WriteData(0x43);
    LCD_WriteData(0x42);
    LCD_WriteData(0x3B);
    LCD_WriteData(0x16);
    LCD_WriteData(0x14);
    LCD_WriteData(0x17);
    LCD_WriteData(0x1B);

    HAL_Delay(120);

    /* Disable extension command set */
    LCD_WriteCommand(0xF0);
    LCD_WriteData(0x3C);

    LCD_WriteCommand(0xF0);
    LCD_WriteData(0x69);

    HAL_Delay(120);

    /* Display on */
    LCD_WriteCommand(0x29);
    HAL_Delay(100);
}

void ST7796_FillScreen(uint16_t color)
{
    uint8_t buffer[512];

    uint8_t highByte = (uint8_t)(color >> 8);
    uint8_t lowByte  = (uint8_t)(color & 0xFF);

    /*
     * Fill the buffer with 256 RGB565 pixels.
     * Each pixel occupies two bytes.
     */
    for (uint16_t i = 0; i < sizeof(buffer); i += 2)
    {
        buffer[i]     = highByte;
        buffer[i + 1] = lowByte;
    }

    /* Column address: 0 through 319 */
    LCD_WriteCommand(0x2A);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x01);
    LCD_WriteData(0x3F);

    /* Row address: 0 through 479 */
    LCD_WriteCommand(0x2B);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x01);
    LCD_WriteData(0xDF);

    /* Begin display-memory write */
    LCD_WriteCommand(0x2C);

    /*
     * Select LCD and enter data mode.
     * Keep CS low throughout the complete pixel transfer.
     */
    HAL_GPIO_WritePin(
        LCD_CS_GPIO_Port,
        LCD_CS_Pin,
        GPIO_PIN_RESET);

    HAL_GPIO_WritePin(
        LCD_RS_GPIO_Port,
        LCD_RS_Pin,
        GPIO_PIN_SET);

    /*
     * 320 × 480 = 153,600 pixels.
     * Each 512-byte transfer contains 256 pixels.
     * 153,600 / 256 = 600 transfers.
     */
    for (uint16_t block = 0; block < 600; block++)
    {
        HAL_StatusTypeDef status;

        status = HAL_SPI_Transmit(
            &hspi1,
            buffer,
            sizeof(buffer),
            1000);

        if (status != HAL_OK)
        {
            HAL_GPIO_WritePin(
                LCD_CS_GPIO_Port,
                LCD_CS_Pin,
                GPIO_PIN_SET);

            Error_Handler();
        }
    }

    /* End LCD transaction */
    HAL_GPIO_WritePin(
        LCD_CS_GPIO_Port,
        LCD_CS_Pin,
        GPIO_PIN_SET);
}

void ST7796_FillRectangle(
    uint16_t x,
    uint16_t y,
    uint16_t width,
    uint16_t height,
    uint16_t color)
{
    uint32_t pixels = width * height;

    uint8_t high = color >> 8;
    uint8_t low  = color & 0xFF;

    LCD_WriteCommand(0x2A);

    LCD_WriteData(x >> 8);
    LCD_WriteData(x & 0xFF);

    LCD_WriteData((x + width - 1) >> 8);
    LCD_WriteData((x + width - 1) & 0xFF);

    LCD_WriteCommand(0x2B);

    LCD_WriteData(y >> 8);
    LCD_WriteData(y & 0xFF);

    LCD_WriteData((y + height - 1) >> 8);
    LCD_WriteData((y + height - 1) & 0xFF);

    LCD_WriteCommand(0x2C);

    HAL_GPIO_WritePin(
        LCD_CS_GPIO_Port,
        LCD_CS_Pin,
        GPIO_PIN_RESET);

    HAL_GPIO_WritePin(
        LCD_RS_GPIO_Port,
        LCD_RS_Pin,
        GPIO_PIN_SET);

    for(uint32_t i = 0; i < pixels; i++)
    {
        uint8_t pixel[2] = {high, low};

        HAL_SPI_Transmit(
            &hspi1,
            pixel,
            2,
            100);
    }

    HAL_GPIO_WritePin(
        LCD_CS_GPIO_Port,
        LCD_CS_Pin,
        GPIO_PIN_SET);
}

void DrawLetterH(uint16_t x, uint16_t y, uint16_t color)
{
    ST7796_FillRectangle(x,     y, 8, 40, color);
    ST7796_FillRectangle(x+24,  y, 8, 40, color);
    ST7796_FillRectangle(x, y+16, 32, 8, color);
}

static const uint8_t *ST7796_GetGlyph(char character)
{
    /*
     * Each character is 5 pixels wide by 7 pixels tall.
     * Each byte represents one horizontal row.
     * Only the letters needed for HELLO PUMPKIN are included.
     */

    static const uint8_t glyph_H[7] =
    {
        0x11,
        0x11,
        0x11,
        0x1F,
        0x11,
        0x11,
        0x11
    };

    static const uint8_t glyph_E[7] =
    {
        0x1F,
        0x10,
        0x10,
        0x1E,
        0x10,
        0x10,
        0x1F
    };

    static const uint8_t glyph_L[7] =
    {
        0x10,
        0x10,
        0x10,
        0x10,
        0x10,
        0x10,
        0x1F
    };

    static const uint8_t glyph_O[7] =
    {
        0x0E,
        0x11,
        0x11,
        0x11,
        0x11,
        0x11,
        0x0E
    };

    static const uint8_t glyph_P[7] =
    {
        0x1E,
        0x11,
        0x11,
        0x1E,
        0x10,
        0x10,
        0x10
    };

    static const uint8_t glyph_U[7] =
    {
        0x11,
        0x11,
        0x11,
        0x11,
        0x11,
        0x11,
        0x0E
    };

    static const uint8_t glyph_M[7] =
    {
        0x11,
        0x1B,
        0x15,
        0x15,
        0x11,
        0x11,
        0x11
    };

    static const uint8_t glyph_K[7] =
    {
        0x11,
        0x12,
        0x14,
        0x18,
        0x14,
        0x12,
        0x11
    };

    static const uint8_t glyph_I[7] =
    {
        0x1F,
        0x04,
        0x04,
        0x04,
        0x04,
        0x04,
        0x1F
    };

    static const uint8_t glyph_N[7] =
    {
        0x11,
        0x19,
        0x19,
        0x15,
        0x13,
        0x13,
        0x11
    };

    static const uint8_t glyph_blank[7] =
    {
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00
    };

    switch (character)
    {
        case 'H': return glyph_H;
        case 'E': return glyph_E;
        case 'L': return glyph_L;
        case 'O': return glyph_O;
        case 'P': return glyph_P;
        case 'U': return glyph_U;
        case 'M': return glyph_M;
        case 'K': return glyph_K;
        case 'I': return glyph_I;
        case 'N': return glyph_N;
        case ' ': return glyph_blank;
        default:  return glyph_blank;
    }
}


void ST7796_DrawChar(
    uint16_t x,
    uint16_t y,
    char character,
    uint16_t color,
    uint8_t scale)
{
    const uint8_t *glyph = ST7796_GetGlyph(character);

    for (uint8_t row = 0; row < 7; row++)
    {
        for (uint8_t column = 0; column < 5; column++)
        {
            /*
             * Bit 4 is the leftmost pixel.
             * Bit 0 is the rightmost pixel.
             */
            if (glyph[row] & (1U << (4 - column)))
            {
                ST7796_FillRectangle(
                    x + (column * scale),
                    y + (row * scale),
                    scale,
                    scale,
                    color);
            }
        }
    }
}


void ST7796_DrawText(
    uint16_t x,
    uint16_t y,
    const char *text,
    uint16_t color,
    uint8_t scale)
{
    uint16_t cursorX = x;

    while (*text != '\0')
    {
        ST7796_DrawChar(
            cursorX,
            y,
            *text,
            color,
            scale);

        /*
         * Each glyph is five blocks wide.
         * The sixth block provides one space between characters.
         */
        cursorX += 6 * scale;

        text++;
    }
}


void ST7796_DrawHelloPumpkin(void)
{
    /*
     * Scale 4 produces characters:
     *
     * Width:  5 × 4 = 20 pixels
     * Height: 7 × 4 = 28 pixels
     *
     * HELLO occupies 120 pixels including spacing.
     * PUMPKIN occupies 168 pixels including spacing.
     *
     * These X coordinates center both lines on a 320-pixel display.
     */

    ST7796_DrawText(
        100,
        325,
        "HELLO",
        ST7796_WHITE,
        4);

    ST7796_DrawText(
        76,
        370,
        "PUMPKIN",
        ST7796_WHITE,
        4);
}

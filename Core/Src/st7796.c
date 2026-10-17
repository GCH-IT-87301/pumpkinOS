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
     */

	//letters
	static const uint8_t glyph_A[7] = {0x0E,0x11,0x11,0x1F,0x11,0x11,0x11};
	static const uint8_t glyph_B[7] = {0x1E,0x11,0x11,0x1E,0x11,0x11,0x1E};
	static const uint8_t glyph_C[7] = {0x0E,0x11,0x10,0x10,0x10,0x11,0x0E};
	static const uint8_t glyph_D[7] = {0x1E,0x11,0x11,0x11,0x11,0x11,0x1E};
	static const uint8_t glyph_E[7] = {0x1F,0x10,0x10,0x1E,0x10,0x10,0x1F};
	static const uint8_t glyph_F[7] = {0x1F,0x10,0x10,0x1E,0x10,0x10,0x10};
	static const uint8_t glyph_G[7] = {0x0E,0x11,0x10,0x17,0x11,0x11,0x0E};
	static const uint8_t glyph_H[7] = {0x11,0x11,0x11,0x1F,0x11,0x11,0x11};
	static const uint8_t glyph_I[7] = {0x1F,0x04,0x04,0x04,0x04,0x04,0x1F};
	static const uint8_t glyph_J[7] = {0x01,0x01,0x01,0x01,0x11,0x11,0x0E};
	static const uint8_t glyph_K[7] = {0x11,0x12,0x14,0x18,0x14,0x12,0x11};
	static const uint8_t glyph_L[7] = {0x10,0x10,0x10,0x10,0x10,0x10,0x1F};
	static const uint8_t glyph_M[7] = {0x11,0x1B,0x15,0x15,0x11,0x11,0x11};
	static const uint8_t glyph_N[7] = {0x11,0x19,0x15,0x13,0x11,0x11,0x11};
	static const uint8_t glyph_O[7] = {0x0E,0x11,0x11,0x11,0x11,0x11,0x0E};
	static const uint8_t glyph_P[7] = {0x1E,0x11,0x11,0x1E,0x10,0x10,0x10};
	static const uint8_t glyph_Q[7] = {0x0E,0x11,0x11,0x11,0x15,0x12,0x0D};
	static const uint8_t glyph_R[7] = {0x1E,0x11,0x11,0x1E,0x14,0x12,0x11};
	static const uint8_t glyph_S[7] = {0x0F,0x10,0x10,0x0E,0x01,0x01,0x1E};
	static const uint8_t glyph_T[7] = {0x1F,0x04,0x04,0x04,0x04,0x04,0x04};
	static const uint8_t glyph_U[7] = {0x11,0x11,0x11,0x11,0x11,0x11,0x0E};
	static const uint8_t glyph_V[7] = {0x11,0x11,0x11,0x11,0x11,0x0A,0x04};
	static const uint8_t glyph_W[7] = {0x11,0x11,0x11,0x15,0x15,0x15,0x0A};
	static const uint8_t glyph_X[7] = {0x11,0x11,0x0A,0x04,0x0A,0x11,0x11};
	static const uint8_t glyph_Y[7] = {0x11,0x11,0x0A,0x04,0x04,0x04,0x04};
	static const uint8_t glyph_Z[7] = {0x1F,0x01,0x02,0x04,0x08,0x10,0x1F};

	//numbers
	static const uint8_t glyph_0[7] = {0x0E,0x11,0x13,0x15,0x19,0x11,0x0E};
	static const uint8_t glyph_1[7] = {0x04,0x0C,0x04,0x04,0x04,0x04,0x0E};
	static const uint8_t glyph_2[7] = {0x0E,0x11,0x01,0x02,0x04,0x08,0x1F};
	static const uint8_t glyph_3[7] = {0x1F,0x02,0x04,0x02,0x01,0x11,0x0E};
	static const uint8_t glyph_4[7] = {0x02,0x06,0x0A,0x12,0x1F,0x02,0x02};
	static const uint8_t glyph_5[7] = {0x1F,0x10,0x1E,0x01,0x01,0x11,0x0E};
	static const uint8_t glyph_6[7] = {0x06,0x08,0x10,0x1E,0x11,0x11,0x0E};
	static const uint8_t glyph_7[7] = {0x1F,0x01,0x02,0x04,0x08,0x08,0x08};
	static const uint8_t glyph_8[7] = {0x0E,0x11,0x11,0x0E,0x11,0x11,0x0E};
	static const uint8_t glyph_9[7] = {0x0E,0x11,0x11,0x0F,0x01,0x02,0x0C};

	//symbols
	static const uint8_t glyph_space[7] =
	{
	    0x00,0x00,0x00,0x00,0x00,0x00,0x00
	};

	static const uint8_t glyph_period[7] =
	{
	    0x00,0x00,0x00,0x00,0x00,0x0C,0x0C
	};

	static const uint8_t glyph_comma[7] =
	{
	    0x00,0x00,0x00,0x00,0x0C,0x0C,0x08
	};

	static const uint8_t glyph_colon[7] =
	{
	    0x00,0x0C,0x0C,0x00,0x0C,0x0C,0x00
	};

	static const uint8_t glyph_semicolon[7] =
	{
	    0x00,0x0C,0x0C,0x00,0x0C,0x0C,0x08
	};

	static const uint8_t glyph_dash[7] =
	{
	    0x00,0x00,0x00,0x1F,0x00,0x00,0x00
	};

	static const uint8_t glyph_underscore[7] =
	{
	    0x00,0x00,0x00,0x00,0x00,0x00,0x1F
	};

	static const uint8_t glyph_slash[7] =
	{
	    0x01,0x02,0x04,0x08,0x10,0x00,0x00
	};

	static const uint8_t glyph_backslash[7] =
	{
	    0x10,0x08,0x04,0x02,0x01,0x00,0x00
	};

	static const uint8_t glyph_lparen[7] =
	{
	    0x02,0x04,0x08,0x08,0x08,0x04,0x02
	};

	static const uint8_t glyph_rparen[7] =
	{
	    0x08,0x04,0x02,0x02,0x02,0x04,0x08
	};

	static const uint8_t glyph_lbracket[7] =
	{
	    0x0E,0x08,0x08,0x08,0x08,0x08,0x0E
	};

	static const uint8_t glyph_rbracket[7] =
	{
	    0x0E,0x02,0x02,0x02,0x02,0x02,0x0E
	};

	static const uint8_t glyph_greater[7] =
	{
	    0x10,0x08,0x04,0x02,0x04,0x08,0x10
	};

	static const uint8_t glyph_less[7] =
	{
	    0x01,0x02,0x04,0x08,0x04,0x02,0x01
	};

	static const uint8_t glyph_equals[7] =
	{
	    0x00,0x1F,0x00,0x1F,0x00,0x00,0x00
	};

	static const uint8_t glyph_exclamation[7] =
	{
	    0x04,0x04,0x04,0x04,0x04,0x00,0x04
	};

	static const uint8_t glyph_question[7] =
	{
	    0x0E,0x11,0x01,0x02,0x04,0x00,0x04
	};


//lower case letters
	static const uint8_t glyph_a[7] = {0x00,0x00,0x0E,0x01,0x0F,0x11,0x0F};
	static const uint8_t glyph_b[7] = {0x10,0x10,0x1E,0x11,0x11,0x11,0x1E};
	static const uint8_t glyph_c[7] = {0x00,0x00,0x0E,0x11,0x10,0x11,0x0E};
	static const uint8_t glyph_d[7] = {0x01,0x01,0x0F,0x11,0x11,0x11,0x0F};
	static const uint8_t glyph_e[7] = {0x00,0x00,0x0E,0x11,0x1F,0x10,0x0E};
	static const uint8_t glyph_f[7] = {0x06,0x08,0x08,0x1E,0x08,0x08,0x08};
	static const uint8_t glyph_g[7] = {0x00,0x0F,0x11,0x11,0x0F,0x01,0x0E};
	static const uint8_t glyph_h[7] = {0x10,0x10,0x1E,0x11,0x11,0x11,0x11};
	static const uint8_t glyph_i[7] = {0x04,0x00,0x0C,0x04,0x04,0x04,0x0E};
	static const uint8_t glyph_j[7] = {0x02,0x00,0x06,0x02,0x02,0x12,0x0C};
	static const uint8_t glyph_k[7] = {0x10,0x11,0x12,0x1C,0x12,0x11,0x11};
	static const uint8_t glyph_l[7] = {0x0C,0x04,0x04,0x04,0x04,0x04,0x0E};
	static const uint8_t glyph_m[7] = {0x00,0x00,0x1A,0x15,0x15,0x15,0x15};
	static const uint8_t glyph_n[7] = {0x00,0x00,0x1E,0x11,0x11,0x11,0x11};
	static const uint8_t glyph_o[7] = {0x00,0x00,0x0E,0x11,0x11,0x11,0x0E};
	static const uint8_t glyph_p[7] = {0x00,0x1E,0x11,0x11,0x1E,0x10,0x10};
	static const uint8_t glyph_q[7] = {0x00,0x0F,0x11,0x11,0x0F,0x01,0x01};
	static const uint8_t glyph_r[7] = {0x00,0x00,0x16,0x19,0x10,0x10,0x10};
	static const uint8_t glyph_s[7] = {0x00,0x00,0x0F,0x10,0x0E,0x01,0x1E};
	static const uint8_t glyph_t[7] = {0x08,0x08,0x1E,0x08,0x08,0x08,0x06};
	static const uint8_t glyph_u[7] = {0x00,0x00,0x11,0x11,0x11,0x13,0x0D};
	static const uint8_t glyph_v[7] = {0x00,0x00,0x11,0x11,0x11,0x0A,0x04};
	static const uint8_t glyph_w[7] = {0x00,0x00,0x11,0x11,0x15,0x15,0x0A};
	static const uint8_t glyph_x[7] = {0x00,0x00,0x11,0x0A,0x04,0x0A,0x11};
	static const uint8_t glyph_y[7] = {0x00,0x11,0x11,0x11,0x0F,0x01,0x0E};
	static const uint8_t glyph_z[7] = {0x00,0x00,0x1F,0x02,0x04,0x08,0x1F};


	switch(character)
	{
	    /* Letters */

	    case 'A': return glyph_A;
	    case 'B': return glyph_B;
	    case 'C': return glyph_C;
	    case 'D': return glyph_D;
	    case 'E': return glyph_E;
	    case 'F': return glyph_F;
	    case 'G': return glyph_G;
	    case 'H': return glyph_H;
	    case 'I': return glyph_I;
	    case 'J': return glyph_J;
	    case 'K': return glyph_K;
	    case 'L': return glyph_L;
	    case 'M': return glyph_M;
	    case 'N': return glyph_N;
	    case 'O': return glyph_O;
	    case 'P': return glyph_P;
	    case 'Q': return glyph_Q;
	    case 'R': return glyph_R;
	    case 'S': return glyph_S;
	    case 'T': return glyph_T;
	    case 'U': return glyph_U;
	    case 'V': return glyph_V;
	    case 'W': return glyph_W;
	    case 'X': return glyph_X;
	    case 'Y': return glyph_Y;
	    case 'Z': return glyph_Z;


	    /* Numbers */

	    case '0': return glyph_0;
	    case '1': return glyph_1;
	    case '2': return glyph_2;
	    case '3': return glyph_3;
	    case '4': return glyph_4;
	    case '5': return glyph_5;
	    case '6': return glyph_6;
	    case '7': return glyph_7;
	    case '8': return glyph_8;
	    case '9': return glyph_9;

	    /* Symbols */

	    case ' ': return glyph_space;
	    case '.': return glyph_period;
	    case ',': return glyph_comma;
	    case ':': return glyph_colon;
	    case ';': return glyph_semicolon;
	    case '-': return glyph_dash;
	    case '_': return glyph_underscore;
	    case '/': return glyph_slash;
	    case '\\': return glyph_backslash;
	    case '(': return glyph_lparen;
	    case ')': return glyph_rparen;
	    case '[': return glyph_lbracket;
	    case ']': return glyph_rbracket;
	    case '>': return glyph_greater;
	    case '<': return glyph_less;
	    case '=': return glyph_equals;
	    case '!': return glyph_exclamation;
	    case '?': return glyph_question;

	    //lower case letters
	    case 'a': return glyph_a;
	    case 'b': return glyph_b;
	    case 'c': return glyph_c;
	    case 'd': return glyph_d;
	    case 'e': return glyph_e;
	    case 'f': return glyph_f;
	    case 'g': return glyph_g;
	    case 'h': return glyph_h;
	    case 'i': return glyph_i;
	    case 'j': return glyph_j;
	    case 'k': return glyph_k;
	    case 'l': return glyph_l;
	    case 'm': return glyph_m;
	    case 'n': return glyph_n;
	    case 'o': return glyph_o;
	    case 'p': return glyph_p;
	    case 'q': return glyph_q;
	    case 'r': return glyph_r;
	    case 's': return glyph_s;
	    case 't': return glyph_t;
	    case 'u': return glyph_u;
	    case 'v': return glyph_v;
	    case 'w': return glyph_w;
	    case 'x': return glyph_x;
	    case 'y': return glyph_y;
	    case 'z': return glyph_z;

	    default:
	        return glyph_space;
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
    uint16_t cursorY = y;

    while (*text != '\0')
    {
        if (*text == '\n')
        {
            cursorX = x;
            cursorY += 8 * scale;

            text++;
            continue;
        }

        if (cursorX + (5 * scale) >320)
        {
        	cursorX = x;
        	cursorY += 8 * scale;
        }

        ST7796_DrawChar(
            cursorX,
            cursorY,
            *text,
            color,
            scale);

        /*
         * Each glyph is five blocks wide.
         * The sixth block provides one space
         * between characters.
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
        76,
        325,
        "PUMPKIN",
        ST7796_WHITE,
        4);

    ST7796_DrawText(
        112,
        370,
        "BIOS",
        ST7796_WHITE,
        4);
}

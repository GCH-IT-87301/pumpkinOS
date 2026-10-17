# PumpkinOS 🎃

PumpkinOS is a Halloween-themed embedded graphics project built on an STM32 Blue Pill (STM32F103) driving a 4.0" 480x320 ST7796 TFT display over SPI.

The goal is to create a lightweight graphics and animation framework capable of rendering pumpkins, spooky faces, scenes, simple games, and eventually a complete pumpkin-themed UI.

---

## Current Status

Hardware bring-up successful.

Working features:

- STM32F103 Blue Pill
- ST-Link programming/debugging
- SPI communication
- ST7796 initialization
- RGB565 color output
- Full-screen fills
- Rectangle drawing primitives
- Simple bitmap-style text rendering
- First rendered PumpkinOS face 🎃

---

## Hardware

### MCU

- STM32F103C6T6A ("Blue Pill")

### Display

- 4.0" TFT SPI Display
- Resolution: 320x480
- Controller: ST7796S
- Capacitive Touch version

### Wiring

| Display Pin | Blue Pill |
|------------|-----------|
| VCC | 5V |
| GND | GND |
| LCD_CS | PA4 |
| LCD_RST | PB1 |
| LCD_RS (DC) | PB0 |
| SDI (MOSI) | PA7 |
| SCK | PA5 |

---

## Development Environment

- macOS
- STM32CubeMX
- STM32CubeIDE
- ST-Link V2

---

## Major Bring-Up Milestones

### LED Blink

Confirmed standalone execution from internal flash.

### SPI Initialization

SPI1 configured and verified.

### Display Initialization

Implemented ST7796 initialization sequence.

### First Pixel Output

Successfully displayed:

- Full RED screen
- Full GREEN screen
- Full BLUE screen

### Hardware Fault Found

A faulty solder joint on the display header MOSI/SDI pin prevented display communication.

Symptoms:

- White screen
- No response to commands
- Clock present
- Data line not reaching display

Resolution:

- Re-soldered 14-pin display connector
- MOSI restored
- Display immediately responded

### First Pumpkin

Successfully rendered a pumpkin face using rectangle primitives.

This marks the first visual output of PumpkinOS hardware.

---

## Graphics Primitives Implemented

### Fill Screen

```c
ST7796_FillScreen(color);
```

### Fill Rectangle

```c
ST7796_FillRectangle(
    x,
    y,
    width,
    height,
    color);
```

### Draw Text

```c
ST7796_DrawText(
    x,
    y,
    "HELLO",
    color,
    scale);
```

---

## Color Definitions

```c
#define ST7796_BLACK   0x0000
#define ST7796_WHITE   0xFFFF
#define ST7796_RED     0xF800
#define ST7796_GREEN   0x07E0
#define ST7796_BLUE    0x001F
#define ST7796_ORANGE  0xFD20
```

---

## Next Goals

### Graphics

- DrawPixel()
- DrawLine()
- DrawCircle()
- Filled circles
- Better text rendering

### PumpkinOS

- Scene engine
- Animated pumpkins
- Pumpkin emotions
- Haunted house scene
- Halloween game experiments

### Performance

Current renderer favors simplicity over speed.

Future improvements:

- Buffered rectangle fills
- DMA SPI transfers
- Partial screen updates
- Frame buffering

---

## Project History

### Hello Pumpkin

The first successful PumpkinOS hardware render:

- ST7796 initialized
- Full graphics stack operational
- Rectangle renderer operational
- Text rendering operational
- Pumpkin face rendered

PumpkinOS officially became visible on physical hardware.

🎃

## Next Steps

The display hardware is now fully operational and capable of rendering graphics and text. Development will focus on building reusable graphics primitives, improving rendering performance, and expanding PumpkinOS into a scene-based graphics platform.

### Immediate Goals

#### Graphics Primitives

Implement the remaining low-level drawing functions:

- [ ] ST7796_DrawPixel()
- [ ] ST7796_DrawLine()
- [ ] ST7796_DrawCircle()
- [ ] ST7796_FillCircle()
- [ ] ST7796_DrawTriangle()
- [ ] ST7796_FillTriangle()

These will become the foundation for all future PumpkinOS scenes and animations.

#### Text Rendering

Current text rendering uses a minimal built-in glyph set.

Planned improvements:

- [ ] Complete ASCII character set
- [ ] Multiple font sizes
- [ ] Bitmap font support
- [ ] Text alignment helpers
- [ ] Text centering routines

Example future API:

```c
ST7796_DrawText(
    50,
    400,
    "HELLO PUMPKIN",
    ST7796_WHITE,
    4);
```

### Performance Optimization

Current rendering prioritizes simplicity over speed.

Observed bottleneck:

- Rectangle drawing issues many small SPI transfers
- Display updates are functional but visibly slow

Planned improvements:

- [ ] Buffered rectangle fills
- [ ] Chunked SPI transfers
- [ ] DMA-based SPI rendering
- [ ] Partial screen updates
- [ ] Dirty rectangle system

Target:

- Nearly instantaneous scene rendering
- Smooth animation support

### PumpkinOS Scene Engine

Create reusable scene objects:

```c
Scene_DrawTitle();
Scene_DrawPumpkin();
Scene_DrawGhost();
Scene_DrawHauntedHouse();
Scene_DrawCredits();
```

The objective is to separate scene logic from display driver code.

### Pumpkin Face Version 2

Replace rectangle-only graphics with actual shapes:

- [ ] Circular pumpkin body
- [ ] Triangular eyes
- [ ] Triangular nose
- [ ] Jagged jack-o-lantern smile
- [ ] Multiple facial expressions

### Animation System

Add frame-based animation support:

- [ ] Eye blinking
- [ ] Flickering candle effect
- [ ] Pumpkin breathing effect
- [ ] Scrolling text
- [ ] Scene transitions

### Input Support

Future expansion possibilities:

- [ ] Capacitive touchscreen support
- [ ] Physical buttons
- [ ] Rotary encoder
- [ ] USB serial command interface

### PumpkinOS Milestone Roadmap

#### Milestone 1 — Hello Pumpkin ✅

Completed.

- STM32 operational
- ST7796 display operational
- Graphics rendering operational
- First pumpkin rendered on physical hardware

#### Milestone 2 — Pumpkin Graphics

Current target.

- Drawing primitives
- Faster rendering
- Improved pumpkin artwork

#### Milestone 3 — Animated Pumpkin

- Animation engine
- Multiple expressions
- Scene transitions

#### Milestone 4 — PumpkinOS

- Scene framework
- Menus
- Interactive content
- Full Halloween-themed embedded graphics platform

---

Current known-good hardware configuration:

- STM32F103 Blue Pill
- ST7796 320x480 SPI TFT
- SPI1 @ Prescaler 2
- Verified MOSI/SCK/CS/DC/RST wiring
- Rectangle graphics functional
- Text rendering functional
- Git repository established

PumpkinOS officially achieved first graphics output on 16 October 2026.

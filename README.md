# 🎃 PumpkinOS v0.666

> A completely unnecessary operating system for a pumpkin that does not exist.

PumpkinOS is a Halloween-themed fake operating system running on an STM32 Blue Pill microcontroller and a 4.0-inch ST7796S TFT display.

The project began as a macOS Terminal simulator and eventually escaped onto real embedded hardware. PumpkinOS now includes a custom graphics driver, bitmap font, terminal-style console, randomized typing effects, ASCII art, fake Linux commands, simulated boot failures, scene transitions, and a healthy disrespect for printers.

PumpkinOS serves no practical purpose whatsoever.

**Version 0.666 is the first complete hardware release.**

---

## Screenshots

_Add photographs or screenshots of PumpkinOS here._

Suggested images:

- PUMPKIN BIOS splash screen
- PumpkinOS terminal prompt
- ASCII art scene
- Printer troubleshooting scene
- STM32 and display hardware

Example Markdown:

```markdown
![PumpkinOS terminal](images/pumpkin-terminal.jpg)
```

---

## Features

### Display system

- ST7796S TFT display support
- SPI graphics rendering
- 480 × 320 landscape orientation
- Filled rectangles and primitive graphics
- Custom character and text rendering
- Screen-clearing and cursor-management functions

### Custom font engine

- Custom 5 × 7 bitmap glyphs
- Uppercase letters
- Lowercase letters
- Numbers
- Terminal punctuation and symbols
- Scalable character rendering
- Character-by-character drawing

### Terminal console

- Linux-style command prompt
- Automatic line wrapping
- Cursor position tracking
- Automatic screen clearing at the bottom of the display
- Immediate text output with `DisplayText()`
- Typewriter output with `TypeText()`
- Randomized typing delays
- Short, long, and fixed scene delays

### PumpkinOS content

- PUMPKIN BIOS splash screen
- Multi-stage fake boot process
- Simulated boot failures and reboot attempts
- Scene-to-scene execution
- ASCII art
- Fake Linux commands
- Fake networking output
- Printer troubleshooting jokes
- Intentionally questionable system administration

---

## Example output

```text
root@pumpkin:~# test-NetConnection printer0.local -p 8080
bash: test-NetConnection:
command not found

root@pumpkin:~# ping printer0.local
PING printer0 (10.0.0.667)
```

---

## Hardware

The current PumpkinOS build was developed and tested with the following hardware:

- STM32F103C8T6-compatible Blue Pill development board
- 4.0-inch 480 × 320 TFT display using the ST7796S controller
- ST-Link programmer/debugger
- Breadboard or other suitable prototyping arrangement
- Female-to-female or male-to-female jumper wires, depending on the display header
- USB cable or regulated power source
- Soldering equipment, particularly when the display header decides to become a software problem

### Shopping search terms

Compatible-looking hardware can be found by searching common electronics retailers for:

```text
STM32F103C8T6 Blue Pill development board
```

```text
4.0 inch ST7796S 480x320 SPI TFT display
```

```text
ST-Link V2 STM32 programmer
```

> [!IMPORTANT]
> ST7796 display modules are sold in several electrical and pinout configurations. Verify that a display supports SPI communication and inspect its required logic and power voltages before connecting it to the STM32.

---

## Wiring

PumpkinOS communicates with the display through SPI.

The working project uses these STM32 SPI signals:

| STM32 signal | Display signal | Purpose |
|---|---|---|
| PA5 / SPI1_SCK | SCK or CLK | SPI clock |
| PA7 / SPI1_MOSI | SDI, MOSI, or DIN | Display data |
| Configured GPIO | CS | Chip select |
| Configured GPIO | DC or RS | Data/command selection |
| Configured GPIO | RST or RESET | Display reset |
| GND | GND | Common ground |

The exact `CS`, `DC`, and `RESET` pins depend on the GPIO assignments in the STM32CubeMX project configuration. Check the included `.ioc` file and `main.h` before wiring a new build.

> [!CAUTION]
> Do not assume that every display pin marked `VCC` should connect directly to the STM32 3.3 V rail. Display boards differ in regulator, backlight, and logic-level design. Confirm the specifications for the particular module being used.

---

## Software requirements

- STM32CubeIDE
- STM32 HAL drivers
- ST-Link programming support
- Git, if version control is desired

The repository contains the STM32CubeIDE project and the custom PumpkinOS source files.

---

## Building PumpkinOS

1. Clone or download this repository.
2. Open STM32CubeIDE.
3. Import the repository as an existing STM32CubeIDE project.
4. Open the included `.ioc` file and confirm the clock, SPI, and GPIO configuration.
5. Build the project.
6. Connect the STM32 through an ST-Link programmer.
7. Flash the firmware.
8. Watch a tiny pumpkin-themed computer make increasingly poor decisions.

If the display remains white, verify the following before rewriting the entire driver:

- Display power
- Shared ground
- SPI clock activity
- MOSI/SDI activity
- CS, DC, and RESET connections
- Header solder joints

---

## Project structure

The project is separated into several layers:

```text
Core/
├── Inc/
│   ├── pumpkin_console.h
│   ├── pumpkin_os.h
│   └── st7796.h
└── Src/
    ├── main.c
    ├── pumpkin_console.c
    ├── pumpkin_os.c
    └── st7796.c
```

### `main.c`

Initializes the STM32 hardware, display, and PumpkinOS execution.

### `st7796.c`

Contains the low-level display driver, drawing primitives, bitmap glyph table, and character-rendering functions.

### `pumpkin_console.c`

Provides cursor management, text wrapping, prompt rendering, screen clearing, standard text output, and randomized typewriter output.

### `pumpkin_os.c`

Contains the boot sequence, scenes, jokes, ASCII art, transitions, and other poor operating-system decisions.

---

## Development history

PumpkinOS began as a macOS Terminal program with timed text, simulated commands, ASCII art, and scene transitions.

The experience was then ported to an STM32F103 board. The embedded version required:

- ST7796S display initialization
- SPI troubleshooting
- Landscape rotation
- Custom drawing primitives
- A complete bitmap character system
- Uppercase, lowercase, number, and punctuation glyphs
- Cursor and console management
- Automatic line wrapping
- Randomized typewriter timing
- Scene conversion from terminal output to display rendering

One of the longest display-debugging sessions was eventually traced to a poor solder connection on the MOSI/SDI display header.

Several hours of software debugging were resolved with a soldering iron.

As is tradition.

---

## Current status

PumpkinOS v0.666 successfully provides:

- A working STM32 hardware implementation
- Stable ST7796S display output
- 480 × 320 landscape graphics
- A custom bitmap font
- A functional terminal-style console
- Randomized typewriter output
- Automatic text wrapping
- Multiple animated scenes
- ASCII art rendering
- Fake boot and reboot sequences
- A complete start-to-finish PumpkinOS demonstration

---

## Future ideas

Possible future additions include:

- True terminal scrolling
- Interactive command input
- Physical buttons or keyboard input
- Sound effects
- SD card support
- Additional animation
- More scenes
- More ASCII art
- Network connectivity
- Additional printer jokes
- Save files nobody asked for
- A shutdown process that does not inspire confidence

---

## Version history

### v0.666

First complete hardware release.

Major milestones:

- ST7796S display bring-up completed
- Bad MOSI/SDI solder connection identified and repaired
- Stable SPI communication achieved
- Display rotated into landscape mode
- Custom bitmap font completed
- Console subsystem implemented
- Typewriter output implemented
- ASCII art rendering implemented
- Scene architecture ported from macOS to STM32
- Full PumpkinOS sequence running on physical hardware

---

## License

PumpkinOS is released under the MIT License.

You are free to use, copy, modify, merge, publish, distribute, sublicense, and sell copies of the software, provided that the original copyright notice and license are included.

See the LICENSE file for the complete license text.

Copyright © 2026 Christopher Hoover

---

## Final warning

PumpkinOS is experimental Halloween firmware.

It is not a real operating system.

It should not be used for critical infrastructure, medical equipment, aviation, nuclear control systems, production print servers, or any device expected to behave sensibly.

Especially production print servers. ;)

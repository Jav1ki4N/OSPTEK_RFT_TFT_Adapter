#pragma once

#include "spi.h" // HAL SPI 
#include <cstdint>
#include <cstring>

#define ABS_WIDTH     210
#define ABS_HEIGHT    480
#define GATE_LINES    (ABS_HEIGHT/2)

#define SPI_MAX_DELAY 1000

#define GPIO_PORT     GPIOA
#define GPIO_PIN_DC   GPIO_PIN_2
#define GPIO_PIN_CS   GPIO_PIN_3
#define GPIO_PIN_RST  GPIO_PIN_4

enum class PinState:bool
{
    LOW  = false,
    HIGH = true
};

inline void Set_PinState(uint16_t pin,PinState state)
{
    HAL_GPIO_WritePin(GPIO_PORT, pin, static_cast<GPIO_PinState>(state));
}

enum class sendtype:bool
{
    COMMAND = false,
    DATA    = true
};

/* COMMANDS */
#define CMD_DISPLAY_ON     0x29
#define CMD_NVMLOAD_CTRL   0xD6
#define CMD_BOOSTER_EN     0xD1

/* Inner Voltage Settings */
#define CMD_GV_CTRL        0xC0 
#define CMD_VSHP_CTRL      0xC1
#define CMD_VSLP_CTRL      0xC2
#define CMD_VSHN_CTRL      0xC4
#define CMD_VSLN_CTRL      0xC5

/* Frame Rate settings */
#define CMD_FRAMERATE_CTRL 0xB2
#define CMD_OSC_SETTING    0xD8

/* EQ Settings */
/* Normally needn't to be modified */
#define CMD_UPGEQH_CTRL    0xB3
#define CMD_UPGEQL_CTRL    0xB4
#define CMD_SOURCEEQ_EN    0xB7

#define CMD_GATELINE_SET   0xB0
#define CMD_SLEEP_OUT	   0x11
#define CMD_VSHL_SEL	   0xC9

#define CMD_MAD_CTRL	   0x36
#define CMD_DATAFMT_SEL    0x3A

#define CMD_GAMMAMODE_SET  0xB9
#define CMD_PANEL_SET      0xB8
#define CMD_TEAREFFECT_ON  0x35
#define CMD_AUTOPWR_CTRL   0xD0
#define CMD_HIGHPWR_ON     0x38

/*****************************/

/* Function prototypes provided by ST7306 implementation */
void send_byte(uint8_t byte);
void Send     (uint8_t toSand, sendtype type);
void LCD_Init();
void Set_Window();
void Clear_FullScreen();
void Fill_Black();

/* Parameters of Column/Row Address                             */
/* Format: 0x00xxxxxx                                           */
/* The display is by default 480px in height and 240px in width */
/* RANGE     */
/* XS<XE<59  */
#define ABS_XS 0x04
#define ABS_XE 0X38
/* YS<YE<239 */
#define ABS_YS 0x00
#define ABS_YE (ABS_HEIGHT/2)-1 //480*0.5 = 240,240 - 1 = 239

#define CMD_COL_ADDR  0x2A // XS,XE
#define CMD_ROW_ADDR  0x2B // YS,YE
#define CMD_MEM_WRITE 0x2C






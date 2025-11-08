
/* ! ONLY FOR TESTING   */


#include "ST7306.h"
#include "spi.h"

void send_byte(uint8_t byte)
{
    Set_PinState(GPIO_PIN_CS, PinState::LOW);          //Page 35, Section 7.1.4
    HAL_SPI_Transmit(&hspi1, &byte, 1, SPI_MAX_DELAY);
    Set_PinState(GPIO_PIN_CS, PinState::HIGH);
}

void Send(uint8_t toSend, sendtype type)
{
    Set_PinState(GPIO_PIN_DC, (type == sendtype::DATA) ? PinState::HIGH : PinState::LOW); //A0
    send_byte(toSend);
    Set_PinState(GPIO_PIN_DC, PinState::LOW);
}

/*
 * @brief  LCD Initialization Sequence for ST7306
*/
void LCD_Init()
{
    /* Follow the initialization sequence from the bare prototype,
       but use Send(...) and Set_PinState(...) provided by this API. */

    // Hardware reset
    Set_PinState(GPIO_PIN_RST, PinState::LOW);
    HAL_Delay(50); // wait for power stabilization
    Set_PinState(GPIO_PIN_RST, PinState::HIGH);

    // NVM load: enable ID & source voltage load, timer triggered
    Send(CMD_NVMLOAD_CTRL, sendtype::COMMAND);
    Send(0x17, sendtype::DATA);
    Send(0x02, sendtype::DATA);

    // Inner booster circuit
    Send(CMD_BOOSTER_EN, sendtype::COMMAND);
    Send(0x01, sendtype::DATA);

    // Gate voltage control (GV)
    Send(CMD_GV_CTRL, sendtype::COMMAND);
    Send(0x0E, sendtype::DATA); // VGH
    Send(0x0A, sendtype::DATA); // VGL

    // Source High Positive Voltage Control (VSHP)
    Send(CMD_VSHP_CTRL, sendtype::COMMAND);
    Send(0x41, sendtype::DATA);
    Send(0x41, sendtype::DATA);
    Send(0x41, sendtype::DATA);
    Send(0x41, sendtype::DATA);

    // Source Low Positive Voltage Control (VSLP)
    Send(CMD_VSLP_CTRL, sendtype::COMMAND);
    Send(0x32, sendtype::DATA);
    Send(0x32, sendtype::DATA);
    Send(0x32, sendtype::DATA);
    Send(0x32, sendtype::DATA);

    // Source High Negative Voltage Control (VSHN)
    Send(CMD_VSHN_CTRL, sendtype::COMMAND);
    Send(0x46, sendtype::DATA);
    Send(0x46, sendtype::DATA);
    Send(0x46, sendtype::DATA);
    Send(0x46, sendtype::DATA);

    // Source Low Negative Voltage Control (VSLN)
    Send(CMD_VSLN_CTRL, sendtype::COMMAND);
    Send(0x46, sendtype::DATA);
    Send(0x46, sendtype::DATA);
    Send(0x46, sendtype::DATA);
    Send(0x46, sendtype::DATA);

    // OSC Setting: max FPS / fixed
    Send(CMD_OSC_SETTING, sendtype::COMMAND);
    Send(0x80, sendtype::DATA); // max FPS 51Hz
    Send(0xE9, sendtype::DATA);

    // Frame rate control
    Send(CMD_FRAMERATE_CTRL, sendtype::COMMAND);
    Send(0x12, sendtype::DATA); // HPM FPS=32Hz, LPM=1Hz

    // Update period gate EQ control (HPM)
    Send(CMD_UPGEQH_CTRL, sendtype::COMMAND);
    Send(0xE5, sendtype::DATA);
    Send(0xF6, sendtype::DATA);
    Send(0x05, sendtype::DATA);
    Send(0x46, sendtype::DATA);
    Send(0x77, sendtype::DATA);
    Send(0x77, sendtype::DATA);
    Send(0x77, sendtype::DATA);
    Send(0x77, sendtype::DATA);
    Send(0x76, sendtype::DATA);
    Send(0x45, sendtype::DATA);

    // Update period gate EQ control (LPM)
    Send(CMD_UPGEQL_CTRL, sendtype::COMMAND);
    Send(0x05, sendtype::DATA);
    Send(0x46, sendtype::DATA);
    Send(0x77, sendtype::DATA);
    Send(0x77, sendtype::DATA);
    Send(0x77, sendtype::DATA);
    Send(0x77, sendtype::DATA);
    Send(0x76, sendtype::DATA);
    Send(0x45, sendtype::DATA);

    // Source EQ enable
    Send(CMD_SOURCEEQ_EN, sendtype::COMMAND);
    Send(0x13, sendtype::DATA);

    // Gate line setting (must be done before sleep-out)
    Send(CMD_GATELINE_SET, sendtype::COMMAND);
    Send(0x78, sendtype::DATA); // 480 gate lines -> 480px height

    // Sleep out and delay
    Send(CMD_SLEEP_OUT, sendtype::COMMAND);
    HAL_Delay(120);

    // Source voltage select
    Send(CMD_VSHL_SEL, sendtype::COMMAND);
    Send(0x00, sendtype::DATA);

    // Memory Data Access Control (rotation, BGR)
    Send(CMD_MAD_CTRL, sendtype::COMMAND);
    // Use the same MAD value as the prototype so the pixel mapping matches
    Send(0x48, sendtype::DATA);

    // Data format select
    Send(CMD_DATAFMT_SEL, sendtype::COMMAND);
    Send(0x32, sendtype::DATA); //0x00110010b, 8 color

    // Gamma mode setting
    Send(CMD_GAMMAMODE_SET, sendtype::COMMAND);
    Send(0x00, sendtype::DATA); // 4GS Gray Scale

    // Panel setting
    Send(CMD_PANEL_SET, sendtype::COMMAND);
    Send(0x0A, sendtype::DATA);

    // TE (Tearing Effect) setting
    Send(CMD_TEAREFFECT_ON, sendtype::COMMAND);
    Send(0x00, sendtype::DATA);

    // Auto power down
    Send(CMD_AUTOPWR_CTRL, sendtype::COMMAND);
    Send(0xFF, sendtype::DATA);

    // High power on and display on
    Send(CMD_HIGHPWR_ON, sendtype::COMMAND);
    Send(CMD_DISPLAY_ON, sendtype::COMMAND); // Display ON
}

/**********************************************************/

void Set_Window()
{
    Send(CMD_COL_ADDR, sendtype::COMMAND);
    Send(ABS_XS, sendtype::DATA);
    Send(ABS_XE, sendtype::DATA);

    Send(CMD_ROW_ADDR, sendtype::COMMAND);
    Send(ABS_YS, sendtype::DATA);
    Send(ABS_YE, sendtype::DATA);

    Send(CMD_MEM_WRITE, sendtype::COMMAND);
}

void Fill_Black()
{
    Set_Window();
    unsigned int i;
    for (i = 0; i < (480*106); i++)
    {
        Send(0xff, sendtype::DATA);
    }
}
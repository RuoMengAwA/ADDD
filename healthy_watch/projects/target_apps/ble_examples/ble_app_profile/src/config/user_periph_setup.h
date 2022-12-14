/**
 ****************************************************************************************
 *
 * @file user_periph_setup.h
 *
 * @brief Peripherals setup header file.
 *
 * Copyright (C) 2015. Dialog Semiconductor Ltd, unpublished work. This computer
 * program includes Confidential, Proprietary Information and is a Trade Secret of
 * Dialog Semiconductor Ltd.  All use, disclosure, and/or reproduction is prohibited
 * unless authorized in writing. All Rights Reserved.
 *
 * <bluetooth.support@diasemi.com> and contributors.
 *
 ****************************************************************************************
 */

#ifndef _USER_PERIPH_SETUP_H_
#define _USER_PERIPH_SETUP_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"
#include "global_io.h"
#include "arch.h"
#include "da1458x_periph_setup.h"
#include "i2c_eeprom.h"

/*
 * DEFINES
 ****************************************************************************************
 */
//dgh add
#define LCD_CS_PORT    GPIO_PORT_0
#define LCD_CS_PIN     GPIO_PIN_2
#define LCD_CD_PORT    GPIO_PORT_2
#define LCD_CD_PIN     GPIO_PIN_0
#define LCD_RST_PORT   GPIO_PORT_0
#define LCD_RST_PIN    GPIO_PIN_4
#define backlight_pin		GPIO_PIN_5
#define backlight_port	GPIO_PORT_2
//motor
#define MOTOR_PORT     GPIO_PORT_0
#define MOTOR_PIN      GPIO_PIN_7
//spi
#define SPI_PORT     GPIO_PORT_0
#define SPI_PIN_CLK  GPIO_PIN_0
#define SPI_PIN_CS   GPIO_PIN_3
#define SPI_PIN_DI   GPIO_PIN_5
#define SPI_PIN_DO   GPIO_PIN_6
//button
#define BUTTON_PORT  GPIO_PORT_2
#define BUTTON_PIN1  GPIO_PIN_2
//stm32ldo
#define stm32_port GPIO_PORT_1
#define stm32_pin  GPIO_PIN_0
//adc
#define adc_port	GPIO_PORT_0
#define adc_pin 	GPIO_PIN_1
//st2378
#define st2378_port	GPIO_PORT_1
#define st2378_cl 	GPIO_PIN_2
#define st2378_da		GPIO_PIN_3
//uart
#define uart_port	GPIO_PORT_2
#define uart_tx		GPIO_PIN_8
#define uart_rx		GPIO_PIN_9

//Select shock pin
#define SHOCK_PORT GPIO_PORT_0
#define SHOCK_PIN GPIO_PIN_7


//*** <<< Use Configuration Wizard in Context Menu >>> ***

// <o> DK selection <0=> As in da1458x_periph_setup.h <1=> Basic <2=> Pro <3=> Expert
#define HW_CONFIG (2)

#define HW_CONFIG_BASIC_DK  ((HW_CONFIG==0 && SDK_CONFIG==1) || HW_CONFIG==1)
#define HW_CONFIG_PRO_DK    ((HW_CONFIG==0 && SDK_CONFIG==2) || HW_CONFIG==2)
#define HW_CONFIG_EXPERT_DK ((HW_CONFIG==0 && SDK_CONFIG==3) || HW_CONFIG==3)

//*** <<< end of configuration section >>>    ***

/****************************************************************************************/
/* i2c eeprom configuration                                                             */
/****************************************************************************************/

#define I2C_EEPROM_SIZE   0x20000         // EEPROM size in bytes
#define I2C_EEPROM_PAGE   256             // EEPROM's page size in bytes
#define I2C_SPEED_MODE    I2C_FAST        // 1: standard mode (100 kbits/s), 2: fast mode (400 kbits/s)
#define I2C_ADDRESS_MODE  I2C_7BIT_ADDR   // 0: 7-bit addressing, 1: 10-bit addressing
#define I2C_ADDRESS_SIZE  I2C_2BYTES_ADDR // 0: 8-bit memory address, 1: 16-bit memory address, 3: 24-bit memory address

/****************************************************************************************/
/* SPI FLASH configuration                                                              */
/****************************************************************************************/

#define SPI_FLASH_DEFAULT_SIZE  131072    // SPI Flash memory size in bytes
#define SPI_FLASH_DEFAULT_PAGE  256
#define SPI_SECTOR_SIZE         4096

#ifndef __DA14583__
    #define SPI_EN_GPIO_PORT    GPIO_PORT_0
    #define SPI_EN_GPIO_PIN     GPIO_PIN_3

    #define SPI_CLK_GPIO_PORT   GPIO_PORT_0
    #define SPI_CLK_GPIO_PIN    GPIO_PIN_0

    #define SPI_DO_GPIO_PORT    GPIO_PORT_0
    #define SPI_DO_GPIO_PIN     GPIO_PIN_6

    #define SPI_DI_GPIO_PORT    GPIO_PORT_0
    #define SPI_DI_GPIO_PIN     GPIO_PIN_5
#else // DA14583
    #define SPI_EN_GPIO_PORT    GPIO_PORT_2
    #define SPI_EN_GPIO_PIN     GPIO_PIN_3

    #define SPI_CLK_GPIO_PORT   GPIO_PORT_2
    #define SPI_CLK_GPIO_PIN    GPIO_PIN_0

    #define SPI_DO_GPIO_PORT    GPIO_PORT_2
    #define SPI_DO_GPIO_PIN     GPIO_PIN_9

    #define SPI_DI_GPIO_PORT    GPIO_PORT_2
    #define SPI_DI_GPIO_PIN     GPIO_PIN_4
#endif


/****************************************************************************************/
/* UART2 pin configuration (debug print console)                                        */
/****************************************************************************************/

#ifdef CFG_PRINTF_UART2
    #if HW_CONFIG_BASIC_DK
        #define UART2_TX_GPIO_PORT  GPIO_PORT_2
        #define UART2_TX_GPIO_PIN   GPIO_PIN_6

        #define UART2_RX_GPIO_PORT  GPIO_PORT_2
        #define UART2_RX_GPIO_PIN   GPIO_PIN_7

    #elif HW_CONFIG_PRO_DK
        #define UART2_TX_GPIO_PORT  GPIO_PORT_2
        #define UART2_TX_GPIO_PIN   GPIO_PIN_6

        #define UART2_RX_GPIO_PORT  GPIO_PORT_2
        #define UART2_RX_GPIO_PIN   GPIO_PIN_7

    #elif HW_CONFIG_EXPERT_DK
        #define UART2_TX_GPIO_PORT  GPIO_PORT_2
        #define UART2_TX_GPIO_PIN   GPIO_PIN_6

        #define UART2_RX_GPIO_PORT  GPIO_PORT_2
        #define UART2_RX_GPIO_PIN   GPIO_PIN_7

    #else // (e.g. HW_CONFIG_USB_DONGLE)
        #define UART2_TX_GPIO_PORT  GPIO_PORT_0
        #define UART2_TX_GPIO_PIN   GPIO_PIN_4

        #define UART2_RX_GPIO_PORT  GPIO_PORT_0
        #define UART2_RX_GPIO_PIN   GPIO_PIN_5

    #endif
#endif

/****************************************************************************************/
/* LED configuration                                                                    */
/****************************************************************************************/

#if HW_CONFIG_BASIC_DK
    #define GPIO_LED_PORT     GPIO_PORT_1
    #define GPIO_LED_PIN      GPIO_PIN_0

#elif HW_CONFIG_PRO_DK
    #define GPIO_LED_PORT     GPIO_PORT_1
    #define GPIO_LED_PIN      GPIO_PIN_0

#elif HW_CONFIG_EXPERT_DK
    #define GPIO_LED_PORT     GPIO_PORT_1
    #define GPIO_LED_PIN      GPIO_PIN_0

#else // (other configuration)
#endif

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Enable pad's and peripheral clocks assuming that peripherals' power domain
 * is down. The Uart and SPi clocks are set.
 * @return void
 ****************************************************************************************
 */
void periph_init(void);

/**
 ****************************************************************************************
 * @brief Map port pins. The Uart and SPI port pins and GPIO ports are mapped
 * @return void
 ****************************************************************************************
 */
void set_pad_functions(void);

/**
 ****************************************************************************************
 * @brief Each application reserves its own GPIOs here.
 * @return void
 ****************************************************************************************
 */
void GPIO_reservations(void);

#endif // _USER_PERIPH_SETUP_H_

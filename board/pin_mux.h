/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/*!
 * @brief Selects function mode (on-chip pull-up/pull-down resistor control).: Pull-up. Pull-up resistor enabled. */
#define PIO0_1_MODE_PULL_UP 0x02u
/*!
 * @brief Invert input: Input not inverted (HIGH on pin reads as 1; LOW on pin reads as 0). */
#define PIO0_21_INV_NOT_INVERTED 0x00u

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void); /* Function assigned for the Cortex-M0P */

#define IOCON_PIO_CLKDIV0 0x00u      /*!<@brief IOCONCLKDIV0 */
#define IOCON_PIO_HYS_EN 0x20u       /*!<@brief Enable hysteresis */
#define IOCON_PIO_INV_DI 0x00u       /*!<@brief Input not invert */
#define IOCON_PIO_MODE_PULLUP 0x10u  /*!<@brief Selects pull-up function */
#define IOCON_PIO_OD_DI 0x00u        /*!<@brief Disables Open-drain function */
#define IOCON_PIO_OD_EN 0x0400u      /*!<@brief Enables Open-drain function */
#define IOCON_PIO_SMODE_BYPASS 0x00u /*!<@brief Bypass input filter */

/*! @name PIO0_0 (number 48), D1/P0_0-GREEN
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITLEDSPINS_LED_GREEN_GPIO GPIO                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITLEDSPINS_LED_GREEN_GPIO_PIN_MASK (1U << 0U) /*!<@brief GPIO pin mask */
#define BOARD_INITLEDSPINS_LED_GREEN_PORT 0U                  /*!<@brief PORT device index: 0 */
#define BOARD_INITLEDSPINS_LED_GREEN_PIN 0U                   /*!<@brief PORT pin number */
#define BOARD_INITLEDSPINS_LED_GREEN_PIN_MASK (1U << 0U)      /*!<@brief PORT pin mask */
                                                              /* @} */

/*! @name PIO1_15 (number 24), D2/P3[44]/P1_15-BLUE
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITLEDSPINS_LED_BLUE_GPIO GPIO                 /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITLEDSPINS_LED_BLUE_GPIO_PIN_MASK (1U << 15U) /*!<@brief GPIO pin mask */
#define BOARD_INITLEDSPINS_LED_BLUE_PORT 1U                   /*!<@brief PORT device index: 1 */
#define BOARD_INITLEDSPINS_LED_BLUE_PIN 15U                   /*!<@brief PORT pin number */
#define BOARD_INITLEDSPINS_LED_BLUE_PIN_MASK (1U << 15U)      /*!<@brief PORT pin mask */
                                                              /* @} */

/*! @name PIO0_12 (number 4), ButtonRed
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITLEDSPINS_LED_RED_GPIO GPIO                 /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITLEDSPINS_LED_RED_GPIO_PIN_MASK (1U << 12U) /*!<@brief GPIO pin mask */
#define BOARD_INITLEDSPINS_LED_RED_PORT 0U                   /*!<@brief PORT device index: 0 */
#define BOARD_INITLEDSPINS_LED_RED_PIN 12U                   /*!<@brief PORT pin number */
#define BOARD_INITLEDSPINS_LED_RED_PIN_MASK (1U << 12U)      /*!<@brief PORT pin mask */
                                                             /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLEDsPins(void); /* Function assigned for the Cortex-M0P */

#define IOCON_PIO_CLKDIV0 0x00u      /*!<@brief IOCONCLKDIV0 */
#define IOCON_PIO_HYS_EN 0x20u       /*!<@brief Enable hysteresis */
#define IOCON_PIO_INV_DI 0x00u       /*!<@brief Input not invert */
#define IOCON_PIO_MODE_PULLUP 0x10u  /*!<@brief Selects pull-up function */
#define IOCON_PIO_OD_DI 0x00u        /*!<@brief Disables Open-drain function */
#define IOCON_PIO_SMODE_BYPASS 0x00u /*!<@brief Bypass input filter */

/*! @name PIO1_17 (number 37), P3[13]/P6[1]/U4[31]/TARGET_TX_DEBUG_P1_17
  @{ */
/*!
 * @brief PORT device index: 1 */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_TX_PORT 1U
/*!
 * @brief PORT pin number */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_TX_PIN 17U
/*!
 * @brief PORT pin mask */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_TX_PIN_MASK (1U << 17U)
/* @} */

/*! @name PIO1_16 (number 36), P7[1]/U4[32]/TARGET_RX_DEBUG_P1_16
  @{ */
/*!
 * @brief PORT device index: 1 */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_RX_PORT 1U
/*!
 * @brief PORT pin number */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_RX_PIN 16U
/*!
 * @brief PORT pin mask */
#define BOARD_INITDEBUG_UARTPINS_DEBUG_UART_RX_PIN_MASK (1U << 16U)
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitDEBUG_UARTPins(void); /* Function assigned for the Cortex-M0P */

#define IOCON_PIO_CLKDIV0 0x00u      /*!<@brief IOCONCLKDIV0 */
#define IOCON_PIO_HYS_EN 0x20u       /*!<@brief Enable hysteresis */
#define IOCON_PIO_INV_DI 0x00u       /*!<@brief Input not invert */
#define IOCON_PIO_MODE_PULLUP 0x10u  /*!<@brief Selects pull-up function */
#define IOCON_PIO_OD_DI 0x00u        /*!<@brief Disables Open-drain function */
#define IOCON_PIO_SMODE_BYPASS 0x00u /*!<@brief Bypass input filter */

/*! @name SWCLK (number 12), U4[16]/P4[4]/TARGET_SWCLK
  @{ */
/*!
 * @brief PORT device index: 0 */
#define BOARD_INITSWD_DEBUGPINS_DEBUG_SWD_SWCLK_PORT 0U
/*!
 * @brief PORT pin number */
#define BOARD_INITSWD_DEBUGPINS_DEBUG_SWD_SWCLK_PIN 3U
/*!
 * @brief PORT pin mask */
#define BOARD_INITSWD_DEBUGPINS_DEBUG_SWD_SWCLK_PIN_MASK (1U << 3U)
/* @} */

/*! @name SWDIO (number 14), U4[17]/P4[2]/TARGET_SWDIO
  @{ */
/*!
 * @brief PORT device index: 0 */
#define BOARD_INITSWD_DEBUGPINS_DEBUG_SWD_SWDIO_PORT 0U
/*!
 * @brief PORT pin number */
#define BOARD_INITSWD_DEBUGPINS_DEBUG_SWD_SWDIO_PIN 2U
/*!
 * @brief PORT pin mask */
#define BOARD_INITSWD_DEBUGPINS_DEBUG_SWD_SWDIO_PIN_MASK (1U << 2U)
/* @} */

/*! @name RESETN (number 5), P3[4]/J5[3]/U4[8]/P4[10]/SW3[1]/TARGET_nRESET-P0_5
  @{ */
/*!
 * @brief PORT device index: 0 */
#define BOARD_INITSWD_DEBUGPINS_DEBUG_SWD_RESETN_PORT 0U
/*!
 * @brief PORT pin number */
#define BOARD_INITSWD_DEBUGPINS_DEBUG_SWD_RESETN_PIN 5U
/*!
 * @brief PORT pin mask */
#define BOARD_INITSWD_DEBUGPINS_DEBUG_SWD_RESETN_PIN_MASK (1U << 5U)
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitSWD_DEBUGPins(void); /* Function assigned for the Cortex-M0P */

#define IOCON_PIO_CLKDIV0 0x00u      /*!<@brief IOCONCLKDIV0 */
#define IOCON_PIO_HYS_EN 0x20u       /*!<@brief Enable hysteresis */
#define IOCON_PIO_INV_DI 0x00u       /*!<@brief Input not invert */
#define IOCON_PIO_MODE_PULLUP 0x10u  /*!<@brief Selects pull-up function */
#define IOCON_PIO_OD_DI 0x00u        /*!<@brief Disables Open-drain function */
#define IOCON_PIO_SMODE_BYPASS 0x00u /*!<@brief Bypass input filter */

/*! @name PIO0_12 (number 4), ButtonRed
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITBUTTONSPINS_SW1_GPIO GPIO                 /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITBUTTONSPINS_SW1_GPIO_PIN_MASK (1U << 12U) /*!<@brief GPIO pin mask */
#define BOARD_INITBUTTONSPINS_SW1_PORT 0U                   /*!<@brief PORT device index: 0 */
#define BOARD_INITBUTTONSPINS_SW1_PIN 12U                   /*!<@brief PORT pin number */
#define BOARD_INITBUTTONSPINS_SW1_PIN_MASK (1U << 12U)      /*!<@brief PORT pin mask */
                                                            /* @} */

/*! @name PIO0_4 (number 6), P3[50]/SW2/P0_4-WAKEUP
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITBUTTONSPINS_SW2_GPIO GPIO                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITBUTTONSPINS_SW2_GPIO_PIN_MASK (1U << 4U) /*!<@brief GPIO pin mask */
#define BOARD_INITBUTTONSPINS_SW2_PORT 0U                  /*!<@brief PORT device index: 0 */
#define BOARD_INITBUTTONSPINS_SW2_PIN 4U                   /*!<@brief PORT pin number */
#define BOARD_INITBUTTONSPINS_SW2_PIN_MASK (1U << 4U)      /*!<@brief PORT pin mask */
                                                           /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitBUTTONsPins(void); /* Function assigned for the Cortex-M0P */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/

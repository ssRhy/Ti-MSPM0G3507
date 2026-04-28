/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     32000000



/* Defines for TB6612_PWM */
#define TB6612_PWM_INST                                                    TIMG0
#define TB6612_PWM_INST_IRQHandler                              TIMG0_IRQHandler
#define TB6612_PWM_INST_INT_IRQN                                (TIMG0_INT_IRQn)
#define TB6612_PWM_INST_CLK_FREQ                                        32000000
/* GPIO defines for channel 0 */
#define GPIO_TB6612_PWM_C0_PORT                                            GPIOA
#define GPIO_TB6612_PWM_C0_PIN                                    DL_GPIO_PIN_12
#define GPIO_TB6612_PWM_C0_IOMUX                                 (IOMUX_PINCM34)
#define GPIO_TB6612_PWM_C0_IOMUX_FUNC                IOMUX_PINCM34_PF_TIMG0_CCP0
#define GPIO_TB6612_PWM_C0_IDX                               DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_TB6612_PWM_C1_PORT                                            GPIOA
#define GPIO_TB6612_PWM_C1_PIN                                    DL_GPIO_PIN_13
#define GPIO_TB6612_PWM_C1_IOMUX                                 (IOMUX_PINCM35)
#define GPIO_TB6612_PWM_C1_IOMUX_FUNC                IOMUX_PINCM35_PF_TIMG0_CCP1
#define GPIO_TB6612_PWM_C1_IDX                               DL_TIMER_CC_1_INDEX




/* Defines for I2C_MPU6050 */
#define I2C_MPU6050_INST                                                    I2C0
#define I2C_MPU6050_INST_IRQHandler                              I2C0_IRQHandler
#define I2C_MPU6050_INST_INT_IRQN                                  I2C0_INT_IRQn
#define I2C_MPU6050_BUS_SPEED_HZ                                          400000
#define GPIO_I2C_MPU6050_SDA_PORT                                          GPIOA
#define GPIO_I2C_MPU6050_SDA_PIN                                  DL_GPIO_PIN_28
#define GPIO_I2C_MPU6050_IOMUX_SDA                                (IOMUX_PINCM3)
#define GPIO_I2C_MPU6050_IOMUX_SDA_FUNC                 IOMUX_PINCM3_PF_I2C0_SDA
#define GPIO_I2C_MPU6050_SCL_PORT                                          GPIOA
#define GPIO_I2C_MPU6050_SCL_PIN                                  DL_GPIO_PIN_31
#define GPIO_I2C_MPU6050_IOMUX_SCL                                (IOMUX_PINCM6)
#define GPIO_I2C_MPU6050_IOMUX_SCL_FUNC                 IOMUX_PINCM6_PF_I2C0_SCL


/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_FREQUENCY                                           32000000
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_32_MHZ_115200_BAUD                                      (17)
#define UART_0_FBRD_32_MHZ_115200_BAUD                                      (23)





/* Port definition for Pin Group GPIO_MPU6050 */
#define GPIO_MPU6050_PORT                                                (GPIOB)

/* Defines for MPU6050_INT: GPIOB.0 with pinCMx 12 on package pin 47 */
// groups represented: ["Encoder_PORT","GPIO_MPU6050"]
// pins affected: ["Encoder_A_PIN","Encoder_B_PIN","Encoder_C_PIN","Encoder_D_PIN","MPU6050_INT"]
#define GPIO_MULTIPLE_GPIOB_INT_IRQN                            (GPIOB_INT_IRQn)
#define GPIO_MULTIPLE_GPIOB_INT_IIDX            (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define GPIO_MPU6050_MPU6050_INT_IIDX                        (DL_GPIO_IIDX_DIO0)
#define GPIO_MPU6050_MPU6050_INT_PIN                             (DL_GPIO_PIN_0)
#define GPIO_MPU6050_MPU6050_INT_IOMUX                           (IOMUX_PINCM12)
/* Port definition for Pin Group TB6612_IO */
#define TB6612_IO_PORT                                                   (GPIOB)

/* Defines for AIN1: GPIOB.12 with pinCMx 29 on package pin 64 */
#define TB6612_IO_AIN1_PIN                                      (DL_GPIO_PIN_12)
#define TB6612_IO_AIN1_IOMUX                                     (IOMUX_PINCM29)
/* Defines for AIN2: GPIOB.13 with pinCMx 30 on package pin 1 */
#define TB6612_IO_AIN2_PIN                                      (DL_GPIO_PIN_13)
#define TB6612_IO_AIN2_IOMUX                                     (IOMUX_PINCM30)
/* Defines for BIN1: GPIOB.15 with pinCMx 32 on package pin 3 */
#define TB6612_IO_BIN1_PIN                                      (DL_GPIO_PIN_15)
#define TB6612_IO_BIN1_IOMUX                                     (IOMUX_PINCM32)
/* Defines for BIN2: GPIOB.16 with pinCMx 33 on package pin 4 */
#define TB6612_IO_BIN2_PIN                                      (DL_GPIO_PIN_16)
#define TB6612_IO_BIN2_IOMUX                                     (IOMUX_PINCM33)
/* Defines for HW_OUT_1: GPIOA.8 with pinCMx 19 on package pin 54 */
#define GRAPH_SENSOR_HW_OUT_1_PORT                                       (GPIOA)
#define GRAPH_SENSOR_HW_OUT_1_PIN                                (DL_GPIO_PIN_8)
#define GRAPH_SENSOR_HW_OUT_1_IOMUX                              (IOMUX_PINCM19)
/* Defines for HW_OUT_2: GPIOA.25 with pinCMx 55 on package pin 26 */
#define GRAPH_SENSOR_HW_OUT_2_PORT                                       (GPIOA)
#define GRAPH_SENSOR_HW_OUT_2_PIN                               (DL_GPIO_PIN_25)
#define GRAPH_SENSOR_HW_OUT_2_IOMUX                              (IOMUX_PINCM55)
/* Defines for HW_OUT_3: GPIOA.27 with pinCMx 60 on package pin 31 */
#define GRAPH_SENSOR_HW_OUT_3_PORT                                       (GPIOA)
#define GRAPH_SENSOR_HW_OUT_3_PIN                               (DL_GPIO_PIN_27)
#define GRAPH_SENSOR_HW_OUT_3_IOMUX                              (IOMUX_PINCM60)
/* Defines for HW_OUT_4: GPIOA.26 with pinCMx 59 on package pin 30 */
#define GRAPH_SENSOR_HW_OUT_4_PORT                                       (GPIOA)
#define GRAPH_SENSOR_HW_OUT_4_PIN                               (DL_GPIO_PIN_26)
#define GRAPH_SENSOR_HW_OUT_4_IOMUX                              (IOMUX_PINCM59)
/* Defines for HW_OUT_5: GPIOB.3 with pinCMx 16 on package pin 51 */
#define GRAPH_SENSOR_HW_OUT_5_PORT                                       (GPIOB)
#define GRAPH_SENSOR_HW_OUT_5_PIN                                (DL_GPIO_PIN_3)
#define GRAPH_SENSOR_HW_OUT_5_IOMUX                              (IOMUX_PINCM16)
/* Defines for HW_OUT_6: GPIOB.2 with pinCMx 15 on package pin 50 */
#define GRAPH_SENSOR_HW_OUT_6_PORT                                       (GPIOB)
#define GRAPH_SENSOR_HW_OUT_6_PIN                                (DL_GPIO_PIN_2)
#define GRAPH_SENSOR_HW_OUT_6_IOMUX                              (IOMUX_PINCM15)
/* Defines for HW_OUT_7: GPIOB.9 with pinCMx 26 on package pin 61 */
#define GRAPH_SENSOR_HW_OUT_7_PORT                                       (GPIOB)
#define GRAPH_SENSOR_HW_OUT_7_PIN                                (DL_GPIO_PIN_9)
#define GRAPH_SENSOR_HW_OUT_7_IOMUX                              (IOMUX_PINCM26)
/* Defines for HW_OUT_8: GPIOB.24 with pinCMx 52 on package pin 23 */
#define GRAPH_SENSOR_HW_OUT_8_PORT                                       (GPIOB)
#define GRAPH_SENSOR_HW_OUT_8_PIN                               (DL_GPIO_PIN_24)
#define GRAPH_SENSOR_HW_OUT_8_IOMUX                              (IOMUX_PINCM52)
/* Port definition for Pin Group Encoder_PORT */
#define Encoder_PORT_PORT                                                (GPIOB)

/* Defines for Encoder_A_PIN: GPIOB.17 with pinCMx 43 on package pin 14 */
#define Encoder_PORT_Encoder_A_PIN_IIDX                     (DL_GPIO_IIDX_DIO17)
#define Encoder_PORT_Encoder_A_PIN_PIN                          (DL_GPIO_PIN_17)
#define Encoder_PORT_Encoder_A_PIN_IOMUX                         (IOMUX_PINCM43)
/* Defines for Encoder_B_PIN: GPIOB.18 with pinCMx 44 on package pin 15 */
#define Encoder_PORT_Encoder_B_PIN_IIDX                     (DL_GPIO_IIDX_DIO18)
#define Encoder_PORT_Encoder_B_PIN_PIN                          (DL_GPIO_PIN_18)
#define Encoder_PORT_Encoder_B_PIN_IOMUX                         (IOMUX_PINCM44)
/* Defines for Encoder_C_PIN: GPIOB.20 with pinCMx 48 on package pin 19 */
#define Encoder_PORT_Encoder_C_PIN_IIDX                     (DL_GPIO_IIDX_DIO20)
#define Encoder_PORT_Encoder_C_PIN_PIN                          (DL_GPIO_PIN_20)
#define Encoder_PORT_Encoder_C_PIN_IOMUX                         (IOMUX_PINCM48)
/* Defines for Encoder_D_PIN: GPIOB.19 with pinCMx 45 on package pin 16 */
#define Encoder_PORT_Encoder_D_PIN_IIDX                     (DL_GPIO_IIDX_DIO19)
#define Encoder_PORT_Encoder_D_PIN_PIN                          (DL_GPIO_PIN_19)
#define Encoder_PORT_Encoder_D_PIN_IOMUX                         (IOMUX_PINCM45)




/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_TB6612_PWM_init(void);
void SYSCFG_DL_I2C_MPU6050_init(void);
void SYSCFG_DL_UART_0_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */

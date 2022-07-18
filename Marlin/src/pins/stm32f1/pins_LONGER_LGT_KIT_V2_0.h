/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * Longer3D LK1/LK2 & Alfawise U20/U30 (STM32F103VET6) board pin assignments
 */

#if NOT_TARGET(__STM32F1__, STM32F1xx)
  #error "Oops! Select a STM32F1 board in 'Tools > Board.'"
#elif HOTENDS > 1 || E_STEPPERS > 1
  #error "Longer3D only supports one hotend / E-stepper. Comment out this line to continue."
#elif HAS_FSMC_TFT
  #error "MKS Robin nano v2 doesn't support FSMC-based TFT displays."
#endif

#define BOARD_INFO_NAME "LGT_KIT_V2.0"

#define BOARD_NO_NATIVE_USB

// Avoid conflict with TIMER_SERVO when using the STM32 HAL
#define TEMP_TIMER                             5

//#define DISABLE_DEBUG                           //  We still want to debug with STLINK...
#define DISABLE_JTAG                              //  We free the jtag pins (PA15) but keep STLINK
                                                  //  Release PB4 (STEP_X_PIN) from JTAG NRST role.
//
// Limit Switches
//
#define X_STOP_PIN                           PE6   // pin 16
// #define X_MAX_PIN                           PE5   // pin 15 (Filament sensor on Alfawise setup)
#define Y_STOP_PIN                           PE4  // pin 9
// #define Y_MAX_PIN                           PE3  // pin 8 (Unused in stock Alfawise setup)
#define Z_STOP_PIN                           PE2   // pin 5 Standard Endstop or Z_Probe endstop function
// #define Z_MAX_PIN                           PE1   // pin 4 (Unused in stock Alfawise setup)
                                 // May be used for BLTouch Servo function on older variants (<= V08)
#define ONBOARD_ENDSTOPPULLUPS

//
// Filament Sensor
//
#ifndef FIL_RUNOUT_PIN
  #define FIL_RUNOUT_PIN                    PE5   // XMAX plug on PCB used as filament runout sensor on Alfawise boards (inverting true)
#endif

//
// Steppers
//
#define E0_ENABLE_PIN                       PE0   // pin 3
#define E0_STEP_PIN                         PB9   // pin 2
#define E0_DIR_PIN                          PB8//PE2   // pin 1

#define X_ENABLE_PIN                        PD4   // pin 91
#define X_STEP_PIN                          PD3   // pin 90
#define X_DIR_PIN                           PD2//PB3   // pin 89

#define Y_ENABLE_PIN                        PD7   // pin 95
#define Y_STEP_PIN                          PD6//PB7   // pin 93
#define Y_DIR_PIN                           PD5//PB6   // pin 92

#define Z_ENABLE_PIN                        PB5   // pin 98
#define Z_STEP_PIN                          PB4//PE0   // pin 97
#define Z_DIR_PIN                           PB3//PB9   // pin 96



//
// Temperature Sensors
//
#define TEMP_0_PIN                          PC1   // pin 23 (Nozzle 100K/3950 thermistor)
#define TEMP_BED_PIN                        PC0   // pin 24 (Hot Bed 100K/3950 thermistor)

//
// Heaters / Fans
//
#define HEATER_0_PIN                        PA7//PD3   // pin 84 (Nozzle Heat Mosfet)
#define HEATER_BED_PIN                      PA0//PA8   // pin 67 (Hot Bed Mosfet)

#define FAN_PIN                             PA1//PA15  // pin 77 (4cm Fan)
#define FAN_SOFT_PWM                              // Required to avoid issues with heating or STLink
#define FAN_MIN_PWM 35                            // Fan will not start in 1-30 range
#define FAN_MAX_PWM 255

//#define BEEPER_PIN                        PD13  // pin 60 (Servo PWM output 5V/GND on Board V0G+) made for BL-Touch sensor
                                 // Can drive a PC Buzzer, if connected between PWM and 5V pins

#define LED_PIN                             PD0//PC2   // pin 17

//
// PWM for a servo probe
// Other servo devices are not supported on this board!
//
#if HAS_Z_SERVO_PROBE
  #define SERVO0_PIN                        PA8//PD13  // Open drain PWM pin on the V0G (GND or floating 5V)
  // #define SERVO0_PWM_OD                           // Comment this if using PE5

  //#define SERVO0_PIN                      PE5   // Pulled up PWM pin on the V08 (3.3V or 0)
  //#undef Z_MAX_PIN                              // Uncomment if using ZMAX connector (PE5)
#endif


//
// Persistent Storage
// If no option is selected below the SD Card will be used
// I2C BUG with maple core
#if EITHER(NO_EEPROM_SELECTED, I2C_EEPROM)
  #define I2C_EEPROM
  #define MARLIN_EEPROM_SIZE 0x3FFF                            // AT24C16C 16KB
#endif

//#define FLASH_EEPROM_EMULATION
//#define SDCARD_EEPROM_EMULATION

#if ENABLED(FLASH_EEPROM_EMULATION)
  #define EEPROM_PAGE_SIZE     (0x800U)           // 2KB
  #define EEPROM_START_ADDRESS (0x8000000UL + (STM32_FLASH_SIZE) * 1024UL - (EEPROM_PAGE_SIZE) * 2UL)
  #define MARLIN_EEPROM_SIZE (EEPROM_PAGE_SIZE)
#endif

//
// SD Card
//
#ifndef SDCARD_CONNECTION
  #define SDCARD_CONNECTION              ONBOARD
#endif

#if SD_CONNECTION_IS(ONBOARD)
  #define SPI_DEVICE                             2
  // #define ENABLE_SPI2
  #define SD_DETECT_PIN                       PB11//PC10
  #define SCK_PIN                             PB13
  #define MISO_PIN                            PB14
  #define MOSI_PIN                            PB15
  #define SS_PIN                              PB12//PA15
#endif
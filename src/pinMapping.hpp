/**
 * @file pinMapping.hpp
 * @author Alexander Tonn (tonn@jumag.de)
 * @brief Global declaration of all pins
 * @version 1.0
 * @date 2024-07-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef PINMAPPING_HPP
#define PINMAPPING_HPP

#include <Arduino.h>


constexpr static  uint8_t EXT_FWT_FILL_REQUEST PROGMEM = 22; // Digital Input
constexpr static  uint8_t BUFFER_TANK_FILL_START PROGMEM = 23;// Digital Input
constexpr static  uint8_t BUFFER_TANK_FILL_STOP PROGMEM = 24;// Digital Input
constexpr static  uint8_t HARDNESS_TO_HIGH PROGMEM = 25;// Digital Input
constexpr static  uint8_t START_STOP PROGMEM = 26;// Digital Input
constexpr static  uint8_t CONDUCTIVITY_TO_HIGH PROGMEM = 27;// Digital Input
constexpr static uint8_t  FRESHWATER_PUMP_PROTECTION PROGMEM = 28; // Digital Input
constexpr static uint8_t  BUFFER_PUMP_PROTECTION PROGMEM = 29; // Digital Input

constexpr static  uint8_t SV_FRESHWATER PROGMEM = 5; // Digital Output
constexpr static  uint8_t SV_CONCENTRATE PROGMEM = 6; // Digital Output
constexpr static  uint8_t SV_BACKFLOW PROGMEM = 2; // Digital Output
constexpr static  uint8_t FRESHWATER_PUMP PROGMEM = 3; // Digital Output
constexpr static  uint8_t BUFFER_PUMP PROGMEM = 4; // Digital Output

constexpr static  uint8_t LED_PLANT_OPERATIONAL PROGMEM = 10; // Digital Output
constexpr static  uint8_t LED_ERR_H3 PROGMEM = 11; // Digital Output
constexpr static  uint8_t LED_ERR_P_BUFFER PROGMEM = 12; // Digital Output
constexpr static  uint8_t LED_ERR_H2 PROGMEM= 13; // Digital Output
constexpr static  uint8_t LED_ERR_BUFFER PROGMEM = 14; // Digital Output
constexpr static  uint8_t ERR_COLLECTIVE PROGMEM = 15; // Digital Output

constexpr static  uint8_t P_FRESHWATER PROGMEM = A0; // Analog Input - 0-5V
constexpr static  uint8_t P_MEMBRANE_SECUNDARY PROGMEM = A1; // Analog Input - 0-5V

constexpr static  uint8_t CONDUCTIVITY PROGMEM = A8; // Analog Input - 4-20mA
constexpr static  uint8_t TEMPERATURE PROGMEM = A9; // Analog Input - 4-20mA

constexpr static  uint8_t SPI_CS PROGMEM = 53; // SPI Bus Pin | SPI chip select / Slave Select
constexpr static  uint8_t SPI_COPI PROGMEM = 51; // SPI Bus Pin | SPI MOSI
constexpr static  uint8_t SPI_SCK PROGMEM = 52; // SPI Bus Pin
constexpr static  uint8_t SPI_CIPO PROGMEM = 50; // SPI Bus Pin | SPI MISO

#endif // PINMAPPING_HPP
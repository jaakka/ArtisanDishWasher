#ifndef PINOUT_H
#define PINOUT_H

#include <Arduino.h>

// Releet
#define VALVE_RELAY_PIN 6
#define PUMPOUT_RELAY_PIN 5
#define PUMPWASH_RELAY_PIN 7
#define HEATER_RELAY_PIN 4
#define SOAPDOOR_RELAY_PIN 13
#define POWERCONTROL_RELAY_PIN 9

// Anturit
#define DOOR_SENSOR_PIN A2
#define FLOOD_SENSOR_PIN A4
#define OVERHEAT_SENSOR_PIN A3
#define LEVEL_SENSOR_PIN A5
#define TEMP_SENSOR_PIN 12
#define DIGITAL_QUALITITY_SENSOR_PIN A0
#define QUALITY_SENSOR_PIN A1

// Enkooderi
#define ENCODER_RIGHT_PIN 3
#define ENCODER_LEFT_PIN 2
#define ENCODER_BUTTON_PIN A6

// WLAN-yhteys
#define WLAN_RX 10
#define WLAN_TX 11

// LCD-näyttö
#define LCD_RX 10 // this can be same than wlan because lcd not use
#define LCD_TX 8

#endif
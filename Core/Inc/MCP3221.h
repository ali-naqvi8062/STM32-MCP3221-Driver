/*
 * MCP3221.h
 *
 *	MCP3221 ADC I2C Driver
 *
 *  Created on: Nov 13, 2024
 *  Author: Ali Naqvi
 */

#ifndef MCP3221_I2C_DRIVER_H
#define MCP3221_I2C_DRIVER_H

#include "stm32f1xx_hal.h" 							// hardware abstraction for i2c

#define MCP3221_DEVICE_ID		0x4D 				// According to VIPER backplane schematic

#define MCP3221_RESOLUTION  	4096     			// 12-bit resolution
#define MCP3221_I2C_TIMEOUT 	HAL_MAX_DELAY
#define MCP3221_VREF_MV         3000				// in mV (is 3V according to VIPER backplane)

typedef enum {
    MCP3221_SMOOTHING_NONE = 0,
    MCP3221_SMOOTHING_EMA,
    MCP3221_SMOOTHING_ROLLING_AVG
} MCP3221_Smoothing;

// define constructor
typedef struct {
    I2C_HandleTypeDef *hi2c;  						// Pointer to the I2C handle
    uint8_t devAddr; 								// I2C address of the MCP3221 (7-bit address)
    MCP3221_SmoothingMethod smoothingMethod;
    uint16_t alpha;           						// For exponential moving average (1-256)
    uint8_t numSamples;       						// Number of samples for rolling average
    uint16_t samples[20];     						// Sample buffer for rolling average
    uint16_t emAvg;
} MCP3221;

HAL_StatusTypeDef MCP3221_Init(MCP3221 *dev, I2C_HandleTypeDef *hi2c, uint8_t devAddr);

HAL_StatusTypeDef MCP3221_Ping(MCP3221 *dev); 		// error handling

//HAL_StatusTypeDef MCP3221_ReadRawData(MCP3221 *dev, uint16_t *rawData);

#endif


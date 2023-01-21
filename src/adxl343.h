#ifndef ADXL343_H
#define ADXL343_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdint.h>


/* SDO - 0 --> 0x1D, SDO - 1 --> 0x53 (pg 16)*/
#define ADXL343_ADDRESS  0x53  //SDO pin grounded

#define ADXL343_DEVID 0xE5 //ADXL343 device ID

 
//ADXL343 register definitions (pg 22)
#define  ADXL343_REG_DEVID  0x00 
#define ADXL343_REG_THRESH_TAP 0x1D
#define ADXL343_REG_OFSX 0x1E
#define ADXL343_REG_OFSY 0x1F
#define ADXL343_REG_OFSZ 0x20
#define ADXL343_REG_DUR 0x21
#define ADXL343_REG_LATENT 0x22
#define ADXL343_REG_WINDOW 0x23
#define ADXL343_REG_THRESH_ACT 0x24
#define ADXL343_REG_THRESH_INACT 0x25
#define ADXL343_REG_TIME_INACT 0x26
#define ADXL343_REG_ACT_INACT_CTL 0x27
#define ADXL343_REG_THRESH_FF 0x28
#define ADXL343_REG_TIME_FF 0x29
#define ADXL343_REG_TAP_AXES 0x2A
#define ADXL343_REG_ACT_TAP_STATUS 0x2B
#define ADXL343_REG_BW_RATE 0x2C
#define ADXL343_REG_POWER_CTL 0x2D
#define ADXL343_REG_INT_ENABLE 0x2E
#define ADXL343_REG_INT_MAP 0x2F
#define ADXL343_REG_INT_SOURCE 0x30
#define ADXL343_REG_DATA_FORMAT 0x31
#define ADXL343_REG_DATA_X0 0x32
#define ADXL343_REG_DATA_X1 0x33
#define ADXL343_REG_DATA_Y0 0x34
#define ADXL343_REG_DATA_Y1 0x35
#define ADXL343_REG_DATA_Z0 0x36
#define ADXL343_REG_DATA_Z1 0x37
#define ADXL343_REG_FIFO_CTL 0x38
#define ADXL343_REG_DATA_STATUS 0x39

typedef enum {
    ADXL_INIT_SUCCESS,
    ADXL_INIT_FAIL
} adxl_status;

/*
SENSOR STRUCT
*/

typedef struct {
    /* i2c port */
    i2c_inst_t *i2c;

    /*Acceleration data (X,Y,Z)*/
    float acc[3];

} ADXL343;

/*
INITIALISATION
*/

 int ADXL343_Initialise(ADXL343 *dev, i2c_inst_t *i2c);


/*
DATA READING
*/
int ADXL343_ReadAccelerations(ADXL343 *dev);

/*
LOW LEVEL FUNCTIONS
*/
void ADXL343_ReadRegisters(ADXL343 *dev, const uint8_t reg, const uint8_t addr, uint8_t *data_buff, const uint8_t num_bytes);

enum pico_error_codes ADXL343_WriteRegister(ADXL343 *dev, const uint8_t reg, const uint8_t addr, uint8_t *data_buff, const uint8_t num_bytes);


#endif
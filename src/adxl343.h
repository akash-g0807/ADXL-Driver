#ifndef ADXL343_H
#define ADXL343_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdint.h>


static const float SENSITIVITY_2G = 1.0 / 256;  // (g/LSB)
static const float EARTH_GRAVITY = 9.80665;     // Earth's gravity in [m/s^2]

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

typedef uint8_t (*read_Data)(i2c_inst_t*, const uint8_t, const uint8_t, uint8_t*, const uint8_t);
typedef void (*write_Data)(i2c_inst_t*, const uint8_t, const uint8_t, uint8_t*, const uint8_t);


typedef struct adxl{

    /* i2c port */
    i2c_inst_t *i2c;

    /*Acceleration data (X,Y,Z)*/
    float acc[3];

    read_Data read_ADXL_Data;

    write_Data write_ADXL_Data;


} ADXL;

/*
INITIALISATION
*/

uint8_t ADXL343_Initialise(ADXL *dev, i2c_inst_t *i2c, uint8_t sda_pin, uint8_t scl_pin);


/*
DATA READING
*/
int ADXL343_ReadAccelerations(ADXL *dev);

/*
LOW LEVEL FUNCTIONS
*/
uint8_t ADXL343_ReadRegisters(i2c_inst_t* i2c, const uint8_t reg, const uint8_t addr, uint8_t *data_buff, const uint8_t num_bytes);

void ADXL343_WriteRegister(i2c_inst_t* i2c, const uint8_t reg, const uint8_t addr, uint8_t *data_buff, const uint8_t num_bytes);


#endif
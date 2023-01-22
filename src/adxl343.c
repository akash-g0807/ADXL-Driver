#include "adxl343.h"
#include <stdio.h>
 

 uint8_t ADXL343_ReadRegisters(ADXL343 *dev, const uint8_t reg, const uint8_t addr, uint8_t *data_buff, const uint8_t num_bytes){
     i2c_write_blocking(dev->i2c, addr, &reg, 1, true);  
     uint8_t num_bytes_read = i2c_read_blocking(dev->i2c, addr, data_buff, num_bytes, false);
     return num_bytes_read;

}

void ADXL343_WriteRegister(ADXL343 *dev, const uint8_t reg, const uint8_t addr, uint8_t *data_buff, const uint8_t num_bytes){
    uint8_t data[num_bytes + 1];

    data[0] = reg;
    for (int i = 0; i < num_bytes; i++) {
        data[i + 1] = data_buff[i];
    }

    i2c_write_blocking(dev->i2c, addr, data, (num_bytes + 1), false);

}


 int  ADXL343_Initialise(ADXL343 *dev, i2c_inst_t *i2c, uint8_t sda_pin, uint8_t scl_pin){

    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
     
    gpio_pull_up(sda_pin);
    gpio_pull_up(scl_pin);

    /* Setting sensor struct parameters*/
    dev->i2c = i2c;

    dev->acc[0] = 0.00f;
    dev->acc[1] = 0.00f;
    dev->acc[2] = 0.00f;
    sleep_ms(1000);
    
    uint8_t chipID[1];
    uint8_t read = ADXL343_ReadRegisters(dev,ADXL343_REG_DEVID,ADXL343_ADDRESS,chipID,1);


    uint8_t msg[1];
    msg[0] = 0x08;   // Setting measure but high

    uint8_t return_data[1];

    ADXL343_WriteRegister(dev, ADXL343_REG_POWER_CTL, ADXL343_ADDRESS, msg, 1);

    uint8_t return_value = ADXL343_ReadRegisters(dev,ADXL343_REG_POWER_CTL,ADXL343_ADDRESS,return_data,1);

    // while(true){
    //     printf("CHIP_ID: 0x%X\n", chipID[0]);   
    //     sleep_ms(1000);
    // 	printf("POWER_CTL_REG: 0x%X\n", return_data[0]);
    // }


    if(chipID[0] == ADXL343_DEVID){
        return 1;
    }      


    return 0;
}

int ADXL343_ReadAccelerations(ADXL343 *dev){
    uint8_t regData[6];

    uint8_t bytes_read = ADXL343_ReadRegisters(dev, ADXL343_REG_DATA_X0, ADXL343_ADDRESS ,regData, 6);
    

    int16_t acc_x = (int16_t)((regData[1] << 8) | regData[0]);
    int16_t acc_y = (int16_t)((regData[3] << 8) | regData[2]);
    int16_t acc_z = (int16_t)((regData[5] << 8) | regData[4]);

    dev->acc[0] = acc_x * SENSITIVITY_2G * EARTH_GRAVITY;
    dev->acc[1] = acc_y * SENSITIVITY_2G * EARTH_GRAVITY;
    dev->acc[2] = acc_z * SENSITIVITY_2G * EARTH_GRAVITY;

    return bytes_read;

}


int main() {

    stdio_init_all();
 
    const uint8_t sda_pin = 16;
    const uint8_t scl_pin = 17;

    //Initialize I2C port at 400 kHz
    i2c_init(i2c0, 400 * 1000);
 

    ADXL343 sensor1;

    int status = ADXL343_Initialise(&sensor1,i2c0, sda_pin, scl_pin);


    while (status){
        printf("Connected Properly\n");

        int read = ADXL343_ReadAccelerations(&sensor1);

        printf("%d\n", read);
        printf("X: %.2f | Y: %.2f | Z: %.2f\r\n", sensor1.acc[0], sensor1.acc[1], sensor1.acc[2]);
        
        
        
        sleep_ms(1000);

    }

    while(!status){
        printf("Haiiyyyaaaa");
    }

    return 0;
} 


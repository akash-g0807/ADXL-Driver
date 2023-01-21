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



 int  ADXL343_Initialise(ADXL343 *dev, i2c_inst_t *i2c){

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

    while(true){
        printf("Chip_ID: 0x%X\n", chipID[0]);   
        sleep_ms(1000);
    	printf("POWER_CTL_REG: 0x%X\n", return_data[0]);
    }


    if(chipID[0] == ADXL343_DEVID){
        return 1;
    }      


    return 0;
}




int main() {

    stdio_init_all();
 
    const uint sda_pin = 16;
    const uint scl_pin = 17;

    //Initialize I2C port at 400 kHz
    i2c_init(i2c0, 400 * 1000);


    // Initialize I2C pins
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
     
    gpio_pull_up(sda_pin);
    gpio_pull_up(scl_pin);
 

    ADXL343 sensor1;

    int status = ADXL343_Initialise(&sensor1,i2c0);


    while (status){
        printf("Connected Properly\n");
    }

    while(!status){
        printf("Haiiyyyaaaa");
    }

    return 0;
} 

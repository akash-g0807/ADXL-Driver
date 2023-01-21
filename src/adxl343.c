#include "adxl343.h"
#include <stdio.h>
 

 int  ADXL343_Initialise(ADXL343 *dev, i2c_inst_t *i2c){

    /* Setting sensor struct parameters*/
    dev->i2c = i2c;

    dev->acc[0] = 0.00f;
    dev->acc[0] = 0.00f;
    dev->acc[0] = 0.00f;

    sleep_ms(1000);
    uint8_t chipID[1];
    i2c_write_blocking(i2c, ADXL343_ADDRESS, ADXL343_REG_DEVID, 1, true);
    i2c_read_blocking(i2c, ADXL343_ADDRESS, chipID, 1, false);

    while(true){
    	printf("%X\n", chipID[0]);    
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

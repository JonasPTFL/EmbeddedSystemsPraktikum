#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include "encoding.h"
#include "platform.h"
#include "wrap.h"
#include "startup.h"

LIGHT_SENSOR_H

void i2c_init()
{
	// set up gpio pins to i2c use
	GPIO_REG(GPIO_IOF_SEL) &= ~((1 << IOF_I2C_SCL) | (1 << IOF_I2C_SDA));
	GPIO_REG(GPIO_IOF_EN)  |= ((1 << IOF_I2C_SCL) | (1 << IOF_I2C_SDA));

	// prescaler to 100 kHz
	I2C_REG(I2C0_CONTROL) &= ~(1 << I2C_CTRL_EN);
	I2C_REG(I2C0_PRESCALE_HIGH) = 0x00;
	I2C_REG(I2C0_PRESCALE_LOW) = 0x1F; // = 100kHz
	I2C_REG(I2C0_CONTROL) |= (1 << I2C_CTRL_EN);

}

void i2c_wait_response(){
	// no operation loop until 
    while ((I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_TIP)) > 0U) {
    }
}

uint_t i2c_read(uint_t i2c_address, uint_t analog_channel)
{
	// initialize the read process
	I2C_REG(I2C0_TRANSMIT) = 0;
    I2C_REG(I2C0_COMMAND)  = (1 << I2C_CMD_STA);
    
	i2c_wait_response();
	if ( (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_RXACK)))
	return 0;

	// enabled write mode for reading 
	I2C_REG(I2C0_TRANSMIT) = i2c_address | 0x0;
    I2C_REG(I2C0_COMMAND)  = (1 << I2C_CMD_WR);
    
	i2c_wait_response();

	// write the control byte into the channel while in write mode 
	I2C_REG(I2C0_TRANSMIT) = analog_channel;
    I2C_REG(I2C0_COMMAND)  = (1 << I2C_CMD_WR);
    
	i2c_wait_response();

	// send read request to i2c address
    I2C_REG(I2C0_TRANSMIT) = i2c_address | 0x1;
    I2C_REG(I2C0_COMMAND)  = (1 << I2C_CMD_STA) | (1 << I2C_CMD_WR);
    
	i2c_wait_response();

	// read and skip the first read byte, because the real data is 
	// contained in secod byte as described in the data sheet 
    I2C_REG(I2C0_TRANSMIT) = 0;
    I2C_REG(I2C0_COMMAND)  = (1 << I2C_CMD_RD);
    
	i2c_wait_response();

	// read the light sensor data byte, after skipping the first byte
    I2C_REG(I2C0_TRANSMIT) = 0;
    I2C_REG(I2C0_COMMAND)  = (1 << I2C_CMD_RD);
    
	i2c_wait_response();

    uint_t sensor_data = I2C_REG(I2C0_RECEIVE);

	// send acknowledge to the sensor and finish read process
    I2C_REG(I2C0_TRANSMIT) = 0;
    I2C_REG(I2C0_COMMAND)  = (1 << I2C_CMD_ACK);
    
	i2c_wait_response();

    return sensor_data;
}

uint_t read_light_sensor(){
	// read data from analog pin 0 and i2c address 0x90 (144)
	// as described in the data sheet of the sensor
	uint_t brightness = i2c_read(0x90, 0); 
	return brightness;
}

#endif
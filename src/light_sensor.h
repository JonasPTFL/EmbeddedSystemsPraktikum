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

uint_t i2c_read(uint_t f_addr)
{
	// write address
	I2C_REG(I2C0_TRANSMIT) = (I2C_SL_ADDR << 1);
	I2C_REG(I2C0_COMMAND) = (1 << I2C_CMD_STA) | (1 << I2C_CMD_WR);

	// wait
	while (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_TIP));
	if ( (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_RXACK)))
		return 0;

	// write reg addr
	I2C_REG(I2C0_TRANSMIT) = f_addr;
	I2C_REG(I2C0_COMMAND) = (1 << I2C_CMD_WR) | (1 << I2C_CMD_STO);

	// wait
	while (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_TIP));
	if ( (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_RXACK)))
		return 0;

	// send read request
	I2C_REG(I2C0_TRANSMIT) = (I2C_SL_ADDR << 1) | 0x1;
	I2C_REG(I2C0_COMMAND) = (1 << I2C_CMD_STA) | (1 << I2C_CMD_WR);

	// wait
	while (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_TIP));

	// read, ack and end
	I2C_REG(I2C0_COMMAND) = (1 << I2C_CMD_RD ) | ( 1 << I2C_CMD_ACK) | (1 << I2C_CMD_STO);

	// wait
	while (I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_TIP));

	uint_t rx = 0;
	rx = I2C_REG(I2C0_RECEIVE);

	return (uint_t)(rx & 0xff);
}

void i2c_transmit(uint32_t transmit, uint32_t command)
{
    I2C_REG(I2C0_TRANSMIT) = transmit;
    I2C_REG(I2C0_COMMAND)  = command;
    
    while ((I2C_REG(I2C0_STATUS) & (1 << I2C_STAT_TIP)) > 0U) {
    }
}

uint8_t pcf8591_read(const uint_t f_address, const uint_t channel)
{
    i2c_transmit(0, (1 << I2C_CMD_STA));
    i2c_transmit(f_address | 0, (1 << I2C_CMD_WR));
    i2c_transmit(channel, (1 << I2C_CMD_WR));
    i2c_transmit(f_address | 1, (1 << I2C_CMD_STA) | (1 << I2C_CMD_WR));
    i2c_transmit(0, (1 << I2C_CMD_RD));
    i2c_transmit(0, (1 << I2C_CMD_RD));
    uint32_t result = I2C_REG(I2C0_RECEIVE);
    i2c_transmit(0, (1 << I2C_CMD_ACK));

    return result;
}

uint_t read_light_sensor(){
	uint_t brightness = pcf8591_read(0x90, 0); 
	return brightness;
}

#endif
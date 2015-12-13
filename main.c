//
// BeagleboneBlack I2C Demo Program
//
// mixed C & assembly 
// demonstrates I2C operation in poll mode 
// also UART0 and GPIO
// requires Compass Module HMC5883l from Sparkfun (a cheap, documented I2C device)
// built with GNU tools :) on platform Win32 :(
//
// BBB-I2C driver hacked from Nick Kondrashov, github.com/spbnick.  Nice work!  
//
// provide feedback at www.baremetal.tech
//
#include <stdio.h>
#include <stdint.h>

#include "main.h"

uint32_t main() {
  uint32_t i=0, pins;
  uint16_t x, y, z;
  char buf[32];

  pins = 0xf << 21;  // enab USR LEDs, pins 21-24
  gpio_init(SOC_GPIO_1_REGS, pins);
  uart0_init(consoleUART);      // pinmux unnecessary for UART0 
  uart_tx(consoleUART, 0x0A);   // print n! in poll mode
  uart_tx(consoleUART, 0x6E);
  uart_tx(consoleUART, 0x21);
  uart_tx(consoleUART, 0x0A);

  poke(SOC_CM_PER_REGS, CM_PER_I2C1_CLKCTRL, 0x2);  // I2C1 module clock ENAB
  pinmux(CONF_I2C1_SDA, 0x72);  // Slow slew, receiver enabled, PullUp, MUXmode 2
  pinmux(CONF_I2C1_SCL, 0x72);  // was 0X62, spruh73l 9.2.2

  i2c_init(SOC_I2C_1_REGS);

  i2c_write(SOC_I2C_1_REGS, 0x1e0000, 0x70);  // 0x1e is the Compass Module address
  i2c_write(SOC_I2C_1_REGS, 0x1e0001, 0xa0);  // reg values per HMC5883L-FDS.pdf p18
  i2c_write(SOC_I2C_1_REGS, 0x1e0002, 0x00);
  while (i < 6000000) i++;  // kill 6 msec

  while (1) {
    uart0_rbuf=uart_rx(consoleUART);
    if(uart0_rbuf >= 0x20) {  // ASCII char received => take a compass reading
      uart0_rbuf=0x0;
      gpio_on(SOC_GPIO_1_REGS, pins);  // flash LEDs
      i2c_read(SOC_I2C_1_REGS, 0x1e0000, (uint32_t)buf, 0xd);  // read all 13 registers
//      for (i = 0; i <= 12; i++) hexprint(buf[i]);  // print all 13 registers
      x = (buf[3] <<8) | buf[4];
      hexprint(x);
      y = (buf[5] <<8) | buf[6];
      hexprint(y);
      z = (buf[7] <<8) | buf[8];
      hexprint(z);
      uart_tx(consoleUART, 0x0A);
      gpio_off(SOC_GPIO_1_REGS, pins);
    }
  }
}

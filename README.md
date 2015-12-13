# BBB_I2C
Beaglebone I2C program, all bare metal

README  Beaglebone Black  I2C Demo Program

Main prog written in C and drivers/runtime services in GNU-Assembly.  
Makefile & loadscript provided for GCC :) in Win32 :(  I use the XDS100V2 jtag 
to load programs.  It is more work up front, but much easier in the long run
and it is cheap, $70.  You can also boot from SDcard, see the makefile.  

It is all there in very concise format, documentation is within the code.  
So it should be easy for noobs to understand/test/hack/mod for your next 
BBB bare metal project requiring I2C communication.  Suitable for embedded jobs.  

It requires Compass Module HMC5883l from Sparkfun, a cheap, documented I2C device.  
Sparkfun.com also has I2C documentation & a tutorial.
The compass outputs magnetic field strength in the x-y-z directions.  
The actual 2-D compass heading is calculated with atan2().  This requires 
importing some GNU math libs that I have not figured out yet.  Ditto stdlib stuff.

I stripped out all the unnecessary IRQ stuff.  The IRQ version is coming.

I included a MMC-bootable file you may test: rts.bin

Many thanks to Nick Kondrashov, who initially got the I2C module up and running!  
See his work at www.github.com/spbnick. 

You can provide feedback at www.baremetal.tech  

//
// BeagleboneBlack I2C Demo Program - main header file
//
#define SOC_CM_PER_REGS            0x44E00000
#define SOC_GPIO_1_REGS            0x4804c000
#define SOC_UART_0_REGS            0x44E09000
#define CONF_UART_0_RXD            0x970
#define CONF_UART_0_TXD            0x974

#define SOC_I2C_0_REGS             0x44E0B000
#define SOC_I2C_1_REGS             0x4802A000
#define SOC_I2C_2_REGS             0x4819C000
#define CONF_I2C1_SDA              0x958
#define CONF_I2C1_SCL              0x95c
#define CM_PER_I2C1_CLKCTRL        0x48

extern uint32_t uart0_init(uint32_t uart_base_addr);
extern uint32_t uart_rx(uint32_t uart_base_addr);
extern void uart_tx(uint32_t uart_base_addr, uint32_t byte);
extern void uart_txi(uint32_t uart_base_addr);
extern void pinmux(uint32_t pin, uint32_t val);
extern void hexprint(uint32_t word);

extern uint32_t gpio_init(uint32_t gpio_base_addr, uint32_t gpio_pins);
extern void gpio_on(uint32_t gpio_base_addr, uint32_t gpio_pins);
extern void gpio_off(uint32_t gpio_base_addr, uint32_t gpio_pins);
extern void blink32(uint32_t data);

extern uint32_t i2c_init(uint32_t i2c_base_addr);
extern uint32_t i2c_read(uint32_t base_addr, uint32_t slave_addr, uint32_t buf_ptr, uint32_t len);
extern uint32_t i2c_write(uint32_t base_addr, uint32_t slave_addr, uint32_t data);
extern void poke(uint32_t base_addr, uint32_t offset, uint32_t value);

volatile uint32_t gpio_irq_count=0;
volatile uint32_t uart0_irq_count=0;
volatile uint32_t uart0_rbuf=0;
volatile uint32_t uart0_tbuf=0;
volatile uint32_t consoleUART = SOC_UART_0_REGS;

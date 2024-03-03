#ifndef __I2C_H__
#define __I2C_H__

#ifndef F_CPU_
#define F_CPU_ 16000000UL
#endif

#ifndef __AVR_ATmega2560__
#define __AVR_ATmega2560__
#endif

// Buffer sizes for TWI communication
#define TWI_TX_BUFFER_SIZE 12
#define TWI_RX_BUFFER_SIZE 8

// Global buffers
extern volatile uint8_t TWI_TX_BUFFER[TWI_TX_BUFFER_SIZE];
extern volatile uint8_t TWI_RX_BUFFER[TWI_RX_BUFFER_SIZE];

// Buffer indexes
volatile int TWI_TX_BUFFER_INDEX;
volatile int TWI_RX_BUFFER_INDEX;

#define SLAVE_ADDRESS 0x20

// Status Codes

    #define TWI_SR_SLA_ACK              0x60

    #define TWI_SR_ARB_LOST_SLA_ACK     0x68
    #define TWI_SR_GCALL_ACK            0x70
    #define TWI_SR_ARB_LOST_GCALL_ACK   0x78
    
    #define TWI_SR_DATA_ACK             0x80
    #define TWI_SR_DATA_NACK            0x88
    #define TWI_SR_GCALL_DATA_ACK       0x90
    #define TWI_SR_GCALL_DATA_NACK      0x98
    #define TWI_SR_STOP_RS_RECOGNIZED   0xA0

    #define TWI_ST_SLA_ACK              0xA8
    #define TWI_ST_ARB_LOST_SLA_ACK     0xB0
    #define TWI_ST_DATA_ACK             0xB8
    #define TWI_ST_DATA_NACK            0xC0
    #define TWI_ST_LAST_DATA_ACK        0xC8

    #define TWI_BUS_ERROR               0x00
/*-------------------------------------------*/

#define SLAVE_END_TWI()  (TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT))

// Function Prototypes
extern volatile uint8_t thrusters_values[TWI_RX_BUFFER_SIZE] = {0, 0, 0, 0};
volatile uint8_t sensor_values[TWI_TX_BUFFER_SIZE] = {0, 0, 0, 0, 0, 0};
void TWI_init(void);

#endif // __I2C_H__

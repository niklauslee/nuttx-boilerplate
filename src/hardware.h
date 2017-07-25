#ifndef __HARDWARE_H
#define __HARDWARE_H

void hardware_initialize ();
void hardware_finalize ();

long hardware_get_serial_number();
long hardware_get_system_time();

void uart_transmit(char *data, unsigned char size);
void uart_receive();

// i2c_setup
// i2c_write
// i2c_read

// spi
// serial
// timer
// ...

#endif /* __HARDWARE_H */

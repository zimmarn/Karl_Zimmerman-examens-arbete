#ifndef UART_COM_H
#define UART_COM_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

bool com_init(const char *parameters);

bool com_read_timeout(uint8_t *buf, size_t length, size_t wait_ticks);

bool com_read(uint8_t *buf, size_t length);

bool com_write(uint8_t *data, size_t length);

#endif
#ifndef COMMUNICAITON_H
#define COMMUNICATION_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Initialize the UART communication interface.
 *
 * Configures and installs the UART driver using the baud rate
 * specified in the parameter string.
 *
 * @param params Null-terminated string containing the baud rate
 *               in decimal (e.g. "115200").
 *
 * @return true  If UART was successfully initialized
 * @return false If parameters are invalid or baud rate is too low
 */
bool communication_init(const char *params);

/**
 * @brief Read bytes from UART with a timeout.
 *
 * Attempts to read up to the requested number of bytes from UART,
 * blocking for at most the specified timeout.
 *
 * @param buf Pointer to destination buffer
 * @param length Maximum number of bytes to read
 * @param wait_ms Timeout in milliseconds
 *
 * @return int Number of bytes actually read before timeout
 */
int communication_read_timeout(uint8_t *buf, size_t length, size_t wait_ms);

/**
 * @brief Read bytes from UART with a blocking wait for data.
 *
 * Waits until at least one byte is available in the UART RX buffer,
 * then attempts to read up to the requested number of bytes.
 *
 * @param buf    Pointer to destination buffer
 * @param length Maximum number of bytes to read
 *
 * @return int Number of bytes actually read from UART
 */
int communication_read(uint8_t *buf, size_t length);

/**
 * @brief Write bytes to UART.
 *
 * Transmits the provided buffer over UART.
 *
 * @param data   Pointer to data to transmit
 * @param length Number of bytes to send
 *
 * @return true  If all bytes were written successfully
 * @return false If transmission failed or incomplete
 */
bool communication_write(uint8_t *data, size_t length);

#endif
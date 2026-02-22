#ifndef SESSION_H
#define SESSION_H

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    INVALID = -1,
    CLOSE_SESSION = 0,
    GET_TEMP = 1,
    TOGGLE_LED = 2
} session_request_t;

/**
 * @brief Initialize the session subsystem and crypto context.
 *
 * Initializes communication and PSA crypto. Must be called once
 * before any other session function.
 *
 * @return true  If initialization succeeded
 * @return false If initialization failed
 */
bool session_init(void);

/**
 * @brief Check whether a secure session is currently active.
 *
 * @return true  If a session is established and valid
 * @return false If no active session exists
 */
bool session_is_active(void);

/**
 * @brief Establish a secure encrypted session with the client.
 *
 * Performs the authenticated handshake using the pre-shared secret,
 * negotiates a session key and session ID, synchronizes time, and
 * enables encrypted communication.
 *
 * This function blocks until the handshake completes or fails.
 *
 * @return true  If the session was successfully established
 * @return false If the handshake failed
 */
bool session_establish(void);

/**
 * @brief Receive and decrypt the next client request.
 *
 * Waits for an encrypted request packet, authenticates and decrypts it,
 * validates timestamp freshness, and updates session state.
 *
 * If the session expired or the request is invalid, INVALID is returned.
 *
 * @return session_request_t The decoded request type or INVALID
 */
session_request_t session_get_request(void);

/**
 * @brief Send an encrypted temperature response to the client.
 *
 * Encrypts and transmits the response containing status, timestamp,
 * and temperature value using the active session key.
 *
 * @param status true if the temperature reading is valid, false on error
 * @param temp   Temperature value in degrees (float)
 *
 * @return true  If the encrypted response was sent successfully
 * @return false If encryption or transmission failed
 */
bool session_send_temperature(bool status, float temp);

/**
 * @brief Send an encrypted LED toggle response to the client.
 *
 * Encrypts and transmits the response containing status, timestamp,
 * and LED state using the active session key.
 *
 * @param status true if the toggle operation succeeded
 * @param state  LED state after toggle (0 = off, 1 = on)
 *
 * @return true  If the encrypted response was sent successfully
 * @return false If encryption or transmission failed
 */
bool session_send_toggle_led(bool status, int state);

/**
 * @brief Close the active session and notify the client.
 *
 * Sends an encrypted close response containing the final session
 * status and timestamp, then clears session state and destroys
 * the AES key.
 *
 * @return true  If the close message was sent successfully
 * @return false If encryption or transmission failed
 */
bool session_close(void);

#endif
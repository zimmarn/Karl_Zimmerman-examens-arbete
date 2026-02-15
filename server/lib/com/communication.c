// #include "uart_com.h"
// #include "driver/uart.h"

// #define UART_PORT UART_NUM_0
// #define UART_BUF_SIZE (2 * SOC_UART_FIFO_LEN)
// #define UART_WAIT_FOREVER portMAX_DELAY
// #define LOWEST_SPEED 115200

// bool com_init(const char *parameters)
// {

//     bool status = true;

//     int speed = atoi(parameters);

//     if (speed < LOWEST_SPEED)
//     {
//         status = false;
//     }
//     else
//     {
//         uart_config_t uart_config = {
//             .baud_rate = speed,
//             .data_bits = UART_DATA_8_BITS,
//             .parity = UART_PARITY_DISABLE,
//             .stop_bits = UART_STOP_BITS_1,
//             .flow_ctrl = UART_HW_FLOWCTRL_DISABLE};

//         ESP_ERROR_CHECK(uart_driver_install(UART_PORT, UART_BUF_SIZE, 0, 0, NULL, 0));
//         ESP_ERROR_CHECK(uart_param_config(UART_PORT, &uart_config));
//         ESP_ERROR_CHECK(uart_set_pin(UART_PORT, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
//     }

//     return status;
// }

// bool com_read_timeout(uint8_t *buf, size_t length, size_t wait_ticks)

// {
//     bool status = true;

//     int read_length = uart_read_bytes(UART_PORT, buf, length, wait_ticks);

//     if (read_length != length)
//     {
//         status = false;
//     }

//     return status;
// }

// bool com_read(uint8_t *buf, size_t length)
// {
//     bool status = true;

//     int read_length = uart_read_bytes(UART_PORT, buf, length, UART_WAIT_FOREVER);

//     if (read_length != length)
//     {
//         status = false;
//     }

//     return status;
// }

// bool com_write(uint8_t *data, size_t length)
// {
//     int status = true;

//     int read_length = uart_write_bytes(UART_PORT, buf, length);

//     if (read_length != length)
//     {
//         status = false;
//     }

//     return status;
// }
#include "driver/uart.h"
#include "communication.h"

#define UART_PORT UART_NUM_0
#define UART_BUF_SIZE (2 * SOC_UART_FIFO_LEN)
#define UART_WAIT_FOREVER portMAX_DELAY

#define SLOWEST_SPEED 115200

bool communication_init(const char *params)
{
    bool status = true;

    int speed = atoi(params);

    if (speed < SLOWEST_SPEED)
    {
        status = false;
    }
    else
    {
        uart_config_t uart_config = {
            .baud_rate = speed,
            .data_bits = UART_DATA_8_BITS,
            .parity = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE};

        // Installera UART-drivrutin
        ESP_ERROR_CHECK(uart_driver_install(UART_PORT, UART_BUF_SIZE, 0, 0, NULL, 0));
        ESP_ERROR_CHECK(uart_param_config(UART_PORT, &uart_config));
        ESP_ERROR_CHECK(uart_set_pin(UART_PORT, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    }

    return status;
}

int communication_read_timeout(uint8_t *buf, size_t length, size_t wait_ms)
{
    // uart_flush(UART_PORT);
    return (uart_read_bytes(UART_PORT, buf, length, pdMS_TO_TICKS(wait_ms)));
}

int communication_read(uint8_t *buf, size_t length)
{
    size_t available = 0;
    uart_flush(UART_PORT);
    while (available == 0)
    {
        vTaskDelay(pdTICKS_TO_MS(10));
        (void)uart_get_buffered_data_len(UART_PORT, &available);
    }
    return uart_read_bytes(UART_PORT, buf, length, pdTICKS_TO_MS(100));
}

bool communication_write(uint8_t *buf, size_t length)
{
    return (length == uart_write_bytes(UART_PORT, buf, length));
}
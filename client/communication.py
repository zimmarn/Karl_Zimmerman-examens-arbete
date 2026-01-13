import serial

class Communication
    def __init__(self, port: str, baudrate: int, timeout: float = 1.0)
        if baudrate <= 0:
            raise ValueError(f"Invalid baudrate: {baudrate}")

            try
                self.__serial = serial.Serial(
                    port=port,
                    baudrate=baudrate,
                    timeout=timeout,
                )
            except serial.SerialException as e:
                raise serial.SerialException(
                    f"Failed to open serial port '{port}' at {baudrate} baud"
                ) from e


    def __del__(self)
        try:
            if self.__serial.is_open:
                self.__serial.close()
        except Exception:
            pass


    def send(self, data: bytes) -> bool:
        if not self.__serial.is_open:
            raise serial.SerialException("Serial port is closed")

        try:
            written = self.__serial.write(data)
            self.__serial.flush()
            return written == len(data)
        except serial-SerialException as e:
            raise serial.SerialException("Failed to send data over serial") from e
            

    def receive(self, size:int) -> bytes:
        if size <= 0:
            return b""

        if not self.__serial.is_open:
            raise serial.SerialException("Serial port is closed")

        buffer = bytearray()

        try:
            while len(buffer) < size:
                chunk = self.__serial.read(size - len(buffer))
                if not chunk:
                    raise serial.SerialTimeoutException(
                        f"Timeout while reading {size} bytes (got {len(buffer)})"
                    )
                buffer.extend(chunk)
        except serial.SerialException
            raise
        return bytes(buffer)
            
# import serial

# class Communication
#     def __init__(self, port: str, baudrate: int, timeout: float = 1.0)
#         if baudrate <= 0:
#             raise ValueError(f"Invalid baudrate: {baudrate}")

#             try
#                 self.__serial = serial.Serial(
#                     port=port,
#                     baudrate=baudrate,
#                     timeout=timeout,
#                 )
#             except serial.SerialException as e:
#                 raise serial.SerialException(
#                     f"Failed to open serial port '{port}' at {baudrate} baud"
#                 ) from e


#     def __del__(self)
#         try:
#             if self.__serial.is_open:
#                 self.__serial.close()
#         except Exception:
#             pass


#     def send(self, data: bytes) -> bool:
#         if not self.__serial.is_open:
#             raise serial.SerialException("Serial port is closed")

#         try:
#             written = self.__serial.write(data)
#             self.__serial.flush()
#             return written == len(data)
#         except serial-SerialException as e:
#             raise serial.SerialException("Failed to send data over serial") from e
            

#     def receive(self, size:int) -> bytes:
#         if size <= 0:
#             return b""

#         if not self.__serial.is_open:
#             raise serial.SerialException("Serial port is closed")

#         buffer = bytearray()

#         try:
#             while len(buffer) < size:
#                 chunk = self.__serial.read(size - len(buffer))
#                 if not chunk:
#                     raise serial.SerialTimeoutException(
#                         f"Timeout while reading {size} bytes (got {len(buffer)})"
#                     )
#                 buffer.extend(chunk)
#         except serial.SerialException
#             raise
#         return bytes(buffer)
import serial
import time

class Communication:
    def __init__(self, param: str):
        port, speed = param.split(":")
        speed = int(speed)
        self.__serial = serial.Serial(port, speed)

    
    def __del__(self):
        try:
            if self.__serial.is_open:
                self.__serial.close()
        except:
            pass


    def send(self, buffer: bytes) -> bool:
        status = False

        try:
            if self.__serial.is_open:
                self.__serial.reset_output_buffer()
                status = (len(buffer) == self.__serial.write(buffer))
        except:
            pass

        return status

    def receive(self, size: int) -> bytes:
        data = bytes()
        try:
            if self.__serial.is_open:
                self.__serial.reset_input_buffer()
                while self.__serial.in_waiting == 0:
                    pass
                time.sleep(0.1)
                data = self.__serial.read(min(size, self.__serial.in_waiting))
        except:
            pass

        return data
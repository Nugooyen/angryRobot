import keyboard
import time
import serial

# Set up the serial connection to the Arduino
ser = serial.Serial('/dev/ttyACM0', 9600)

# Create the start byte and stop byte
start_byte = b'\x78'
stop_byte = b'\x7a'

# or this
while True:
    # Wait for the next event.

    first_byte = b'\x32'
    second_byte = b'\x32'
    third_byte = b'\x32'

    event = keyboard.read_event()
    if event.event_type == keyboard.KEY_DOWN and event.name == 'w':
        first_byte = b'\x33'
    if event.event_type == keyboard.KEY_DOWN and event.name == 's':
        first_byte = b'\x31'
    if event.event_type == keyboard.KEY_DOWN and event.name == 'a':
        second_byte = b'\x31'
    if event.event_type == keyboard.KEY_DOWN and event.name == 'd':
        second_byte = b'\x33'
    if event.event_type == keyboard.KEY_DOWN and event.name == 'j':
        third_byte = b'\x33'
    if event.event_type == keyboard.KEY_DOWN and event.name == 'k':
        third_byte = b'\x31'
  
    if event.event_type == keyboard.KEY_UP :
        first_byte = b'\x32'
        second_byte = b'\x32'
        third_byte = b'\x32'
    
    ser.write(start_byte + first_byte + second_byte + third_byte + stop_byte)
    


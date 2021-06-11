# Smart-Door-Lock
Smart Door lock using Keypad with
- Changing Assigned Password feature (Entering Resetting Password cmd) after checking Old password.
- Resetting password cmd (****).
Consists of 2 ECUs: 
* First ECU (HMI) responsible for Interfacing with the User
* Second ECU responsible for System operations and Control.
# Drivers Used:
- UART(Communication between 2 uC).
- SPI (Connection between uC and EEPROM)
- External EEPROM
- LCD
- Keypad

Door Locker Security System consists of two ECU’s. The first ECU called HMI responsible for interfacing with the user and the second ECU called control ECU which is responsible for the system operations and control. In the project I implemented the following drivers Keypad, LCD, DC Motor, UART, Timer, I2C and External EEPROM.

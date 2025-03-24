# Embedded Pick to Light System

## Overview
This project implements an embedded Pick to Light system using the PIC18F4580 microcontroller and the CAN protocol to enhance real-time stock management in warehouse operations.

## Features

- **Operation Mode:** The display remains blank when no data is received from the server, ensuring clear status indication.
- **Mode Selection:** A MODE key allows users to switch between Operation Mode and Config Mode.
- **Config Mode:**
  - Update stock count to the server.
  - Set Node ID.
  - Use the INC key to increment stock count and send the final value via CAN communication.
  - Modify and store the Node ID in persistent memory using the ACK key.
- **CAN Communication:** Ensures low-latency, reliable data transmission between PIC18F4580-based nodes and the central server.
- **Error Handling:** Implements robust validation to prevent incorrect stock updates and misconfigured Node IDs.

## Technologies Used
- **Microcontroller:** PIC18F4580
- **Communication Protocol:** CAN (Controller Area Network)
- **Programming Language:** Embedded C

## Installation & Usage
1. Flash the firmware onto the PIC18F4580 microcontroller.
2. Connect the device to the CAN network.
3. Use the MODE key to switch between modes.
4. Utilize INC and ACK keys for stock updates and Node ID configuration.


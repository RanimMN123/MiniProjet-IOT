# IoT System with ESP32, DHT11 Sensor, GraphQL Server, and LED

## Project Overview
This project aims to create an IoT system that integrates an ESP32 microcontroller, a DHT11 temperature and humidity sensor, a GraphQL server, and an LED. The ESP32 reads data from the sensor, sends it to the GraphQL server, and allows remote control of the LED through a web interface using GraphQL queries.

## Table of Contents
- [Project Components](#project-components)
- [Functionality](#functionality)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

## Project Components
### Hardware
- ESP32 microcontroller
- DHT11 temperature and humidity sensor
- LED

### Software
- Node.js
- Express.js
- GraphQL
- graphql-tools
- Cors (Cross-Origin Resource Sharing)
- Arduino IDE
- HTML
- CSS
- JavaScript

## Functionality
### Initialization
- ESP32 connects to Wi-Fi.
- DHT11 sensor is configured.

### Data Processing
- ESP32 reads temperature and humidity from the DHT11 sensor.
- Sends sensor data to the GraphQL server via HTTP POST requests.
- GraphQL server processes the data using mutations.

### LED Control
- The server controls the LED based on the received data.

### Web Interface
- A web interface allows users to view sensor data and control the LED remotely.
- Users can send GraphQL queries to retrieve sensor data and LED state.
- The web interface displays received data and allows LED control.

## Installation
1. Install Node.js and npm.
2. Clone this repository.
3. Install dependencies: `npm install`.
4. Upload Arduino IDE code to the ESP32.
5. Start the GraphQL server: `npm start`.

## Usage
1. Access the web interface through a browser.
2. View sensor data and control the LED remotely using GraphQL queries.

## Project Structure
- **/arduino:** Contains Arduino IDE code for the ESP32.
- **/server:** Contains GraphQL server code.
- **/client:** Contains web interface code.

## Contributing
Contributions are welcome! Feel free to submit issues or pull requests.

## License
This project is licensed under the [MIT License](LICENSE).

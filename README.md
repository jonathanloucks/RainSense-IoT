# 🌧️ RainSense-IoT - Monitor Rainfall Easily and Effectively

[![Download RainSense-IoT](https://img.shields.io/badge/Download-RainSense--IoT-brightgreen)](https://github.com/jonathanloucks/RainSense-IoT/releases)

## 🌟 Introduction

Welcome to **RainSense-IoT**! This application allows you to detect rain early using your Arduino. It monitors weather conditions with DHT22 and BMP280 sensors, providing real-time alerts to keep you informed. The system processes data and sends it via HTTP/JSON, making it easy to access.

## 🚀 Getting Started

To set up RainSense-IoT and start monitoring rain, you'll need to follow these steps:

1. **Prepare Your Arduino**: Ensure your Arduino is ready. You will need:
    - An Arduino board (like Arduino Uno or Nano).
    - DHT22 and BMP280 sensors for weather detection.
    - Additional jumper wires for connections.
  
2. **Install PlatformIO**: This application uses PlatformIO, an integrated development environment (IDE) that makes working with embedded systems easy.
    - Follow the [PlatformIO installation guide](https://platformio.org/install) based on your computer's operating system.

3. **Clone the Repository**: Open your command prompt or terminal and run the following command:
    ```
    git clone https://github.com/jonathanloucks/RainSense-IoT.git
    ```
    This will download the RainSense-IoT files to your computer.

4. **Open the Project in PlatformIO**: Launch PlatformIO and open the cloned project. You will see the code files.

5. **Connect Your Arduino**: Use a USB cable to connect your Arduino board to your computer.

## 📥 Download & Install

To download the latest version of RainSense-IoT, visit the releases page by clicking the link below:

[Visit this page to download](https://github.com/jonathanloucks/RainSense-IoT/releases)

Follow the instructions on the Releases page for the latest updates and installation files.

## 🔌 Configure Sensors

Before deploying the system, you need to configure the sensors:

1. **Wiring**:
   - Connect the DHT22 sensor to your Arduino as follows:
     - VCC to 5V
     - GND to Ground
     - Data pin to digital pin 2 (or as specified in the code)
    
   - Connect the BMP280 sensor similarly:
     - VCC to 3.3V
     - GND to Ground
     - SCL to A5 (I2C)
     - SDA to A4 (I2C)

2. **Update Settings**: Open the `config.h` file in the project and update any required settings, like sensor pin numbers or Wi-Fi credentials.

## 🌐 Running the Application

1. **Compile the Code**: In PlatformIO, click the "Build" button to compile the code. This process will ensure that everything is set up correctly.

2. **Upload to Arduino**: After successful compilation, click on the "Upload" button. This will install the code onto your Arduino.

3. **Open the Serial Monitor**: After uploading, open the serial monitor in PlatformIO. You should start seeing data from your sensors as they monitor the environment.

4. **Check Data via HTTP/JSON**: The application will send data to a web server. You can check this through the endpoint specified in the code. Monitoring rain has never been easier!

## 📊 Features

RainSense-IoT includes several useful features:
- Real-time weather monitoring with DHT22 and BMP280 sensors.
- Data processing and alert system for rainfall.
- HTTP/JSON data output for easy integration with other applications.
- Simple setup without needing extensive programming knowledge.

## ⚙️ System Requirements

- **Hardware**: Arduino board (Uno, Nano, etc.)
- **Software**: PlatformIO IDE.
- **Sensors**: DHT22 (temperature and humidity) and BMP280 (barometric pressure).

## 📦 Contributing

If you'd like to contribute to RainSense-IoT:
1. Fork the repository.
2. Create a new branch for your feature.
3. Make your changes.
4. Submit a pull request with a description of your changes.

## 📞 Support

For support or issues, please open an issue in the GitHub repository, and the community will assist you.

## 🌍 Related Topics

- Arduino
- BMP280
- Data Analysis
- DHT22
- Embedded Systems
- IoT
- Rain Detection
- Weather Prediction

Thank you for choosing RainSense-IoT. We hope this application helps you stay ahead of the weather!
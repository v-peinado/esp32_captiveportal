# WiFi Security Awareness Captive Portal

## Overview

This project implements a captive portal on an ESP32 microcontroller to educate users about WiFi security risks. When users connect to the "Free_WiFi" access point, they are automatically redirected to an informational page highlighting the dangers of connecting to unsecured networks.

## What is a Captive Portal?

A captive portal is a web page that is displayed to newly connected users of a WiFi network before they are granted broader access to network resources. Captive portals are commonly used in:

- Public WiFi hotspots (coffee shops, airports, hotels)
- Guest networks in businesses
- Paid WiFi services
- Educational network environments

When a device connects to a network with a captive portal, any HTTP request is intercepted and redirected to the portal page, regardless of the originally requested URL.

## Project Features

- Creates an open WiFi access point named "Free_WiFi"
- Implements DNS redirection to capture all web requests
- Displays a security warning page to connected users
- Tracks unique visitors and completed awareness sessions
- Includes an admin panel to reset statistics (password protected)

## Educational Purpose

This project is designed for educational purposes to demonstrate:

1. How easily users can be tricked into connecting to rogue WiFi networks
2. The security risks of using unsecured public WiFi
3. The technical implementation of captive portals
4. Basic cybersecurity awareness principles

## Technical Implementation

### Hardware Requirements
- ESP32 development board
- USB cable for programming and power

### Libraries Used
- WiFi.h - Manages WiFi functionality
- DNSServer.h - Handles DNS request redirection
- WebServer.h - Serves web content to connected users
- Standard C++ libraries (map, string)

### Key Components

1. **Access Point Setup**
   - Creates a WiFi access point with a fixed IP address
   - Configures DNS server to redirect all requests

2. **Web Server**
   - Handles HTTP requests and serves warning pages
   - Provides different routes for information and completion

3. **Statistics Tracking**
   - Counts unique visitors based on IP addresses
   - Tracks completed awareness sessions

4. **Admin Interface**
   - Password-protected reset functionality
   - Allows clearing statistics for demonstration purposes

## Installation Guides

For detailed setup instructions, please refer to our guides:

- [English Installation Guide](https://github.com/v-peinado/esp32_captiveportal/blob/main/esp32-captive-portal-guide-english.md) - Complete guide to setting up the Arduino IDE and deploying this project
- [Guía de Instalación en Español](https://github.com/v-peinado/esp32_captiveportal/blob/main/esp32-captive-portal-guide.md) - Guía completa para configurar el IDE de Arduino y desplegar este proyecto

## Security Notes

The default admin password is set to "admin123" and should be changed for any deployment. This project should only be used for educational purposes and with proper authorization - never deploy it in public spaces without appropriate permissions.

## Responsible Use

This tool demonstrates techniques that could potentially be misused. Only deploy it:
- In controlled educational environments
- With clear signage indicating it's an educational demonstration
- With permission from relevant authorities
- In accordance with local laws and regulations

## Getting Started

1. Upload the code to your ESP32 using the Arduino IDE
2. Power on the ESP32
3. Look for the "Free_WiFi" network on your device
4. Connect to the network and observe the captive portal behavior
5. Access the admin interface at [http://192.168.4.1/reset](http://192.168.4.1/reset)

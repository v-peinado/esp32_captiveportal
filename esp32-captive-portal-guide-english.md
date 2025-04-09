# Guide: Educational Captive Portal with ESP32

This guide explains how to set up and use an ESP32 to create an educational captive portal about WiFi security. The project is ideal for cybersecurity demonstrations and education about the risks of public WiFi networks.

## Table of Contents
1. [Arduino IDE Installation](#1-arduino-ide-installation)
2. [ESP32 Configuration](#2-esp32-configuration)
3. [Code Installation](#3-code-installation)
4. [Verification and Upload](#4-verification-and-upload)
5. [Using the Captive Portal](#5-using-the-captive-portal)
6. [Troubleshooting](#6-troubleshooting)
7. [Customization](#7-customization)

## 1. Arduino IDE Installation

### Windows
1. Download Arduino IDE from [arduino.cc/en/software](https://www.arduino.cc/en/software)
2. Run the installer and follow the instructions

### Linux
**Option 1: Using apt (Ubuntu/Debian)**
```bash
sudo apt update
sudo apt install arduino
```

**Option 2: Manual installation (recommended)**
```bash
# Download the latest version
cd ~/Downloads
wget https://downloads.arduino.cc/arduino-ide/arduino-ide_2.2.1_Linux_64bit.AppImage

# Make it executable
chmod +x arduino-ide_2.2.1_Linux_64bit.AppImage

# Run it
./arduino-ide_2.2.1_Linux_64bit.AppImage
```

**Optional: Create a shortcut**
```bash
sudo mkdir -p /opt/arduino-ide
sudo mv arduino-ide_2.2.1_Linux_64bit.AppImage /opt/arduino-ide/arduino-ide
sudo chmod +x /opt/arduino-ide/arduino-ide

echo "[Desktop Entry]
Name=Arduino IDE
Comment=Arduino IDE
Exec=/opt/arduino-ide/arduino-ide
Icon=arduino
Terminal=false
Type=Application
Categories=Development;" | sudo tee /usr/share/applications/arduino-ide.desktop

sudo update-desktop-database
```

### MacOS
1. Download Arduino IDE from [arduino.cc/en/software](https://www.arduino.cc/en/software)
2. Drag the application to your Applications folder

## 2. ESP32 Configuration

1. **Open Arduino IDE**

2. **Add the ESP32 board manager URL**:
   - Go to **File > Preferences**
   - In "Additional Board Manager URLs", add:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
   - Click "OK"

3. **Install ESP32 support**:
   - Go to **Tools > Board > Boards Manager**
   - Search for "esp32"
   - Install the "ESP32 by Espressif Systems" package (the latest version)

4. **Select your ESP32 board**:
   - Go to **Tools > Board > ESP32 Arduino**
   - Select your specific model (e.g., "ESP32 Dev Module", "ESP32C3 Dev Module")

5. **Configure board options**:
   - **Upload Speed**: 921600
   - **Flash Size**: 4MB (32Mb)
   - Other options can be left at default values

## 3. Code Installation

1. **Open Arduino IDE** and create a new sketch (File > New)

2. **Copy the complete code** for the Educational Captive Portal

3. **Customize the code as needed**:
   - Change the WiFi network name (variable `g_ssid`)
   - Change the admin password (variable `g_admin_pwd`)
   - Modify the HTML content if you want to customize the messages

## 4. Verification and Upload

1. **Connect your ESP32** to your computer using a USB cable

2. **Select the correct port**:
   - Go to **Tools > Port**
   - Select the port where your ESP32 is connected

3. **Verify the code**:
   - Click the "Verify" button (✓) or press Ctrl+R
   - Make sure there are no compilation errors

4. **Upload the code**:
   - Click the "Upload" button (→) or press Ctrl+U
   - If necessary, hold down the BOOT button on your ESP32 while uploading begins

5. **Upload mode** (if prompted):
   - Choose "Program" (not "Using programmer")
   - Some models may require a button sequence: hold BOOT, press RESET, release RESET, then release BOOT

## 5. Using the Captive Portal

Once the code is uploaded, the ESP32 will automatically create a WiFi access point:

1. **Search for the WiFi network** called "Free_WiFi" (or the name you configured) from your phone or other device

2. **Connect to this network** (no password required)

3. **You'll see the captive portal** automatically, or you'll need to navigate to any website for it to appear

4. **Interact with the portal**:
   - You'll see counters for visitors, connections, and completed tests
   - By clicking "I understand the risks", the test completion counter will increase
   - To reset the counters, click "Reset counters" and enter the admin password

## 6. Troubleshooting

### Compilation or Upload Issues
- **Python/GLIBC Error**: If you see errors related to Python or GLIBC on Linux, consider using Arduino IDE 2.x instead of the Snap version
- **Port Not Available Error**: Make sure no other programs are using the serial port
- **Board Doesn't Enter Upload Mode**: Try the BOOT and RESET button sequence mentioned above

### ESP32 Doesn't Create WiFi Access Point
- Check the code to ensure the WiFi configuration is correct
- Try restarting the board by pressing the RESET button
- Verify that your ESP32 model has WiFi enabled

### Captive Portal Doesn't Appear
- Some devices may need you to navigate to a web page to trigger the portal
- Try navigating directly to 192.168.4.1
- Turn off mobile data on your phone to force WiFi usage

## 7. Customization

### Change the WiFi Network Name
```c
const char *g_ssid = "YourNetworkName";
```

### Change the Admin Password
```c
const char *g_admin_pwd = "YourPassword";
```

### Modify the Displayed Content
You can edit the HTML strings in the functions to customize messages, colors, or layout.

### Add Functionality
- Track incorrect access attempts
- More educational statistics
- Additional language options
- Indicator LEDs for visual demonstration

---

## Educational Use

This project is ideal for educational sessions on computer security. Some usage scenarios:

1. **Classroom Demonstrations**: Show students the risks of open networks
2. **Technology Fairs**: As a practical cybersecurity demonstration
3. **Security Workshops**: As part of broader training on WiFi security

Always remember to use this project only for educational purposes and to raise awareness about security.

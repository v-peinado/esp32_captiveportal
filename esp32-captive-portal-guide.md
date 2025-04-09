# Guía: Portal Cautivo Educativo con ESP32

Esta guía explica cómo configurar y utilizar un ESP32 para crear un portal cautivo educativo sobre seguridad WiFi. El proyecto es ideal para demostraciones de ciberseguridad y educación sobre los riesgos de las redes WiFi públicas.

## Índice
1. [Instalación de Arduino IDE](#1-instalación-de-arduino-ide)
2. [Configuración para ESP32](#2-configuración-para-esp32)
3. [Instalación del Código](#3-instalación-del-código)
4. [Verificación y Carga](#4-verificación-y-carga)
5. [Uso del Portal Cautivo](#5-uso-del-portal-cautivo)
6. [Solución de Problemas](#6-solución-de-problemas)
7. [Personalización](#7-personalización)

## 1. Instalación de Arduino IDE

### Windows
1. Descarga Arduino IDE desde [arduino.cc/en/software](https://www.arduino.cc/en/software)
2. Ejecuta el instalador y sigue las instrucciones

### Linux
**Opción 1: Usando apt (Ubuntu/Debian)**
```bash
sudo apt update
sudo apt install arduino
```

**Opción 2: Instalación manual (recomendada)**
```bash
# Descargar la última versión
cd ~/Downloads
wget https://downloads.arduino.cc/arduino-ide/arduino-ide_2.2.1_Linux_64bit.AppImage

# Hacer ejecutable
chmod +x arduino-ide_2.2.1_Linux_64bit.AppImage

# Ejecutar
./arduino-ide_2.2.1_Linux_64bit.AppImage
```

**Opcional: Crear acceso directo**
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
1. Descarga Arduino IDE desde [arduino.cc/en/software](https://www.arduino.cc/en/software)
2. Arrastra la aplicación a tu carpeta de Aplicaciones

## 2. Configuración para ESP32

1. **Abre Arduino IDE**

2. **Añade la URL del gestor de placas ESP32**:
   - Ve a **Archivo > Preferencias**
   - En "URLs adicionales de Gestor de Placas", añade:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
   - Haz clic en "OK"

3. **Instala el soporte para ESP32**:
   - Ve a **Herramientas > Placa > Gestor de placas**
   - Busca "esp32"
   - Instala el paquete "ESP32 by Espressif Systems" (la versión más reciente)

4. **Selecciona tu placa ESP32**:
   - Ve a **Herramientas > Placa > ESP32 Arduino**
   - Selecciona tu modelo específico (ej: "ESP32 Dev Module", "ESP32C3 Dev Module")

5. **Configura las opciones de la placa**:
   - **Upload Speed**: 921600
   - **Flash Size**: 4MB (32Mb)
   - Otras opciones pueden dejarse con los valores predeterminados

## 3. Instalación del Código

1. **Abre Arduino IDE** y crea un nuevo sketch (Archivo > Nuevo)

2. **Copia el código completo** del Portal Cautivo Educativo

3. **Personaliza el código según necesites**:
   - Cambia el nombre de la red WiFi (variable `g_ssid`)
   - Cambia la contraseña de administrador (variable `g_admin_pwd`)
   - Modifica el contenido HTML si deseas personalizar los mensajes

## 4. Verificación y Carga

1. **Conecta tu ESP32** a tu computadora mediante un cable USB

2. **Selecciona el puerto correcto**:
   - Ve a **Herramientas > Puerto**
   - Selecciona el puerto donde está conectado tu ESP32

3. **Verifica el código**:
   - Haz clic en el botón "Verificar" (✓) o presiona Ctrl+R
   - Asegúrate de que no haya errores de compilación

4. **Carga el código**:
   - Haz clic en el botón "Subir" (→) o presiona Ctrl+U
   - Si es necesario, mantén presionado el botón BOOT en tu ESP32 mientras inicia la carga

5. **Modo de carga** (si se solicita):
   - Elige "Programar" (no "Usando programador")
   - Algunos modelos pueden requerir una secuencia de botones: mantén presionado BOOT, presiona RESET, suelta RESET, luego suelta BOOT

## 5. Uso del Portal Cautivo

Una vez cargado el código, el ESP32 creará automáticamente un punto de acceso WiFi:

1. **Busca la red WiFi** llamada "Free_WiFi" (o el nombre que hayas configurado) desde tu teléfono u otro dispositivo

2. **Conéctate a esta red** (no requiere contraseña)

3. **Verás el portal cautivo** automáticamente, o tendrás que navegar a cualquier sitio web para que aparezca

4. **Interactúa con el portal**:
   - Verás los contadores de visitantes, conexiones y tests completados
   - Al hacer clic en "I understand the risks", se incrementará el contador de tests completados
   - Para reiniciar los contadores, haz clic en "Reset counters" e introduce la contraseña de administrador

## 6. Solución de Problemas

### Problemas de compilación o carga
- **Error de Python/GLIBC**: Si ves errores relacionados con Python o GLIBC en Linux, considera usar Arduino IDE 2.x en lugar de la versión Snap
- **Error de puerto no disponible**: Asegúrate de que no haya otros programas usando el puerto serial
- **La placa no entra en modo de carga**: Intenta la secuencia de botones BOOT y RESET mencionada anteriormente

### El ESP32 no crea el punto de acceso WiFi
- Revisa el código para asegurarte de que la configuración WiFi es correcta
- Intenta reiniciar la placa presionando el botón RESET
- Verifica que el modelo de ESP32 tenga WiFi habilitado

### No aparece el portal cautivo
- Algunos dispositivos pueden necesitar que navegues a una página web para activar el portal
- Intenta navegar a 192.168.4.1 directamente
- Desactiva los datos móviles en tu teléfono para forzar el uso de WiFi

## 7. Personalización

### Cambiar el nombre de la red WiFi
```c
const char *g_ssid = "TuNombreDeRed";
```

### Cambiar la contraseña de administrador
```c
const char *g_admin_pwd = "TuContraseña";
```

### Modificar el contenido mostrado
Puedes editar las cadenas HTML en las funciones para personalizar los mensajes, colores o disposición.

### Añadir funcionalidades
- Registro de intentos de acceso incorrectos
- Más estadísticas educativas
- Opciones de idioma adicionales
- LEDs indicadores para demostración visual

---

## Uso educativo

Este proyecto es ideal para sesiones educativas sobre seguridad informática. Algunos escenarios de uso:

1. **Demostraciones en clase**: Muestra a los estudiantes los riesgos de las redes abiertas
2. **Ferias de tecnología**: Como demostración práctica de ciberseguridad
3. **Talleres de seguridad**: Como parte de una formación más amplia sobre seguridad WiFi

Recuerda siempre usar este proyecto solo con fines educativos y para concientizar sobre la seguridad.

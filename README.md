# Sistema Controllo Ventilatore ESP32

Questo progetto è un sistema automatico per il controllo di un ventilatore basato sulla temperatura ambiente. Quando la temperatura supera la soglia impostata, il ventilatore si accende automaticamente.

## Hardware Necessario
- ESP32
- Sensore di temperatura e umidità DHT11
- Display OLED 128x64 (I2C)
- Ventilatore 5V
- LED bianco
- Resistenza 220Ω

## Collegamenti
| Componente         | Pin ESP32 |
|--------------------|-----------|
| DHT11 Data         | D4        |
| OLED SDA           | D21       |
| OLED SCL           | D22       |
| LED                | D18       |
| Ventilatore        | D15       |

## Librerie Richieste
Installa queste librerie tramite l'IDE Arduino:
- DHT sensor library (Adafruit)
- Adafruit GFX Library
- Adafruit SSD1306

## Funzionamento
Il sistema legge continuamente temperatura e umidità dal sensore DHT11. Quando la temperatura supera i 24°C, il ventilatore si accende automaticamente e il LED si spegne per indicare che il sistema è attivo.

Il display OLED mostra in tempo reale:
- Temperatura con un decimale
- Umidità in percentuale
- Stato del ventilatore (ON/OFF)

## Configurazione
Per modificare la soglia di temperatura, cambia questa riga nel codice:
```cpp
const float TEMP_SOGLIA = 24.0;  // Temperatura in gradi Celsius
```
prova

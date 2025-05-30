# Sistema di Controllo Ventilatore con ESP32

Questo progetto implementa un sistema automatico per il controllo di un ventilatore basato sulla temperatura dell'ambiente. Quando la temperatura supera una soglia preimpostata ( 24 - 25°C ), il ventilatore si attiva automaticamente.


## Hardware Necessario
- ESP32
- Sensore di temperatura e umidità DHT11
- Display OLED 128x64 (interfaccia I2C)
- Ventilatore >5V
- LED bianco
- Resistenza 220Ω
- Transistor NPN 2N2222 con resistenza da 1 kΩ

## Schema di Collegamento
| Componente             | Pin ESP32 / Collegamento                 |
|------------------------|-----------------------------------------|
| DHT11 Data             | D4                                      |
| OLED SDA               | D21                                     |
| OLED SCL               | D22                                     |
| LED bianco             | D18                                     |
| Ventilatore positivo   | Alimentazione 3.3V o 5V (non su pin ESP32) |
| Transistor 2N2222 Base | D15 tramite resistenza 1 kΩ              |
| Transistor 2N2222 Collettore | Ventilatore polo negativo           |
| Transistor 2N2222 Emettitore | GND comune (ESP32 + alimentazione)  |

## Librerie Software Richieste
Per il funzionamento del progetto, si consiglia di installare tramite l’IDE Arduino le seguenti librerie:
- DHT sensor library (Adafruit)
- Adafruit GFX Library
- Adafruit SSD1306

## Funzionamento del Sistema
Il sistema monitora costantemente temperatura e umidità tramite il sensore DHT11. Quando la temperatura rilevata supera i 24°C, il ventilatore viene attivato automaticamente e il LED bianco si spegne.

Il display OLED visualizza in tempo reale:
- Temperatura con precisione di un decimale
- Umidità relativa in percentuale
- Stato del ventilatore (ON/OFF)

## Configurazione
La soglia di attivazione della temperatura può essere modificata agendo sulla seguente costante nel codice sorgente:
```cpp
const float TEMP_SOGLIA = 24.0;  // Temperatura in gradi Celsius
```

## Problematiche Iniziali e Soluzioni Implementate

Durante la fase di sviluppo sono stati riscontrati problemi relativi al controllo diretto del ventilatore tramite il pin GPIO D2 dell’ESP32:
- Il pin GPIO non forniva corrente sufficiente per pilotare il ventilatore.
- Il collegamento diretto del ventilatore al pin GPIO poteva danneggiare l’ESP32.
- L’utilizzo di MOSFET non logic-level ha causato malfunzionamenti, con il ventilatore che rimaneva sempre acceso o non si spegneva correttamente.
- Collegamenti errati e assenza di resistenza pull-down sul gate del MOSFET hanno peggiorato la situazione.

### Soluzioni Idealizzate
- Utilizzo di transistor MOSFET (non disponibile).
- Utilizzo di modulo relè (non disponibile).

### Soluzione Definitiva
L’utilizzo di un transistor NPN 2N2222 con collegamenti corretti ha garantito un controllo affidabile e sicuro del ventilatore, risolvendo i problemi di corrente e proteggendo l’ESP32.

[Video dimostrativo disponibile qui](https://drive.google.com/drive/folders/1GUEUTkNlYGJk-smshIuskiLKClhBi8_J?usp=drive_link)  
*Nota: la qualità video è stata ridotta dalla compressione di Google Drive.*

---


    
    
    
    
    



    
        
            Visualizza Presentazione
        
    



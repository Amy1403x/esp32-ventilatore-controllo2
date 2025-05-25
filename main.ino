// Librerie necessarie
#include <Wire.h>           // display
#include <Adafruit_GFX.h>   // display
#include <Adafruit_SSD1306.h> // display 
#include <DHT.h>            // sensore di temperatura/umidità

// ===== DEFINIZIONE DEI PIN =====
#define DHT_PIN 4        // Pin D4 per il sensore DHT11
#define LED_PIN 18       // Pin D18 per il LED bianco
#define VENTOLA_PIN 2   // Pin D2 per il ventilatore
#define OLED_SDA 21      // Pin SDA per display OLED
#define OLED_SCL 22      // Pin SCL per display OLED

// ===== COMPONENTI =====
#define DHT_TYPE DHT11      // Tipo di sensore
#define SCREEN_WIDTH 128    // Larghezza display OLED in pixel
#define SCREEN_HEIGHT 64    // Altezza display OLED in pixel
#define OLED_RESET -1       // Pin di reset

// ===== SOGLIA DI TEMPERATURA =====
const float TEMP_SOGLIA = 24.0;  // Temperatura oltre la quale si accende il ventilatore

DHT dht(DHT_PIN, DHT_TYPE);                                           
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); 

// ===== VARIABILI =====
float temperatura = 0;     
float umidita = 0;         
bool ventola_accesa = false;

void setup() {
  // ===== INIZIALIZZAZIONE SERIALE =====
  Serial.begin(115200);  
  Serial.println("=== Sistema Controllo Ventilatore Avviato ===");
  
  // ===== CONFIGURAZIONE PIN =====
  pinMode(LED_PIN, OUTPUT);     
  pinMode(VENTOLA_PIN, OUTPUT); 
  
  digitalWrite(LED_PIN, HIGH);  
  digitalWrite(VENTOLA_PIN, LOW); 
  
  // ===== INIZIALIZZAZIONE SENSORE DHT11 =====
  dht.begin();
  Serial.println("Sensore DHT11 inizializzato");
  
  // ===== INIZIALIZZAZIONE DISPLAY OLED =====
  Wire.begin(OLED_SDA, OLED_SCL);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("ERRORE: Display OLED non trovato!");
    while(1);
  }
  
  display.clearDisplay();
  display.setTextSize(1);      
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(0,0);
  display.println("Sistema acceso...");
  display.display();
  
  Serial.println("Display OLED inizializzato");
  delay(2000);
}

void loop() {
  leggiSensori();
  controllaVentilatore();
  gestisciLED();
  aggiornaDisplay();
  stampaDebug();
  delay(1000); 
}

void leggiSensori() {
  umidita = dht.readHumidity();
  temperatura = dht.readTemperature();
  
  if (isnan(umidita) || isnan(temperatura)) {
    Serial.println("errore nel dht11");
    return;
  }
}

void controllaVentilatore() {
  if (temperatura > TEMP_SOGLIA) {
    digitalWrite(VENTOLA_PIN, HIGH);
    ventola_accesa = true;
    Serial.println("Ventilatore ACCESO");
  } else {
    digitalWrite(VENTOLA_PIN, LOW);
    ventola_accesa = false;
    Serial.println("Ventilatore SPENTO");
  }
}

void gestisciLED() {
  if (ventola_accesa) {
    digitalWrite(LED_PIN, LOW);   // LED spento quando ventilatore acceso
  } else {
    digitalWrite(LED_PIN, HIGH);  // LED acceso quando ventilatore spento
  }
}

void aggiornaDisplay() {
  display.clearDisplay(); 
  
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("=== CLIMA CASA ===");
  
  display.setTextSize(2);
  display.setCursor(0, 15);
  display.print("T: ");
  display.print(temperatura, 1);
  display.println("C");
  
  display.setCursor(0, 35);
  display.print("U: ");
  display.print(umidita, 0); 
  display.println("%");
  
  display.setTextSize(1);
  display.setCursor(0, 55);
  if (ventola_accesa) {
    display.println("Ventilatore: ON");
  } else {
    display.println("Ventilatore: OFF");
  }
  
  display.display(); 
}

void stampaDebug() {
  Serial.println("==================");
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println("°C");
  
  Serial.print("Umidità: ");
  Serial.print(umidita);
  Serial.println("%");
  
  Serial.print("Ventilatore: ");
  Serial.println(ventola_accesa ? "ACCESO" : "SPENTO");
  
  Serial.print("Soglia temperatura: ");
  Serial.print(TEMP_SOGLIA);
  Serial.println("°C");
  Serial.println("==================");
}

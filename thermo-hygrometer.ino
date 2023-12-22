#include <DHT.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 3
#define DHTTYPE DHT11
#define SCREEN_WIDTH 128    // OLED display width,  in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
	Serial.begin(9600);
  dht.begin();

// Start diplay OLED with the address 0x3C to 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
}

void loop() {

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  float heatIndex = dht.computeHeatIndex(temperature, humidity, false); // Heat Index

// Verify if the DHT sensor is working
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Falha ao ler o sensor DHT!"));
    return;
  }
    
  Serial.print("Temperature: "); Serial.print(temperature); Serial.println("°C");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.println("%");
  Serial.print("Heat Index: "); Serial.print(heatIndex); Serial.println("°C");

// OLED Display
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 8);
  oled.print("Temperature: "); oled.print(temperature); oled.println("C");
  oled.setCursor(0, 17);
  oled.print("Humidity: "); oled.print(humidity); oled.println("%");
  oled.setCursor(0, 26);
  oled.print("Heat Index: "); oled.print(heatIndex); oled.println("C"); 
  oled.display();
}

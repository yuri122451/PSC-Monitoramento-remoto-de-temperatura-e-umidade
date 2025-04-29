#include <DHTesp.h>  // Biblioteca para o DHT22


#define DHT_PIN        15 
#define LED_RED_PIN    0  
#define LED_GREEN_PIN  2  
#define LED_BLUE_PIN   16 

DHTesp dhtSensor;  

void setup() {
  Serial.begin(115200);


  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);


  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);

  delay(2000);  
}

void loop() {

  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  
  if (dhtSensor.getStatus() != 0) {
    Serial.println("Erro ao ler o sensor DHT22! Tentando novamente...");
    delay(5000);  
    return;
  }


  if (isnan(data.temperature)) {
    Serial.println("Erro ao ler a temperatura!");
  } else {
    Serial.print("Temperatura: ");
    Serial.print(data.temperature, 2); 
    Serial.println(" °C");

   
    if (data.temperature > 25) {
      digitalWrite(LED_RED_PIN, HIGH);  
      digitalWrite(LED_GREEN_PIN, LOW);
      digitalWrite(LED_BLUE_PIN, LOW);
    } else if (data.temperature >= 15 && data.temperature <= 25) {
      digitalWrite(LED_GREEN_PIN, HIGH);  
      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(LED_BLUE_PIN, LOW);
    } else {
      digitalWrite(LED_BLUE_PIN, HIGH);  
      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(LED_GREEN_PIN, LOW);
    }
    delay(2000);
  }

  if (isnan(data.humidity)) {
    Serial.println("Erro ao ler a umidade!");
  } else {
    Serial.print("Umidade: ");
    Serial.print(data.humidity, 2);  
    Serial.println(" %");

  
    if (data.humidity < 33) {
      digitalWrite(LED_BLUE_PIN, HIGH); 
      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(LED_GREEN_PIN, LOW);
    } else if (data.humidity >= 33 && data.humidity <= 66) {
      digitalWrite(LED_GREEN_PIN, HIGH);  
      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(LED_BLUE_PIN, LOW);
    } else {
      digitalWrite(LED_RED_PIN, HIGH);  
      digitalWrite(LED_GREEN_PIN, LOW);
      digitalWrite(LED_BLUE_PIN, LOW);
    }
  }

  delay(2000);
}

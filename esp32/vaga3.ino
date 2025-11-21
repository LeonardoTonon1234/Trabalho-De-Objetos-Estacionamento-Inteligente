const int PIN_SENSOR      = 15; // Switch -> D15
const int PIN_LED_LIVRE   = 2;  // LED verde -> D2
const int PIN_LED_OCUPADA = 4;  // LED vermelho -> D4

#include <WiFi.h>
#include <PubSubClient.h>

// Broker público HiveMQ
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

// Cliente MQTT
WiFiClient espClient;
PubSubClient client(espClient);

const char* ssid = "Wokwi-GUEST";
const char* password = "";

void conectaWifi() {
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(" Conectado!");
}

void conectaMQTT() {
  // Tenta conectar até conseguir
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT... ");

    // CLIENTE EXCLUSIVO DA VAGA 3
    if (client.connect("vaga3_client")) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Falhou, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando de novo em 1s...");
      delay(1000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  conectaWifi();
  client.setServer(mqtt_server, mqtt_port);
  conectaMQTT();

  pinMode(PIN_SENSOR, INPUT_PULLUP);
  pinMode(PIN_LED_LIVRE, OUTPUT);
  pinMode(PIN_LED_OCUPADA, OUTPUT);

  digitalWrite(PIN_LED_LIVRE, LOW);
  digitalWrite(PIN_LED_OCUPADA, HIGH);

  Serial.println("Sistema de vaga 3 iniciado (Vaga OCUPADA).");
}

void loop() {
  if (!client.connected()) {
    conectaMQTT();
  }
  client.loop();

  bool ocupado = (digitalRead(PIN_SENSOR) == LOW);

  if (ocupado) {
    digitalWrite(PIN_LED_LIVRE, LOW);
    digitalWrite(PIN_LED_OCUPADA, HIGH);
    Serial.println("Vaga 3 OCUPADA");

    // MQTT - VAGA 3 (OCUPADA)
    client.publish("estacionamento/vaga3/status", "ocupada");

  } else {
    digitalWrite(PIN_LED_LIVRE, HIGH);
    digitalWrite(PIN_LED_OCUPADA, LOW);
    Serial.println("Vaga 3 LIVRE");

    // MQTT - VAGA 3 (LIVRE)
    client.publish("estacionamento/vaga3/status", "livre");
  }

  delay(300);
}

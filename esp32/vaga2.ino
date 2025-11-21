const int PIN_SENSOR      = 15; // Switch -> D15 (pino 7 lado direito)
const int PIN_LED_LIVRE   = 2;  // LED verde -> D2 (pino 16 lado esquerdo)
const int PIN_LED_OCUPADA = 4;  // LED vermelho -> D4 (pino 17 lado esquerdo)

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
  Serial.print("Conectando ao WiFi");

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

    // 🔄 CLIENT ID EXCLUSIVO DA VAGA 2
    if (client.connect("vaga2_client")) {
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

  Serial.println("Sistema de vaga 2 iniciado (Vaga OCUPADA).");
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
    Serial.println("Vaga 2 OCUPADA");

    // 🔗 ENVIA STATUS PARA O MQTT — VAGA 2
    client.publish("estacionamento/vaga2/status", "ocupada");

  } else {
    digitalWrite(PIN_LED_LIVRE, HIGH);
    digitalWrite(PIN_LED_OCUPADA, LOW);
    Serial.println("Vaga 2 LIVRE");

    // 🔗 ENVIA STATUS PARA O MQTT — VAGA 2
    client.publish("estacionamento/vaga2/status", "livre");
  }

  delay(300);
}

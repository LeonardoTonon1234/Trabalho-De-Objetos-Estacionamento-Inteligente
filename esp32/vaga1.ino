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

    if (client.connect("vaga1_client")) {
      Serial.println("Conectado!");
      // Aqui podemos assinar tópicos se precisar (não vamos usar agora)
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

  // Vaga começa OCUPADA
  digitalWrite(PIN_LED_LIVRE, LOW);
  digitalWrite(PIN_LED_OCUPADA, HIGH);

  Serial.println("Sistema de vaga iniciado (Vaga OCUPADA).");
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
    Serial.println("Vaga OCUPADA");

    // 🔗 ENVIA STATUS PARA O MQTT
    client.publish("estacionamento/vaga1/status", "ocupada");

  } else {
    digitalWrite(PIN_LED_LIVRE, HIGH);
    digitalWrite(PIN_LED_OCUPADA, LOW);
    Serial.println("Vaga LIVRE");

    // 🔗 ENVIA STATUS PARA O MQTT
    client.publish("estacionamento/vaga1/status", "livre");
  }

  delay(300);
}

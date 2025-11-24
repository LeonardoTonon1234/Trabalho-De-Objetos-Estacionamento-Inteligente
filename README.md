# Estacionamento Inteligente – Sistema IoT com ESP32, MQTT, Node-RED, InfluxDB e Grafana

## 👥 Integrantes do Grupo
- **Leonardo De Castro Tonon** – RA: 10426930  
- **Marcel Nobrega Zamboni** – RA: 10417821  
- **João Pedro Fernandes Milhomens** – RA: 10417578  

---

## 🚗 Sobre o Projeto

Este projeto apresenta um **Estacionamento Inteligente** utilizando Internet das Coisas (IoT), comunicação via MQTT e visualização de dados em tempo real no Grafana.  
O sistema simula três vagas de estacionamento, cada uma monitorada individualmente e integrada a um fluxo completo de automação.

O objetivo principal é demonstrar:
- Monitoramento em tempo real de **vagas livres e ocupadas**
- **Envio automático** de dados via MQTT
- **Processamento low-code** com Node-RED
- **Armazenamento histórico** no InfluxDB
- **Dashboards avançados** no Grafana

---

## 🧩 Arquitetura do Sistema

### **1. ESP32 – Simulação no Wokwi**
Cada vaga possui:
- 1 LED verde (vaga livre)  
- 1 LED vermelho (vaga ocupada)  
- 1 botão/switch para alternar o estado  

### 🔗 **Links dos Arduinos utilizados**
- **Vaga 1:** https://wokwi.com/projects/448077469127603201  
- **Vaga 2:** https://wokwi.com/projects/448072349126302721  
- **Vaga 3:** https://wokwi.com/projects/448072489850477569  

Os dispositivos enviam os status via MQTT utilizando o tópico:
- estacionamento/vaga1
- estacionamento/vaga2
- estacionamento/vaga3
![Print](https://github.com/LeonardoTonon1234/Trabalho-De-Objetos-Estacionamento-Inteligente/blob/main/esp32/imagem_2025-11-21_170137302.png)

---

### **2. Broker MQTT – HiveMQ**
Responsável por receber as mensagens enviadas pelos ESP32.

Configuração usada:
- Broker: broker.hivemq.com
- Porta: 1883
- Tópicos: estacionamento/#
---

### **3. Node-RED – Processamento dos Dados**
Funções do fluxo:
- Receber mensagens MQTT
- Tratar e converter valores
- Enviar status ao InfluxDB
- Criar automações e lógicas simples

O projeto utiliza exclusivamente **programação low-code**.

![Print](https://github.com/LeonardoTonon1234/Trabalho-De-Objetos-Estacionamento-Inteligente/blob/main/node-red/imagem_2025-11-21_170016983.png
)

---

### **4. Banco de Dados – InfluxDB**
Armazena:
- Status das 3 vagas
- Histórico completo de ocupação
- Quantidade total de vagas ocupadas

Bucket utilizado:
- estacionamento

---

### **5. Grafana – Dashboards**

#### 📊 **Dashboard 1 – Status das Vagas (Tempo Real)**
- 3 indicadores Gauge (vaga1, vaga2, vaga3)
- Cores dinâmicas (verde / vermelho)
- Atualização automática
![Print](https://github.com/LeonardoTonon1234/Trabalho-De-Objetos-Estacionamento-Inteligente/blob/main/dashboards/Dashboard%20Estacionamento-1763755913104.png
)

#### 📈 **Dashboard 2 – Resumo do Estacionamento**
Inclui:
- Total de vagas ocupadas com escala de cores (verde, amarelo, laranja, vermelho)
- Histórico de ocupação
![Print](https://github.com/LeonardoTonon1234/Trabalho-De-Objetos-Estacionamento-Inteligente/blob/main/dashboards/RESUMO%20DO%20ESTACIONAMENTO-1763755620039.png)

---

## 📌 Conclusão

Este projeto demonstra como integrar ESP32 + MQTT + Node-RED + InfluxDB + Grafana em um sistema funcional de IoT.  
O resultado final permite monitorar um estacionamento completo em tempo real, visualizar indicadores, analisar histórico e entender padrões de utilização.

---

## 📜 Licença
Projeto acadêmico desenvolvido para fins educacionais.
---

## Link do Vídeo 

- https://youtu.be/m3tlUyz49YI

---



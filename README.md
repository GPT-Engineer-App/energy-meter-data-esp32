# energy-meter-data-esp32

Buscando obter dados de um medidor bidirecional conectado a rede elétrica e a um sistema de geração de energia.
Usando um ESP32 conectado a saida serial do medidor, Foi criado o código a seguir.
Reescreva o codigo inserindo o maximo de comentarios e faça melhorias na variaveis


#include <WiFi.h>

// Definições de SSID e senha da rede Wi-Fi
const char* ssid = "CLARO_2G982C7C";
const char* password = "********";

// Criação do servidor na porta 80
WiFiServer server(80);

// Função para gerenciar a conexão Wi-Fi
void relay_wifi();

// Variáveis globais para armazenar os dados do medidor
int M, tamanho, escopo, indice;
int n = 0;
byte D1, D2, D3, D4, D5, und, dez;
byte atv1, atv2, atv3, rev1, rev2, rev3;
byte reati1, reati2, reati3, reatc1, reatc2, reatc3;
unsigned long identidade, atv, rev, reati, reatc;

void setup() {
    // Inicialização das comunicações seriais
    Serial.begin(2400);
    Serial2.begin(2400);

    // Conectando ao Wi-Fi
    Serial.println();
    Serial.print("Conectando-se a ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    // Espera até que a conexão seja estabelecida
    while (WiFi.status() != WL_CONNECTED) {
        delay(741);
        Serial.print(".");
    }

    // Conexão Wi-Fi estabelecida
    Serial.println("");
    Serial.println("WiFi Conectado");
    Serial.println("Endereço IP:");
    Serial.println(WiFi.localIP());

    // Inicia o servidor
    server.begin();
}

void loop() {
    // Verifica se a conexão Wi-Fi está ativa
    while (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, password);
        Serial.print(".");
        delay(741);
    }

    // Gerencia a conexão Wi-Fi e responde aos clientes
    relay_wifi();

    // Verifica se há dados disponíveis na Serial2
    if (Serial2.available()) {
        M = Serial2.read();

        // Verifica o início da sequência de dados
        if (M == 170) {
            if (Serial2.available()) {
                M = Serial2.read();
                if (M == 85) {
                    Serial.println("_____________________________________");

                    // Leitura do ID do medidor
                    if (Serial2.available()) {
                        D1 = Serial2.read();
                        dez = D1 >> 4;
                        und = D1 << 4;
                        und = und >> 4;
                        D1 = (dez * 10) + (und);

                        if (Serial2.available()) {
                            D2 = Serial2.read();
                            dez = D2 >> 4;
                            und = D2 << 4;
                            und = und >> 4;
                            D2 = (dez * 10) + (und);

                            if (Serial2.available()) {
                                D3 = Serial2.read();
                                dez = D3 >> 4;
                                und = D3 << 4;
                                und = und >> 4;
                                D3 = (dez * 10) + (und);

                                if (Serial2.available()) {
                                    D4 = Serial2.read();
                                    dez = D4 >> 4;
                                    und = D4 << 4;
                                    und = und >> 4;
                                    D4 = (dez * 10) + (und);

                                    if (Serial2.available()) {
                                        D5 = Serial2.read();
                                        dez = D5 >> 4;
                                        und = D5 << 4;
                                        und = und >> 4;
                                        D5 = (dez * 10) + (und);

                                        identidade = (D5) + (D4 * 100) + (D3 * 10000) + (D2 * 1000000) + (D1 * 100000000);
                                        Serial.println(identidade);

                                        // Leitura dos dados de consumo de energia
                                        if (Serial2.available()) {
                                            tamanho = (Serial2.read() - 2);

                                            if (Serial2.available()) {
                                                escopo = Serial2.read();

                                                if (Serial2.available()) {
                                                    indice = Serial2.read();

                                                    if (indice == 2) {
                                                        Serial.println("ENERGIA ATIVA CONSUMIDA");

                                                        if (Serial2.available()) {
                                                            atv1 = Serial2.read();
                                                            dez = atv1 >> 4;
                                                            und = atv1 << 4;
                                                            und = und >> 4;
                                                            atv1 = (dez * 10) + (und);

                                                            if (Serial2.available()) {
                                                                atv2 = Serial2.read();
                                                                dez = atv2 >> 4;
                                                                und = atv2 << 4;
                                                                und = und >> 4;
                                                                atv2 = (dez * 10) + (und);

                                                                if (Serial2.available()) {
                                                                    atv3 = Serial2.read();
                                                                    dez = atv3 >> 4;
                                                                    und = atv3 << 4;
                                                                    und = und >> 4;
                                                                    atv3 = (dez * 10) + (und);

                                                                    atv = (atv3) + (atv2 * 100) + (atv1 * 10000);
                                                                    Serial.println(atv);
                                                                }
                                                            }
                                                        }
                                                    }

                                                    if (indice == 81) {
                                                        Serial.println("ENERGIA ATIVA REVERSA");

                                                        if (Serial2.available()) {
                                                            rev1 = Serial2.read();
                                                            dez = rev1 >> 4;
                                                            und = rev1 << 4;
                                                            und = und >> 4;
                                                            rev1 = (dez * 10) + (und);

                                                            if (Serial2.available()) {
                                                                rev2 = Serial2.read();
                                                                dez = rev2 >> 4;
                                                                und = rev2 << 4;
                                                                und = und >> 4;
                                                                rev2 = (dez * 10) + (und);

                                                                if (Serial2.available()) {
                                                                    rev3 = Serial2.read();
                                                                    dez = rev3 >> 4;
                                                                    und = rev3 << 4;
                                                                    und = und >> 4;
                                                                    rev3 = (dez * 10) + (und);

                                                                    rev = (rev3) + (rev2 * 100) + (rev1 * 10000);
                                                                    Serial.println(rev);
                                                                }
                                                            }
                                                        }
                                                    }

                                                    if (indice == 7) {
                                                        Serial.println("ENERGIA REATIVA INDUTIVA");

                                                        if (Serial2.available()) {
                                                            reati1 = Serial2.read();
                                                            dez = reati1 >> 4;
                                                            und = reati1 << 4;
                                                            und = und >> 4;
                                                            reati1 = (dez * 10) + (und);

                                                            if (Serial2.available()) {
                                                                reati2 = Serial2.read();
                                                                dez = reati2 >> 4;
                                                                und = reati2 << 4;
                                                                und = und >> 4;
                                                                reati2 = (dez * 10) + (und);

                                                                if (Serial2.available()) {
                                                                    reati3 = Serial2.read();
                                                                    dez = reati3 >> 4;
                                                                    und = reati3 << 4;
                                                                    und = und >> 4;
                                                                    reati3 = (dez * 10) + (und);

                                                                    reati = (reati3) + (reati2 * 100) + (reati1 * 10000);
                                                                    Serial.println(reati);
                                                                }
                                                            }
                                                        }
                                                    }

                                                    if (indice == 12) {
                                                        Serial.println("ENERGIA REATIVA CAPACITIVA");

                                                        if (Serial2.available()) {
                                                            reatc1 = Serial2.read();
                                                            dez = reatc1 >> 4;
                                                            und = reatc1 << 4;
                                                            und = und >> 4;
                                                            reatc1 = (dez * 10) + (und);

                                                            if (Serial2.available()) {
                                                                reatc2 = Serial2.read();
                                                                dez = reatc2 >> 4;
                                                                und = reatc2 << 4;
                                                                und = und >> 4;
                                                                reatc2 = (dez * 10) + (und);

                                                                if (Serial2.available()) {
                                                                    reatc3 = Serial2.read();
                                                                    dez = reatc3 >> 4;
                                                                    und = reatc3 << 4;
                                                                    und = und >> 4;
                                                                    reatc3 = (dez * 10) + (und);

                                                                    reatc = (reatc3) + (reatc2 * 100) + (reatc1 * 10000);
                                                                    Serial.println(reatc);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void relay_wifi() {
    WiFiClient client = server.available();

    if (client) {
        Serial.println("Novo cliente conectado");
        String currentLine = "";

        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);

                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-Type: text/html");
                        client.println();
                        client.println();
                        client.print("<h2>Medidor</h2>");
                        client.print(identidade);
                        client.print("<h2>ENERGIA ATIVA CONSUMIDA</h2>");
                        client.print(atv);
                        client.print("<h2>ENERGIA ATIVA REVERSA</h2>");
                        client.print(rev);
                        client.print("<h2>ENERGIA REATIVA INDUTIVA</h2>");
                        client.print(reati);
                        client.print("<h2>ENERGIA REATIVA CAPACITIVA</h2>");
                        client.print(reatc);
                        break;
                    } else {
                        currentLine = "";
                    }
                } else if (c != '\r') {
                    currentLine += c;
                }
            }
        }

        client.stop();
        Serial.println("Cliente desconectado");
    }
}


## Collaborate with GPT Engineer

This is a [gptengineer.app](https://gptengineer.app)-synced repository 🌟🤖

Changes made via gptengineer.app will be committed to this repo.

If you clone this repo and push changes, you will have them reflected in the GPT Engineer UI.

## Tech stack

This project is built with React with shadcn-ui and Tailwind CSS.

- Vite
- React
- shadcn/ui
- Tailwind CSS

## Setup

```sh
git clone https://github.com/GPT-Engineer-App/energy-meter-data-esp32.git
cd energy-meter-data-esp32
npm i
```

```sh
npm run dev
```

This will run a dev server with auto reloading and an instant preview.

## Requirements

- Node.js & npm - [install with nvm](https://github.com/nvm-sh/nvm#installing-and-updating)

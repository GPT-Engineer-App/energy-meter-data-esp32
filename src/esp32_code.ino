#include <WiFi.h>

// Wi-Fi network credentials
const char* wifiSSID = "CLARO_2G982C7C";
const char* wifiPassword = "********";

// Create a server on port 80
WiFiServer server(80);

// Function to manage Wi-Fi connection and handle client requests
void handleWiFiConnection();

// Global variables to store meter data
int meterData, dataLength, scope, index;
int retryCount = 0;
byte digit1, digit2, digit3, digit4, digit5, unit, tens;
byte activeEnergy1, activeEnergy2, activeEnergy3, reverseEnergy1, reverseEnergy2, reverseEnergy3;
byte reactiveInductive1, reactiveInductive2, reactiveInductive3, reactiveCapacitive1, reactiveCapacitive2, reactiveCapacitive3;
unsigned long meterID, activeEnergy, reverseEnergy, reactiveInductive, reactiveCapacitive;

void setup() {
    // Initialize serial communications
    Serial.begin(2400);
    Serial2.begin(2400);

    // Connect to Wi-Fi
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(wifiSSID);
    WiFi.begin(wifiSSID, wifiPassword);

    // Wait until the connection is established
    while (WiFi.status() != WL_CONNECTED) {
        delay(741);
        Serial.print(".");
    }

    // Wi-Fi connection established
    Serial.println("");
    Serial.println("WiFi Connected");
    Serial.println("IP Address:");
    Serial.println(WiFi.localIP());

    // Start the server
    server.begin();
}

void loop() {
    // Check if the Wi-Fi connection is active
    while (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(wifiSSID, wifiPassword);
        Serial.print(".");
        delay(741);
    }

    // Manage the Wi-Fi connection and respond to clients
    handleWiFiConnection();

    // Check if there is data available on Serial2
    if (Serial2.available()) {
        meterData = Serial2.read();

        // Check the start of the data sequence
        if (meterData == 170) {
            if (Serial2.available()) {
                meterData = Serial2.read();
                if (meterData == 85) {
                    Serial.println("_____________________________________");

                    // Read the meter ID
                    if (Serial2.available()) {
                        digit1 = Serial2.read();
                        tens = digit1 >> 4;
                        unit = digit1 << 4;
                        unit = unit >> 4;
                        digit1 = (tens * 10) + (unit);

                        if (Serial2.available()) {
                            digit2 = Serial2.read();
                            tens = digit2 >> 4;
                            unit = digit2 << 4;
                            unit = unit >> 4;
                            digit2 = (tens * 10) + (unit);

                            if (Serial2.available()) {
                                digit3 = Serial2.read();
                                tens = digit3 >> 4;
                                unit = digit3 << 4;
                                unit = unit >> 4;
                                digit3 = (tens * 10) + (unit);

                                if (Serial2.available()) {
                                    digit4 = Serial2.read();
                                    tens = digit4 >> 4;
                                    unit = digit4 << 4;
                                    unit = unit >> 4;
                                    digit4 = (tens * 10) + (unit);

                                    if (Serial2.available()) {
                                        digit5 = Serial2.read();
                                        tens = digit5 >> 4;
                                        unit = digit5 << 4;
                                        unit = unit >> 4;
                                        digit5 = (tens * 10) + (unit);

                                        meterID = (digit5) + (digit4 * 100) + (digit3 * 10000) + (digit2 * 1000000) + (digit1 * 100000000);
                                        Serial.println(meterID);

                                        // Read the energy consumption data
                                        if (Serial2.available()) {
                                            dataLength = (Serial2.read() - 2);

                                            if (Serial2.available()) {
                                                scope = Serial2.read();

                                                if (Serial2.available()) {
                                                    index = Serial2.read();

                                                    if (index == 2) {
                                                        Serial.println("ACTIVE ENERGY CONSUMED");

                                                        if (Serial2.available()) {
                                                            activeEnergy1 = Serial2.read();
                                                            tens = activeEnergy1 >> 4;
                                                            unit = activeEnergy1 << 4;
                                                            unit = unit >> 4;
                                                            activeEnergy1 = (tens * 10) + (unit);

                                                            if (Serial2.available()) {
                                                                activeEnergy2 = Serial2.read();
                                                                tens = activeEnergy2 >> 4;
                                                                unit = activeEnergy2 << 4;
                                                                unit = unit >> 4;
                                                                activeEnergy2 = (tens * 10) + (unit);

                                                                if (Serial2.available()) {
                                                                    activeEnergy3 = Serial2.read();
                                                                    tens = activeEnergy3 >> 4;
                                                                    unit = activeEnergy3 << 4;
                                                                    unit = unit >> 4;
                                                                    activeEnergy3 = (tens * 10) + (unit);

                                                                    activeEnergy = (activeEnergy3) + (activeEnergy2 * 100) + (activeEnergy1 * 10000);
                                                                    Serial.println(activeEnergy);
                                                                }
                                                            }
                                                        }
                                                    }

                                                    if (index == 81) {
                                                        Serial.println("REVERSE ACTIVE ENERGY");

                                                        if (Serial2.available()) {
                                                            reverseEnergy1 = Serial2.read();
                                                            tens = reverseEnergy1 >> 4;
                                                            unit = reverseEnergy1 << 4;
                                                            unit = unit >> 4;
                                                            reverseEnergy1 = (tens * 10) + (unit);

                                                            if (Serial2.available()) {
                                                                reverseEnergy2 = Serial2.read();
                                                                tens = reverseEnergy2 >> 4;
                                                                unit = reverseEnergy2 << 4;
                                                                unit = unit >> 4;
                                                                reverseEnergy2 = (tens * 10) + (unit);

                                                                if (Serial2.available()) {
                                                                    reverseEnergy3 = Serial2.read();
                                                                    tens = reverseEnergy3 >> 4;
                                                                    unit = reverseEnergy3 << 4;
                                                                    unit = unit >> 4;
                                                                    reverseEnergy3 = (tens * 10) + (unit);

                                                                    reverseEnergy = (reverseEnergy3) + (reverseEnergy2 * 100) + (reverseEnergy1 * 10000);
                                                                    Serial.println(reverseEnergy);
                                                                }
                                                            }
                                                        }
                                                    }

                                                    if (index == 7) {
                                                        Serial.println("REACTIVE INDUCTIVE ENERGY");

                                                        if (Serial2.available()) {
                                                            reactiveInductive1 = Serial2.read();
                                                            tens = reactiveInductive1 >> 4;
                                                            unit = reactiveInductive1 << 4;
                                                            unit = unit >> 4;
                                                            reactiveInductive1 = (tens * 10) + (unit);

                                                            if (Serial2.available()) {
                                                                reactiveInductive2 = Serial2.read();
                                                                tens = reactiveInductive2 >> 4;
                                                                unit = reactiveInductive2 << 4;
                                                                unit = unit >> 4;
                                                                reactiveInductive2 = (tens * 10) + (unit);

                                                                if (Serial2.available()) {
                                                                    reactiveInductive3 = Serial2.read();
                                                                    tens = reactiveInductive3 >> 4;
                                                                    unit = reactiveInductive3 << 4;
                                                                    unit = unit >> 4;
                                                                    reactiveInductive3 = (tens * 10) + (unit);

                                                                    reactiveInductive = (reactiveInductive3) + (reactiveInductive2 * 100) + (reactiveInductive1 * 10000);
                                                                    Serial.println(reactiveInductive);
                                                                }
                                                            }
                                                        }
                                                    }

                                                    if (index == 12) {
                                                        Serial.println("REACTIVE CAPACITIVE ENERGY");

                                                        if (Serial2.available()) {
                                                            reactiveCapacitive1 = Serial2.read();
                                                            tens = reactiveCapacitive1 >> 4;
                                                            unit = reactiveCapacitive1 << 4;
                                                            unit = unit >> 4;
                                                            reactiveCapacitive1 = (tens * 10) + (unit);

                                                            if (Serial2.available()) {
                                                                reactiveCapacitive2 = Serial2.read();
                                                                tens = reactiveCapacitive2 >> 4;
                                                                unit = reactiveCapacitive2 << 4;
                                                                unit = unit >> 4;
                                                                reactiveCapacitive2 = (tens * 10) + (unit);

                                                                if (Serial2.available()) {
                                                                    reactiveCapacitive3 = Serial2.read();
                                                                    tens = reactiveCapacitive3 >> 4;
                                                                    unit = reactiveCapacitive3 << 4;
                                                                    unit = unit >> 4;
                                                                    reactiveCapacitive3 = (tens * 10) + (unit);

                                                                    reactiveCapacitive = (reactiveCapacitive3) + (reactiveCapacitive2 * 100) + (reactiveCapacitive1 * 10000);
                                                                    Serial.println(reactiveCapacitive);
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

void handleWiFiConnection() {
    WiFiClient client = server.available();

    if (client) {
        Serial.println("New client connected");
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
                        client.print("<h2>Meter</h2>");
                        client.print(meterID);
                        client.print("<h2>ACTIVE ENERGY CONSUMED</h2>");
                        client.print(activeEnergy);
                        client.print("<h2>REVERSE ACTIVE ENERGY</h2>");
                        client.print(reverseEnergy);
                        client.print("<h2>REACTIVE INDUCTIVE ENERGY</h2>");
                        client.print(reactiveInductive);
                        client.print("<h2>REACTIVE CAPACITIVE ENERGY</h2>");
                        client.print(reactiveCapacitive);
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
        Serial.println("Client disconnected");
    }
}
#include <Wire.h>

#include <DHT.h>

#include <SPI.h>
#include <Ethernet.h>
#include <DallasTemperature.h>

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

DHT dht(7, DHT22);

int watersensor   = 0; // Pin analogico a cui è collegato il watersensor

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xAD
};

// DNS
IPAddress dnServer(192, 168, 15, 210);
// GW
IPAddress gateway(192, 168, 15, 253);
// NM
IPAddress subnet(255, 255, 255, 0);
// IP
IPAddress ip(192, 168, 15, 190);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  sensors.begin();

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  int lettura = analogRead(watersensor);
  sensors.requestTemperatures();
  Serial.print("Dallas temp: ");
  Serial.println(sensors.getTempCByIndex(0));
  Serial.print("DHT22 Temp: ");
  Serial.println(dht.readTemperature());
  Serial.print("DHT22 hum: ");
  Serial.println(dht.readHumidity());
  Serial.print("Water height: ");
  Serial.println(lettura);
  delay(1000);
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        //Serial.write(c);
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 5");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html><head><title>ArduSensor Temperatura e umidita'</title></head><body>");
          client.print("<p>TemperaturaA: ");
          client.println(sensors.getTempCByIndex(0));
          client.print("<p>TemperaturaB: ");
          client.print(dht.readTemperature());
          client.print("<p>UmiditaC: ");
          client.print(dht.readHumidity());
          client.print("<p>WaterheightD: ");
          client.print(lettura);
          client.println("</p><br /></body></html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

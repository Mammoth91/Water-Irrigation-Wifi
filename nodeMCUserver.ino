#include <ESP8266WiFi.h>
const char* ssid = "Wifi SSID"; // enter wifi network
const char* password = "Wifi Password"; // enter wifi network password
const int hour = 3600000; //3600000
const int thirdymin = 1800000; //1800000
const int fifteenmin = 900000; //900000
const int nowater = 0;
int watertimeF = 0;
int watertimeB = 0;
int watercountF = 0;
int watercountB = 0;
String req;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(5, OUTPUT);  // D1
  pinMode(4, OUTPUT);  // D2
  digitalWrite(5, 0);
  digitalWrite(4, 0);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void request() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }
  req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
}

void water() {
  digitalWrite(4, HIGH);
  while (1) {
    request();
    watercountF = watercountF + 1;
    if (watercountF == watertimeF || watertimeF == 0) {
      watercountF = 0;
      digitalWrite(4, LOW);
      break;
    }
    if (req.indexOf("/gpio/0/0") != -1) {
      watercountF = 0;
      digitalWrite(4, LOW);
      break;
    }
    delay(1);
  }
  digitalWrite(5, HIGH);
  while (1) {
    request();
    watercountB = watercountB + 1;
    if (watercountB == watertimeB || watertimeB == 0) {
      watercountB = 0;
      digitalWrite(5, LOW);
      break;
    }
    if (req.indexOf("/gpio/0/0") != -1) {
      watercountB = 0;
      digitalWrite(5, LOW);
      break;
    }
    delay(1);
  }
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }
  req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  if (req.indexOf("/gpio/1/1") != -1) {
    watertimeF = hour;
    watertimeB = hour;
    water();
  } else if (req.indexOf("/gpio/1/2") != -1) {
    watertimeF = hour;
    watertimeB = thirdymin;
    water();
  } else if (req.indexOf("/gpio/1/3") != -1) {
    watertimeF = hour;
    watertimeB = fifteenmin;
    water();
  } else if (req.indexOf("/gpio/1/4") != -1) {
    watertimeF = hour;
    watertimeB = nowater;
    water();
  } else if (req.indexOf("/gpio/2/1") != -1) {
    watertimeF = thirdymin;
    watertimeB = hour;
    water();
  } else if (req.indexOf("/gpio/2/2") != -1) {
    watertimeF = thirdymin;
    watertimeB = thirdymin;
    water();
  } else if (req.indexOf("/gpio/2/3") != -1) {
    watertimeF = thirdymin;
    watertimeB = fifteenmin;
    water();
  } else if (req.indexOf("/gpio/2/4") != -1) {
    watertimeF = thirdymin;
    watertimeB = nowater;
    water();
  } else if (req.indexOf("/gpio/3/1") != -1) {
    watertimeF = fifteenmin;
    watertimeB = hour;
    water();
    digitalWrite(4, LOW);
  } else if (req.indexOf("/gpio/3/2") != -1) {
    watertimeF = fifteenmin;
    watertimeB = thirdymin;
    water();
  } else if (req.indexOf("/gpio/3/3") != -1) {
    watertimeF = fifteenmin;
    watertimeB = fifteenmin;
    water();
  } else if (req.indexOf("/gpio/3/4") != -1) {
    watertimeF = fifteenmin;
    watertimeB = nowater;
    water();
  } else if (req.indexOf("/gpio/4/1") != -1) {
    watertimeF = nowater;
    watertimeB = hour;
    water();
  } else if (req.indexOf("/gpio/4/2") != -1) {
    watertimeF = nowater;
    watertimeB = thirdymin;
    water();
  } else if (req.indexOf("/gpio/4/3") != -1) {
    watertimeF = nowater;
    watertimeB = fifteenmin;
    water();
  } else if (req.indexOf("/gpio/5/5") != -1) {
    digitalWrite(5, HIGH);
    delay(20000);
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
    delay(20000);
    digitalWrite(4, LOW);
  } else if (req.indexOf("/gpio/0/0") != -1) {
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
  } else {
    Serial.println("invalid request");
    client.stop();
    return;
  }
  client.flush();
}

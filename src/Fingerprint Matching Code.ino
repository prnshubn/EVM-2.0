#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include <Wire.h>
#include "SSD1306Wire.h"

#define SDA 21
#define SCL 22
 
SSD1306Wire display(0x3c, SDA, SCL);

#define button_pinA 12
#define button_pinB 14

int button_press_countA = 0;
int button_stateA = 0;
int prev_button_stateA = 0;

int button_press_countB = 0;
int button_stateB = 0;
int prev_button_stateB = 0;

const char* NAME;
const char* PHONENO;

String Event_Name = "Temp_logs";
String Event_Name_Vote = "Vote_Count";

String Key = " "; //your key

// Replace with your unique IFTTT URL resource
String resource = "/trigger/" + Event_Name + "/with/key/" + Key;
String resourceVote = "/trigger/" + Event_Name_Vote + "/with/key/" + Key;

// Maker Webhooks IFTTT
const char* server = "maker.ifttt.com";

// Replace with your SSID and Password
const char* ssid     = " ";
const char* password = " ";

//Google Sheet
String GOOGLE_SCRIPT_ID = " ";

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);

void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  pinMode (button_pinA, INPUT); 
  pinMode (button_pinB, INPUT);

  //OLED
  display.init();
  Serial.println("\n\nEVM 2.0");
  display.clear();
  display.setFont(ArialMT_Plain_24);//font sizes of 10, 16 and 24 are available
  display.drawString(15,15,"EVM 2.0" );
  display.display();
  delay(3000);
  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) {
      delay(1);
    }
  }

  finger.getTemplateCount();
  
  Serial.print("Connecting to: ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);

  int timeout = 10 * 4; // 10 seconds
  while (WiFi.status() != WL_CONNECTED  && (timeout-- > 0)) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Failed to connect, going back to sleep");
  }

  Serial.print("WiFi connected in: ");
  Serial.print(millis());
  Serial.print(", IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");

}

void loop()                     // run over and over again
{
  getFingerprintIDez();

  display.clear();
  display.setFont(ArialMT_Plain_16);//font sizes of 10, 16 and 24 are available
  display.drawString(15,15,"Place Finger" );
  display.display();
  
  if (finger.fingerID == 1) {

    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "";
    PHONENO = "";
    if (finger.confidence >= 60) {
      Serial.print("Fingerprint matched with "); Serial.println(NAME);
      display.clear();
      display.drawString(5,0,"Hi " + String(NAME));
      display.setFont(ArialMT_Plain_10);
      display.drawString(10,20,"Look at the Camera");
      display.display();
      delay(5000);
      String str = spreadsheet_comm();
      if(str == ""){
        display.clear();
        display.drawString(5,0,"Face Matched!");
        delay(2000);
        display.clear();
        display.setFont(ArialMT_Plain_16);
        display.drawString(10,5,"Cast your vote");
        display.display();
        Serial.println("Press the button");
        String vt = vote();
        if(vt == "Yes"){
          makeIFTTTRequest();
          makeIFTTTRequestVote();
          Serial.println("Thanks for your valuable vote!");
          display.clear();
          display.drawString(15,15,"Thank you!");
          display.display();
          delay(5000);
        }
        else{
          Serial.println("You haven't pressed the button. Again verify your identity.");
        }
      }
      else{
        Serial.println("Face Does Not Match!");
        display.clear();
        display.setFont(ArialMT_Plain_10);
        display.drawString(10,15,"Face Doesn't match");
        display.display();
        delay(5000);
      }
    }

  }

  if (finger.fingerID == 2) {

    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "";
    PHONENO = "";
    if (finger.confidence >= 60) {
      Serial.print("Fingerprint matched with "); Serial.println(NAME);
      display.clear();
      display.drawString(5,0,"Hi " + String(NAME));
      display.setFont(ArialMT_Plain_10);
      display.drawString(10,20,"Look at the Camera");
      display.display();
      delay(5000);
      String str = spreadsheet_comm();
      if(str == ""){
        display.clear();
        display.drawString(5,0,"Face Matched!");
        delay(2000);
        display.clear();
        display.setFont(ArialMT_Plain_16);
        display.drawString(10,5,"Cast your vote");
        display.display();
        Serial.println("Press the button");
        String vt = vote();
        if(vt == "Yes"){
          makeIFTTTRequest();
          makeIFTTTRequestVote();
          Serial.println("Thanks for your valuable vote!");
          display.clear();
          display.drawString(15,15,"Thank you!");
          display.display();
          delay(5000);
        }
        else{
          Serial.println("You haven't pressed the button. Again verify your identity.");
        }
      }
      else{
        Serial.println("Face Does Not Match!");
        display.clear();
        display.setFont(ArialMT_Plain_10);
        display.drawString(10,15,"Face Doesn't match");
        display.display();
        delay(5000);
      }
    }

  }

  if (finger.fingerID == 3) {

    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "";
    PHONENO = "";
    if (finger.confidence >= 60) {
      Serial.print("Fingerprint matched with "); Serial.println(NAME);
      display.clear();
      display.drawString(5,0,"Hi " + String(NAME));
      display.setFont(ArialMT_Plain_10);
      display.drawString(10,20,"Look at the Camera");
      display.display();
      delay(5000);
      String str = spreadsheet_comm();
      if(str == ""){
        display.clear();
        display.drawString(5,0,"Face Matched!");
        delay(2000);
        display.clear();
        display.setFont(ArialMT_Plain_16);
        display.drawString(10,5,"Cast your vote");
        display.display();
        Serial.println("Press the button");
        String vt = vote();
        if(vt == "Yes"){
          makeIFTTTRequest();
          makeIFTTTRequestVote();
          Serial.println("Thanks for your valuable vote!");
          display.clear();
          display.drawString(15,15,"Thank you!");
          display.display();
          delay(5000);
        }
        else{
          Serial.println("You haven't pressed the button. Again verify your identity.");
        }
      }
      else{
        Serial.println("Face Does Not Match!");
        display.clear();
        display.setFont(ArialMT_Plain_10);
        display.drawString(10,15,"Face Doesn't match");
        display.display();
        delay(5000);
      }
    }

  }

  if (finger.fingerID == 4) {

    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "";
    PHONENO = "";
    if (finger.confidence >= 60) {
      Serial.print("Fingerprint matched with "); Serial.println(NAME);
      display.clear();
      display.drawString(5,0,"Hi " + String(NAME));
      display.setFont(ArialMT_Plain_10);
      display.drawString(10,20,"Look at the Camera");
      display.display();
      delay(5000);
      String str = spreadsheet_comm();
      if(str == ""){
        display.clear();
        display.drawString(5,0,"Face Matched!");
        delay(2000);
        display.clear();
        display.setFont(ArialMT_Plain_16);
        display.drawString(10,5,"Cast your vote");
        display.display();
        Serial.println("Press the button");
        String vt = vote();
        if(vt == "Yes"){
          makeIFTTTRequest();
          makeIFTTTRequestVote();
          Serial.println("Thanks for your valuable vote!");
          display.clear();
          display.drawString(15,15,"Thank you!");
          display.display();
          delay(5000);
        }
        else{
          Serial.println("You haven't pressed the button. Again verify your identity.");
        }
      }
      else{
        Serial.println("Face Does Not Match!");
        display.clear();
        display.setFont(ArialMT_Plain_10);
        display.drawString(10,15,"Face Doesn't match");
        display.display();
        delay(5000);
      }
    }

  }
  finger.fingerID = 0;
}

uint8_t getFingerprintID() {
  
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}

// Make an HTTP request to the IFTTT web service
void makeIFTTTRequest() {
  Serial.print("Connecting to ");
  Serial.print(server);

  WiFiClient client;
  int retries = 5;
  while (!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if (!!!client.connected()) {
    Serial.println("Failed to connect...");
  }

  Serial.print("Request resource: ");
  Serial.println(resource);

  String jsonObject = String("{\"value1\":\"") + NAME + "\",\"value2\":\"" + PHONENO
                      + "\"}";

  client.println(String("POST ") + resource + " HTTP/1.1");
  client.println(String("Host: ") + server);
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);

  int timeout = 5 * 10; // 5 seconds
  while (!!!client.available() && (timeout-- > 0)) {
    delay(100);
  }
  if (!!!client.available()) {
    Serial.println("No response...");
  }
  while (client.available()) {
    Serial.write(client.read());
  }

  Serial.println("\nclosing connection");
  client.stop();
}

//IFTTT request to send vote coun

void makeIFTTTRequestVote() {
  Serial.print("Connecting to ");
  Serial.print(server);

  WiFiClient client;
  int retries = 5;
  while (!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if (!!!client.connected()) {
    Serial.println("Failed to connect...");
  }

  Serial.print("Request resource: ");
  Serial.println(resourceVote);

  String jsonObject = String("{\"value1\":\"") + button_press_countA + "\",\"value2\":\"" + button_press_countB
                      + "\"}";

  client.println(String("POST ") + resourceVote + " HTTP/1.1");
  client.println(String("Host: ") + server);
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);

  int timeout = 5 * 10; // 5 seconds
  while (!!!client.available() && (timeout-- > 0)) {
    delay(100);
  }
  if (!!!client.available()) {
    Serial.println("No response...");
  }
  while (client.available()) {
    Serial.write(client.read());
  }

  Serial.println("\nclosing connection");
  client.stop();
}

//Get data from Google Sheet

String spreadsheet_comm(void) {
  HTTPClient http;
  String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?read";
  Serial.print("Making a request to Google Sheet");
  http.begin(url.c_str()); //Specify the URL and certificate
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode = http.GET();
  String payload;
    if (httpCode > 0) { //Check for the returning code
        payload = http.getString();
        
        Serial.println(httpCode);
        Serial.println(payload);
      }
    else {
      Serial.println("Error on HTTP request");
    }
  http.end();
  return payload;
}

String vote(){
  int v = 0;

  while(v == 0){
    button_stateA = digitalRead(button_pinA);
    button_stateB = digitalRead(button_pinB);

    if (button_stateA != prev_button_stateA) {
      if (button_stateA == HIGH) {

      } else { //button press
        button_press_countA++;
        v = 1;
//        Serial.println("ButtonA Pressed!");
      }
      delay(50);
    }
    prev_button_stateA = button_stateA;

    if (button_stateB != prev_button_stateB) {
      if (button_stateB == HIGH) {

      } else { //button press
        button_press_countB++;
//        Serial.println("ButtonB Pressed!");
        v = 1;
      }
      delay(50);
    }
    prev_button_stateB = button_stateB;
  }
  
  return "Yes";
}

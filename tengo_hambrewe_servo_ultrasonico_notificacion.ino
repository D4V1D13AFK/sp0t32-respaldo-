//Include libraries
#include <HTTPClient.h>
#include <WiFi.h>
#include <ESP32Servo.h>
#include <UrlEncode.h>

int trig = 4;   //Transmisor
int eco = 5;    //Receptor
int duracion;   //Variable para duracion del pulso
int distancia;  //Variable para hallar la distancia

//Add WIFI dataijijijij
const char* ssid = "POCO M5s";
const char* password = "UwU12345";

String phoneNumber = "5214612791065";
String apiKey = "8036142";

//Variables used in the code
String LED_id = "1";                   //Just in case you control more than 1 LED
volatile bool toggle_pressed = false;  //Each time we press the push button
String data_to_send = "";              //Text data to send to the server
unsigned long Actual_Millis, Previous_Millis;
int refresh_time = 200;  //Refresh rate of connection to website (recommended more than 1s)

Servo servo;

//Inputs/outputs

const int servoPin = 2;  // Connect servo on this pin (add 150ohm resistor)

//Button press interruption
void IRAM_ATTR isr() {
  toggle_pressed = true;
}

void setup() {
  delay(10);
  Serial.begin(115200);  //Start monitor


  servo.attach(servoPin);  //Attach servo to pin 2

  pinMode(trig, OUTPUT);
  pinMode(eco, INPUT);


  WiFi.begin(ssid, password);  //Start wifi connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {  //Check for the connection
    delay(500);
    Serial.print(".");
    sendMessage("tengo hambre we!");
  }

  Serial.print("Connected, my IP: ");
  Serial.println(WiFi.localIP());
  Actual_Millis = millis();  //Save time for refresh loop
  Previous_Millis = Actual_Millis;
}

void loop() {
  //We make the refresh loop using millis() so we don't have to use delay();
  Actual_Millis = millis();
  if (Actual_Millis - Previous_Millis > refresh_time) {
    Previous_Millis = Actual_Millis;
    if (WiFi.status() == WL_CONNECTED) {  //Check WiFi connection status
      HTTPClient http;                    //Create new client
      if (toggle_pressed) {               //If button was pressed we send text: "toggle_LED"
        data_to_send = "toggle_LED=" + LED_id;
        toggle_pressed = false;  //Also equal this variable back to false
      } else {
        data_to_send = "check_LED_STATUS=" + LED_id;  //If button wasn't pressed we send text: "check_LED_status"
      }

      //Begin new connection to website
      http.begin("https://sp0t32.000webhostapp.com/esp32_update.php");      //Indicate the destination webpage
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Prepare the header

      int response_code = http.POST(data_to_send);  //Send the POST. This will give us a response code

      //If the code is higher than 0, it means we received a response
      if (response_code > 0) {
        Serial.println("HTTP code " + String(response_code));  //Print return code

        if (response_code == 200) {                 //If code is 200, we received a good response and we can read the echo data
          String response_body = http.getString();  //Save the data coming from the website
          Serial.print("Server reply: ");           //Print data to the monitor for debug
          Serial.println(response_body);

          //If the received data is LED_is_off, we set LOW the LED pin
          if (response_body == "LED_is_off") {
            servo.write(0);
            delay(500);
          }
          //If the received data is LED_is_on, we set HIGH the LED pin
          else if (response_body == "LED_is_on") {
            servo.write(100);
            delay(500);
          }
        }  //End of response_code = 200
      }    //END of response_code > 0
      else {
        Serial.print("Error sending POST, code: ");
        Serial.println(response_code);
      }
      http.end();  //End the connection
    }              //END of WIFI connected
    else {
      Serial.println("WIFI connection error");
    }
  }
  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, LOW);

  duracion = pulseIn(eco, HIGH);  //Recibe el puslo
  distancia = duracion / 58.2;    //Calculo para hallar la distancia en cm

  Serial.print(distancia);
  Serial.println(" cm");
  delay(500);
}
void sendMessage(String message) {

  // Data to send with HTTP POST
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  HTTPClient http;
  http.begin(url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200) {
    Serial.print("Message sent successfully");
  } else {
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}

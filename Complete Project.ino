
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h> 
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

constexpr uint8_t RST_PIN = D3;     
constexpr uint8_t SS_PIN = D4;  
int relay = D0;
String content= "";
byte letter;
int id,name; 
int day,month,year,hour,minute,second;

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
LiquidCrystal_I2C lcd(0x27,16,2);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

const char *ssid     = "Pali";
const char *password = "9121945669";
const char* host = "api.thingspeak.com";
const char* privatekey="6X7YV8MDUVSY60GZ"; 
const char* privatekey1="RHH8D2DS4Z4DHEDH"; 


void setup() 
{
  Serial.begin(9600);
  SPI.begin(); 
  mfrc522.PCD_Init(); 
  lcd.init();        
  lcd.backlight();
  lcd.clear();  
  lcd.setCursor(4,0);
  lcd.print("Welcome!");
  lcd.setCursor(0,1);
  lcd.print("Please Scan Card");
  pinMode(relay,OUTPUT);
  digitalWrite(relay,HIGH);

  Serial.print("Connecting to "); 
  Serial.println(ssid);  
  WiFi.begin(ssid, password);   

  while (WiFi.status() != WL_CONNECTED)
  { 
   delay(500);  
   Serial.print("");  
  } 

  Serial.println("WiFi connected");   
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
  timeClient.begin();
  timeClient.setTimeOffset(19800);   
}

void loop() {

  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if (mfrc522.PICC_ReadCardSerial()) 
  { 
   Serial.print("UID tag :");
   String content= "";
   byte letter;
   for (byte i = 0; i < mfrc522.uid.size; i++) 
   {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
   }
   Serial.println();
   Serial.print("Message : ");
   content.toUpperCase();
   if (content.substring(1) == "CE B2 5C 88")
  {
    Serial.println("Access Granted");
    Serial.println();
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Card  Accepted");
    lcd.setCursor(1,1);
    lcd.print("Door  Unlocked");
    digitalWrite(relay,LOW);
    delay(5000);
    digitalWrite(relay,HIGH);
    delay(1000);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Thank  You  ");
    lcd.setCursor(2,1);
    lcd.print("Door Locked");

    timeClient.update();
    time_t epochTime = timeClient.getEpochTime();
    int hour= timeClient.getHours();
    int minute= timeClient.getMinutes();
    int second = timeClient.getSeconds();  
    struct tm *ptm = gmtime ((time_t *)&epochTime); 
    int day= ptm->tm_mday;
    int month = ptm->tm_mon+1;
    int year = ptm->tm_year+1900;
    Serial.println("");

    name=10;
    id=10;
    Serial.println("Name: Praveen");
    delay(1000);
    Serial.println("UID : CE B2 5C 88");
    Serial.print("connecting to "); 

    Serial.println(host);   
    
    WiFiClient client;  

    const int httpPort = 80;  

    if (!client.connect(host, httpPort)) 

    {     
      Serial.println("connection failed");     
      return; 
    }  

    String url = "/update"; 
    url += "?api_key=";  
    url += privatekey1;   
    url += "&field1="; 
    url += name;  
    url += "&field2=";  
    url += id; 
    url += "&field3="; 
    url += hour;  
    url += "&field4=";  
    url += minute; 
    url += "&field5="; 
    url += second;  
    url += "&field6=";  
    url += day; 
    url += "&field7="; 
    url += month;  
    url += "&field8=";  
    url += year; 

    Serial.print("Requesting URL: ");  

    Serial.println(url);  

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +  "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");  
    delay(1000);  

    while(client.available())   
    { 

      String line1 = client.readStringUntil('\r'); 
      Serial.print(line1);  
    }
   Serial.println(); 
   Serial.println("closing connection");  
  }
 else if (content.substring(1) == "5E E8 E8 87")
  {
    Serial.println("Access Granted");
    Serial.println();
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Card  Accepted");
    lcd.setCursor(1,1);
    lcd.print("Door  Unlocked");
    digitalWrite(relay,LOW);
    delay(5000);
    digitalWrite(relay,HIGH);
    delay(1000);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Thank  You  ");
    lcd.setCursor(2,1);
    lcd.print("Door Locked");

    timeClient.update();
    time_t epochTime = timeClient.getEpochTime();
    int hour= timeClient.getHours();
    int minute= timeClient.getMinutes();
    int second = timeClient.getSeconds();  
    struct tm *ptm = gmtime ((time_t *)&epochTime); 
    int day= ptm->tm_mday;
    int month = ptm->tm_mon+1;
    int year = ptm->tm_year+1900;
    Serial.println("");

    name=20;
    id=20;
    Serial.println("Name: Siva Ganesh");
    delay(1000);
    Serial.println("UID : 5E E8 E8 87");
    Serial.print("connecting to "); 

    Serial.println(host);   
    
    WiFiClient client;  

    const int httpPort = 80;  

    if (!client.connect(host, httpPort)) 

    {     
      Serial.println("connection failed");     
      return; 
    }  

    String url = "/update"; 
    url += "?api_key=";  
    url += privatekey1;   
    url += "&field1="; 
    url += name;  
    url += "&field2=";  
    url += id; 
    url += "&field3="; 
    url += hour;  
    url += "&field4=";  
    url += minute; 
    url += "&field5="; 
    url += second;  
    url += "&field6=";  
    url += day; 
    url += "&field7="; 
    url += month;  
    url += "&field8=";  
    url += year; 

    Serial.print("Requesting URL: ");  

    Serial.println(url);  

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +  "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");  
    delay(1000);  

    while(client.available())   
    { 

      String line1 = client.readStringUntil('\r'); 
      Serial.print(line1);  
    }
   Serial.println(); 
   Serial.println("closing connection");  
  }
 else if (content.substring(1) == "43 40 D1 F4")
  {
    Serial.println("Access Granted");
    Serial.println();
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Card  Accepted");
    lcd.setCursor(1,1);
    lcd.print("Door  Unlocked");
    digitalWrite(relay,LOW);
    delay(5000);
    digitalWrite(relay,HIGH);
    delay(1000);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Thank  You  ");
    lcd.setCursor(2,1);
    lcd.print("Door Locked");

    timeClient.update();
    time_t epochTime = timeClient.getEpochTime();
    int hour= timeClient.getHours();
    int minute= timeClient.getMinutes();
    int second = timeClient.getSeconds();  
    struct tm *ptm = gmtime ((time_t *)&epochTime); 
    int day= ptm->tm_mday;
    int month = ptm->tm_mon+1;
    int year = ptm->tm_year+1900;
    Serial.println("");

    name=30;
    id=30;
    Serial.println("Name: Manikanta");
    delay(1000);
    Serial.println("UID : 43 40 D1 F4");
    Serial.print("connecting to "); 

    Serial.println(host);   
    
    WiFiClient client;  

    const int httpPort = 80;  

    if (!client.connect(host, httpPort)) 

    {     
      Serial.println("connection failed");     
      return; 
    }  

    String url = "/update"; 
    url += "?api_key=";  
    url += privatekey1;   
    url += "&field1="; 
    url += name;  
    url += "&field2=";  
    url += id; 
    url += "&field3="; 
    url += hour;  
    url += "&field4=";  
    url += minute; 
    url += "&field5="; 
    url += second;  
    url += "&field6=";  
    url += day; 
    url += "&field7="; 
    url += month;  
    url += "&field8=";  
    url += year; 

    Serial.print("Requesting URL: ");  

    Serial.println(url);  

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +  "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");  
    delay(1000);  

    while(client.available())   
    { 

      String line1 = client.readStringUntil('\r'); 
      Serial.print(line1);  
    }
   Serial.println(); 
   Serial.println("closing connection");  
  }
 
 else   
 {
  lcd.clear();
  lcd.print("UnAuthorized");
  lcd.setCursor(0,1); 
  lcd.print("Invalid RFID Tag");
  Serial.println(" Access denied");
  lcd.setCursor(0,1);
  lcd.print("   Door Locked   ");
  delay(2000);
  lcd.clear();
  lcd.print("plz scan again");
  }
 }
}
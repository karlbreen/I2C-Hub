
#include <Wire.h>
#include <LCD_I2C.h>
LCD_I2C lcd(0x25, 16, 2); // Default address of most PCF8574 modules, change according

#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;

#include <HTTPClient.h>
HTTPClient http;


void setup(){

  Serial.begin(115200);
  delay(500);
  
  Serial.println("I2C Hub - Karl Breen 2023");
  Serial.println();Serial.println();
  
  Serial.println("Setup Begin");
  Serial.println();Serial.println();  
  /*
   * Scan for I2C devices
   * Serial print results
   */
  Serial.println("I2C Setup and Scan");
  Wire.begin();
  byte error, address;
  int nDevices = 0;

  delay(500);

  Serial.println("Scanning for I2C devices...");
  for(address = 0x01; address < 0x7f; address++){
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0){
      Serial.printf("I2C device found at address 0x%02X\n", address);
      nDevices++;
    } else if(error != 2){
      Serial.printf("Error %d at address 0x%02X\n", error, address);
    }
  }
  if (nDevices == 0){
    Serial.println("No I2C devices found");
  }
  Serial.println();Serial.println();
  Serial.println("LCD clear and prep");
  /*
   * LCD prep
   */
  lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
  lcd.backlight();
  lcd.print("Hello!");
  delay(500);
  Serial.println();Serial.println();
      
  /*
   * WiFi Connection
   */
  Serial.println("Wifi scan and connect");
  WiFi.mode(WIFI_STA);// Set WiFi to station mode and disconnect from an AP if it was previously connected.
  WiFi.disconnect();  //Turn off all wifi connections.
  
 /*
  * serial print of all networks found
  */
  Serial.println("Scanning for WiFi networks...");
  int n = WiFi.scanNetworks();  //return the number of networks found.
  if (n == 0){  //If no network is found.
    Serial.println("No networks found");
  }else{  //If a network is found. 
    Serial.printf("networks found:%d\n",n);
    for (int i = 0; i < n; ++i){ // Print SSID and RSSI for each network found.
      Serial.printf("%d:",i + 1);
      Serial.print(WiFi.SSID(i));
      Serial.printf("(%d)",WiFi.RSSI(i));
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      delay(10);
    }
  }

  /*
   * declaring several networks 
   */
  wifiMulti.addAP("One Router To Rule Them All", "10TheBoss");
  wifiMulti.addAP("Applejuice", "10TheBoss");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

  Serial.println("Connecting Wifi...");
  if(wifiMulti.run() == WL_CONNECTED) {
      Serial.println("WiFi connected");
      Serial.print("Network: ");
      Serial.println(WiFi.SSID());
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
  }
  /*
   * include error for unsuccesful connection
   */
   
  /*
   * print connected network name to LCD
   */
  lcd.clear();
  lcd.print(WiFi.SSID());
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  Serial.println();Serial.println();
  
  Serial.println("Setup Complete");
  Serial.println();Serial.println();
  

  /*
   * boot up message on Serial and LCD
   */
//  lcd.setCursor(13, 1);
//  lcd.print("1/8"); 

  /*
   * 404 check on all sources and update pages to display error
   * store each url as variable here and then 404 check
   * MET IE Weather Warnings https://www.met.ie/Open_Data/json/warning_IRELAND.json
   * MET IE Current Obs https://www.met.ie/Open_Data/xml/obs_present.xml
   */
  lcd.clear();
  Serial.println("Met IE Weather Warnings");
  lcd.print("Weather warnings");
  http.begin("https://www.met.ie/Open_Data/json/warning_IRELAND.json");
  Serial.println(http.GET());
  if(http.GET() > 0){
   Serial.println(http.getString());
   lcd.setCursor(0,1);
   lcd.print(http.getString()); 
  }else{
    Serial.println("No warnings");
    lcd.setCursor(0,1);
    lcd.print("No warnings");
  }
  
  
}//end of setup


void loop() {// put your main code here, to run repeatedly:

  

  
  /*
   * Local and additonal cities
   * time + date 
   * HH:MM (no seconds for now...)
   * DD/MM/YYYY
   * Timezone 
   */
   
  /* 
   * weather 
   * Weather Text
   * Temperature
   * Wind speed + direction
   */

  /* 
   * weather warnings 
   * "[]" is returned if no warnings are present
   */

  /*
   * sun rise & sun set times
   */

  /*
   * currency exchange rates
   * rates with aarrow symbol for todays trend
   */
    
  


 // delay(1000);
}//end of main loop

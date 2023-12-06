# ESP2866 Weather station

## Weather forecast 
This Application fetches a temperature   
forecast from given url and presents the result on oled panel  
Indoor temp and humidity is read with DHT-22 Sensor   
WiFi configuration based on WiFi manager (no need to store secrets to code)

TLDR;
* Setup webserver (for example https://github.com/vesakoo/fmiForecastEspoo  into crontab to genate files for your web server)
* Wire your board
* Clone this repo, upload firmware with Arduino IDE
* First run: Press the button on board to set up your Wifi router:
  * With your Mobile phone or computer, Scan Wifi networks and connect to "WeatherStation". This will automatically open a web page for Wifi AP setup (for ESP).  



Forecast format:
```
 08| 12| 18| 21|
 -3| -3| -2| -1|
Ulko: -7'C
```
row1: hour,  16 charaters   
row2: temp,   16 charaters   
row3: temp now   (max 11, varies)   

### Web backend (Server)
Example backend solution:  https://github.com/vesakoo/fmiForecastEspoo  
Creates a forecast.txt file that one can place into webserver to share. 

Example renders weather forecast on Finland / Espoo - area fetching the data  
from  Finish institute of meteorology Open data interface:   
https://www.ilmatieteenlaitos.fi/avoin-data   

### FmiWeatherStationesp2866 (this client)

![Picture](https://github.com/vesakoo/FmiWeatherStationesp2866/blob/main/pics/station.png?raw=true)



### Hardware
* IdeaSpark 2899 Dev board
* DHT-22 Tempereature and humidity sensor
* Switch (For starting WiFi Manager. It's used for WiFi AP configuration https://github.com/tzapu/WiFiManager
  

https://www.aliexpress.com/item/1005005242283189.html?gps-id=pcStoreJustForYou&scm=1007.23125.137358.0&scm_id=1007.23125.137358.0&scm-url=1007.23125.137358.0&pvid=492f1da5-0168-4e7f-85c7-8e3b85eef41f&_t=gps-id:pcStoreJustForYou,scm-url:1007.23125.137358.0,pvid:492f1da5-0168-4e7f-85c7-8e3b85eef41f,tpp_buckets:668%232846%238111%231996&pdp_npi=4%40dis%21EUR%215.47%215.47%21%21%215.79%21%21%402103249617018077493504245e5b81%2112000032335054938%21rec%21FI%212324326771%21


### Pinout
NOTE! Pinout may change from board to board. Look the GPIO <-> PIN -mapping from your manual!   

| GPIO | Usage | 
| ----|:----------------------------|
| 5 | DHT data|
| 4 | Switch to trigger Wifi Manager. Use only irq enabled pin, INPUT_PULLUP & RISING internal resistor in use |
| 14 | Oled SCA |
| 12 | Oled  SDL |


### Arduino ide setup (with example card)
 * Board type NodeMCU 1.0 (ESP-12E Module)   





### Requirements
* install libs

### Links
Esp8266 Pinout guide: https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/    
DHT-22 protocol: https://circuitdigest.com/microcontroller-projects/interface-dht22-sensor-module-with-arduino   








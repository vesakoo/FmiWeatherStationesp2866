# ESP2866 Weather station

## Weather forecast 
This Application fetches a temperature   
forecast from given url and presents the result on TXT 240x240 panel  
Indoor temp and humidity is read with DHT-22 Sensor   
WiFi configuration based on WiFi manager (no need to store secrets to code)

Forecast format:
```
 08| 12| 18| 21|
 -3| -3| -2| -1|
Ulko: -7'C
```
row1: hour
row2: temp
row3: temp now 

![alt text](https://github.com/vesakoo/FmiWeatherStationesp2866/blob/main/pics/station.png?raw=true)





### Web backend
Example backend solution:  https://github.com/vesakoo/fmiForecastEspoo  
Creates a weather.json file that one can place into webserver to share. 

Example renders weather forecast on Finland / Espoo - area fetching the data  
from  Finish institute of meteorology Open data interface:   
https://www.ilmatieteenlaitos.fi/avoin-data   


### Hardware
* IdeaSpark 2899

https://www.aliexpress.com/item/1005005242283189.html?gps-id=pcStoreJustForYou&scm=1007.23125.137358.0&scm_id=1007.23125.137358.0&scm-url=1007.23125.137358.0&pvid=492f1da5-0168-4e7f-85c7-8e3b85eef41f&_t=gps-id:pcStoreJustForYou,scm-url:1007.23125.137358.0,pvid:492f1da5-0168-4e7f-85c7-8e3b85eef41f,tpp_buckets:668%232846%238111%231996&pdp_npi=4%40dis%21EUR%215.47%215.47%21%21%215.79%21%21%402103249617018077493504245e5b81%2112000032335054938%21rec%21FI%212324326771%21


### Arduino ide setup (with example card)
 * Board type NodeMCU 1.0 (ESP-12E Module)   





### Requirements
* install libs   





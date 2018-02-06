# Check_Ardu_Temp
Little Arduino/Genuino sketck, based on Ethernet Shield (v1), that read the temperature from a DS18B20 and a DHT22 sensor. Then, a Nagios ckeck bash script compares the value with warning and critical parameters

## How it works
Arduino read the external temperature from DS18B20 thermometer, connected to pin 2 of the shield, and temperature and humidity from DHT22, connected to pin 7 of the shield. A Nagios check script, then, based on w3m text browser, read the temperature. Run check_ardu_temp.sh -h to show the help page of the check. 

## Arduino Libraries
All the extra Arduino libraries required are attached to this project. Download and you are ready to run!

## How to configure
The IP address is hardcoded: you have to configure it in the sketck, under the lines `// DNS` (DNS primary server), `// GW` (Network Gateway), `// NM` (Network Mask), `// IP` (IP Address). The DS18B20, as specified in the `ONE_WIRE_BUS` define, is connected to te pin number 2, while the data pin of the DHT22 is connected to the pin 7. You can personalize it.

## Future improvements
Now the sketch read only two sensors. But it can show more than two! Infact I left the otuput with an index, an upper case alphabet letter (A, B, C,..). This letter is used by the nagios check do require a specific sensor. Also, all the code is not bind to a temperature sensor: the code compare simply two (three, considering warning and critical value), decimal numbers. You can use for checking humidity, light, pressure, etc.

## Arduino sheme
![Arduino scheme](https://raw.githubusercontent.com/marcoterm/check_ardu_temp/master/scheme.png)

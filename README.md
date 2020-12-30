# IOT
Air Pollution Monitoring

Board Used:- Nodemcu \
Sensors Used:- MQ135,DHT11 \
IDE Used:- Ardunio IDE \

CONNECTIONS

DHT11 to Nodemcu: \
Vcc to 3v3(Nodemcu) \
Data to D3(Nodemcu) \
GND to GND(Nodemcu) \

MQ135 to Nodemcu: \
Pin1 of MQ135 to Vin(Nodemcu) \
Pin2 of MQ135 to GND(Nodemcu) \
Pin4 of MQ135 to A0(Nodemcu) \

This project is hosted on thingspeak.com
[click here](https://thingspeak.com/channels/1219203)

How to get api_key used in APMS.ino: \
  Create account on thingspeak and then create channel on thingspeak.
  Then in the channel search for API Keys 
  Select Write API Key from channel and paste it in APMS.ino on line 4.
  
How to get api_key to send email notification: \
  Go to My Profile on your thingspeak account
  and then look for API Keys and then look for Alerts API Key
  copy the key and paste it in notification.m on line 2.
 
To get notification on email: \
  Signin to thingspeak account
  then from Apps --> MATLAB Analysis --> click on new button
  and paste the code from notification.m to online interface 
  then click on save and run to get notification on email.

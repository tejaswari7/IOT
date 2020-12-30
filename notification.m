channelID = 1234567;	%change this to your channel_id 
alertApiKey = 'Alerts_API_Key'; %change this to your Alerts API Key
alertUrl="https://api.thingspeak.com/alerts/send";
options = weboptions("HeaderFields", ["ThingSpeak-Alerts-API-Key", alertApiKey]);
alertSubject = sprintf("Air Quality");
alert = " ";
quality = thingSpeakRead(channelID,'Fields',1);
temp = thingSpeakRead(channelID,'Fields',2);
hum = thingSpeakRead(channelID,'Fields',3);
msg = "Temperature: " + string(temp) + newline + "Humidity: " + string(hum) + newline + "Air Quality in ppm: " + string(quality)+ newline;
%disp(msg);
if (quality <= 50)
    alert = 'Air Quality: Good ';
elseif(quality > 50 && quality <= 100)
    alert = 'Air Quality: Moderate ';
elseif(quality > 100 && quality < 300)
    alert = 'Air Quality: Unhealthy ';
elseif(quality >= 300)
    alert = 'Air Quality: Hazardous ';
end
alertBody = strcat(msg,alert);
disp(alertBody);
webwrite(alertUrl , "body", alertBody, "subject", alertSubject, options);
import wdt
import time
import sys
import requests
from twilio.rest import Client

TWILIO_ACCOUNT_SID = 'AC0fccf287a3a66ab37a4c44e90e437908' # replace with your Account SID
TWILIO_AUTH_TOKEN = 'b746613363960903ac3738d76ea0d3db' # replace with your Auth Token
TWILIO_PHONE_SENDER = "+16067052993" # replace with the phone number you registered in twilio
TWILIO_PHONE_RECIPIENT = "+40755104677" # replace with your phone number

def send_text_alert(alert_str):
    """Sends an SMS text alert."""
    client = Client(TWILIO_ACCOUNT_SID, TWILIO_AUTH_TOKEN)
    message = client.messages.create(
        to=TWILIO_PHONE_RECIPIENT,
        from_=TWILIO_PHONE_SENDER,
        body=alert_str)
    #print(message.sid)

def retry(func, param=-1):
    r = 3
    ret = -1
    while ret < 0 and r > 0:
        time.sleep(0.1)
        if param != -1:
            ret = func(param)
        else:
            ret = func()
        r -= 1
    return ret
#wait for the internet connection
internet = 0
while internet == 0:
    try:
        if requests.get("https://google.com"):
            internet = 1
    except Exception as e:
        print("Waiting for the internet")
        time.sleep(1)

send_text_alert("Your system is up and running") #Send "power-up" SMS
retry(wdt.setPeriod, 0)  #Disable the wtchdog
retry(wdt.setRepowerOnBattery, 0) #Do not power back on if the main power is not present
while True:
    time.sleep(3)
    lineIn = retry(wdt.getVin)
    if lineIn < 3 and lineIn > -1: #if the main power drops below 3V
        send_text_alert("Main power fails, the system shuts down!") #Send "power-down" SMS
        retry(wdt.setPeriod, 30)  # update the period with your maximum time to shutdown
        from subprocess import call
        call("sudo shutdown -h now", shell=True)



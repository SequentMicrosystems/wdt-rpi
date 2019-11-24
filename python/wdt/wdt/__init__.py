import smbus
import time
import math

HW_ADD = 0x30

RELOAD_ADD = 0x00
RELOAD_KEY = 0xCA

WRITE_INTERVAL_ADD = 0x01
READ_INTERVAL_ADD = 0x03

WRITE_INITIAL_INTERVAL_ADD = 0x05
READ_INITIAL_INTERVAL_ADD = 0x07

RESETS_COUNT_ADD = 0x09
CLEAR_RESET_COUNT_ADD = 0x0b
V_IN_ADD = 0x0c

POWER_OFF_INTERVAL_SET_ADD = 14
POWER_OFF_INTERVAL_GET_ADD = 18
V_BAT_ADD = 22
V_OUT_ADD = 24
TEMP_ADD = 26
CHARGE_STAT_ADD = 27

WDT_MAX_POWER_OFF_INTERVAL = 31*24*3600 

bus = smbus.SMBus(1)

def getPeriod():
  try:
    val = bus.read_word_data(HW_ADD, READ_INTERVAL_ADD)
  except Exception as e:
    val = -1  
  return val
  
  
def setPeriod(val):
  ret = 1
  try:
    bus.write_word_data(HW_ADD, WRITE_INTERVAL_ADD, val)
  except:
    ret = -1
  return ret      


def reload():
  ret = 1
  try:
    bus.write_byte_data(HW_ADD, RELOAD_ADD, RELOAD_KEY)
  except:
    ret = -1
  return ret  
  
def  setDefaultPeriod(val):
  ret = 1
  if val > 10 and val < 65000:
    try:
      bus.write_word_data(HW_ADD, WRITE_INITIAL_INTERVAL_ADD, val)
    except:
      ret = -1
  else:
    ret = -1    
  return ret 
  
def getDefaultPeriod():
  try:
    val = bus.read_word_data(HW_ADD, READ_INITIAL_INTERVAL_ADD)
  except Exception as e:
    val = -1  
  return val  
  
def  setOffInterval(val):
  ret = 1
  if val > 2 and val < WDT_MAX_POWER_OFF_INTERVAL:
    buff =  [0,0,0,0]
    buff[0] = 0xff & val
    buff[1] = 0xff & (val >> 8)
    buff[2] = 0xff & (val >> 16)
    buff[3] = 0xff & (val >> 24)
    try:
      bus.write_i2c_block_data(HW_ADD, POWER_OFF_INTERVAL_SET_ADD, buff)
    except:
      ret = -1
  else:
    ret = -1    
  return ret 
  
def getOffInterval():
  try:
    buff = bus.read_i2c_block_data(HW_ADD, POWER_OFF_INTERVAL_GET_ADD, 4)
    val = buff[0] + (buff[1] << 8) + (buff[2] << 16) + (buff[3] << 24)
  except Exception as e:
    val = -1  
  return val    
  
def getResetCount():
  try:
    val = bus.read_word_data(HW_ADD, RESETS_COUNT_ADD)
  except Exception as e:
    val = -1  
  return val

def getVin():
  try:
    val = bus.read_word_data(HW_ADD, V_IN_ADD)
    v = val/1000.0
  except Exception as e:
    v = -1
  return v
  
def getVrasp():
  try:
    id = bus.read_byte_data(HW_ADD, RELOAD_ADD)
    if 1 == id:
      val = bus.read_word_data(HW_ADD, V_OUT_ADD)
      v = val/1000.0
    else:
      v = -1  
  except Exception as e:
    v = -1
  return v
  
def getVbat():
  try:
    id = bus.read_byte_data(HW_ADD, RELOAD_ADD)
    if 1 == id:
      val = bus.read_word_data(HW_ADD, V_BAT_ADD)
      v = val/1000.0
    else:
      v = -1  
  except Exception as e:
    v = -1
  return v  
  
def getTemp():
  try:
    id = bus.read_byte_data(HW_ADD, RELOAD_ADD)
    if 1 == id:
      val = bus.read_byte_data(HW_ADD, TEMP_ADD)
    else:
      val = -1
  except Exception as e:
    val = -1
  return val    
  
def getChargeStat():
  try:
    id = bus.read_byte_data(HW_ADD, RELOAD_ADD)
    if 1 == id:
      val = bus.read_byte_data(HW_ADD, CHARGE_STAT_ADD)
    else:
      val = -1  
  except Exception as e:
    val = -1
  return val      
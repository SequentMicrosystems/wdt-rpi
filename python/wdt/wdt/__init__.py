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
  try:
    bus.write_word_data(HW_ADD, WRITE_INITIAL_INTERVAL_ADD, val)
  except:
    ret = -1
  return ret 
  
def getDefaultPeriod():
  try:
    val = bus.read_word_data(HW_ADD, READ_INITIAL_INTERVAL_ADD)
  except Exception as e:
    val = -1  
  return val  
  
def getResetCount():
  try:
    val = bus.read_word_data(HW_ADD, RESETS_COUNT_ADD)
  except Exception as e:
    val = -1  
  return val

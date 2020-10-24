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
POWER_OFF_ON_BATTERY_ADD = 28

WDT_MAX_POWER_OFF_INTERVAL = 31 * 24 * 3600


def getPeriod():
    bus = smbus.SMBus(1)
    try:
        val = bus.read_word_data(HW_ADD, READ_INTERVAL_ADD)
    except Exception as e:
        val = -1
    bus.close()
    return val


def setPeriod(val):
    ret = 1
    if val < 1: #disable the watchdog
        val = 65001
    bus = smbus.SMBus(1)
    try:
        bus.write_word_data(HW_ADD, WRITE_INTERVAL_ADD, val)
    except Exception as e:
        ret = -1
    bus.close()
    return ret


def reload():
    ret = 1
    bus = smbus.SMBus(1)
    try:
        bus.write_byte_data(HW_ADD, RELOAD_ADD, RELOAD_KEY)
    except Exception as e:
        ret = -1
    bus.close()
    return ret


def setDefaultPeriod(val):
    ret = 1
    if 10 < val < 65000:
        bus = smbus.SMBus(1)
        try:
            bus.write_word_data(HW_ADD, WRITE_INITIAL_INTERVAL_ADD, val)
        except Exception as e:
            ret = -1
        bus.close()
    else:
        ret = -1
    return ret


def getDefaultPeriod():
    bus = smbus.SMBus(1)
    try:
        val = bus.read_word_data(HW_ADD, READ_INITIAL_INTERVAL_ADD)
    except Exception as e:
        val = -1
    bus.close()
    return val


def setOffInterval(val):
    ret = 1
    if 2 < val < WDT_MAX_POWER_OFF_INTERVAL:
        buff = [0, 0, 0, 0]
        buff[0] = 0xff & val
        buff[1] = 0xff & (val >> 8)
        buff[2] = 0xff & (val >> 16)
        buff[3] = 0xff & (val >> 24)
        bus = smbus.SMBus(1)
        try:
            bus.write_i2c_block_data(HW_ADD, POWER_OFF_INTERVAL_SET_ADD, buff)
        except Exception as e:
            ret = -1
        bus.close()
    else:
        ret = -1
    return ret


def getOffInterval():
    bus = smbus.SMBus(1)
    try:
        buff = bus.read_i2c_block_data(HW_ADD, POWER_OFF_INTERVAL_GET_ADD, 4)
        val = buff[0] + (buff[1] << 8) + (buff[2] << 16) + (buff[3] << 24)
    except Exception as e:
        val = -1
    bus.close()
    return val


def getResetCount():
    bus = smbus.SMBus(1)
    try:
        val = bus.read_word_data(HW_ADD, RESETS_COUNT_ADD)
    except Exception as e:
        val = -1
    bus.close()
    return val


def getVin():
    bus = smbus.SMBus(1)
    try:
        val = bus.read_word_data(HW_ADD, V_IN_ADD)
        v = val / 1000.0
    except Exception as e:
        v = -1
    bus.close()
    return v


def getVrasp():
    bus = smbus.SMBus(1)
    try:
        id = bus.read_byte_data(HW_ADD, RELOAD_ADD)
        if 1 == id:
            val = bus.read_word_data(HW_ADD, V_OUT_ADD)
            v = val / 1000.0
        else:
            v = -1
    except Exception as e:
        v = -1
    bus.close()
    return v


def getVbat():
    bus = smbus.SMBus(1)
    try:
        id = bus.read_byte_data(HW_ADD, RELOAD_ADD)
        if 1 == id:
            val = bus.read_word_data(HW_ADD, V_BAT_ADD)
            v = val / 1000.0
        else:
            v = -1
    except Exception as e:
        v = -1
    bus.close()
    return v


def getTemp():
    bus = smbus.SMBus(1)
    try:
        id = bus.read_byte_data(HW_ADD, RELOAD_ADD)
        if 1 == id:
            val = bus.read_byte_data(HW_ADD, TEMP_ADD)
        else:
            val = -1
    except Exception as e:
        val = -1
    bus.close()
    return val


def getChargeStat():
    bus = smbus.SMBus(1)
    try:
        id = bus.read_byte_data(HW_ADD, RELOAD_ADD)
        if 1 == id:
            val = 0x0f & bus.read_byte_data(HW_ADD, CHARGE_STAT_ADD)
        else:
            val = -1
    except Exception as e:
        val = -1
    bus.close()
    return val


def getRepowerOnBattery():
    bus = smbus.SMBus(1)
    val = -1
    try:
        id = bus.read_byte_data(HW_ADD, RELOAD_ADD)
        if 1 == id:
            id = 0xf0 & bus.read_byte_data(HW_ADD, CHARGE_STAT_ADD)
            if id > 0:
                val = bus.read_byte_data(HW_ADD, POWER_OFF_ON_BATTERY_ADD)
                if val > 0:
                    val = 0
                else:
                    val = 1
    except Exception as e:
        val = -1
    bus.close()
    return val


def setRepowerOnBattery(val):
    ret = -1
    bus = smbus.SMBus(1)
    if val != 0:
        val = 0
    else:
        val = 1
    try:
        id = bus.read_byte_data(HW_ADD, RELOAD_ADD)
        if 1 == id:
            id = 0xf0 & bus.read_byte_data(HW_ADD, CHARGE_STAT_ADD)
            if id > 0:
                bus.write_byte_data(HW_ADD, POWER_OFF_ON_BATTERY_ADD, val)
                ret = 1
    except Exception as e:
        ret = -1
    bus.close()
    return ret
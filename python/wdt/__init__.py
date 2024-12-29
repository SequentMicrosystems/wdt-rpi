import smbus2
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
POWER_SW_USAGE_ADD = 29
POWER_SW_STATUS_ADD = 30
POWER_SW_INT_OUT_ADD = 48



WDT_MAX_POWER_OFF_INTERVAL = 31 * 24 * 3600


def getPeriod():
    bus = smbus2.SMBus(1)
    try:
        val = bus.read_word_data(HW_ADD, READ_INTERVAL_ADD)
    except Exception as e:
        val = -1
    bus.close()
    return val


def setPeriod(val):
    ret = 1
    if val < 1:  # disable the watchdog
        val = 65001
    bus = smbus2.SMBus(1)
    try:
        bus.write_word_data(HW_ADD, WRITE_INTERVAL_ADD, val)
    except Exception as e:
        ret = -1
    bus.close()
    return ret


def reload():
    ret = 1
    bus = smbus2.SMBus(1)
    try:
        bus.write_byte_data(HW_ADD, RELOAD_ADD, RELOAD_KEY)
    except Exception as e:
        ret = -1
    bus.close()
    return ret


def setDefaultPeriod(val):
    ret = 1
    if 10 < val < 65000:
        bus = smbus2.SMBus(1)
        try:
            bus.write_word_data(HW_ADD, WRITE_INITIAL_INTERVAL_ADD, val)
        except Exception as e:
            ret = -1
        bus.close()
    else:
        ret = -1
    return ret


def getDefaultPeriod():
    bus = smbus2.SMBus(1)
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
        bus = smbus2.SMBus(1)
        try:
            bus.write_i2c_block_data(HW_ADD, POWER_OFF_INTERVAL_SET_ADD, buff)
        except Exception as e:
            ret = -1
        bus.close()
    else:
        ret = -1
    return ret


def getOffInterval():
    bus = smbus2.SMBus(1)
    try:
        buff = bus.read_i2c_block_data(HW_ADD, POWER_OFF_INTERVAL_GET_ADD, 4)
        val = buff[0] + (buff[1] << 8) + (buff[2] << 16) + (buff[3] << 24)
    except Exception as e:
        val = -1
    bus.close()
    return val


def getResetCount():
    bus = smbus2.SMBus(1)
    try:
        val = bus.read_word_data(HW_ADD, RESETS_COUNT_ADD)
    except Exception as e:
        val = -1
    bus.close()
    return val


def getVin():
    bus = smbus2.SMBus(1)
    try:
        val = bus.read_word_data(HW_ADD, V_IN_ADD)
        v = val / 1000.0
    except Exception as e:
        v = -1
    bus.close()
    return v


def getVrasp():
    bus = smbus2.SMBus(1)
    try:
        id = 1#  bus.read_byte_data(HW_ADD, RELOAD_ADD)
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
    bus = smbus2.SMBus(1)
    try:
        id = 1 # bus.read_byte_data(HW_ADD, RELOAD_ADD)
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
    bus = smbus2.SMBus(1)
    try:
        id = 1 #bus.read_byte_data(HW_ADD, RELOAD_ADD)
        if 1 == id:
            val = bus.read_byte_data(HW_ADD, TEMP_ADD)
        else:
            val = -1
    except Exception as e:
        val = -1
    bus.close()
    return val


def getChargeStat():
    bus = smbus2.SMBus(1)
    try:
        id = 1 #bus.read_byte_data(HW_ADD, RELOAD_ADD)
        if 1 == id:
            val = 0x0f & bus.read_byte_data(HW_ADD, CHARGE_STAT_ADD)
        else:
            val = -1
    except Exception as e:
        val = -1
    bus.close()
    return val


def getRepowerOnBattery():
    bus = smbus2.SMBus(1)
    val = -1
    try:
        id = 1 #bus.read_byte_data(HW_ADD, RELOAD_ADD)
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
    bus = smbus2.SMBus(1)
    if val != 0:
        val = 0
    else:
        val = 1
    try:
        id = 1 #bus.read_byte_data(HW_ADD, RELOAD_ADD)
        if 1 == id:
            id = 0xf0 & bus.read_byte_data(HW_ADD, CHARGE_STAT_ADD)
            if id > 0:
                bus.write_byte_data(HW_ADD, POWER_OFF_ON_BATTERY_ADD, val)
                ret = 1
    except Exception as e:
        ret = -1
    bus.close()
    return ret


def getPowerButtonEnable():
    bus = smbus2.SMBus(1)
    val = 0
    try:
        id = 1 #bus.read_byte_data(HW_ADD, RELOAD_ADD)
        if 1 == id:
            id = 0xf0 & bus.read_byte_data(HW_ADD, CHARGE_STAT_ADD)
            if id > 0x10:
                val = bus.read_byte_data(HW_ADD, POWER_SW_USAGE_ADD)
    except Exception as e:
        val = -1
    bus.close()
    return val


def setPowerButtonEnable(val):
    ret = -1
    bus = smbus2.SMBus(1)
    if val != 0:
        val = 1
    try:
        id = 1#bus.read_byte_data(HW_ADD, RELOAD_ADD)
        if 1 == id:
            id = 0xf0 & bus.read_byte_data(HW_ADD, CHARGE_STAT_ADD)
            if id > 0x10:
                bus.write_byte_data(HW_ADD, POWER_SW_USAGE_ADD, val)
                ret = 1
    except Exception as e:
        ret = -1
    bus.close()
    return ret


def getPowerButtonPush():
    bus = smbus2.SMBus(1)
    val = 0
    try:
        id = 1#bus.read_byte_data(HW_ADD, RELOAD_ADD)
        if 1 == id:
            id = 0xf0 & bus.read_byte_data(HW_ADD, CHARGE_STAT_ADD)
            if id > 0x10:
                val = bus.read_byte_data(HW_ADD, POWER_SW_STATUS_ADD)
    except Exception as e:
        val = -1
    bus.close()
    return val


def clrPowerButton():
    ret = -1
    val = 0
    bus = smbus2.SMBus(1)
    try:
        bus.write_byte_data(HW_ADD, POWER_SW_STATUS_ADD, val)
        ret = 1
    except Exception as e:
        ret = -1
    bus.close()
    return ret


def getPowerButton():
    bus = smbus2.SMBus(1)
    val = 0
    try:
        id = 1#bus.read_byte_data(HW_ADD, RELOAD_ADD)
        if 1 == id:
            id = 0xf0 & bus.read_byte_data(HW_ADD, CHARGE_STAT_ADD)
            if id > 0x10:
                val = bus.read_byte_data(HW_ADD, POWER_SW_STATUS_ADD)
    except Exception as e:
        val = -1
    bus.close()
    return val


def setPowerButton(val):
    ret = -1
    if val < 0:
        val = 0
    if val > 1:
        val = 1
    bus = smbus2.SMBus(1)
    try:
        bus.write_byte_data(HW_ADD, POWER_SW_STATUS_ADD, val)
        ret = 1
    except Exception as e:
        ret = -1
    bus.close()
    return ret


def getPowerButtonInterruptEnable():
    bus = smbus2.SMBus(1)
    val = 0
    try:
        id = 1 #bus.read_byte_data(HW_ADD, RELOAD_ADD)
        if 1 == id:
            id = 0xf0 & bus.read_byte_data(HW_ADD, CHARGE_STAT_ADD)
            if id > 0x10:
                val = bus.read_byte_data(HW_ADD, POWER_SW_INT_OUT_ADD)
    except Exception as e:
        val = -1
    bus.close()
    return val


def setPowerButtonInterruptEnable(val):
    ret = -1
    bus = smbus2.SMBus(1)
    if val != 0:
        val = 1
    try:
        id = 1#bus.read_byte_data(HW_ADD, RELOAD_ADD)
        if 1 == id:
            id = 0xf0 & bus.read_byte_data(HW_ADD, CHARGE_STAT_ADD)
            if id > 0x10:
                bus.write_byte_data(HW_ADD, POWER_SW_INT_OUT_ADD, val)
                ret = 1
    except Exception as e:
        ret = -1
    bus.close()
    return ret

I2C_RTC_YEAR_ADD = 31
I2C_RTC_MONTH_ADD = 32
I2C_RTC_DAY_ADD = 33
I2C_RTC_HOUR_ADD = 34
I2C_RTC_MINUTE_ADD = 35
I2C_RTC_SECOND_ADD = 36
I2C_RTC_SET_YEAR_ADD = 37
I2C_RTC_SET_MONTH_ADD = 38
I2C_RTC_SET_DAY_ADD = 39
I2C_RTC_SET_HOUR_ADD = 40
I2C_RTC_SET_MINUTE_ADD = 41
I2C_RTC_SET_SECOND_ADD = 42
I2C_RTC_CMD_ADD = 43


def getRTC():
    bus = smbus2.SMBus(1)
    try:
        buff = bus.read_i2c_block_data(HW_ADD, I2C_RTC_YEAR_ADD, 6)
    except Exception as e:
        bus.close()
        raise ValueError(e)
    bus.close()
    t = (2000 + buff[0], buff[1], buff[2], buff[3], buff[4], buff[5])
    return t


def setRTC(y, mo, d, h, m, s):
    if y > 2000:
        y -= 2000
    if y < 0 or y > 255:
        raise ValueError("Invalid year!")
    if mo > 12 or mo < 1:
        raise ValueError("Invalid month!")
    if d < 1 or d > 31:
        raise ValueError("Invalid day!")
    if h < 0 or h > 23:
        raise ValueError("Invalid hour!")
    if m < 0 or m > 59:
        raise ValueError("Invalid minute!")
    if s < 0 or s > 59:
        raise ValueError("Invalid seconds!")
    bus = smbus2.SMBus(1)
    buff = [int(y), int(mo), int(d), int(h), int(m), int(s), 0xaa]
    # buff[0] = int(y)
    # buff[1] = int(mo)
    # buff[2] = int(d)
    # buff[3] = int(h)
    # buff[4] = int(m)
    # buff[5] = int(s)
    # buff[6] = 0xaa
    try:
        bus.write_i2c_block_data(HW_ADD, I2C_RTC_SET_YEAR_ADD, buff)
    except Exception as e:
        bus.close()
        raise ValueError(e)
    bus.close()

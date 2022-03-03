#pragma once

/* Slave Addresses */
#define MS5083-05BA_ALTIMETER_ADDRESS   0x77
#define HTU20DF_HUMIDITY_ADDRESS        0x40

  
/** 
 *  MS5083 Altimeter Commands & Offsets
 *  URL: https://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FMS5803-05BA%7FB3%7Fpdf%7FEnglish%7FENG_DS_MS5803-05BA_B3.pdf%7FCAT-BLPS0011
 */
enum class MS5083_ALTIMER_COMMANDS
{
    CONVERT_PRESSURE_256    = 0x40,
    CONVERT_PRESSURE_512    = 0x42,
    CONVERT_PRESSURE_1024   = 0x44,
    CONVERT_PRESSURE_2048   = 0x46,
    CONVERT_PRESSURE_4096   = 0x48,
    CONVERT_TEMP_256        = 0x50,
    CONVERT_TEMP_512        = 0x52,
    CONVERT_TEMP_1024       = 0x54,
    CONVERT_TEMP_2048       = 0x56,
    CONVERT_TEMP_4096       = 0x58,
    ADC_READ                = 0x00,
    PROM_READ_BASE          = 0xA0,
    PROM_READ_COEFF_1       = 0xA2,
    PROM_READ_COEFF_2       = 0xA4,
    PROM_READ_COEFF_3       = 0xA6,
    PROM_READ_COEFF_4       = 0xA8,
    PROM_READ_COEFF_5       = 0xAA,
    PROM_READ_COEFF_6       = 0xAC,
    PROM_READ_CRC           = 0xAE,
};

/**
 *  HTU20D Humidity Sensor Commands & Offsets
 *  URL: https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=HPC202&DocType=DS&DocLang=English
 */
enum class HTU20D_HUMIDITY_COMMANDS
{
    SOFT_RESET                      = 0xFE,
    READ_USER_REGISTER              = 0xE7,
    WRITE_USER_REGISTER             = 0xE6,
    TRIGGER_TEMP_MEAS_HOLD          = 0xE3,
    TRIGGER_TEMP_MEAS_NO_HOLD       = 0xF3,
    TRIGGER_HUMIDITY_MEAS_HOLD      = 0xE5,
    TRIGGER_HUMIDITY_MEAS_NO_HOLD   = 0xF5,
}

enum class HTU20D_USER
{
    RESOLUTION_H12_T14  = 0b00000000,
    RESOLUTION_H08_T13  = 0b00000001,
    RESOLUTION_H10_T12  = 0b10000000, // <-- Used resolution
    RESOLUTION_H11_T11  = 0b10000001,
    STATUS_BATTERY_BIT  = 0b01000000,
    ENABLE_HEATER       = 0b00000100,
    DISALBE_OTP_RELOAD  = 0b00000010,
}
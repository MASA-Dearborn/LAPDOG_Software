#pragma once

/* Slave Addresses */
#define MS5083-05BA_ALTIMETERESS   0x77
#define HTU20DF_HUMIDITYESS        0x40

  
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
};

enum class HTU20D_USER
{
    RESOLUTION_H12_T14  = 0b00000000,
    RESOLUTION_H08_T13  = 0b00000001,
    RESOLUTION_H10_T12  = 0b10000000, // <-- Used resolution
    RESOLUTION_H11_T11  = 0b10000001,
    STATUS_BATTERY_BIT  = 0b01000000,
    ENABLE_HEATER       = 0b00000100,
    DISALBE_OTP_RELOAD  = 0b00000010,
};

/**
 *  BNO055 IMU and Magnetometer
 *  URL: https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bno055-ds000.pdf
 *  REF: https://github.com/adafruit/Adafruit_BNO055/blob/master/Adafruit_BNO055.h
 */

enum class BNO055_DATA_ADDR
{
    /* Accel data register */
    ACCEL_X_LSB = 0X08,
    ACCEL_X_MSB = 0X09,
    ACCEL_Y_LSB = 0X0A,
    ACCEL_Y_MSB = 0X0B,
    ACCEL_Z_LSB = 0X0C,
    ACCEL_Z_MSB = 0X0D,

    /* Mag data register */
    MAG_X_LSB = 0X0E,
    MAG_X_MSB = 0X0F,
    MAG_Y_LSB = 0X10,
    MAG_Y_MSB = 0X11,
    MAG_Z_LSB = 0X12,
    MAG_Z_MSB = 0X13,

    /* Gyro data registers */
    GYRO_X_LSB = 0X14,
    GYRO_X_MSB = 0X15,
    GYRO_Y_LSB = 0X16,
    GYRO_Y_MSB = 0X17,
    GYRO_Z_LSB = 0X18,
    GYRO_Z_MSB = 0X19,

    /* Euler data registers */
    EULER_H_LSB = 0X1A,
    EULER_H_MSB = 0X1B,
    EULER_R_LSB = 0X1C,
    EULER_R_MSB = 0X1D,
    EULER_P_LSB = 0X1E,
    EULER_P_MSB = 0X1F,

    /* Quaternion data registers */
    QUATERNION_W_LSB = 0X20,
    QUATERNION_W_MSB = 0X21,
    QUATERNION_X_LSB = 0X22,
    QUATERNION_X_MSB = 0X23,
    QUATERNION_Y_LSB = 0X24,
    QUATERNION_Y_MSB = 0X25,
    QUATERNION_Z_LSB = 0X26,
    QUATERNION_Z_MSB = 0X27,

    /* Linear acceleration data registers */
    LINEAR_ACCEL_X_LSB = 0X28,
    LINEAR_ACCEL_X_MSB = 0X29,
    LINEAR_ACCEL_Y_LSB = 0X2A,
    LINEAR_ACCEL_Y_MSB = 0X2B,
    LINEAR_ACCEL_Z_LSB = 0X2C,
    LINEAR_ACCEL_Z_MSB = 0X2D,

    /* Gravity data registers */
    GRAVITY_X_LSB = 0X2E,
    GRAVITY_X_MSB = 0X2F,
    GRAVITY_Y_LSB = 0X30,
    GRAVITY_Y_MSB = 0X31,
    GRAVITY_Z_LSB = 0X32,
    GRAVITY_Z_MSB = 0X33,

    /* Temperature data register */
    TEMP = 0X34,
};

enum class BNO055_OFFSETS
{
    /* Accelerometer Offset registers */
    ACCEL_OFFSET_X_LSB = 0X55,
    ACCEL_OFFSET_X_MSB = 0X56,
    ACCEL_OFFSET_Y_LSB = 0X57,
    ACCEL_OFFSET_Y_MSB = 0X58,
    ACCEL_OFFSET_Z_LSB = 0X59,
    ACCEL_OFFSET_Z_MSB = 0X5A,

    /* Magnetometer Offset registers */
    MAG_OFFSET_X_LSB = 0X5B,
    MAG_OFFSET_X_MSB = 0X5C,
    MAG_OFFSET_Y_LSB = 0X5D,
    MAG_OFFSET_Y_MSB = 0X5E,
    MAG_OFFSET_Z_LSB = 0X5F,
    MAG_OFFSET_Z_MSB = 0X60,

    /* Gyroscope Offset registers */
    GYRO_OFFSET_X_LSB = 0X61,
    GYRO_OFFSET_X_MSB = 0X62,
    GYRO_OFFSET_Y_LSB = 0X63,
    GYRO_OFFSET_Y_MSB = 0X64,
    GYRO_OFFSET_Z_LSB = 0X65,
    GYRO_OFFSET_Z_MSB = 0X66,    
};

enum class BNO055_OPERATION_MODE
{
    CONFIG          = 0X00,
    ACCONLY         = 0X01,
    MAGONLY         = 0X02,
    GYRONLY         = 0X03,
    ACCMAG          = 0X04,
    ACCGYRO         = 0X05,
    MAGGYRO         = 0X06,
    AMG             = 0X07,
    IMUPLUS         = 0X08,
    COMPASS         = 0X09,
    M4G             = 0X0A,
    NDOF_FMC_OFF    = 0X0B,
    NDOF            = 0X0C
};

enum class BNO055
{
    /* Status registers */
    CALIB_STAT = 0X35,
    SELFTEST_RESULT = 0X36,
    INTR_STAT = 0X37,

    SYS_CLK_STAT = 0X38,
    SYS_STAT = 0X39,
    SYS_ERR = 0X3A,

    /* Unit selection register */
    UNIT_SEL = 0X3B,

    /* Mode registers */
    OPR_MODE = 0X3D,
    PWR_MODE = 0X3E,
    SYS_TRIGGER = 0X3F,
    TEMP_SOURCE = 0X40,

    /* Axis remap registers */
    AXIS_MAP_CONFIG = 0X41,
    AXIS_MAP_SIGN = 0X42,    
};
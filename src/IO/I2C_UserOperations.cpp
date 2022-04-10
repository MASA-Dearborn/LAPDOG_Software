#include "IO/I2C_Operations.h"
#include "IO/I2C_UserOperations.h"
#include "IO/I2C_Devices.h"
#include "broker/broker.h"

void _bnoSetPage(uint8_t page, int fileDescriptor, IO::IOInterface* obj)
{
    msg::RawMessageUnion temp;
    msg::real::BNO055_PAGE* msg = (msg::real::BNO055_PAGE*)pubsub::DataBroker.getCurrentMessagePtr(msg::id::BNO055_PAGE);
    
    if (msg->page == page || page >= 2) {
        return;
    } else {
        msg->page = page;
        uint8_t val = msg->page;
        i2c_operations::_i2c_write(fileDescriptor, (uint8_t) BNO055::PAGE_REG, &val, 1);
    }
}

void dequeueMessageFromInterface(IO::IOInterface* obj, msg::GENERIC_MESSAGE* dest)
{
    if (obj == nullptr || dest == nullptr)
        return;

    int size = ((msg::GENERIC_MESSAGE*)obj->getTXBuffer()->peek())->size;
    if (dest->size >= size)
        obj->getTXBuffer()->dequeue((uint8_t*)dest, size);
}

void sendMessageToInterface(IO::IOInterface* obj, msg::GENERIC_MESSAGE* m)
{
    obj->getRXBuffer()->enqueue((uint8_t*)m, m->size);
}

void _setup_callback(unsigned long delay_ms, void (*func)(sigval), int fileDescriptor, int slave_address, IO::IOInterface* obj)
{
    i2c_operations::callback_data* temp = new i2c_operations::callback_data();
    (*temp).fileDescriptor = fileDescriptor;
    (*temp).slave_address = slave_address;
    (*temp).obj = obj;
    Timer callback_timer = Timer(func, temp, 0, delay_ms);
}

void i2c_operations::ALTIMETER_READ_ALTITUDE(int fileDescriptor, int slave_address, IO::IOInterface* obj)
{
    _i2c_set_slave_address(fileDescriptor, slave_address);
    _i2c_write_one(fileDescriptor, (uint8_t)MS5083_ALTIMETER_COMMANDS::CONVERT_PRESSURE_2048);
    _setup_callback(5, &ALTIMETER_READ_ALTITUDE_CALLBACK, fileDescriptor, slave_address, obj);
}

void i2c_operations::ALTIMETER_READ_ALTITUDE_CALLBACK(sigval data)
{
    uint8_t buffer[3] = {0};
    msg::raw::ALTIMETER_DATA m;
    callback_data* args = ((callback_data*)data.sival_ptr);

    _i2c_set_slave_address(args->fileDescriptor, args->slave_address);
    _i2c_read(args->fileDescriptor, buffer, 3);

    m.pressure_bar = *(uint32_t*)buffer;
    sendMessageToInterface(args->obj, &m);
    delete args;
}

void i2c_operations::ALTIMETER_READ_CONFIG(int fileDescriptor, int slave_address, IO::IOInterface* obj)
{
    uint8_t buffer[32];
    msg::raw::ALTIMETER_COEFFS m;
    _i2c_set_slave_address(fileDescriptor, slave_address);

    // Read Coefficients
    _i2c_write_one(fileDescriptor, (uint8_t)MS5083_ALTIMETER_COMMANDS::PROM_READ_COEFF_1);
    _i2c_read(fileDescriptor, buffer, 2);
    m.coeff_1 = *(uint16_t*)buffer;

    _i2c_write_one(fileDescriptor, (uint8_t)MS5083_ALTIMETER_COMMANDS::PROM_READ_COEFF_2);
    _i2c_read(fileDescriptor, buffer, 2);
    m.coeff_2 = *(uint16_t*)buffer;

    _i2c_write_one(fileDescriptor, (uint8_t)MS5083_ALTIMETER_COMMANDS::PROM_READ_COEFF_3);
    _i2c_read(fileDescriptor, buffer, 2);
    m.coeff_3 = *(uint16_t*)buffer;

    _i2c_write_one(fileDescriptor, (uint8_t)MS5083_ALTIMETER_COMMANDS::PROM_READ_COEFF_4);
    _i2c_read(fileDescriptor, buffer, 2);
    m.coeff_4 = *(uint16_t*)buffer;

    _i2c_write_one(fileDescriptor, (uint8_t)MS5083_ALTIMETER_COMMANDS::PROM_READ_COEFF_5);
    _i2c_read(fileDescriptor, buffer, 2);
    m.coeff_5 = *(uint16_t*)buffer;

    _i2c_write_one(fileDescriptor, (uint8_t)MS5083_ALTIMETER_COMMANDS::PROM_READ_COEFF_6);
    _i2c_read(fileDescriptor, buffer, 2);
    m.coeff_6 = *(uint16_t*)buffer;

    sendMessageToInterface(obj, &m);
}

void i2c_operations::HTU20D_SET_USER_REG(int fileDescriptor, int slave_address, IO::IOInterface* obj)
{
    _i2c_set_slave_address(fileDescriptor, slave_address);
    _i2c_write_one(fileDescriptor, (uint8_t)HTU20D_HUMIDITY_COMMANDS::WRITE_USER_REGISTER);
    _i2c_write_one(fileDescriptor, (uint8_t)HTU20D_USER::RESOLUTION_H10_T12);
}

void i2c_operations::HTU20D_READ_HUMIDITY(int fileDescriptor, int slave_address, IO::IOInterface* obj)
{
    _i2c_set_slave_address(fileDescriptor, slave_address);
    _i2c_write_one(fileDescriptor, (uint8_t)HTU20D_HUMIDITY_COMMANDS::TRIGGER_HUMIDITY_MEAS_NO_HOLD);
    _setup_callback(6, &HTU20D_READ_HUMIDITY_CALLBACK, fileDescriptor, slave_address, obj);
}

void i2c_operations::HTU20D_READ_HUMIDITY_CALLBACK(sigval data)
{
    uint8_t buffer[2] = {0};
    msg::raw::HUMIDITY_DATA m;
    callback_data* args = ((callback_data*)data.sival_ptr);

    // Update m to current
    msg::RawMessageUnion temp;
    msg::conv::convertRealToRaw(&temp, pubsub::DataBroker.getCurrentMessagePtr(msg::id::HUMIDITY_DATA));
    m = temp.HUMIDITY_DATA;

    _i2c_set_slave_address(args->fileDescriptor, args->slave_address);
    _i2c_read(args->fileDescriptor, buffer, 2);
    m.relative_humidity = *(int*)buffer;

    sendMessageToInterface(args->obj, &m);
    delete args;
}

void i2c_operations::HTU20D_READ_TEMPERATURE(int fileDescriptor, int slave_address, IO::IOInterface* obj)
{
    _i2c_set_slave_address(fileDescriptor, slave_address);
    _i2c_write_one(fileDescriptor, (uint8_t)HTU20D_HUMIDITY_COMMANDS::TRIGGER_TEMP_MEAS_NO_HOLD);
    _setup_callback(6, &HTU20D_READ_TEMPERATURE_CALLBACK, fileDescriptor, slave_address, obj);
}

void i2c_operations::HTU20D_READ_TEMPERATURE_CALLBACK(sigval data)
{
    uint8_t buffer[2] = {0};
    msg::raw::HUMIDITY_DATA m;
    callback_data* args = ((callback_data*)data.sival_ptr);

    // Update m to current
    msg::RawMessageUnion temp;
    msg::conv::convertRealToRaw(&temp, pubsub::DataBroker.getCurrentMessagePtr(msg::id::HUMIDITY_DATA));
    m = temp.HUMIDITY_DATA;

    _i2c_set_slave_address(args->fileDescriptor, args->slave_address);
    _i2c_read(args->fileDescriptor, buffer, 2);
    m.temp_celcius = *(int*)buffer;

    sendMessageToInterface(args->obj, &m);
    delete args;
}


void i2c_operations::BNO_READ_ACCEL_DATA(int fileDescriptor, int slave_address, IO::IOInterface* obj)
{
    uint8_t buffer[6];
    msg::raw::BNO055_DATA_ACCEL msg;

    // Read data
    _i2c_set_slave_address(fileDescriptor, slave_address);
    _bnoSetPage(0, fileDescriptor, obj);
    _i2c_write_one(fileDescriptor, (uint8_t)BNO055_DATA_ADDR::ACCEL_X_LSB);
    _i2c_read(fileDescriptor, buffer, 6);

    // Distribute data
    msg.X = *(uint16_t*)&buffer[0];
    msg.Y = *(uint16_t*)&buffer[2];
    msg.Z = *(uint16_t*)&buffer[4];

    sendMessageToInterface(obj, &msg);
}

void i2c_operations::BNO_READ_GYRO_DATA(int fileDescriptor, int slave_address, IO::IOInterface* obj)
{
    uint8_t buffer[6];
    msg::raw::BNO055_DATA_GYRO msg;

    // Read data
    _i2c_set_slave_address(fileDescriptor, slave_address);
    _bnoSetPage(0, fileDescriptor, obj);
    _i2c_write_one(fileDescriptor, (uint8_t)BNO055_DATA_ADDR::GYRO_X_LSB);
    _i2c_read(fileDescriptor, buffer, 6);

    // Distribute data
    msg.X = *(uint16_t*)&buffer[0];
    msg.Y = *(uint16_t*)&buffer[2];
    msg.Z = *(uint16_t*)&buffer[4];

    sendMessageToInterface(obj, &msg);
}

void i2c_operations::BNO_READ_MAG_DATA(int fileDescriptor, int slave_address, IO::IOInterface* obj)
{
    uint8_t buffer[6];
    msg::raw::BNO055_DATA_MAG msg;

    // Read data
    _i2c_set_slave_address(fileDescriptor, slave_address);
    _bnoSetPage(0, fileDescriptor, obj);
    _i2c_write_one(fileDescriptor, (uint8_t)BNO055_DATA_ADDR::MAG_X_LSB);
    _i2c_read(fileDescriptor, buffer, 6);

    // Distribute data
    msg.X = *(uint16_t*)&buffer[0];
    msg.Y = *(uint16_t*)&buffer[2];
    msg.Z = *(uint16_t*)&buffer[4];

    sendMessageToInterface(obj, &msg);
}

void i2c_operations::BNO_SET_OPR_MODE(int fileDescriptor, int slave_address, IO::IOInterface* obj)
{
    msg::raw::BNO055_OPR_MODE msg;
    dequeueMessageFromInterface(obj, &msg);

    uint8_t data[2];
    data[0] = (uint8_t)BNO055::OPR_MODE;
    data[1] = msg.MODE;

    _i2c_set_slave_address(fileDescriptor, slave_address);
    _bnoSetPage(0, fileDescriptor, obj);
    _i2c_write(fileDescriptor, data, 2);
}

void i2c_operations::BNO_SET_AXIS_CONFIG(int fileDescriptor, int slave_address, IO::IOInterface* obj)
{
    msg::raw::BNO055_AXIS_CONFIG msg;
    dequeueMessageFromInterface(obj, &msg);

    uint8_t map_config[2];
    map_config[0] = (uint8_t)BNO055::AXIS_MAP_CONFIG;
    map_config[1] = msg.Z_MAP << 4 | msg.Y_MAP << 2 | msg.X_MAP;

    uint8_t sign_config[2];
    sign_config[0] = (uint8_t)BNO055::AXIS_MAP_SIGN;
    sign_config[1] = msg.X_SIGN_INVERT << 2 | msg.Y_SIGN_INVERT << 1 | msg.Z_SIGN_INVERT;

    _i2c_set_slave_address(fileDescriptor, slave_address);
    _bnoSetPage(0, fileDescriptor, obj);
    _i2c_write(fileDescriptor, map_config, 2);
    _i2c_write(fileDescriptor, sign_config, 2);
}

void i2c_operations::BNO_SET_UNIT_SELECTION(int fileDescriptor, int slave_address, IO::IOInterface* obj)
{
    msg::raw::BNO055_UNIT_SELECTION msg;
    dequeueMessageFromInterface(obj, &msg);

    uint8_t data[2];
    data[0] = (uint8_t) BNO055::UNIT_SEL;
    data[1] = (uint8_t)BNO055_UNITS::ACCEL_METERS_PER_SECOND | (uint8_t)BNO055_UNITS::ANGULAR_RATE_RPS 
            | (uint8_t)BNO055_UNITS::EULER_RADS | (uint8_t)BNO055_UNITS::TEMP_CEL;

    _i2c_set_slave_address(fileDescriptor, slave_address);
    _bnoSetPage(0, fileDescriptor, obj);
    _i2c_write(fileDescriptor, data, 2);
}

void i2c_operations::BNO_SET_ACCEL_CONFIG(int fileDescriptor, int slave_address, IO::IOInterface* obj)
{
    msg::raw::BNO055_ACCEL_CONFIG msg;
    dequeueMessageFromInterface(obj, &msg);

    uint8_t data = msg.G_RANGE | msg.SAMPLE_RATE << 2 | msg.OPERATION_MODE << 5;
    _i2c_set_slave_address(fileDescriptor, slave_address);
    _bnoSetPage(0, fileDescriptor, obj);
    _i2c_write(fileDescriptor, (uint8_t) BNO055::ACC_CONFIG, &data, 1);
}

void i2c_operations::BNO_SET_GYRO_CONFIG(int fileDescriptor, int slave_address, IO::IOInterface* obj)
{
    msg::raw::BNO055_GYRO_CONFIG msg;
    dequeueMessageFromInterface(obj, &msg);

    uint8_t data_0 = msg.RANGE | msg.SAMPLE_RATE << 3;
    uint8_t data_1 = msg.OPERATION_MODE;

    _i2c_set_slave_address(fileDescriptor, slave_address);
    _bnoSetPage(0, fileDescriptor, obj);
    _i2c_write(fileDescriptor, (uint8_t) BNO055::GYR_CONFIG_0, &data_0, 1);
    _i2c_write(fileDescriptor, (uint8_t) BNO055::GYR_CONFIG_1, &data_1, 1);
}

void i2c_operations::BNO_SET_MAG_CONFIG(int fileDescriptor, int slave_address, IO::IOInterface* obj)
{
    msg::raw::BNO055_MAG_CONFIG msg;
    dequeueMessageFromInterface(obj, &msg);

    uint8_t data = msg.SAMPLE_RATE | msg.OPERATION_MODE << 3; // Need powermode
    _i2c_set_slave_address(fileDescriptor, slave_address);
    _bnoSetPage(0, fileDescriptor, obj);
    _i2c_write(fileDescriptor, (uint8_t) BNO055::MAG_CONFIG, &data, 1);
}


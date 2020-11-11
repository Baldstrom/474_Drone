#include "bme.h"
#include "i2c.h"

static int read_raw_pressure_regisers(int32_t *val);
static int read_raw_temperature_regisgters(int32_t *val);
static int read_raw_humidity_registers(short *val);

static void get_compensation_parameters(compensation_params *params);

static float get_temperature(int32_t raw_temp, compensation_params *params);
static float get_pressure(int32_t raw_press, float temp, compensation_params *params);
static float get_humidity(int32_t raw_press, float temp, compensation_params *params);

static oversampling osrs_hum = OS_1X;
static oversampling osrs_temp = OS_1X;
static oversampling osrs_press = OS_1X;

static compensation_params *params;

static float temp, press, hum;

void bme_init()
{
    // Initialize readings
    temp = 0.0f;
    press = 0.0f;
    hum = 0.0f;
    // Initialize parameters and sleep mode on BME
    get_compensation_parameters(params);
    bme_set_mode(SLEEP);

    // Read CTL registers
    char raw_data[4];
    for (int i = 0; i < 4; i++) { i2c3_read_registers(BME_ADDR, BME_CTRL_HUM_REG + i, 1, raw_data + i); }

    char ctrl_hum = (raw_data[0] & 0xF8) | osrs_hum;
    char ctrl_meas = (((osrs_temp << 5) & 0xE0) | ((osrs_press >> 2) & 0x1C) | 0x11); // Stays in SLEEP mode, we'll exit once these writes are all done.
    char ctrl = raw_data[3] & 0x02;

    i2c3_write_register(BME_ADDR, BME_CTRL_HUM_REG, ctrl_hum);
    i2c3_write_register(BME_ADDR, BME_CTRL_MEAS_REG, ctrl_meas);
    i2c3_write_register(BME_ADDR, BME_CONFIG_REG, ctrl);

    bme_set_mode(NORMAL);
    bme_update_readings();
}

void bme_update_readings()
{
    int32_t raw_temp, raw_press;
    short raw_hum;

    read_raw_humidity_registers(&raw_hum);
    read_raw_pressure_regisers(&raw_press);
    read_raw_temperature_regisgters(&raw_temp);

    temp = get_temperature(raw_temp, params);
    press = get_pressure(raw_press, temp, params);
    hum = get_humidity(raw_hum, temp, params);
}

float bme_pressure() { return press; }
float bme_humidity() { return hum; }
float bme_temperature() { return temp; }

float get_temperature(int32_t raw_temp, compensation_params *params)
{
   float var1, var2;
   var1 = (raw_temp / 16384.0f) - (params->T1 / 1024.0f);
   var1 *= params->T2;
   var2 = (raw_temp / 131072.0f) - (params->T1 / 8192.0f);
   var2 = (var2 * var2) * params->T3;
   return (var1 + var2) / 5120.0f;
}

float get_pressure(int32_t raw_press, float temp, compensation_params *params)
{
   int temp_comp = (int)(temp * 5120.0f);
   float var1, var2, var3, press;
   var1 = (temp_comp / 2.0f) - 64000.0f;
   var2 = (var1 * var1) * params->P6 / 32768.0f;
   var2 = (var2 + var1) * params->P5 * 2;
   var2 = (var2 / 4.0f) + (params->P4 * 65536.0f);
   var3 = params->P3 * var1 * var1 / 524288.0f;
   var1 = (var3 + (params->P2 * var1)) / 524288.0f;
   var1 = (1.0 + (var1 / 32768.0f)) * params->P1;
   if (var1 > 0)
   {
       press = 1048576.0f - raw_press;
       press = (press - (var2 / 4096.0f)) * 6250.0f / var1;
       var1 = params->P9 * press * press / 2147483648.0f;
       var2 = press * params->P8 / 32768.0f;
       press = press + ((var1 + var2 + params->P7) / 16.0f);
       if (press < 30000) { return 30000; }
       if (press > 110000) { return 110000; }
   } 
   else
   {
       return 0;
   }
   return press;
}

float get_humidity(int32_t raw_hum, float temp, compensation_params *params)
{
   int temp_comp = (int)(temp * 5120.0f);
   float humid, var1, var2, var3, var4, var5, var6;
   var1 = temp_comp - 76800.0f;
   var2 = (params->H4 * 64.0f) + ((params->H5 / 16384.0f) * var1);
   var3 = raw_hum - var2;
   var4 = params->H2 / 65536.0f;
   var5 = 1.0f + ((params->H3 / 67108864.0f) * var1);
   var6 = 1.0f + ((params->H6 / 67108864.0f) *var1 * var5);
   var6 = var3 * var4 * var5 * var6;
   humid = var6 * (1.0f - (params->H1 * var6 / 524288.0f));
   if (humid > 100) { return 100; }
   if (humid < 0) { return 0; }
   return humid;
}

void bme_set_mode(mode newmode)
{
    // Read current config
    char config;
    i2c3_read_registers(BME_ADDR, BME_CTRL_MEAS_REG, 1, (char *)&config);
    config &= 0xFC;
    config |= newmode;
    i2c3_write_register(BME_ADDR, BME_CTRL_MEAS_REG, config);
}

int read_raw_humidity_registers(short *val)
{
    char data[2];
    int fail = 0;
    fail |= i2c3_read_registers(BME_ADDR, BME_HUMIDITY_MSB_REG,  1, (char *)&data[0]); // MSB
    fail |= i2c3_read_registers(BME_ADDR, BME_HUMIDITY_LSB_REG,  1, (char *)&data[1]); // MID
    *val = (data[0] << 8) | data[1];
    *val &= 0xFFFF; // 16 bits
    return fail;
}

int read_raw_temperature_regisgters(int32_t *val)
{
    char data[3];
    int fail = 0;
    fail |= i2c3_read_registers(BME_ADDR, BME_TEMPERATURE_MSB_REG,  1, (char *)&data[0]); // MSB
    fail |= i2c3_read_registers(BME_ADDR, BME_TEMPERATURE_LSB_REG,  1, (char *)&data[1]); // MID
    fail |= i2c3_read_registers(BME_ADDR, BME_TEMPERATURE_XLSB_REG, 1, (char *)&data[2]); // LSB
    *val = ((data[0] & 0xFF) << 12) | ((data[1] & 0xFF) << 4) | (data[2] & 0x0F);
    *val &= 0xFFFFF; // 20 bits
    return fail;
}

int read_raw_pressure_regisers(int32_t *val)
{ 
    char data[3];
    int fail = 0;
    fail |= i2c3_read_registers(BME_ADDR, BME_PRESSURE_MSB_REG,  1, (char *)&data[0]); // MSB
    fail |= i2c3_read_registers(BME_ADDR, BME_PRESSURE_LSB_REG,  1, (char *)&data[1]); // MID
    fail |= i2c3_read_registers(BME_ADDR, BME_PRESSURE_XLSB_REG, 1, (char *)&data[2]); // LSB
    *val = ((data[0] & 0xFF) << 12) | ((data[1] & 0xFF) << 4) | (data[2] & 0x0F);
    *val &= 0xFFFFF; // 20 bits
    return fail;
}

void get_compensation_parameters(compensation_params *params)
{
    char lowvals[26];
    char highvals[7];
    
    get_compensation_registers(lowvals, highvals);

    params->T1 = (uint16_t) (lowvals[0] | (lowvals[1] << 8));
    params->T2 = (short)    (lowvals[2] | (lowvals[3] << 8));
    params->T3 = (short)    (lowvals[4] | (lowvals[5] << 8));
    params->P1 = (uint16_t) (lowvals[6] | (lowvals[7] << 8));
    params->P2 = (short)    (lowvals[8] | (lowvals[9] << 8));
    params->P3 = (short)    (lowvals[10] | (lowvals[11] << 8));
    params->P4 = (short)    (lowvals[12] | (lowvals[13] << 8));
    params->P5 = (short)    (lowvals[14] | (lowvals[15] << 8));
    params->P6 = (short)    (lowvals[16] | (lowvals[17] << 8));
    params->P7 = (short)    (lowvals[18] | (lowvals[19] << 8));
    params->P8 = (short)    (lowvals[20] | (lowvals[21] << 8));
    params->P9 = (short)    (lowvals[22] | (lowvals[23] << 8));
    params->H1 = (char)     lowvals[25];
    params->H2 = (short)    (highvals[0] | (highvals[1] << 8));
    params->H3 = (char)     highvals[2];
    params->H4 = (short)    ((highvals[3] << 4) | (highvals[4] & 0x0F));
    params->H5 = (short)    (((highvals[4] & 0xF0) >> 4) | highvals[5] << 4);
    params->H6 = (int8_t)   (highvals[6]);
}

int get_compensation_registers(char *lowvals, char *highvals)
{
    int fail = 0;
    int i;
    for (i = 0; i < 26; i++)
    {
        // Get LOW Parameters
        fail |= i2c3_read_registers(BME_ADDR, BME_CALIBRATION_LOW_REG + i,  1, lowvals + i);
    }
    for (i = 0; i < 7; i++)
    {
        // Get HIGH Parameters
        fail |= i2c3_read_registers(BME_ADDR, BME_CALIBRATION_HIGH_REG + i,  1, highvals + i);
    }
    return fail;
}
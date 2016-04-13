/**
 * @file  fabo-si1132.cpp
 * @brief fabo libtary of SI1132
 * @author Akira Sasaki
 * @date 2,10, 2016
 */
#include "fabo-si1132.h"

/**
 * @brief Serch si1132
 * @retval true  : Found
 * @retval false : Not Found
 */
bool FaBoUV::searchDevice()
{
  byte device = 0x00;
  readI2c(SI1132_WHO_AM_I_REG, 1, &device);

  if(device == SI1132_DEVICE){
    return true;
  } else{
    return false;
  }
}

/**
 * @brief Set Config
 */
void FaBoUV::configuration()
{
  writeI2c(SI1132_UCOEF0_REG, 0x7B);
  writeI2c(SI1132_UCOEF1_REG, 0x6B);
  writeI2c(SI1132_UCOEF2_REG, 0x01);
  writeI2c(SI1132_UCOEF3_REG, 0x00);

  int enable_sensor = SI1132_EN_UV|SI1132_EN_AUX|SI1132_EN_ALS_IR|SI1132_EN_ALS_VIS;
  writeI2c(SI1132_CHIPLIST_REG, enable_sensor);

  // Rate setting
  writeI2c(SI1132_MEASRATE0_REG, 0xff);

  int flag_als_encoding = SI1132_ALS_VIS_ALIGN | SI1132_ALS_IR_ALIGN;
  writeI2c(SI1132_ALS_ENCODING_REG, flag_als_encoding);

  // Visible
  writeI2c(SI1132_ALS_VIS_ADC_COUNTER_REG, SI1132_511_ADC_CLOCK);

  writeI2c(SI1132_ALS_VIS_ADC_GAIN_REG, SI1132_1_DIVIDED_ADC_CLOCK);

  writeI2c(SI1132_ALS_VIS_ADC_MISC_REG, SI1132_HIGH_SIGNAL_RANGE);

  // IR
  writeI2c(SI1132_ALS_IR_ADC_COUNTER_REG, SI1132_511_ADC_CLOCK);

  writeI2c(SI1132_ALS_IR_ADC_GAIN_REG, SI1132_1_DIVIDED_ADC_CLOCK);

  writeI2c(SI1132_ALS_IR_ADC_MISC_REG, SI1132_HIGH_SIGNAL_RANGE);

  writeI2c(SI1132_ALS_IR_ADCMUX_REG, SI1132_ALS_IR_ADCMUX_SMALLIR);

  // AUX
  writeI2c(SI1132_AUX_ADCMUX_REG, SI1132_AUX_ADCMUX_TEMPERATURE);

  // COMMAND
  writeI2c(SI1132_COMMAND_REG, SI1132_COMMAND_ALS_AUTO);
}

/**
 * @brief Reset Si1132
 */
void FaBoUV::reset()
{
  writeI2c(SI1132_COMMAND_REG, SI1132_COMMAND_RESET);
}

/**
 * @brief Read UV
 * @return uint16_t : uv data
 */
uint16_t FaBoUV::readUV()
{
  uint16_t uv_index;
  uint8_t buffer[2];

  readI2c(SI1132_AUX_DATA_REG, 2, buffer);
  uv_index = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];

  return uv_index;
}

/**
 * @brief Read IR
 * @return uint16_t : IR data
 */
uint16_t FaBoUV::readIR()
{
  uint16_t ir;
  uint8_t buffer[2];

  readI2c(SI1132_IR_DATA_REG, 2, buffer);
  ir = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];

  return ir;
}


/**
 * @brief Read Visible
 * @return uint16_t : Visible data
 */
uint16_t FaBoUV::readVisible()
{
  uint16_t visible;
  uint8_t buffer[2];

  readI2c(SI1132_VISIBLE_DATA_REG, 2, buffer);
  visible = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];

  return visible;
}

/**
 * @brief Write I2C Data
 * @param [in] register_addr : Write Register Address
 * @param [in] value  : Write Data
 */
void FaBoUV::writeI2c(byte register_addr, byte value) {
  Wire.beginTransmission(SI1132_SLAVE_ADDRESS);
  Wire.write(register_addr);
  Wire.write(value);
  Wire.endTransmission();
}

/**
 * @brief Read I2C Data
 * @param [in] register_addr : register address
 * @param [in] num   : Data Length
 * @param [out] *buf : Read Data
 */
void FaBoUV::readI2c(byte register_addr, int num, byte *buf) {
  Wire.beginTransmission(SI1132_SLAVE_ADDRESS);
  Wire.write(register_addr);
  Wire.endTransmission(false);

  //Wire.beginTransmission(DEVICE_ADDR);
  Wire.requestFrom(SI1132_SLAVE_ADDRESS, num);

  int i = 0;
  while (Wire.available())
  {
    buf[i] = Wire.read();
    i++;
  }
  //Wire.endTransmission();
}

/**
 * @file  fabo-si1132.h
 * @brief fabo libtary of SI1132
 * @author Akira Sasaki
 * @date 2,10, 2016
 */
#include "Arduino.h"
#include "Wire.h"

/** si1132 Slave Address register */
#define SI1132_SLAVE_ADDRESS 0x60
/** Who_am_i register */
#define SI1132_WHO_AM_I_REG 0x00
/** Device check register */
#define SI1132_DEVICE 0x32

/** UCOEF0 register */
#define SI1132_UCOEF0_REG 0x13
/** UCOEF1 register */
#define SI1132_UCOEF1_REG 0x14
/** UCOEF2 register */
#define SI1132_UCOEF2_REG 0x15
/** UCOEF3 register */
#define SI1132_UCOEF3_REG 0x16

/** Chip list register */
#define SI1132_CHIPLIST_REG 0x01
/** MEASRATE0 register */
#define SI1132_MEASRATE0_REG 0x08
/** ALS Encoding register */
#define SI1132_ALS_ENCODING_REG 0x06
/** ALS VIS ADC Counter register */
#define SI1132_ALS_VIS_ADC_COUNTER_REG 0x10
/** ALS VIS ADC Gain register */
#define SI1132_ALS_VIS_ADC_GAIN_REG 0x11
/** ALS VIS ADC Misc register */
#define SI1132_ALS_VIS_ADC_MISC_REG 0x12

/** ALS IR ADC Counter register */
#define SI1132_ALS_IR_ADC_COUNTER_REG 0x1D
/** ALS IR ADC Gain register */
#define SI1132_ALS_IR_ADC_GAIN_REG 0x1E
/** ALS IR ADC Misc register */
#define SI1132_ALS_IR_ADC_MISC_REG 0x1F
/** ALS IR Adcmux register */
#define SI1132_ALS_IR_ADCMUX_REG 0x0E
/** Auxiliary Adcmux register */
#define SI1132_AUX_ADCMUX_REG 0x0F
/** Command register */
#define SI1132_COMMAND_REG 0x18
/** Auxiliary Data register */
#define SI1132_AUX_DATA_REG 0x2C
/** IR Data register */
#define SI1132_IR_DATA_REG 0x24
/** Visible Data register */
#define SI1132_VISIBLE_DATA_REG 0x22


/** Enables UV Index register */
#define SI1132_EN_UV 0b10000000
/** Enables Auxiliary Channel register */
#define SI1132_EN_AUX 0b01000000
/** Enables ALS IR Channel register */
#define SI1132_EN_ALS_IR 0b00100000
/** Enables ALS Visible Channel register */
#define SI1132_EN_ALS_VIS 0b00010000

/** ALS　VIS ALIGN register */
#define SI1132_ALS_VIS_ALIGN 0b00010000
/** ALS　IR ALIGN register */
#define SI1132_ALS_IR_ALIGN 0b00100000

/** ADC Clock 1 : 50 ns times */
#define SI1132_1_ADC_CLOCK   0b00000000
/** ADC Clock 7 : 350 ns times */
#define SI1132_7_ADC_CLOCK   0b00010000
/** ADC Clock 15 : 750 ns times */
#define SI1132_15_ADC_CLOCK  0b00100000
/** ADC Clock 31 : 1.15 us times */
#define SI1132_31_ADC_CLOCK  0b00110000
/** ADC Clock 63 : 3.15 us times */
#define SI1132_63_ADC_CLOCK  0b01000000
/** ADC Clock 127 : 6.35 us times */
#define SI1132_127_ADC_CLOCK 0b10100000
/** ADC Clock 255 : 12.75 us times */
#define SI1132_255_ADC_CLOCK 0b01100000
/** ADC Clock 511 : 25.55 us times */
#define SI1132_511_ADC_CLOCK 0b01110000

/** Divided ADC Clock 1 */
#define SI1132_1_DIVIDED_ADC_CLOCK 0b0000000
/** Divided ADC Clock 16 */
#define SI1132_16_DEVIDED_ADC_CLOCK 0b0000100
/** Divided ADC Clock 64 */
#define SI1132_64_DEVIDED_ADC_CLOCK 0b0000110

/** Normal single range */
#define SI1132_NORMAL_SIGNAL_RANGE 0b00000000
/** High single range */
#define SI1132_HIGH_SIGNAL_RANGE 0b00100000

/** ALS IR Adcmux SMALLIR */
#define SI1132_ALS_IR_ADCMUX_SMALLIR 0x00

/** ALS IR Adcmux Temperature */
#define SI1132_AUX_ADCMUX_TEMPERATURE 0x65
/** Auxiliary ADCMUX VDD */
#define SI1132_AUX_ADCMUX_VDD 0x75

/** Command ALS Auto */
#define SI1132_COMMAND_ALS_AUTO 0x0E
/** Command Reset */
#define SI1132_COMMAND_RESET 0x01

/**
 * @class FaBoUV
 * @brief si1132 Control
 */
class FaBoUV
{
public:
	bool searchDevice(void);
	void configuration(void);
	void reset(void);
	uint16_t readUV(void);
	uint16_t readIR(void);
	uint16_t readVisible(void);
private:
	void writeI2c(byte register_addr, byte value);
	void readI2c(byte register_addr, int num, byte *buf);
};

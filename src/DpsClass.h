/**
 * Arduino library to control Dps310
 *
 * "Dps310" represents Infineon's high-sensetive pressure and temperature sensor. 
 * It measures in ranges of 300 - 1200 hPa and -40 and 85 °C. 
 * The sensor can be connected via SPI or I2C. 
 * It is able to perform single measurements
 * or to perform continuous measurements of temperature and pressure at the same time, 
 * and stores the results in a FIFO to reduce bus communication. 
 *
 * Have a look at the datasheet for more information. 
 */

#ifndef DPSCLASS_H_INCLUDED
#define DPSCLASS_H_INCLUDED

#include <SPI.h>
#include <Wire.h>
#include "util/dps_config.h"

class DpsClass
{
  public:
	//constructor
	DpsClass(void);
	//destructor
	~DpsClass(void);

	/**
	 * I2C begin function with standard address
	 */
	void begin(TwoWire &bus);

	/**
	 * Standard I2C begin function
	 *
	 * &bus: 			I2CBus which connects MC to the sensor
	 * slaveAddress: 	I2C address of the sensor (0x77 or 0x76)
	 */
	void begin(TwoWire &bus, uint8_t slaveAddress);

	/**
	 * SPI begin function for Dps310 with 4-wire SPI
	 */
	void begin(SPIClass &bus, int32_t chipSelect);

	/**
	 * Standard SPI begin function
	 *
	 * &bus: 			SPI bus which connects MC to Dps310
	 * chipSelect: 		Number of the CS line for the Dps310
	 * threeWire: 		1 if Dps310 is connected with 3-wire SPI
	 * 					0 if Dps310 is connected with 4-wire SPI (standard)
	 */
	void begin(SPIClass &bus, int32_t chipSelect, uint8_t threeWire);

	/**
	 * End function for Dps310
	 * Sets the sensor to idle mode
	 */
	void end(void);

	/**
	 * returns the Product ID of the connected Dps310 sensor
	 */
	uint8_t getProductId(void);

	/**
	 * returns the Revision ID of the connected Dps310 sensor
	 */
	uint8_t getRevisionId(void);

	/**
	 * Sets the Dps310 to standby mode
	 *
	 * returns:		status code
	 */
	int16_t standby(void);

	/**
	 * performs one temperature measurement
	 *
	 * &result:		reference to a float value where the result will be written
	 * returns: 	status code
	 */
	int16_t measureTempOnce(float &result);

	/**
	 * performs one temperature measurement with specified oversamplingRate
	 *
	 * &result:				reference to a float where the result will be written
	 * oversamplingRate: 	DPS__OVERSAMPLING_RATE_1, DPS__OVERSAMPLING_RATE_2, DPS__OVERSAMPLING_RATE_4 ... DPS__OVERSAMPLING_RATE_128, which are defined as integers 0 - 7
	 * 						The number of measurements equals to 2^n, if the value written to the register field is n. 2^n internal measurements are combined to return a more exact measurement
	 * returns: 			status code
	 */
	int16_t measureTempOnce(float &result, uint8_t oversamplingRate);

	/**
	 * starts a single temperature measurement
	 *
	 * returns: 	status code
	 */
	int16_t startMeasureTempOnce(void);

	/**
	 * starts a single temperature measurement with specified oversamplingRate
	 *
	 * oversamplingRate: 	DPS__OVERSAMPLING_RATE_1, DPS__OVERSAMPLING_RATE_2, DPS__OVERSAMPLING_RATE_4 ... DPS__OVERSAMPLING_RATE_128, which are defined as integers 0 - 7
	 * returns: 			status code
	 */
	int16_t startMeasureTempOnce(uint8_t oversamplingRate);

	/**
	 * performs one pressure measurement
	 *
	 * &result:		reference to a float value where the result will be written
	 * returns: 	status code
	 */
	int16_t measurePressureOnce(float &result);

	/**
	 * performs one pressure measurement with specified oversamplingRate
	 *
	 * &result:				reference to a float where the result will be written
	 * oversamplingRate: 	DPS__OVERSAMPLING_RATE_1, DPS__OVERSAMPLING_RATE_2, DPS__OVERSAMPLING_RATE_4 ... DPS__OVERSAMPLING_RATE_128
	 * returns: 			status code
	 */
	int16_t measurePressureOnce(float &result, uint8_t oversamplingRate);

	/**
	 * starts a single pressure measurement
	 *
	 * returns: 	status code
	 */
	int16_t startMeasurePressureOnce(void);

	/**
	 * starts a single pressure measurement with specified oversamplingRate
	 *
	 * oversamplingRate: 	DPS__OVERSAMPLING_RATE_1, DPS__OVERSAMPLING_RATE_2, DPS__OVERSAMPLING_RATE_4 ... DPS__OVERSAMPLING_RATE_128
	 * returns: 			status code
	 */
	int16_t startMeasurePressureOnce(uint8_t oversamplingRate);

	/**
	 * gets the result a single temperature or pressure measurement in °C or Pa
	 *
	 * &result:		reference to a float value where the result will be written
	 * returns: 	status code
	 */
	int16_t getSingleResult(float &result);

	/**
	 * starts a continuous temperature measurement with specified measurement rate and oversampling rate
	 * If measure rate is n and oversampling rate is m, the DPS310 performs 2^(n+m) internal measurements per second. 
	 * The DPS310 cannot operate with high precision and high speed at the same time. Consult the datasheet for more information.
	 * 
	 * measureRate: 		DPS__MEASUREMENT_RATE_1, DPS__MEASUREMENT_RATE_2,DPS__MEASUREMENT_RATE_4 ... DPS__MEASUREMENT_RATE_128
	 * oversamplingRate: 	DPS__OVERSAMPLING_RATE_1, DPS__OVERSAMPLING_RATE_2, DPS__OVERSAMPLING_RATE_4 ... DPS__OVERSAMPLING_RATE_128
	 * 						
	 * returns: 			status code
	 * 						
	 */
	int16_t startMeasureTempCont(uint8_t measureRate, uint8_t oversamplingRate);

	/**
	 * starts a continuous temperature measurement with specified measurement rate and oversampling rate
	 *
	 * measureRate: 		DPS__MEASUREMENT_RATE_1, DPS__MEASUREMENT_RATE_2,DPS__MEASUREMENT_RATE_4 ... DPS__MEASUREMENT_RATE_128
	 * oversamplingRate: 	DPS__OVERSAMPLING_RATE_1, DPS__OVERSAMPLING_RATE_2, DPS__OVERSAMPLING_RATE_4 ... DPS__OVERSAMPLING_RATE_128
	 * returns: 			status code
	 */
	int16_t startMeasurePressureCont(uint8_t measureRate, uint8_t oversamplingRate);

	/**
	 * starts a continuous temperature and pressure measurement with specified measurement rate and oversampling rate for temperature and pressure measurement respectvely.
	 *
	 * tempMr				measure rate for temperature
	 * tempOsr				oversampling rate for temperature
	 * prsMr				measure rate for pressure
	 * prsOsr				oversampling rate for pressure
	 * returns: 			status code
	 */
	int16_t startMeasureBothCont(uint8_t tempMr, uint8_t tempOsr, uint8_t prsMr, uint8_t prsOsr);

	/**
	 * Gets the interrupt status flag of the FIFO
	 *
	 * Returns: 	1 if the FIFO is full and caused an interrupt
	 * 				0 if the FIFO is not full or FIFO interrupt is disabled
	 * 				-1 on fail
	 */
	int16_t getIntStatusFifoFull(void);

	/**
	 * Gets the interrupt status flag that indicates a finished temperature measurement
	 *
	 * Returns: 	1 if a finished temperature measurement caused an interrupt;
	 * 				0 if there is no finished temperature measurement or interrupts are disabled;
	 * 				-1 on fail.
	 */
	int16_t getIntStatusTempReady(void);

	/**
	 * Gets the interrupt status flag that indicates a finished pressure measurement
	 *
	 * Returns: 	1 if a finished pressure measurement caused an interrupt; 
	 * 				0 if there is no finished pressure measurement or interrupts are disabled;
	 * 				-1 on fail.
	 */
	int16_t getIntStatusPrsReady(void);

	/**
	 * Function to fix a hardware problem on some devices
	 * You have this problem if you measure a temperature which is too high (e.g. 60°C when temperature is around 20°C)
	 * Call correctTemp() directly after begin() to fix this issue
	 */
	int16_t correctTemp(void);

  protected:
	//scaling factor table
	static const int32_t scaling_facts[DPS__NUM_OF_SCAL_FACTS];

	dps::Mode m_opMode;

	//flags
	uint8_t m_initFail;

	uint8_t m_productID;
	uint8_t m_revisionID;

	//settings
	uint8_t m_tempMr;
	uint8_t m_tempOsr;
	uint8_t m_prsMr;
	uint8_t m_prsOsr;

	// compensation coefficients for both dps310 and dps422
	int32_t m_c00;
	int32_t m_c10;
	int32_t m_c01;
	int32_t m_c11;
	int32_t m_c20;
	int32_t m_c21;
	int32_t m_c30;

	// last measured scaled temperature (necessary for pressure compensation)
	float m_lastTempScal;

	//bus specific
	uint8_t m_SpiI2c; //0=SPI, 1=I2C

	//used for I2C
	TwoWire *m_i2cbus;
	uint8_t m_slaveAddress;
	//used for SPI
	SPIClass *m_spibus;
	int32_t m_chipSelect;
	uint8_t m_threeWire;

	/**
	 * Initializes the sensor.
	 * This function has to be called from begin()
	 * and requires a valid bus initialization.
	 */
	virtual void init(void) = 0;

	/**
	 * reads the compensation coefficients from the sensor
	 * this is called once from init(), which is called from begin()
	 *
	 * returns: 	0 on success, -1 on fail
	 */
	virtual int16_t readcoeffs(void) = 0;

	/**
	 * Sets the Operation Mode of the sensor
	 * 
	 * opMode: 			the new OpMode as defined by dps::Mode; CMD_BOTH should not be used for DPS310
	 * return: 			0 on success, -1 on fail
	 */
	int16_t setOpMode(uint8_t opMode);

	/**
	 * Configures temperature measurement
	 *
	 * temp_mr: 		DPS__MEASUREMENT_RATE_1, DPS__MEASUREMENT_RATE_2,DPS__MEASUREMENT_RATE_4 ... DPS__MEASUREMENT_RATE_128
	 * temp_osr: 	DPS__OVERSAMPLING_RATE_1, DPS__OVERSAMPLING_RATE_2, DPS__OVERSAMPLING_RATE_4 ... DPS__OVERSAMPLING_RATE_128
	 * 				
	 * returns: 	0 normally or -1 on fail
	 */
	virtual int16_t configTemp(uint8_t temp_mr, uint8_t temp_osr);

	/**
	 * Configures pressure measurement
	 *
	 * prs_mr: 		DPS__MEASUREMENT_RATE_1, DPS__MEASUREMENT_RATE_2,DPS__MEASUREMENT_RATE_4 ... DPS__MEASUREMENT_RATE_128
	 * prs_osr: 	DPS__OVERSAMPLING_RATE_1, DPS__OVERSAMPLING_RATE_2, DPS__OVERSAMPLING_RATE_4 ... DPS__OVERSAMPLING_RATE_128
	 * returns: 	0 normally or -1 on fail
	 */
	virtual int16_t configPressure(uint8_t prs_mr, uint8_t prs_osr);

	virtual int16_t flushFIFO() = 0;

	virtual float calcTemp(int32_t raw) = 0;

	virtual float calcPressure(int32_t raw) = 0;

	int16_t enableFIFO();

	int16_t disableFIFO();

	/**
	 * calculates the time that the sensor needs for 2^mr measurements with an oversampling rate of 2^osr (see table "pressure measurement time (ms) versus oversampling rate")
	 * Note that the total measurement time for temperature and pressure must not be more than 1 second.
	 * Timing behavior of pressure and temperature sensors can be considered the same.
	 * 
	 * mr: 		DPS__MEASUREMENT_RATE_1, DPS__MEASUREMENT_RATE_2,DPS__MEASUREMENT_RATE_4 ... DPS__MEASUREMENT_RATE_128
	 * osr: 	DPS__OVERSAMPLING_RATE_1, DPS__OVERSAMPLING_RATE_2, DPS__OVERSAMPLING_RATE_4 ... DPS__OVERSAMPLING_RATE_128
	 * returns: time that the sensor needs for this measurement
	 */
	uint16_t calcBusyTime(uint16_t temp_rate, uint16_t temp_osr);

	/**
	 * reads the next raw value from the FIFO
	 *
	 * value: 	the raw pressure or temperature value read from the pressure register blocks, where the LSB of PRS_B0 marks wheather the value is a temperatur or a pressure.
	 * 
	 * returns:	-1 on fail
	 * 			0 if result is a temperature raw value
	 * 			1 if result is a pressure raw value
	 */
	int16_t getFIFOvalue(int32_t *value);

	/**
	 * Gets the results from continuous measurements and writes them to given arrays
	 *
	 * *tempBuffer: 	The start address of the buffer where the temperature results
	 * 					are written
	 * 					If this is NULL, no temperature results will be written out
	 * &tempCount:		The size of the buffer for temperature results.
	 * 					When the function ends, it will contain the number of bytes written to the buffer.
	 * *prsBuffer: 		The start address of the buffer where the pressure results
	 * 					are written
	 * 					If this is NULL, no pressure results will be written out
	 * &prsCount:		The size of the buffer for pressure results.
	 * 					When the function ends, it will contain the number of bytes written to the buffer.
	 * returns:			status code
	 */
	int16_t getContResults(float *tempBuffer, uint8_t &tempCount, float *prsBuffer, uint8_t &prsCount, RegMask_t reg);

	/**
	 * reads a byte from the sensor
	 *
	 * regAdress: 	Address that has to be read
	 * returns: 	register content or -1 on fail
	 */
	int16_t readByte(uint8_t regAddress);

	/**
	 * reads a byte from the sensor via SPI
	 * this function is automatically called by readByte
	 * if the sensor is connected via SPI
	 *
	 * regAdress: 	Address that has to be read
	 * returns: 	register content or -1 on fail
	 */
	int16_t readByteSPI(uint8_t regAddress);

	/**
	 * reads a block from the sensor
	 *
	 * regAdress: 	Address that has to be read
	 * length: 		Length of data block
	 * buffer: 	Buffer where data will be stored
	 * returns: 	number of bytes that have been read successfully, which might not always equal to length due to rx-Buffer overflow etc.
	 */
	int16_t readBlock(RegBlock_t regBlock, uint8_t *buffer);

	/**
	 * reads a block from the sensor via SPI
	 *
	 * regAdress: 	Address that has to be read
	 * length: 		Length of data block
	 * readbuffer: 	Buffer where data will be stored
	 * returns: 	number of bytes that have been read successfully, which might not always equal to length due to rx-Buffer overflow etc.
	 */
	int16_t readBlockSPI(RegBlock_t regBlock, uint8_t *readbuffer);

	/**
	 * writes a byte to a given register of the sensor without checking
	 *
	 * regAdress: 	Address of the register that has to be updated
	 * data:		Byte that will be written to the register
	 * return:		0 if byte was written successfully
	 * 				or -1 on fail
	 */
	int16_t writeByte(uint8_t regAddress, uint8_t data);

	/**
	 * writes a byte to a register of the sensor
	 *
	 * regAdress: 	Address of the register that has to be updated
	 * data:		Byte that will be written to the register
	 * check: 		If this is true, register content will be read after writing
	 * 				to check if update was successful
	 * return:		0 if byte was written successfully
	 * 				or -1 on fail
	 */
	int16_t writeByte(uint8_t regAddress, uint8_t data, uint8_t check);

	/**
	 * writes a byte to a register of the sensor via SPI
	 *
	 * regAdress: 	Address of the register that has to be updated
	 * data:		Byte that will be written to the register
	 * check: 		If this is true, register content will be read after writing
	 * 				to check if update was successful
	 * return:		0 if byte was written successfully
	 * 				or -1 on fail
	 */
	int16_t writeByteSpi(uint8_t regAddress, uint8_t data, uint8_t check);

	/**
	 * updates a bit field of the sensor without checking
	 *
	 * regMask: 	Mask of the register that has to be updated
	 * data:		BitValues that will be written to the register
	 * return:		0 if byte was written successfully
	 * 				or -1 on fail
	 */
	int16_t writeByteBitfield(uint8_t data, RegMask_t regMask);

	/**
	 * updates a bit field of the sensor
	 *
	 * regMask: 	Mask of the register that has to be updated
	 * data:		BitValues that will be written to the register
	 * check: 		enables/disables check after writing; 0 disables check.
	 * 				if check fails, -1 will be returned
	 * return:		0 if byte was written successfully
	 * 				or -1 on fail
	 */
	int16_t writeByteBitfield(uint8_t data, uint8_t regAddress, uint8_t mask, uint8_t shift, uint8_t check);

	/**
	 * reads a bit field from the sensor
	 * regMask: 	Mask of the register that has to be updated
	 * data:		BitValues that will be written to the register
	 * return:		read and processed bits
	 * 				or -1 on fail
	 */
	int16_t readByteBitfield(RegMask_t regMask);

	/**
	 * @brief converts non-32-bit negative numbers to 32-bit negative numbers with 2's complement
	 * 
	 * @param raw The raw number of less than 32 bits
	 * @param length The bit length
	 */
	void getTwosComplement(int32_t *raw, uint8_t length);

	/**
	 * @brief Get a raw result from a given register block
	 * 
	 * @param raw The address where the raw value is to be written
	 * @param reg The register block to be read from
	 * @return status code 
	 */
	int16_t getRawResult(int32_t *raw, RegBlock_t reg);
};

#endif //DPSCLASS_H_INCLUDED

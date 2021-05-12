/******************************************************************************
 * Copyright (c) 2017 by Silicon Laboratories Inc. All rights reserved.
 *
 * http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
 *****************************************************************************/

#ifndef _CSLIB_H_
#define _CSLIB_H_

#include "si_toolchain_select.h"

/**************************************************************************//**
 * @addtogroup CSLIB_ApplicationAPI
 * @{
 * @brief Capacitive sensing firmware library for Silicon Labs MCUs
 *
 * # Introduction #
 * The capacitive sensing library provides pre-compiled code set that
 * performs touch qualification, filtering, and state maintenance for
 * capacitive sensing-enabled Silicon Laboratories MCUs.
 *
 * The library functions using calls into a device layer that interfaces
 * with hardware peripherals.
 *****************************************************************************/

/**************************************************************************//**
 * @brief Defines the depth of the buffers for raw and processed data
 * used in the sensor node struct.  Should not be changed without a library
 * re-compilation.
*****************************************************************************/
#define DEF_SENSOR_BUFFER_SIZE 2 /*!< Depth of sensor node structure's raw data buffer */

/*! @struct SensorStruct_t
    @brief Stores all runtime values for an enabled capacitive sensor.
 */
typedef struct
{
   uint16_t rawBuffer[DEF_SENSOR_BUFFER_SIZE]; /*!< Newest sample taken from CS hardware, without any processing */
   uint16_t currentBaseline;                   /*!< Runtime estimate of untouched or inactive state of CS sensor input */
   uint8_t touchDeltaDiv16;                    /*!< Describes the expected difference between untouched and touched CS value */
   uint8_t activeIndicator;                    /*!< Bit array showing whether touch is qualified on sensor */
   uint8_t debounceCounts;                     /*!< Stores consecutive CS values above or below active or inactive threshold */
   int8_t baselineAccumulator;                 /*!< Estimates data-baseline positive/negative offset, leads to baseline update */
   SI_UU32_t expValue;                         /*!< Filtered, exponentially averaged version of newest data */
} SensorStruct_t;

#define DEBOUNCE_ACTIVE_MASK 0x80             /*!< Signifies a qualified touch*/
#define SINGLE_ACTIVE_MASK   0x40             /*!< Signifies a candidate touch*/

/*! @brief Defines all noise characterization states the CSLIB will use for characterization
 */
enum CSLIB_noiseLevels
{
  low = 1,            /*!< Interference should have negligible impact on sensing */
  mid = 2,            /*!< Interference forces system to qualify touches conservatively */
  high = 3            /*!< Interference forces entrance into no confidence mode if enabled */
};

#ifdef DOXYGEN
/**************************************************************************//**
 * @version 0.0.0
 * @struct CSLIB_LibraryVersion_t
 * @brief Structure for version of CSLIB library
 * @details This structure holds the CSLIB library version in the format
 * MAJOR.MINOR.REVISION.
 * @var CSLIB_LibraryVersion_t::major
 * @brief Major field of CSLIB library version
 * @var CSLIB_LibraryVersion_t::minor
 * @brief Minor field of CSLIB library version
 * @var CSLIB_LibraryVersion_t::revision
 * @brief Revision field of CSLIB library version
*****************************************************************************/
typedef struct
{
  uint8_t major;
  uint8_t minor;
  uint8_t revision;
} CSLIB_LibraryVersion_t;
#else
typedef SI_SEG_CODE struct
{
  uint8_t major;
  uint8_t minor;
  uint8_t revision;
} CSLIB_LibraryVersion_t;
#endif

/*!
@brief CSLIB library version.
 */
#define CSLIB_LIBRARY_VERSION { 0, 0, 0 }

/*!
@brief Global variable which holds the CSLIB library version.
 */
extern CSLIB_LibraryVersion_t CSLIB_Version;

/**************************************************************************//**
 * @brief Initializes capacitive sensing-related peripherals
 * @details This function calls into the library, which in turn calls into the device
 * layer functions initializing the sensing and timing hardware used during
 * capacitive sensing conversions.  Active mode versions of configuration
 * functions are called here, as the library always starts in active mode.
 *****************************************************************************/
void CSLIB_initHardware(void);

/**************************************************************************//**
 * @brief Initializes capacitive sensing state variables
 * @details This function resets all state variables in the sensor node struct
 * and library-internal state variables to default.
 *****************************************************************************/
void CSLIB_initLibrary(void);

/**************************************************************************//**
 * @brief Scans capacitive sensing inputs, processes and updates state variables
 * @details This function should be called in a firmware project's main() loop.  The
 * function will execute a capacitive sensing scan sequence, filter samples,
 * examine samples for qualified touches, and update other state variables.
 *****************************************************************************/
void CSLIB_update(void);

/**************************************************************************//**
 * @brief Scans Reverts all values in a sensor node struct element to reset
 * @details This function resets all data in a sensor node struct element.  It is used
 * during initialization.
 * @note In most cases it is not recommended that this function be used
 * by application firmware because baseline information will be lost without being
 * re-initialized.
 *****************************************************************************/
void CSLIB_resetSensorStruct(uint8_t sensorIndex, uint16_t fillValue);

/**************************************************************************//**
 * @brief Checks to see if any enabled sensor is single "candidate" active
 * @details This function checks the #SINGLE_ACTIVE_MASK in #SensorStruct_t::activeIndicator
 * structure for all enabled sensors.  If any sensor's #SINGLE_ACTIVE_MASK
 * is set, meaning that the sensor is a candidate active sensor, the
 * the function returns TRUE.  Otherwise it returns FALSE.
 * @return 1 if any sensor is active, 0 otherwise
 *****************************************************************************/
uint8_t CSLIB_anySensorSingleActive(void);

/**************************************************************************//**
 * @brief Checks if a sensor is single "candidate" active
 * @param sensorIndex into sensor node element to be checked
 * @details This function checks the #SINGLE_ACTIVE_MASK in #SensorStruct_t::activeIndicator
 * structure for the sensor defined by sensorIndex.  If any sensor's #SINGLE_ACTIVE_MASK
 * is set, meaning that the sensor is a candidate active sensor, the
 * the function returns TRUE.  Otherwise it returns FALSE.
 * @return 1 if sensor at sensorIndex is active, 0 otherwise
 *****************************************************************************/
uint8_t CSLIB_isSensorSingleActive(uint8_t sensorIndex);

/**************************************************************************//**
 * @brief Checks to see if any enabled sensor is debounce "qualified" active
 * @details This function checks the #DEBOUNCE_ACTIVE_MASK in #SensorStruct_t::activeIndicator
 * structure for all enabled sensors.  If any sensor's #DEBOUNCE_ACTIVE_MASK
 * is set, meaning that the sensor is a qualified active sensor, the
 * the function returns TRUE.  Otherwise it returns FALSE.
 * @return 1 if any sensor is active, 0 otherwise
 *****************************************************************************/
uint8_t CSLIB_anySensorDebounceActive(void);

/**************************************************************************//**
 * @brief Checks if a sensor is single "qualified" active
 * @param sensorIndex into sensor node element to be checked
 * @details This function checks the #DEBOUNCE_ACTIVE_MASK in #SensorStruct_t::activeIndicator
 * structure for the sensor defined by sensorIndex.  If any sensor's #DEBOUNCE_ACTIVE_MASK
 * is set, meaning that the sensor is a qualified active sensor, the
 * the function returns TRUE.  Otherwise it returns FALSE.
 * @return 1 if sensor at sensorIndex is active, 0 otherwise
 *****************************************************************************/
uint8_t CSLIB_isSensorDebounceActive(uint8_t sensorIndex);

/**************************************************************************//**
 * @brief Get baseline-adjusted, noise-adjusted touch delta
 * @param sensorIndex Index into sensor node struct
 * @param flood_level additional value that can be subtracted in addition to baseline
 * @details This function executes math operations to find the raw data value for
 * sensor at sensorIndex normalized bythat sensor's baseline value.  Note that
 * the function uses #SensorStruct_t::rawBuffer if #noise_level is #low
 * and uses #SensorStruct_t::expValue otherwise.
 *
 * flood_level can be used to subtract out additional value after normalization.
 * @return Absolute delta between baseline and raw/filtered data
 *****************************************************************************/
uint16_t CSLIB_getNormalizedDelta(uint8_t sensorIndex, uint16_t flood_level);

/**************************************************************************//**
 * @brief Pushes new sensor sample into sensor node buffer
 * @param sensorIndex index into sensor node array
 * @param newValue value to be pushed at index
 * @details This function is used by the device layer of code that interfaces
 * with capacitive sensing hardware.  When @ref CSLIB_update() calls
 * into the device layer to convert a new sample set using @ref CSLIB_scanSensorCB(),
 * the device layer implementation of @ref CSLIB_scanSensorCB() should use this
 * routine to push newly converted samples into the sensor node structure
 * for processing within the library.
 *****************************************************************************/
void CSLIB_nodePushRaw(uint8_t sensorIndex, uint16_t newValue);

/**************************************************************************//**
 * @brief Reads a node structure sensor's raw buffer value
 * @param sensorIndex The element of the sensor node structure
 * @param bufferIndex The element inside the sensor node element's raw data buffer
 * @details This function can be used to read values in the raw data buffer at
 * bufferIndex of an enabled sensor specified by sensorIndex.
 * @note sensorIndex should not exceed the value defined by DEF_NUM_SENSORS
 * @note bufferIndex should not exceed the value defined by #DEF_SENSOR_BUFFER_SIZE
 * @return raw data at CSLIB_node[sensorIndex].rawBuffer[bufferIndex]
 *****************************************************************************/
uint16_t CSLIB_nodeGetRaw(uint8_t sensorIndex, uint8_t bufferIndex);

/**************************************************************************//**
 * @brief Read touch delta from sensor node struct and expand from 8-bit value
 * @param sensorIndex Designates the sensor touch delta to be read
 * @details This function converts the 8-bit packed touch delta stored in
 * non-volatile memory as an expanded, 16-bit value.
 * @return Touch delta in capacitive sensing output codes
 *****************************************************************************/
int16_t CSLIB_getUnpackedTouchDelta(uint8_t sensorIndex);

/**************************************************************************//**
 * @brief Callback routine to configure sensors for baseline initialization
 * @details This function provides applications with an opportunity to configure
 * a device with any special characteristics needed to perform baseline
 * initialization.
 * @note The example function provided in code examples should be sufficient.
 *****************************************************************************/
void CSLIB_baselineInitEnableCB(void);

/**************************************************************************//**
 * @brief Callback routine to revert configuration back to sensing state after baseline initialization
 * @details This function provides applications with an opportunity to
 * restore the configuration of the sensors to what it was before
 * @ref CSLIB_baselineInitEnableCB was called.
 * @note The code example version of this function should be sufficient in most cases.
 *****************************************************************************/
void CSLIB_baselineInitDisableCB(void);

/**************************************************************************//**
 * @brief Callback to configure sensors for sleep mode
 * @details If low power mode is included in build, this function configures
 * the capacitive sensing block and inputs for sleep mode.
 *****************************************************************************/
void CSLIB_configureSensorForSleepModeCB(void);

/**************************************************************************//**
 * @brief Callback to configure timer for sleep mode
 * @details If low power mode is included in build, this function sets the wake-up
 * event to the sleep mode scan period.
 *****************************************************************************/
void CSLIB_configureTimerForSleepModeCB(void);

/**************************************************************************//**
 * @brief Callback to configure timer for active mode scanning
 * @details Configures the timer to initiate a scan as defined by active
 * mode scan period.
 *****************************************************************************/
void CSLIB_configureTimerForActiveModeCB(void);

/**************************************************************************//**
 * @brief Callback to enter low power mode
 * @details If low power mode is included in build, this function
 * mode-switches the core to a low power state.
 *****************************************************************************/
extern void CSLIB_enterLowPowerStateCB(void);

/**************************************************************************//**
 * @brief Callback to initiate a scan and return result
 * @details This function only interfaces with hardware to initiate a scan and
 * return the result.  It relies on other functions for all capacitive sensor
 * and port configuration.  It is usually used by #CSLIB_scanSensorCB.
 * @returns 16-bit scan result
 *****************************************************************************/
uint16_t CSLIB_executeConversionCB(void);

/**************************************************************************//**
 * @brief Check wake sources
 * @details This function examines the system timer to check for wake events.
 *****************************************************************************/
void CSLIB_checkTimerCB(void);

/*!
@brief Callback to initialize sensors for active mode scanning
*/
extern void CSLIB_configureSensorForActiveModeCB(void);

/**************************************************************************//**
 * @brief Performs capacitive sensing conversion on a sensor
 * @param sensorIndex sensor to be scanned, corresponds to sensor node struct
 * @details This device layer function is called from within library code after
 * #CSLIB_update() is called in the main loop.  The function is responsible
 * for any configuration of the capacitive sensing block necessary to perform
 * the scan.
 * @return the newly converted capacitive sensing output
 *****************************************************************************/
uint16_t CSLIB_scanSensorCB(uint8_t sensorIndex);

/**************************************************************************//**
 * @brief Checks timing and possibly enters low power mode
 * @details This function checks the time in the system relative to active mode
 * scan period timing.  It should be called in the firmware project's main()
 * while(1) loop.
 *
 * If FREE_RUN_SETTING is set to 0, the function will enter low power until
 * the next active mode scan period.
 *
 * If FREE_RUN_SETTING is set to 1, the function will exit, allowing for
 * another iteration in the main() loop.
 *
 * If the function finds that no qualified touches have been
 * found in a time specified by COUNTS_BEFORE_SLEEP multiplied by
 * ACTIVE_MODE_SCAN_PERIOD, the function initializes the system to run
 * in its sleep scanning mode and enters a low power state.
 *****************************************************************************/
void CSLIB_lowPowerUpdate(void);

/**************************************************************************//**
 * @brief Returns raw or filtered sensor data, based on characterized interference
 * @param sensorIndex Sensor node element whose data is to be read
 * @details This function either returns the newest raw data for a sensor, or
 * the newest filtered data for a sensor, depending on which data type the
 * interference characterization algorithm determines to be necessary to
 * show current sensor state.  In low interference environments, raw data
 * will be returned.  In higher interference states, filtered data will
 * be returned.
 * @return sensor data from sensor node struct defined index
 *****************************************************************************/
uint16_t CSLIB_getNoiseAdjustedSensorData(uint8_t sensorIndex);

/*!
@brief Global counter incremented by the system timer
*/
extern SI_SEG_XDATA uint8_t timerTick;

/*!
@brief Stores current interference characterization level, defined by #CSLIB_noiseLevels
*/
extern SI_SEG_DATA uint8_t noise_level;

/*!
@brief Sensor node data structure
*/
SI_SEG_XDATA SensorStruct_t CSLIB_node[];

/*!
@brief Bit that can be set to disable entrance to sleep, overriding timers.
*/
extern uint8_t disable_sleep_and_stall;

/*!
@brief Average sample-to-sample code difference for enabled sensors, used to define #noise_level
 */
extern SI_SEG_IDATA uint16_t CSLIB_systemNoiseAverage;

#ifndef FFD
/*!
@brief Size of the sensor node struct, should only be changed at compile time by editing DEF_NUM_SENSORS
*/
extern SI_SEG_DATA uint8_t CSLIB_numSensors;

/*!
@brief saves the depth of the raw data buffer
*/
extern SI_SEG_DATA uint8_t CSLIB_sensorBufferSize;

/*!
@brief Size of raw data buffers within sensor node struct elements, should not be changed
*/
extern SI_SEG_DATA uint8_t CSLIB_buttonDebounce;

/*!
@brief Sets the scan period in ms for active mode scanning.  Defaults to DEF_ACTIVE_MODE_PERIOD
*/
extern SI_SEG_DATA uint16_t CSLIB_activeModePeriod;

/*!
@brief Sets the scan period in ms for sleep mode scanning.  Defaults to DEF_SLEEP_MODE_PERIOD
*/
extern SI_SEG_DATA uint16_t CSLIB_sleepModePeriod;

/*!
@brief Sets the number of consecutive scans without a single qualified touch before entering sleep mode.
*/
extern SI_SEG_DATA uint16_t CSLIB_countsBeforeSleep;

/**************************************************************************//**
 * @brief Configures whether system goes to sleep between scans in active mode.
 * @details 1 means that the system is in free run mode and will not go to
 * sleep.  0 means that the system will take a single scan within an active
 * mode scan period and will then enter sleep once
 * #CSLIB_lowPowerUpdate() is called. The system will stay asleep until the
 * next active mode scan period begins.
 *****************************************************************************/
extern SI_SEG_DATA uint8_t CSLIB_freeRunSetting;

/**************************************************************************//**
 * @brief Sets whether the system is allowed to ever use sleep mode scanning.
 * @details If set to 0, the system will always remain in active mode.  If
 * set to 1, the system is allowed to perform sleep mode scanning when
 * conditions permit it.
 *****************************************************************************/
extern SI_SEG_DATA uint8_t CSLIB_sleepModeEnable;

/*!
@brief Array storing percentages within touch deltas below which touch release events are qualified.
*/
extern SI_SEG_CODE uint8_t CSLIB_inactiveThreshold[];

/*!
@brief Array storing percentages within touch deltas below which touch events are qualified.
*/
extern SI_SEG_CODE uint8_t CSLIB_activeThreshold[];

/*!
@brief Array of expected conversion output codes between inactive and active sensor states
*/
extern SI_SEG_CODE uint8_t CSLIB_averageTouchDelta[];
#endif

/** @} (end CSLIB_ApplicationAPI) */

/*! @addtogroup CS0_Plausibility
 * @{
 * @brief Capacitive sensing plausibility check for IEC compliance
*/

/**************************************************************************//**
 * @brief IEC60730 analog plausibility check for capacitive sensing hardware
 * @details Each execution of this function checks one enabled capacitive
 * sensing input to determine if that input is functioning within safety
 * specifications.  The test should check that each input converts to valid
 * capacitive sensing output codes when that pin is not shorted to ground/VDD.
 *****************************************************************************/
void iec60730_CSPlausibilityCheck(void);
/** @} (end CS0_Plausibility) */

#endif

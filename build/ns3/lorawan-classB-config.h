/*!
 * \file      LoRaMacClassBConfig.h
 *
 * \brief     LoRa MAC Class B configuration
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \code
 *                ______                              _
 *               / _____)             _              | |
 *              ( (____  _____ ____ _| |_ _____  ____| |__
 *               \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 *               _____) ) ____| | | || |_| ____( (___| | | |
 *              (______/|_____)_|_|_| \__)_____)\____)_| |_|
 *              (C)2013 Semtech
 *
 *               ___ _____ _   ___ _  _____ ___  ___  ___ ___
 *              / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 *              \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 *              |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 *              embedded.connectivity.solutions===============
 *
 * \endcode
 *
 * \author    Miguel Luis ( Semtech )
 *
 * \author    Gregory Cristian ( Semtech )
 *
 * \author    Daniel Jaeckle ( STACKFORCE )
 *
 * \defgroup  LORAMACCLASSB LoRa MAC Class B configuration + Beacon Functions 
 *            This header file contains parameters/functions to configure the class b operation.
 *            By default, all parameters are set according to the specification.
 * \{
 */
#ifndef __LORAWANCLASSBCONFIG_H__
#define __LORAWANCLASSBCONFIG_H__


#include <stdint.h> // Shouldn't need this because C++11 is used 



/*!
 * Defines the beacon interval in ms
 */
#define CLASSB_BEACON_INTERVAL                      128000

/*!
 * Minimum required number of symbols to detect an Rx frame
 * Default: 6 symbols
 */
#define DEFAULT_MIN_BEACON_RX_SYMBOLS               6

/*!
 * Beacon reserved time in ms
 */
#define CLASSB_BEACON_RESERVED                      2120

/*!
 * Beacon guard time in ms
 */
#define CLASSB_BEACON_GUARD                         3000

/*!
 * Beacon window time in ms
 */
#define CLASSB_BEACON_WINDOW                        122880

/*!
 * Beacon window time in numer of slots
 */
#define CLASSB_BEACON_WINDOW_SLOTS                  4096

/*!
 * Ping slot length time in ms
 */
#define CLASSB_PING_SLOT_WINDOW                     30

/*!
 * Maximum allowed beacon less time in ms
 */
#define CLASSB_MAX_BEACON_LESS_PERIOD               7200000

/*!
 * Delay time for the BeaconTimingAns in ms
 */
#define CLASSB_BEACON_DELAY_BEACON_TIMING_ANS       30

/*!
 * Default symbol timeout for beacons and ping slot windows
 */
#define CLASSB_BEACON_SYMBOL_TO_DEFAULT             8

/*!
 * Maximum symbol timeout for beacons
 */
#define CLASSB_BEACON_SYMBOL_TO_EXPANSION_MAX       255

/*!
 * Maximum symbol timeout for ping slots
 */
#define CLASSB_PING_SLOT_SYMBOL_TO_EXPANSION_MAX    30

/*!
 * Symbol expansion value for beacon windows in case of beacon
 * loss in symbols
 */
#define CLASSB_BEACON_SYMBOL_TO_EXPANSION_FACTOR    2

/*!
 * Defines the default window movement time
 */
#define CLASSB_WINDOW_MOVE_DEFAULT                  2

/*!
 * Defines the maximum time for the beacon movement
 */
#define CLASSB_WINDOW_MOVE_EXPANSION_MAX            256

/*!
 * Defines the expansion factor for the beacon movement
 */
#define CLASSB_WINDOW_MOVE_EXPANSION_FACTOR         2

/*!
 * Minimum required number of symbols to detect an Rx frame
 * Default: 6 symbols
 */
#define CLASSB_MIN_RX_SYMBOLS                       6

/*
 * CLASS B
 */
/*!
 * Beacon frequency
 */
#define AU915_BEACON_CHANNEL_FREQ                   923300000

/*!
 * Beacon frequency channel stepwidth
 */
#define AU915_BEACON_CHANNEL_STEPWIDTH              600000

/*!
 * Ping slot channel frequency
 */
#define AU915_PING_SLOT_CHANNEL_FREQ                923300000

/*!
 * Number of possible beacon channels
 */
#define AU915_BEACON_NB_CHANNELS                    8

/*!
 * Payload size of a beacon frame
 */
#define AU915_BEACON_SIZE                           23

/*!
 * Size of RFU 1 field
 */
#define AU915_RFU1_SIZE                             4

/*!
 * Size of RFU 2 field
 */
#define AU915_RFU2_SIZE                             3

/*!
 * Datarate of the beacon channel
 */
#define AU915_BEACON_CHANNEL_DR                     DR_8

/*!
 * Bandwith of the beacon channel
 */
#define AU915_BEACON_CHANNEL_BW                     2

/*!
 * Ping slot channel datarate
 */
#define AU915_PING_SLOT_CHANNEL_DR                  DR_8

/*!
 * LoRaMac maximum number of bands
 */
#define AU915_MAX_NB_BANDS                          1


/*!
 * \brief Returns the maximum value between a and b
 *
 * \param [IN] a 1st value
 * \param [IN] b 2nd value
 * \retval maxValue Maximum value
 */
#ifndef MAX
#define MAX( a, b ) ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )
#endif

/*!
 * \brief Returns `N / D` rounded to the smallest integer value greater than or equal to `N / D`
 *
 * \warning when `D == 0`, the result is undefined
 *
 * \remark `N` and `D` can be signed or unsigned
 *
 * \param [IN] N the numerator, which can have any sign
 * \param [IN] D the denominator, which can have any sign
 * \retval N / D with any fractional part rounded to the smallest integer value greater than or equal to `N / D`
 */
#define DIV_CEIL( N, D )                                                       \
    (                                                                          \
        ( N > 0 ) ?                                                            \
        ( ( ( N ) + ( D ) - 1 ) / ( D ) ) :                                    \
        ( ( N ) / ( D ) )                                                      \
    )


/*
 *
 *          DATA RATES 
 * 
 * 
*/ 
/*!
 * Region       | SF
 * ------------ | :-----:
 * AS923        | SF12 - BW125
 * AU915        | SF10 - BW125
 * CN470        | SF12 - BW125
 * CN779        | SF12 - BW125
 * EU433        | SF12 - BW125
 * EU868        | SF12 - BW125
 * IN865        | SF12 - BW125
 * KR920        | SF12 - BW125
 * US915        | SF10 - BW125
 * RU864        | SF12 - BW125
 */
#define DR_0                                        0

/*!
 * Region       | SF
 * ------------ | :-----:
 * AS923        | SF11 - BW125
 * AU915        | SF9  - BW125
 * CN470        | SF11 - BW125
 * CN779        | SF11 - BW125
 * EU433        | SF11 - BW125
 * EU868        | SF11 - BW125
 * IN865        | SF11 - BW125
 * KR920        | SF11 - BW125
 * US915        | SF9  - BW125
 * RU864        | SF11 - BW125
 */
#define DR_1                                        1

/*!
 * Region       | SF
 * ------------ | :-----:
 * AS923        | SF10 - BW125
 * AU915        | SF8  - BW125
 * CN470        | SF10 - BW125
 * CN779        | SF10 - BW125
 * EU433        | SF10 - BW125
 * EU868        | SF10 - BW125
 * IN865        | SF10 - BW125
 * KR920        | SF10 - BW125
 * US915        | SF8  - BW125
 * RU864        | SF10 - BW125
 */
#define DR_2                                        2

/*!
 * Region       | SF
 * ------------ | :-----:
 * AS923        | SF9  - BW125
 * AU915        | SF7  - BW125
 * CN470        | SF9  - BW125
 * CN779        | SF9  - BW125
 * EU433        | SF9  - BW125
 * EU868        | SF9  - BW125
 * IN865        | SF9  - BW125
 * KR920        | SF9  - BW125
 * US915        | SF7  - BW125
 * RU864        | SF9  - BW125
 */
#define DR_3                                        3

/*!
 * Region       | SF
 * ------------ | :-----:
 * AS923        | SF8  - BW125
 * AU915        | SF8  - BW500
 * CN470        | SF8  - BW125
 * CN779        | SF8  - BW125
 * EU433        | SF8  - BW125
 * EU868        | SF8  - BW125
 * IN865        | SF8  - BW125
 * KR920        | SF8  - BW125
 * US915        | SF8  - BW500
 * RU864        | SF8  - BW125
 */
#define DR_4                                        4

/*!
 * Region       | SF
 * ------------ | :-----:
 * AS923        | SF7  - BW125
 * AU915        | RFU
 * CN470        | SF7  - BW125
 * CN779        | SF7  - BW125
 * EU433        | SF7  - BW125
 * EU868        | SF7  - BW125
 * IN865        | SF7  - BW125
 * KR920        | SF7  - BW125
 * US915        | RFU
 * RU864        | SF7  - BW125
 */
#define DR_5                                        5

/*!
 * Region       | SF
 * ------------ | :-----:
 * AS923        | SF7  - BW250
 * AU915        | RFU
 * CN470        | SF12 - BW125
 * CN779        | SF7  - BW250
 * EU433        | SF7  - BW250
 * EU868        | SF7  - BW250
 * IN865        | SF7  - BW250
 * KR920        | RFU
 * US915        | RFU
 * RU864        | SF7  - BW250
 */
#define DR_6                                        6

/*!
 * Region       | SF
 * ------------ | :-----:
 * AS923        | FSK
 * AU915        | RFU
 * CN470        | SF12 - BW125
 * CN779        | FSK
 * EU433        | FSK
 * EU868        | FSK
 * IN865        | FSK
 * KR920        | RFU
 * US915        | RFU
 * RU864        | FSK
 */
#define DR_7                                        7

/*!
 * Region       | SF
 * ------------ | :-----:
 * AS923        | RFU
 * AU915        | SF12 - BW500
 * CN470        | RFU
 * CN779        | RFU
 * EU433        | RFU
 * EU868        | RFU
 * IN865        | RFU
 * KR920        | RFU
 * US915        | SF12 - BW500
 * RU864        | RFU
 */
#define DR_8                                        8

/*!
 * Region       | SF
 * ------------ | :-----:
 * AS923        | RFU
 * AU915        | SF11 - BW500
 * CN470        | RFU
 * CN779        | RFU
 * EU433        | RFU
 * EU868        | RFU
 * IN865        | RFU
 * KR920        | RFU
 * US915        | SF11 - BW500
 * RU864        | RFU
 */
#define DR_9                                        9

/*!
 * Region       | SF
 * ------------ | :-----:
 * AS923        | RFU
 * AU915        | SF10 - BW500
 * CN470        | RFU
 * CN779        | RFU
 * EU433        | RFU
 * EU868        | RFU
 * IN865        | RFU
 * KR920        | RFU
 * US915        | SF10 - BW500
 * RU864        | RFU
 */
#define DR_10                                       10

/*!
 * Region       | SF
 * ------------ | :-----:
 * AS923        | RFU
 * AU915        | SF9  - BW500
 * CN470        | RFU
 * CN779        | RFU
 * EU433        | RFU
 * EU868        | RFU
 * IN865        | RFU
 * KR920        | RFU
 * US915        | SF9  - BW500
 * RU864        | RFU
 */
#define DR_11                                       11

/*!
 * Region       | SF
 * ------------ | :-----:
 * AS923        | RFU
 * AU915        | SF8  - BW500
 * CN470        | RFU
 * CN779        | RFU
 * EU433        | RFU
 * EU868        | RFU
 * IN865        | RFU
 * KR920        | RFU
 * US915        | SF8  - BW500
 * RU864        | RFU
 */
#define DR_12                                       12

/*!
 * Region       | SF
 * ------------ | :-----:
 * AS923        | RFU
 * AU915        | SF7  - BW500
 * CN470        | RFU
 * CN779        | RFU
 * EU433        | RFU
 * EU868        | RFU
 * IN865        | RFU
 * KR920        | RFU
 * US915        | SF7  - BW500
 * RU864        | RFU
 */
#define DR_13                                       13

/*!
 * Region       | SF
 * ------------ | :-----:
 * AS923        | RFU
 * AU915        | RFU
 * CN470        | RFU
 * CN779        | RFU
 * EU433        | RFU
 * EU868        | RFU
 * IN865        | RFU
 * KR920        | RFU
 * US915        | RFU
 * RU864        | RFU
 */
#define DR_14                                       14

/*!
 * Region       | SF
 * ------------ | :-----:
 * AS923        | RFU
 * AU915        | RFU
 * CN470        | RFU
 * CN779        | RFU
 * EU433        | RFU
 * EU868        | RFU
 * IN865        | RFU
 * KR920        | RFU
 * US915        | RFU
 * RU864        | RFU
 */
#define DR_15                                       15


/*!
 * \brief Computes the RX window timeout and the RX window offset.
 *
 * \param [IN] tSymbolInUs Symbol timeout.
 *
 * \param [IN] minRxSymbols Minimum required number of symbols to detect an Rx frame.
 *
 * \param [IN] rxErrorInMs System maximum timing error of the receiver. In milliseconds
 *                     The receiver will turn on in a [-rxErrorInMs : +rxErrorInMs] ms interval around RxOffset.
 *
 * \param [IN] wakeUpTimeInMs Wakeup time of the system.
 *
 * \param [OUT] windowTimeoutInSymbols RX window timeout.
 *
 * \param [OUT] windowOffsetInMs RX window time offset to be applied to the RX delay.
 */
void RegionCommonComputeRxWindowParameters( uint32_t tSymbolInUs, uint8_t minRxSymbols, uint32_t rxErrorInMs, uint32_t wakeUpTimeInMs, uint32_t* windowTimeoutInSymbols, int32_t* windowOffsetInMs );


#endif // __LORAMACCLASSBCONFIG_H__

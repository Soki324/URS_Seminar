#ifndef __PROJECT_CONFIG_H__
#define __PROJECT_CONFIG_H__

#include <stdint.h>
#include <stdbool.h>
#include "usart.h"

/**
  ******************************************************************************
  * @file    project_config.h
  * @brief   This file contains the project configuration settings.
  ******************************************************************************
*/

#define DEBUG_LEVEL 3 // Set the debug level (0-3)

/**
 * @brief Safe VOC threshold based on VOC sensor readings and calulations from sensirion_gas_index_algorithm
 * is nicely exlplained and represented here: https://sensirion.com/media/documents/02232963/6294E043/Info_Note_VOC_Index.pdf
 * 
 * As per official Sensirion documentation, the VOC index values are categorized as follows:
 * 0 - 100: Very Low (Great air quality and within typical indoor levels)
 * 100-150: Low (Acceptable air quality)
 * 150-250: Moderate (Unacceptable air quality treshold, at this point low rpm fan should kick in to increase air circulation)
 * 250-400: High (Poor air quality, high rpm fan should be activated to increase air circulation)
 * 400+: Very High (Very poor air quality, maximum fan speed should be activated, and alert user to take action)
 */
#define PROJECT_CONFIG_VOC_SAFE_THRESHOLD 150 // Safe VOC threshold based on VOC index values
#define PROJECT_CONFIG_VOC_MODERATE_THRESHOLD 250 // Moderate VOC threshold based on VOC index values
#define PROJECT_CONFIG_VOC_HIGH_THRESHOLD 400 // High VOC threshold based on VOC index values
#define PROJECT_CONFIG_FILTER_REPLACEMENT_DAYS 30 // Days after which filter replacement is recommended
#define PROJECT_CONFIG_FILTER_WARNING_VOC_DELTA 100 // VOC delta threshold to trigger filter warning (TODO: Adjust based on testing)
#endif /* __PROJECT_CONFIG_H__ */
/* The MIT License (MIT)
 * 
 * Copyright (c) 2014 - 2015, Andreas Merkle
 * http://www.blue-andi.de
 * vscp@blue-andi.de
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */

/*******************************************************************************
	DESCRIPTION
*******************************************************************************/
/**
@brief  Logging
@file   log.c
@author Andreas Merkle, http://www.blue-andi.de

@section desc Description
@see log.h

@section svn Subversion
$Author: amerkle $
$Rev: 449 $
$Date: 2015-01-05 20:23:52 +0100 (Mo, 05 Jan 2015) $
*******************************************************************************/

/*******************************************************************************
	INCLUDES
*******************************************************************************/
#include "log.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

/*******************************************************************************
	COMPILER SWITCHES
*******************************************************************************/

/*******************************************************************************
	CONSTANTS
*******************************************************************************/

/*******************************************************************************
	MACROS
*******************************************************************************/

/*******************************************************************************
	TYPES AND STRUCTURES
*******************************************************************************/

/*******************************************************************************
	PROTOTYPES
*******************************************************************************/

static char const * const   log_getLogLevelStr(LOG_LEVEL level);

/*******************************************************************************
	LOCAL VARIABLES
*******************************************************************************/

/** The current log level in the system. */
static unsigned int log_logLevel    = 0;

/*******************************************************************************
	GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
	GLOBAL FUNCTIONS
*******************************************************************************/

/**
 * This function intializes the module.
 */
extern void log_init(void)
{
    /* Nothing to do */
    
    return;
}

/**
 * This function sets the log level. The log level can be a sum of several single
 * log level. Use OR to combine them.
 *
 * @param[in]   level   Log level
 */
extern void log_setLevel(uint8_t level)
{
    log_logLevel = level;
    return;
}

/**
 * This function write a log message to the configured output stream. Don't call this
 * function direct, use the LOG_XXXXX macros instead!
 *
 * @param[in]   fileName    Module filename
 * @param[in]   line        Line number in the module
 * @param[in]   logLevel    Log level of the message
 * @param[in]   message     Message string
 */
extern void log_write(char const * const fileName, int line, uint8_t logLevel, char const * const message)
{
    if (0 != (log_logLevel & logLevel))
    {
        log_printf("%s (%d) - %s: %s\n", fileName, line, log_getLogLevelStr(logLevel), message);
    }
    
    return;
}

/**
 * This function write a log message to the configured output stream. Don't call this
 * function direct, use the LOG_XXXXX macros instead!
 *
 * @param[in]   fileName    Module filename
 * @param[in]   line        Line number in the module
 * @param[in]   logLevel    Log level of the message
 * @param[in]   message     Message string
 * @param[in]   par         Parameter
 */
extern void log_writeParUInt32(char const * const fileName, int line, uint8_t logLevel, char const * const message, uint32_t par)
{
    if (0 != (log_logLevel & logLevel))
    {
        log_printf("%s (%d) - %s: %s %u\n", fileName, line, log_getLogLevelStr(logLevel), message, par);
    }
    
    return;
}

/**
 * This function write a log message to the configured output stream. Don't call this
 * function direct, use the LOG_XXXXX macros instead!
 *
 * @param[in]   fileName    Module filename
 * @param[in]   line        Line number in the module
 * @param[in]   logLevel    Log level of the message
 * @param[in]   message     Message string
 * @param[in]   par         Parameter
 */
extern void log_writeParInt32(char const * const fileName, int line, uint8_t logLevel, char const * const message, int32_t par)
{
    if (0 != (log_logLevel & logLevel))
    {
        log_printf("%s (%d) - %s: %s %d\n", fileName, line, log_getLogLevelStr(logLevel), message, par);
    }
    
    return;
}

/**
 * This function behave like the standard printf, but it includes always the current
 * date and time in front.
 *
 * @param[in]   format  Format
 * @param[in]   ...     Variable number of parameters
 */
extern void log_printf(char const * const format, ...)
{
    va_list     args;
    time_t      rawtime;
    struct tm * timeInfo;
    
    time(&rawtime);
    timeInfo = localtime(&rawtime);
    
    printf("%04u-%02u-%02u %02u:%02u:%02u ", 
        timeInfo->tm_year + 1900,
        timeInfo->tm_mon,
        timeInfo->tm_mday,
        timeInfo->tm_hour,
        timeInfo->tm_min,
        timeInfo->tm_sec);
    
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    
    return;
}

/*******************************************************************************
	LOCAL FUNCTIONS
*******************************************************************************/

/**
 * Get a user friendly string for a given log level.
 *
 * @param[in]   level   Log level
 * @return User friendly description of log level
 */
static char const * const   log_getLogLevelStr(LOG_LEVEL level)
{
    switch(level)
    {
    case LOG_LEVEL_INFO:
        return "Info";
        
    case LOG_LEVEL_DEBUG:
        return "Debug";
        
    case LOG_LEVEL_WARNING:
        return "Warning";
        
    case LOG_LEVEL_ERROR:
        return "Error";
        
    case LOG_LEVEL_FATAL:
        return "Fatal";
        
    default:
        break;
    }
    
    return "Unknown";
}
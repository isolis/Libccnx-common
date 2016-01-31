/*
 * Copyright (c) 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Patent rights are not granted under this agreement. Patent rights are
 *       available under FRAND terms.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX or PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * @file ccnx_Json.h
 * @ingroup Utility
 * @brief An implementation of JSON object.
 *
 * Portions Copyright 2009, Dave Gamble
 *
 * NOTE: This interface will be changing.
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */
#ifndef libccnx_ccnx_Json_h
#define libccnx_ccnx_Json_h

// Yes, this is an oddity of Linux/gcc/std=c99
#define __need_timespec

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

struct ccnx_json;
/**
 * @typedef CCNxJson
 * @brief Json
 */

typedef struct ccnx_json CCNxJson;


typedef enum ccnx_json_type {
    CCNX_JSON_OBJECT,
    CCNX_JSON_ARRAY,
    CCNX_JSON_STRING,
    CCNX_JSON_NULL,
    CCNX_JSON_NUMBER
} CCNxJsonType;


/**
 * Print a human readable representation of the given instance.
 *
 * @param [in] json A pointer to the instance to display.
 * @param [in] indentation The level of indentation to use to pretty-print the output.
 */
void ccnxJson_Display(const CCNxJson *json, int indentation);

/**
 * Retrieves the key, verifying it is of type `CCNX_JSON_STRING`.
 *
 *   Will assert if key not found or is not of type `CCNX_JSON_STRING`.
 *
 * @param [in] container_json must not be null.
 * @param [in] key A pointer to the key = must not be null.
 * @return The inner JSON object containing a string.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
CCNxJson *ccnxJson_GetJsonString(CCNxJson *container_json, const char *key);

/**
 * Verifies the key is type `CCNX_JSON_STRING` and returns the value.
 *
 *   Will assert if key not found or is not of type `CCNX_JSON_STRING`.
 *
 * @param [in] container_json must not be null.
 * @param [in] key A pointer to the key - must not be null.
 * @return The value of the `key`, do not free it.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
const char *ccnxJson_GetAsString(CCNxJson *container_json, const char *key);

/**
 * Retrieves the key, verifying it is of type CCNX_JSON_NUMBER
 *
 *   Will assert if key not found or is not of type CCNX_JSON_NUMBER
 *
 * @param [in] container_json must not be null
 * @param [in] key must not be null
 * @return The inner JSON object containing a number.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
CCNxJson *getJsonNumber(CCNxJson *container_json, const char *key);

/**
 * Verifies the key is type `CCNX_JSON_NUMBER` and returns the value.
 *
 *   Will assert if key not found or is not of type `CCNX_JSON_NUMBER`.
 *
 * @param [in] container_json must not be null.
 * @param [in] key must not be null.
 * @return The value of `key` as a number.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
int ccnxJson_GetAsNumber(CCNxJson *container_json, const char *key);

/**
 * Determine if two `CCNxJson` instances are equal.
 *
 * Two `CCNxJson` instances are equal if, and only if, their JSON strings are equal.
 *
 * The following equivalence relations on non-null `ccnxJson` instances are maintained:
 *
 *  * It is reflexive: for any non-null reference value x, `ccnxJson_Equals(x, x)`
 *      must return true.
 *
 *  * It is symmetric: for any non-null reference values x and y,
 *    `ccnxJson_Equals(x, y)` must return true if and only if
 *        `ccnxJson_Equals(y, x)` returns true.
 *
 *  * It is transitive: for any non-null reference values x, y, and z, if
 *        `ccnxJson_Equals(x, y)` returns true and
 *        `ccnxJson_Equals(y, z)` returns true,
 *        then  `ccnxJson_Equals(x, z)` must return true.
 *
 *  * It is consistent: for any non-null reference values x and y, multiple
 *      invocations of `ccnxJson_Equals(x, y)` consistently return true or
 *      consistently return false.
 *
 *  * For any non-null reference value x, `ccnxJson_Equals(x, NULL)` must
 *      return false.
 *
 * @param a A pointer to a `CCNxJson` instance.
 * @param b A pointer to a `CCNxJson` instance.
 * @return true if the two `CCNxJson` instances are equal.
 *
 * Example:
 * @code
 * {
 *    CCNxJson *a = ccnxJson_Create();
 *    CCNxJson *b = ccnxJson_Create();
 *
 *    if (ccnxJson_Equals(a, b)) {
 *        // true
 *    } else {
 *        // false
 *    }
 * }
 * @endcode
 */
bool ccnxJson_Equals(const CCNxJson *a, const CCNxJson *b);

/**
 * Duplicate an instance of `CCNxJson`.
 *
 * @param [in] original A pointer to the original `CCNxJson` instance to duplicate.
 *
 * @return A pointer to a new instance of a `CCNxJson`
 *
 * Example:
 * @code
 * {
 *     <#example#>
 * }
 * @endcode
 */
CCNxJson *ccnxJson_Duplicate(const CCNxJson *original);

/**
 * Create a new `CCNxJson` from text.
 *
 * @param [in] text The text to create the `CCNxJson` from.
 *
 * @return A pointer to a new instance of `CCNxJson`.
 *
 * Example:
 * @code
 * {
 *     <#example#>
 * }
 * @endcode
 */
CCNxJson *ccnxJson_CreateFromText(char *text);
/**
 * Create a new `CCNxJson` object.
 *
 * @return A pointer to a new `CCNxJson` object.
 *
 * Example:
 * @code
 * {
 *     <#example#>
 * }
 * @endcode
 */
CCNxJson *ccnxJson_CreateObject(void);
/**
 * Create an Array kind of `CCNxJson`.
 *
 * @return A pointer to a new `CCNxJson` object.
 *
 * Example:
 * @code
 * {
 *     <#example#>
 * }
 * @endcode
 */
CCNxJson *ccnxJson_CreateArray(void);
/**
 * Create a new `CCNxJson` from a String.
 *
 * @param [in] string The String to use to create the `CCNxJson`.
 *
 * @return A pointer to a new `CCNxJson` object.
 *
 * Example:
 * @code
 * {
 *     <#example#>
 * }
 * @endcode
 */
CCNxJson *ccnxJson_CreateString(const char *string);
/**
 * Create a new `CCNxJson` object from a Number.
 *
 * @param [in] value The number from which to create the `CCNxJson`.
 *
 * @return A pointer to a new `CCNxJson` object.
 *
 * Example:
 * @code
 * {
 *     <#example#>
 * }
 * @endcode
 */
CCNxJson *ccnxJson_CreateNumber(double value);

/**
 * Add an item to an existing `CCNxJson` object.
 *
 * @param [in,out] json An existing `CCNxJson` object.
 * @param [in] key A pointer to the key to add.
 * @param [in] value A pointer to the value to add.
 *
 *
 * Example:
 * @code
 * {
 *     <#example#>
 * }
 * @endcode
 */
void ccnxJson_AddItemToObject(CCNxJson *json, const char *key, CCNxJson *value);
/**
 * Append an item to an existing `CCNxJson` array object.
 *
 * @param [in,out] array An existing `CCNxJson` object.
 * @param [in] item A pointer to the item to append.
 *
 *
 * Example:
 * @code
 * {
 *     <#example#>
 * }
 * @endcode
 */
void         ccnxJson_AppendItemToArray(CCNxJson *array, CCNxJson *item);

/**
 * Destroy a CCNxJson instance. Any allocated memory is deallocated.
 *
 * @param [in,out] jsonPtr A pointer to a pointer to the `CCNxJson` instance to be destroyed.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
void         ccnxJson_Destroy(CCNxJson **jsonPtr);

extern char *ccnxJson_ToString(const CCNxJson *json);

extern char         *ccnxJson_ToStringUnformatted(const CCNxJson *ccnx_json);
/**
 * Get the String of the key in a `CCNxJson` instance.
 *
 * @param [in] ccnx_json A pointer to a `CCNxJson` instance.
 *
 * @return A string form of the Key.
 *
 * Example:
 * @code
 * {
 *     <#example#>
 * }
 * @endcode
 */
const char          *ccnxJson_GetKeyString(CCNxJson *ccnx_json);

extern CCNxJsonType  ccnxJson_GetItemType(CCNxJson *json);
extern const char   *ccnxJson_GetItemString(CCNxJson *json);
extern double        ccnxJson_GetItemDouble(CCNxJson *json);
extern int           ccnxJson_GetItemInteger(CCNxJson *json);

extern CCNxJson     *ccnxJson_GetObject(const CCNxJson *json, const char *key);

extern size_t        ccnxJson_GetArrayLength(CCNxJson *json);
extern CCNxJson     *ccnxJson_GetArrayElement(CCNxJson *json, size_t element);

extern uint64_t      ccnxJson_Hash(const CCNxJson *json);

extern int           ccnxJson_WriteToFile(CCNxJson *json, FILE *fh);

extern CCNxJson     *ccnxJson_GetChild(CCNxJson *json);

/**
 * Create a new `CCNxJson` instance from a timeval.
 *
 * @param [in] timeval A pointer to a timeval.
 * @return A pointer to a new instance of a `CCNxJson` instance.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
CCNxJson *CCNxJSON_FromTimeval(const struct timeval *timeval);
/**
 * Create a new `CCNxJson` instance from a timespec.
 *
 * @param [in] timespec A pointer to a timespec.
 * @return A pointer to a new instance of a `CCNxJson` instance.
 *
 * Example:
 * @code
 * {
 *     <#example#>
 * }
 * @endcode
 */
CCNxJson *CCNxJSON_FromTimespec(const struct timespec *timespec);

/**
 * Convert an existing `CCNxJson` instance  to a timeval.
 *
 * @param [in] jsonTimeval A pointer to an existing `CCNxJson` instance.
 * @param [out] timeval A pointer to a timeval struct to accept the conversion.
 *
 * @return `true` if the conversion was succesful.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
bool CCNxJSON_ToTimeval(const CCNxJson *jsonTimeval, struct timeval *timeval);

bool CCNxJSON_ToTimespec(const CCNxJson *jsonTimeval, struct timespec *timespec);

#define ccnxJson_AddStringToObject(object, key, string) \
    ccnxJson_AddItemToObject(object, key, ccnxJson_CreateString(string))

#define ccnxJson_AddIntegerToObject(object, key, value) \
    ccnxJson_AddItemToObject(object, key, ccnxJson_CreateNumber(value))
#define ccnxJson_AppendStringToArray(array, string) \
    ccnxJson_AppendItemToArray(array, ccnxJson_CreateString(string))
#define ccnxJson_AppendIntegerToArray(array, number) \
    ccnxJson_AppendItemToArray(array, ccnxJson_CreateNumber(number))
#endif // libccnx_ccnx_Json_h

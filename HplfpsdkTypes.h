#ifndef _HPLFPSDK__TYPES__H_
#define _HPLFPSDK__TYPES__H_

#include <stdint.h>

#ifdef _WIN32
    #ifdef __GNUC__
        #define HPLFPSDK_STDCALL
    #else
        #define HPLFPSDK_STDCALL __stdcall
    #endif
#elif defined(__ELF__) && defined(__GNUC__) || defined(MACOSX)
    #define HPLFPSDK_STDCALL
#else
    #error "Unsupported platform"
#endif

namespace HPLFPSDK
{
    class Types
    {
    public:
        enum Result: uint32_t
        {
            RESULT_OK                                         = 0, /**< There was no error and the output is properly filled in */
            RESULT_ERROR_INVALID_PARAMETER                    = 1, /**< One of the provided parameters is invalid */
            RESULT_ERROR_UNSUPPORTED_RASTER_FMT               = 2, /**< The specified raster format is not supported */
            RESULT_ERROR_INVALID_USAGE_SEQUENCE               = 3, /**< Other operations must be performed before this one  */
            RESULT_ERROR_COMPRESSOR                           = 4, /**< There was some error in the data compressor */
            RESULT_ERROR_MEMORY                               = 5, /**< Memory could not be allocated */
            RESULT_ERROR_INTERNAL                             = 6, /**< Internal error */
            RESULT_ERROR_MEDIUM_KEY_NOT_VALID                 = 7, /**< The provided medium key is not valid */
            RESULT_ERROR_PROFILE_NOT_EXIST                    = 8, /**< Profile ID not exist on the printer */
            RESULT_ERROR_MEDIUM_CANNOT_BE_DELETED             = 9, /**< Medium cannot be deleted */
            RESULT_ERROR_MEDIUM_NOT_EXIST                     = 10, /**< Medium ID not present on the printer */
            RESULT_ERROR_MEDIUM_ALREADY_EXIST                 = 11, /**< Medium ID already present on the printer */
            RESULT_ERROR_NO_ROOM_FOR_MORE_MEDIA               = 12, /**< There is no space available to store more media configurations */
            RESULT_ERROR_MEDIUM_CANNOT_BE_CLONED              = 13, /**< The selected media ID cannot be cloned */
            RESULT_ERROR_PROFILE_CANNOT_BE_DELETED            = 14, /**< The selected profile ID cannot be deleted */
            RESULT_ERROR_MEDIUM_MISSING_NAME                  = 15, /**< The provided medium name cannot be found on the printer */
            RESULT_ERROR_INCOMPLETE_COND_SPEC                 = 16, /**< The media is incomplete */
            RESULT_ERROR_INCOMPLETE_PRINTMODE_SPEC            = 17, /**< The print mode is incomplete */
            RESULT_ERROR_SPECIFIED_FILE_DOES_NOT_EXIST        = 18, /**< There is any missing file on the printer */
            RESULT_ERROR_UPDATING_SETTINGS                    = 19, /**< The printer returned a non-specific error when updating settings. */
            RESULT_ERROR_MEDIUM_IS_REQUIRED                   = 20, /**< The medium has not been specified for the current request. */
            RESULT_ERROR_TOO_MANY_PROPERTIES                  = 21, /**< Too many properties were provided for this medium id. */
            RESULT_ERROR_SUPPORTED_PM_FILE_NOT_FOUND          = 22, /**< The printer could not find the configuration file for this printer mode. */
            RESULT_ERROR_MEDIUM_CANNOT_BE_MODIFIED            = 23, /**< It is not allowed to modify this medium. */
            RESULT_ERROR_NO_ROOM_FOR_MORE_MODES               = 24, /**< The maximum Paper mode supported for single media is 6. So if user tries to create more than 6 paper modes for a given media, this error code will be returned. */
            RESULT_ERROR_MODE_DOESNT_EXIST                    = 25, /**< Paper mode value is invalid. */
            RESULT_ERROR_MODE_ALREADY_EXISTS                  = 26, /**< If the paper mode already exist this error code will be returned. */
            RESULT_ERROR_MODE_CANNOT_BE_DELETED               = 27, /**< This paper mode id cannot be deleted because has not been created by an user. */
            RESULT_ERROR_CATEGORY_DOESNT_EXIST                = 28, /**< The media category does not exist */
            RESULT_ERROR_PARAM_OUT_OF_RANGE                   = 29, /**< A parameter is out of the valid range values */
            RESULT_ERROR_MEDIUM_INSTALLING                    = 30, /**< The printer is installing a new media. */
            RESULT_ERROR_MEDIUM_PROPERTIES_NOT_FOUND          = 31, /**< The paper modes could not be found. */
            RESULT_ERROR_PAPER_MODE_NOT_DEFINED               = 32, /**< The paperMode was not defined when calling getMechanicalProperties. */
            RESULT_ERROR_MEDIUM_KEY_NOT_DEFINED               = 33, /**< The mediaKey was not defined when calling getMechanicalProperties. */
            RESULT_ERROR_XML_INPUT_DATA_TOO_BIG               = 34, /**< The provided char array in the interface is larger than the maximum integer size supported by the platform. */
            RESULT_ERROR_XML_INPUT_DATA_MALFORMED             = 35, /**< The provided char array in the interface could not be parsed, it not complies with the XML format. */
            RESULT_ERROR_XML_INPUT_DATA_EMPTY                 = 36, /**< The provided char array in the interface is empty and has not root node. */
            RESULT_ERROR_XML_INPUT_DATA_INVALID               = 37, /**< The provided char array in the interface does not have a valid root node. */

            RESULT_ERROR_CALIBRATION_TYPE_EMPTY               = 38, /**< Currently not supported */
            RESULT_ERROR_CALIBRATION_TYPE_INVALID             = 39, /**< Currently not supported */
            RESULT_ERROR_EMPTY_RESPONSE                       = 40, /**< The printer response is empty, so it cannot be properly parsed. This may indicate a printer disconnected or malfunction. */
            RESULT_ERROR_NO_MEDIUM_LOADED                     = 41, /**< The medium is not loaded to perform form feed and cut */
            RESULT_ERROR_ELEMENT_NOT_FOUND                    = 42, /**< The ID cannot be found */
            RESULT_ERROR_INVALID_MEDIUM                       = 43, /**< Medium ID wrong format */
            RESULT_ERROR_MEDIUM_MISMATCH                      = 44, /**< Medium ID cannot be found */
            RESULT_ERROR_NO_EFFECT                            = 45, /**< The Job is already in pause, so the current command has no effect */
            RESULT_ERROR_PRINTER_BUSY                         = 46, /**< The current printer status is busy, so the operation cannot be performed */
            RESULT_ERROR_MEDIUM_NOT_DEFINED                   = 47, /**< Medium ID not defined */
            RESULT_ERROR_MEDIUM_CANNOT_BE_RESET               = 48, /**< Medium ID cannot be reset because has not been created by an user. */
            RESULT_ERROR_ALREADY_IN_FACTORY_SETTINGS          = 49, /**< The printer is still using factory settings */
            RESULT_ERROR_MANUAL_DELETION_NEEDED               = 50, /**< Medium ID cannot be modified using the SDK. */
            RESULT_ERROR_MEDIUM_IDENTIFIER_PROPERTIES_NOT_SET = 51, /**< Settings for this medium ID has not been set */

            RESULT_ERROR_INVALID_RESPONSE                     = 52, /**< The response from the printer is not correct */
            RESULT_ERROR_CONNECTION                           = 53, /**< There is no response from the printer */
            RESULT_ERROR                                      = 54, /**< Non defined error in the API response */
            RESULT_ERROR_DEVICE_ALREADY_EXISTS                = 55, /**< The IP is aready in use for this SDK instance */
            RESULT_ERROR_FILE_NOT_FOUND                       = 56, /**< Data file for the printer model cannot be found */
            RESULT_NOT_SUPPORTED                              = 57, /**< This operation is not supported for the configured printer model */
            RESULT_ERROR_NOT_NETWORK_AVAILABLE                = 58, /**< Operating System does not return a correct socket */
            RESULT_WARNING_DEVICE_NOT_CONNECTED               = 59, /**< Device is offline or cannot be reached */
            RESULT_ERROR_SETTING_MANDATORY_NOT_SET            = 60, /**< There is any mandatory setting that has not been setted for the current job */
            RESULT_ERROR_IN_MARGINS_SETTINGS                  = 61, /**< Margin setting not valid for this printer */
            RESULT_ERROR_PRINTER_MODEL_UNKNOWN                = 62, /**< There is no data file and support for this printer model */
            RESULT_ERROR_MEDIA_SOURCE_NOT_SUPPORTED           = 63, /**< The given media ID is not valid for this printer model */
            RESULT_ERROR_FOLDER_SETTINGS                      = 64, /**< Settings of the folder are not ok, */ // TODO \link link_to_manual_page Follow this steps\endlink */
            RESULT_ERROR_LIBRARY_NOT_INITIALIZED              = 65, /**< The SDK Library needs to be initialized before invoking this API */
            RESULT_PAGE_SETTINGS_NULL                         = 66, /**< Page Settings are NULL> */

            RESULT_ERROR_CHART_DOES_NOT_FIT_AREA_TOO_SMALL               = 67, /**< Color chart does not fit in the layout, the guessing alignment algorithm could not find space to fit any patches */
            RESULT_ERROR_CHART_DOES_NOT_FIT_NO_SPACE_FOR_ALIGNMENT_MARKS = 68, /**< Color chart does not fit in the layout, there is no space for the alignment marks */
            RESULT_ERROR_CHART_DOES_NOT_FIT_NO_SPACE_FOR_PATCHES         = 69, /**< Color chart does not fit in the layout, the guessing algorithm could not find space to fit any patches */
            RESULT_ERROR_CHART_DOES_NOT_FIT_NO_SPACE_FOR_COLUMNS         = 70, /**< Color chart does not fit in the layout, could not find space to fit the specified number of columns */
            RESULT_ERROR_CHART_DOES_NOT_FIT_NO_SPACE_FOR_ROWS            = 71, /**< Color chart does not fit in the layout, there is no space to fit the number of rows required */

            RESULT_ERROR_CHART_INVALID_GEOMETRY                = 72, /**< Invalid canvas or cells layout. The width and height must have valid positive values */
            RESULT_ERROR_CHART_OVERLAPPED_REGIONS              = 73, /**< Layout regions overlap */
            RESULT_ERROR_CHART_INVALID_ALIGNMENT_MARK          = 74, /**< The alignment mark size is invalid */
            RESULT_ERROR_CHART_OVERLAPPED_LEFT_ALIGNMENT_MARK  = 75, /**< The left alignment mark overlaps the grid */
            RESULT_ERROR_CHART_OVERLAPPED_RIGHT_ALIGNMENT_MARK = 76, /**< The right alignment mark overlaps the grid */
            RESULT_ERROR_CHART_INCOMPATIBLE_ALIGNMENT_MARK     = 77, /**< Hexagonal layouts do not allow only left or only right alignment marks */
            RESULT_ERROR_CHART_LAYOUT_OVERFLOW                 = 78, /**< The hexagonal grid overflows the layout */
            RESULT_ERROR_CHART_UNKNOWN_COLOR_SPACE             = 79, /**< Could not determine the color space defined */
            RESULT_ERROR_CHART_INCOMPATIBLE_COLOR_DEFINITION   = 80, /**< Incompatible colors definition and color space specification */

            RESULT_ERROR_TIMEOUT                               = 81, /**< The operation failed = 62, because of a timeout */
            RESULT_ERROR_NOT_YET_INITIALIZED                   = 82, /**< The operation could not be completed because the initialization process is not yet finished */
            RESULT_OFFLINE_OPERATION                           = 83, /**< The operation does not send data to the printer */

            RESULT_ERROR_PARAM_SIZE_OUT_OF_RANGE               = 84, /**< A character string parameter has a size that not complies with the minimum or the maximum size */
            RESULT_ERROR_TOO_MANY_ELEMENTS                     = 85, /**< The element count limit has been reached */
            RESULT_ERROR_UNAUTHORIZED                          = 86, /**< The operation is waiting for authorization */
            RESULT_ERROR_SERVICE_UNAVAILABLE                   = 87, /**< The operation is not available now. Retry later. */
            RESULT_ERROR_SIDE_B_NOT_SUPPORTED                  = 88, /**< The selected print mode or paper mode does not have side B settings */
        };

        enum RasterLibState: uint32_t
        {
            RASTER_LIB_STATE_WAITING_FOR_JOB_BEGIN          = 0, /**< Idle state. There is no job being processed and the system is ready */
            RASTER_LIB_STATE_WAITING_FOR_PAGE_BEGIN         = 1, /**< A Job has been received, settings have been checked and Job Begin header has been created without errors */
            RASTER_LIB_STATE_WAITING_FOR_FIRST_RASTER_START = 2, /**< Page settings have been validated - it is time to begin data rasterizing */
            RASTER_LIB_STATE_WAITING_FOR_RASTER_START       = 3, /**< Raster processing after first raster data block has been rasterized */
            RASTER_LIB_STATE_WAITING_FOR_RASTER             = 4, /**< Raster data is allocated in memory handler */
            RASTER_LIB_STATE_WAITING_FOR_RASTER_END         = 5, /**< Raster data chunk has been sent - time to end raster */
            RASTER_LIB_STATE_WAITING_FOR_PAGE_END           = 6, /**< After processing all the current page Raster data */
            RASTER_LIB_STATE_WAITING_FOR_JOB_END            = 7, /**< An End Page has been reached */
            RASTER_LIB_STATE_WAITING_FOR_DELETE             = 8, /**< After memory has been released, inside Job End phase */
            RASTER_LIB_STATE_ERROR                          = 0xffffffff /**< An error occurred and the job is in an inconsistent state */
        };

        enum RasterFormat: uint32_t
        {
            INVALID   = 0, ///< not a valid format.
            xRGB      = 1, ///< 32-bit chunky xRGB
            xBGR      = 2, ///< 32-bit chunky xBGR
            RGBx      = 3, ///< 32-bit chunky RGBx
            KCMY      = 4, ///< 32-bit chunky KCMY
            KYMC      = 5, ///< 32-bit chunky KYMC
            CMYK      = 6, ///< 32-bit chunky CMYK
            RGB       = 7, ///< 24-bit chunky RGB
            PLANAR    = 8, ///< 8 -bit planar multiformat
            PLANAR_HT = 9, ///< planar halftone
            BGR       = 10,///< 32-bit chunky BGR
            BGRx      = 11 ///< 32-bit chunky BGRx
        };

        enum CalibrationType: uint32_t
        {
            CALIBRATION_COLOR     = 0, /**< Select the color calibration type for the calibration task */
            CALIBRATION_ALIGNMENT = 1, /**< Select the printhead alignment calibration type for the calibration task */
            CALIBRATION_ADVANCE   = 2  /**< Select the paper advance calibration type for the calibration functionality */
        };

        enum CalibrationDestinationType : uint32_t
        {
            CALIBRATION_DESTINATION_BASKET  = 0, /**< Select the basket output when doing a calibration job */
            CALIBRATION_DESTINATION_STACKER = 1  /**< Select the stacker output when doing a calibration job */
        };

        enum LogLevel : uint32_t
        {
            LOG_LEVEL_ALL     = 0, /**< Every log message will be on the log file */
            LOG_LEVEL_VERBOSE = 1, /**< Developer messages and the rest of the log level messages will be on the log file */
            LOG_LEVEL_INFO    = 2, /**< From Error to Info log levels will be on the log file */
            LOG_LEVEL_WARNING = 3, /**< Errors and warnings messages will be on the log file */
            LOG_LEVEL_ERROR   = 4, /**< Only Error messages will be on the log file */
            LOG_LEVEL_NONE    = 5  /**< None log message will be on the log file but those referred to the log level changes. */
        };

        enum LogConfigFlags : uint32_t
        {
            LOG_CONFIG_FILE_FLAG_UNAVAILABLE = 0,    /**< The logger configuration file is not available, setting the defaul values on log level and log file path */
            LOG_CONFIG_FILE_FLAG_AVAILABLE = 1 /**< The logger configuration file is available, overriding the log level and log file path */
        };

        enum LengthUnits : int32_t
        {
            LENGTH_UNIT_NONE      = 0,
            LENGTH_UNIT_EMU       = 1,
            LENGTH_UNIT_100THMM   = 360,      /**< x1/100 mm */
            LENGTH_UNIT_10THMM    = 3600,     /**< x1/10 mm */
            LENGTH_UNIT_MM        = 36000,
            LENGTH_UNIT_CM        = 360000,   /**< x10 mm */
            LENGTH_UNIT_M         = 36000000, /**< x1000 mm */
            LENGTH_UNIT_300THINCH = 3048,     /**< x1/300 inch */
            LENGTH_UNIT_100THINCH = 9144,     /**< x1/100 inch */
            LENGTH_UNIT_INCH      = 914400,   /**< x25.4 mm */
            LENGTH_UNIT_FEET      = 10972800, /**< x12 inch */
            LENGTH_UNIT_POINT     = 12700,    /**< x1/72 inch */
            LENGTH_UNIT_DECIPOINT = 1270,     /**< x1/10 point */
            LENGTH_UNIT_PICA      = 152400,   /**< x12 point */
            LENGTH_UNIT_TWIP      = 635       /**< x1/20 point */
        };

        enum SolChartFlags : uint32_t
        {
            SOL_CHART_FLAGS_ALIGNMENT_NONE     = 0x0000, 
            SOL_CHART_FLAGS_ALIGNMENT_LEFT     = 0x0001, 
            SOL_CHART_FLAGS_ALIGNMENT_RIGHT    = 0x0002, 
            SOL_CHART_FLAGS_ALIGNMENT_BOTH     = 0x0003, 
            SOL_CHART_FLAGS_ALIGNMENT_MASK     = 0x0003, 
            SOL_CHART_FLAGS__RESERVED1__       = 0x000C, 
            SOL_CHART_FLAGS_LAYOUT_RECTANGULAR = 0x0000, 
            SOL_CHART_FLAGS_LAYOUT_HEXAGONAL   = 0x0010, 
            SOL_CHART_FLAGS_LAYOUT_MASK        = 0x0010, 
            SOL_CHART_FLAGS__RESERVED2__       = 0x00E0, 
            SOL_CHART_FLAGS_WARMUP             = 0x0100, 
            SOL_CHART_FLAGS_PREHEAT            = 0x0200, 
            SOL_CHART_FLAGS_HEADER             = 0x0400, 
            SOL_CHART_FLAGS_METADATA           = 0x0800, /**< Currently not supported */
            SOL_CHART_FLAGS_CONTRAST           = 0x1000, 
            SOL_CHART_FLAGS__RESERVED3__       = 0xE000, 
            SOL_CHART_FLAGS_OPTIMIZATION_MASK  = 0xFFFF0000   
        };

        enum SolChartOptimizationFlags : uint32_t
        {
            SOL_CHART_RENDER_FULL_PAGE       = 0x00000000, 
            SOL_CHART_RENDER_PRINTABLE       = 0x00010000, 
            SOL_CHART_RENDER_INKED_AREA      = 0x00020000, 
            SOL_CHART_RENDER_SMART_AREA      = 0x00030000, 
            SOL_CHART_RENDER_REGION_MASK     = 0x00030000, 
            SOL_CHART__RESERVED1__           = 0x000C0000, 
            SOL_CHART_GUESS_OPTIMUM_LAYOUT   = 0x00100000, 
            SOL_CHART_GUESS_OPTIMUM_ALIGN    = 0x00200000, 
            SOL_CHART__RESERVED2__           = 0x00C00000, 
            SOL_CHART_MARGINS_NO_MARGINS     = 0x00000000, 
            SOL_CHART_MARGINS_ONLINE         = 0x01000000, 
            SOL_CHART_MARGINS_OFFLINE        = 0x02000000, 
            SOL_CHART_MARGINS_ROLL           = 0x04000000, 
            SOL_CHART_MARGINS_MASK           = 0x07000000, 
            SOL_CHART__RESERVED3__           = 0x08000000, 
            SOL_CHART_ANCHOR_CENTER          = 0x00000000, 
            SOL_CHART_ANCHOR_LEFT            = 0x10000000, 
            SOL_CHART_ANCHOR_TOP             = 0x20000000, 
            SOL_CHART_ANCHOR_RIGHT           = 0x40000000, 
            SOL_CHART_ANCHOR_BOTTOM          = 0x80000000, 
            SOL_CHART_ANCHOR_MASK            = 0xF0000000,
            SOL_CHART_HORIZONTAL_ANCHOR_MASK = 0x50000000,
            SOL_CHART_VERTICAL_ANCHOR_MASK   = 0xA0000000
        };

        enum SolMeasurementType : uint32_t
        {
            SOL_MEASUREMENT_TYPE_ALL      = 0,
            SOL_MEASUREMENT_TYPE_SPECTRAL = 1,
            SOL_MEASUREMENT_TYPE_CIEXYZ   = 2,
            SOL_MEASUREMENT_TYPE_CIELAB   = 3,
            SOL_MEASUREMENT_TYPE_DENSITY  = 4
        };

        enum SolPrinterState : uint32_t
        {
            SOL_STATUS_PRINTER_UNKNOWN = 0xFFFFFFFF,
            SOL_STATUS_PRINTER_READY   = 0,  /**< The printer is ready to accept SOL operations. Media might not be loaded though */
            SOL_STATUS_PRINTER_BUSY    = 1,  /**< The printer is busy doing things not related to SOL operations */
            SOL_STATUS_PRINTER_WORKING = 2   /**< The printer is currently processing a SOL operation */
        };

        enum SolScanStatus : uint32_t
        {
            SOL_STATUS_OPERATION_UNKNOWN       = 0xFFFFFFFF,
            SOL_STATUS_OPERATION_IDLE          = 0,      
            SOL_STATUS_OPERATION_PREPARING     = 1,     
            SOL_STATUS_OPERATION_FINISHING     = 2,     
            SOL_STATUS_OPERATION_PROCESSING    = 3,    
            SOL_STATUS_OPERATION_PRINTING      = 4,      
            SOL_STATUS_OPERATION_DRYING        = 5,        
            SOL_STATUS_OPERATION_CALIBRATING   = 6,   
            SOL_STATUS_OPERATION_SCANNING      = 7,      
            SOL_STATUS_OPERATION_CANCELLING    = 8,    
            SOL_STATUS_OPERATION_SUCCEEDED     = 9,     
            SOL_STATUS_OPERATION_FAILED        = 10,        
            SOL_STATUS_OPERATION_CANCELLED     = 11,     
            SOL_STATUS_OPERATION_SCAN_ERROR    = 12,    
            SOL_STATUS_OPERATION_SKEW_ERROR    = 13,    
            SOL_STATUS_OPERATION_TIME_OUT      = 14,      
            SOL_STATUS_OPERATION_WAITING_QUEUE = 15  
        };

        enum SolProgressType : uint32_t
        {
            SOL_PROGRESS_UNKNOWN           = 0xFFFFFFFF,
            SOL_PROGRESS_NONE              = 0,  
            SOL_PROGRESS_PERCENT           = 1,   
            SOL_PROGRESS_SECONDS_REMAINING = 2   
        };

        enum JobLanguage : uint32_t
        {
            JOB_LANGUAGE_UNKNOWN = 0,
            JOB_LANGUAGE_PCL3GUI = 1,
            JOB_LANGUAGE_RSTREAM = 2
        };

        enum PrinterFamily : uint32_t
        {
            PRINTER_FAMILY_UNKNOWN   = 0,
            PRINTER_FAMILY_DESIGNJET = 1, // HP DesignJet series
            PRINTER_FAMILY_LATEX     = 2  // HP Latex series
        };

#include "types.h"

    }; //class Types

} //HPLFPSDK

#endif // _HPLFPSDK__TYPES__H_

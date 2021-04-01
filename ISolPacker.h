#ifndef SDK_SOL_PACKER_H
#define SDK_SOL_PACKER_H

//////////////////////////////////////////////////////////////////////////////
/**
* @file   ISolPacker.h
* @author Jesús Lucas (jesus.lucas.natal@hp.com)
* @date   Wed Jul 12 12:54:59 CEST 2017
* @brief  C++ Special Operations Language Packer interface.
*
* @par &copy; Copyright Hewlett-Packard Company, 2000-2012.
* All rights reserved. Copying or other reproduction of this program except
* for archival purposes is prohibited without written consent of
* Hewlett-Packard Company.
*/
//////////////////////////////////////////////////////////////////////////////

#include "HplfpsdkTypes.h"
#include "IJobPacker.h"

typedef struct _HPLFPSDK_GUID
{
    uint32_t    time_low;
    uint16_t    time_mid;
    uint16_t    time_hi_and_version;
    uint8_t     clock_seq_hi_and_reserved;
    uint8_t     clock_seq_low;
    uint8_t     node[6];
} HPLFPSDK_GUID;
#define HPGUID HPLFPSDK_GUID

namespace HPLFPSDK
{
    /**
    * Function pointer to the event callback
    * @param[in] cookie 
    * @param[in] scanline
    * @return result of the operation.
    *- Types::RESULT_OK if the operation was successful.
    */
    typedef Types::Result(*onRasterRowCallback)(uintptr_t cookie, const uint8_t *scanline);

    /**
    * Function pointer to the event callback
    * @param[in] cookie
    * @param[in] request
    * @param[in] response
    * @return result of the operation.
    *- Types::RESULT_OK if the operation was successful.
    */
    typedef Types::Result(*onAsyncQueryCallback)(uintptr_t cookie, const char *request, const char **response);

    /**
    * @brief The ISolPacker class interface allows the client to interact with the spectophotometer, starts a job using the spectophotometer functionality.
    * NOTE: Not supported yet.
    */
    class ISolPacker : public IJobPacker
    {
    public:
        /**
        * @brief The ISolMemoryHandler interface can be implemented by the library client.\n
        * This mechanism will be used by the HPFLPSDK to pass raster data to the client.\n
        * and to read the printer responses to the Sol commands\n
        * The memory handler must not be deleted until job that uses it is finished.\n
        */
        class ISolMemoryHandler : public IMemoryHandler
        {
        public:
            /**
            * @brief readData reads data from the printer. \n
            * The memory is allocated by the HPLFPSDK library. The data should be copied to
            * data buffer up to the specified size established by the numBytes parameter.\n
            * Then the numBytes parameter should be updated to indicate the number of bytes read.\n
            * NOTE: Before performing the actual read, it is mandatory to flush any data to the
            * printer. When the HPLFPSDK calls the readData callback it is because a command 
            * was issued in the previous acquireBuffer and releaseBuffer calls that should create
            * a printer response.
            * @param[out] data array of bytes of the read data.
            * @param[in/out] numBytes as an input parameter is the size of the data buffer.\n
            * As an output parameter is the number of bytes read.
            * @param[in] timeout maximum timeout in milliseconds to wait for a response.
            * @return
            * - Types::RESULT_OK if the operation was successful
            * - Types::RESULT_OFFLINE_OPERATION if the job is not being sent to the printer.\n
            *   This will suppose that every SOL command sent is successful, but it will not be\n
            *   able to obtain scan results.
            * - Types::RESULT_ERROR_TIMEOUT if the operation timed out
            * - Types::RESULT_ERROR if the operation failed for any other reason
            */
            virtual Types::Result readData(uint8_t **data, size_t *numBytes, uint32_t timeout) = 0;
        };

        /**
        * @brief newJob starts a raster job
        * @details A raster job is a formatted block of data obtained compressing an image with a compression method compatible with the printer
        * @param[in] settings job configuration parameters
        * @param[in] mhdl memory buffer to contain job.
        * If NULL then the SDK creates a memory handler and will send the data to the printer.
        * In case the SDK is using this feature with other JobPacker then a RESULT_ERROR_CONNECTION will be return.
        * @param[in] transmissionStatusCallback function pointer for the transmission callback. mhdl shall be null so the SDK can call this function.
        * @param[in] userData pointer to a client memory that will be return each time the JobPacker object calls the transmissionStatusCallback.
        * @return result of the operation
        *- Types::RESULT_OK;
        *- Types::RESULT_ERROR_INVALID_PARAMETER;
        *- Types::RESULT_ERROR_UNSUPPORTED_RASTER_FMT;
        *- Types::RESULT_ERROR_INVALID_USAGE_SEQUENCE;
        *- Types::RESULT_ERROR_COMPRESSOR;
        *- Types::RESULT_ERROR_MEMORY;
        *- Types::RESULT_ERROR_INTERNAL;
        *- Types::RESULT_ERROR_CONNECTION;
        *- Types::RESULT_ERROR;
        */
        virtual Types::Result newJob(IJobSettings* settings, ISolPacker::ISolMemoryHandler * mhdl, transmissionStatusCallback callback, void *userData) = 0;
        Types::Result newJob(IJobSettings* settings, IMemoryHandler * mhdl, transmissionStatusCallback callback, void *userData)
        {
            // To avoid unused parameter warnings
            (void)settings;
            (void)mhdl;
            (void)callback;
            (void)userData;

            return Types::Result::RESULT_NOT_SUPPORTED; 
        };

        /**
        * @brief Initializes a color chart using the restrictions given by the printer device.
        * @param[in] chartConstraints XML that specifies the page size, flags, resolution, number of patches and number of columns. For roll, leave the page height as zero and the calculated height will be returned.
        * @param[in,out] flags bit mask that controls the grid layout and other chart properties. It is a mix of Types::SolChartFlags and Types::SolChartOptimizationFlags. Depending on the optimization flags, it will be changed on return.
        * @param[out] calculatedPageHeight calculated page height.
        * @param[out] calculatedPageUnits units of the calculated page height.
        * @param[out] rasterWidth raster width in pixels.
        * @param[out] rasterHeight raster height in pixels.
        * @param[out] chartLayout XML data with the color chart geometric parameters.
        * @param[out] chartLayoutLength length of the chart layout data.
        * @param[out] scanLayout XML data with the color chart scan layout parameters.
        * @param[out] scanLayoutLength length of the scan layout data.
        * @return result of the operation.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result initializeColorChart(const char *chartConstraints,
            uint32_t &flags,
            uint32_t &calculatedPageHeight,
            Types::LengthUnits &calculatedPageUnits,
            uint32_t &rasterWidth,
            uint32_t &rasterHeight,
            char **chartLayout,
            size_t &chartLayoutLength,
            char **scanLayout,
            size_t &scanLayoutLength) = 0;

        /**
        * @brief Initializes a color chart using the restrictions given by the printer device.
        * @param[in] layout color chart geometric characterization. It can be user generated or generated by the initializeColorChart function.
        * @param[in] chartDefinition contains the description of the chart and its contents.
        * @param[in] flags bit mask that controls the grid layout and other chart properties.
        * @param[in] callback callback to deliver the renderized raster data.
        * @param[in] userData pointer to user data to be passed to the callbacks. It will not be used or modified by the library.
        * @return result of the operation.
        *- Types::RESULT_OK if the operation is successful
        *- Types::RESULT_ERROR_INVALID_PARAMETER if there are invalid or missing parameters
        *- Types::RESULT_ERROR_CHART_INVALID_GEOMETRY if there are negative sizes for the canvas or the cells
        *- Types::RESULT_ERROR_CHART_OVERLAPPED_REGIONS if the boundary box and the grid are overlapped
        *- Types::RESULT_ERROR_CHART_INVALID_ALIGNMENT_MARK if some of the alignment marks sizes are negative
        *- Types::RESULT_ERROR_CHART_OVERLAPPED_LEFT_ALIGNMENT_MARK if the left alignment mark overlaps the boundary box
        *- Types::RESULT_ERROR_CHART_OVERLAPPED_RIGHT_ALIGNMENT_MARK if the right alignment mark overlaps the boundary box
        *- Types::RESULT_ERROR_CHART_INCOMPATIBLE_ALIGNMENT_MARK The alignment marks are not compatible with the layout
        *- Types::RESULT_ERROR_CHART_LAYOUT_OVERFLOW The grid layout overflows the boundary box
        *- Types::RESULT_ERROR_CHART_INCOMPATIBLE_COLOR_DEFINITION if the color space and color definition does not match
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result renderColorChart(const char *layout,
            const char *chartDefinition,
            uint32_t flags,
            onRasterRowCallback callback,
            onAsyncQueryCallback query,
            void *userData) = 0;

        /**
        * @brief Starts the measurement process of a plot.
        * @param[in] flags bit mask that controls the grid layout and the alignment marks.
        * @param[in] absolute defines the coordinates system as absolute (from the physical medium edges) or relative (to the printable area origin).
        * @param[in] scanLayout XML that defines the area to be scanned
        * @param[in] columns number of patches per row.
        * @param[in] patches total number of patches.
        * @param[in] measurementType requested measurement type.
        * @param[in] stabilization stabilization time, in seconds.
        * @param[in] scansPerPatch number of scans to be done per patch.
        * @return result of the operation.
        *- Types::RESULT_OK if the command is successfully issued
        *- Types::RESULT_ERROR_INVALID_USAGE_SEQUENCE if the command could not be sent to the printer due to incorrect usage sequence
        *- Types::RESULT_ERROR_CONNECTION if the command could not be sent to the printer due to connection errors
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result startMeasurement(uint32_t flags,
            bool absolute,
            const char *scanLayout,
            uint32_t columns,
            uint32_t patches,
            Types::SolMeasurementType measurementType,
            uint32_t stabilization,
            uint32_t scansPerPatch) = 0;

        /**
        * @brief Retrieves the result of a measurement.
        * @param[out] data measurement result in CGATS format.
        * @param[out] length size in bytes of the data parameter.
        * @return result of the operation.
        *- Types::RESULT_OK if the command is successfully issued
        *- Types::RESULT_ERROR_INVALID_USAGE_SEQUENCE if the command could not be sent to the printer due to incorrect usage sequence
        *- Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation
        *- Types::RESULT_ERROR_CONNECTION if the command could not be sent to the printer due to connection errors
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result endMeasurement(char **data,
            size_t &length) = 0;

        /**
        * @brief Retrieves the current status of the process.
        * @param[out] status status of the current sol process.
        * @param[out] state general state of the printer.
        * @param[out] type type of progress.
        * @param[out] progress progress value.
        * @return result of the operation.
        *- Types::RESULT_OK if the command is successfully issued
        *- Types::RESULT_ERROR_INVALID_USAGE_SEQUENCE if the command could not be sent to the printer due to incorrect usage sequence
        *- Types::RESULT_ERROR_CONNECTION if the command could not be sent to the printer due to connection errors
        *- Types::RESULT_ERROR if the command could not be processed
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getStatus(Types::SolScanStatus *status,
            Types::SolPrinterState *state,
            Types::SolProgressType *type,
            long *progress) = 0;

    };

}

#endif // SDK_SOL_PACKER_H

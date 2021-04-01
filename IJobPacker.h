#ifndef JOBPACKER_H
#define JOBPACKER_H

//////////////////////////////////////////////////////////////////////////////
/**
 * @file   IJobPacker.h
 * @author David Tousaint (david.toussaint@hp.com)
 * @date   Tue May  24 19:27:33 CEST 2016
 * @brief  C++ Job packer interface classes.
 *
 * @par &copy; Copyright Hewlett-Packard Company, 2000-2012.
 * All rights reserved. Copying or other reproduction of this program except
 * for archival purposes is prohibited without written consent of
 * Hewlett-Packard Company.
 */
//////////////////////////////////////////////////////////////////////////////

#include "HplfpsdkTypes.h"
#include <cstring>

namespace HPLFPSDK
{

/**
 * @brief The IJobPacker provides the interface to print using the HPLFPSDK
 * It proposes methods create a job, pages, rasters and defines the job/page properties.
 */
class IJobPacker
{
public:
    class IPageSettings;
    class IJobSettings;

    enum JobPackerType: uint32_t
    {
        RASTERSTREAM_PWAX         = 0, /**< Page-Wide Array printers                                   */
        RASTERSTREAM_BANDS_DESIGN = 1, /**< Band-Wise DesignJet printers with chunky raster layout     */
        RASTERSTREAM_BANDS        = 2, /**< Band-Wise printers with planar support                     */
        RASTERSTREAM_BANDS_ICF4   = 6, /**< Band-Wise printers with planar support and HQ compression  */
        PCL3_TAOS                 = 3, /**< TAOS/PCL printers                                          */
        PCL3_BERT                 = 4, /**< BERT/PCL printers                                          */
        PCL3_HALFTONE             = 5, /**< Halftone print modes                                       */
        JOBPACKER_TYPE_NONE       = 0xFFFFFFFF /**< Error value                                        */
    };

    /**
    * @brief The IMemoryHandler interface can be implemented by the library client.\n
    * This mechanism will be used by the HPFLPSDK to pass raster data to the client\n
    * The memory handler must not be deleted until job that uses it is finished.\n
    */
    class IMemoryHandler
    {
    public:
        /**
        * @brief acquireBuffer requests access to numBytes in the heap. \n
        * Depending on the implementation it might allocate them. \n
        * This memory buffer will be used by the HPFLPSDK to store the rasterized data generated.\n
        * This memory buffer must not be modified by the client's code until a call to releaseBuffer(). \n
        * The buffer is allocated by the HPLFPSDK client's code and it should not be released until a call to releaseBuffer().
        * @param[in] numBytes size in bytes of the buffer.
        * @return a pointer to the beginning of the buffer.
        *         NULL when memory cannot be accessed or allocated.
        */
        virtual void* acquireBuffer(uint32_t numBytes) = 0;

        /**
        * @brief releaseBuffer notifies the HPFLPSDK client that the buffer was filled in with rasterized data.\n
        * The number of bytes of data returned is passed in the numbytes parameter.\n
        * The HPLFPSDK client's should then use the data (i.e.: send it to print, store it to a file,...)\n
        * @param[in] buffer pointer to be released.
        * @param[in] numBytes number of bytes used.
        */
        virtual void  releaseBuffer(const uint8_t *buffer, uint32_t numBytes) = 0;

    };

    /**
    * @brief To store a preview picture in machines supporting it.
    */
    class Preview
    {
    public:
        uint32_t  numBytes_;    /**< number of bytes of preview contents in the buffer */
        uint8_t  *buffer_;      /**< buffer containing the page preview in jpeg format */

        Preview()
        {
            numBytes_ = 0;
            buffer_ = (uint8_t*)(0);
        }
    };

    /**
    * @brief To store a the render data to be passed to the HPLFPSDK in case of some planar formats.
    */
    class RS_buffer
    {
    public:
        uint8_t numPlane_;      /**< in case of multi planar images, number of planes of this buffer (corresponding to a colour). */
        uint8_t ** buffer;      /**< double pointer to a dual dimension buffer containing the data of each swath to be compressed, buffer[plane][pixel]*/

        RS_buffer()
        {
            numPlane_ = 0;
            buffer = 0;
        }
    };


    /**
    * @brief transmissionStatusCallback is a function pointer to the transmission status callback
    * @details If the client calls newJob with a NULL memory handler, the SDK uses their components to send the job data to the printer.
    * In this case, the client can also gives a function pointer that will be called everytime the SDK send a buffer to the printer with the number of bytes written in that tranmission.
    * @param[in] userData is used to handle any external object or data to the SDK
    * @param[in] bytesSent bytes sent for the last transmission to the printer.
    */
    typedef void(*transmissionStatusCallback)(void *userData, size_t bytesSent);

    typedef uint32_t pageid_t;
    static const pageid_t INVALID_ID = ~pageid_t(0);

    /** @name Methods to get a new settings container.
     *  @{ */

    /**
     * @brief getJobSettingsContainer requests for an object containing job setting parameters
     * @details Job settings are mandatory to create a job, they must comply with the printer accepted values\n
     * The client is not responsible for the cleaning of JobSettings.\n
     * Instead, the resource of a JobSettings object are released by the HPLFKSDK when a new JobSettings container is requested by the client for the same JobPacker,
     * or when the corresponding JobPacker is discarded with the discardJobPacker API.\n
     * As a consequence, the pointer returned in a previous call will no longer be valid
     * after the next call to this method.
     * @return jobSettings object or NULL if unable to create the object
     */
    virtual IJobSettings* getJobSettingsContainer() = 0;

    /**
     * @brief getPageSettingsContainer requests for an object containing page setting parameters
     * @details Page settings are mandatory to generate a page, they must comply with the printer accepted values\n
     * The client is not responsible for the cleaning of IPageSettings.\n
     * Instead, the resource of a JobSettings object are released by the HPLFKSDK when a new PageSettings container is requested by the client for the same JobPacker,
     * or when the corresponding JobPacker is discarded with the discardJobPacker API.\n
     * As a consequence, the pointer returned in a previous call will no longer be valid
     * after the next call to this method.
     * @return pageSettings object or NULL if unable to create the object
     */
    virtual IPageSettings* getPageSettingsContainer() = 0;

     /** @} */
    /** @name Job operations.
     *  @{ */

    /**
     * @brief newJob starts a new job using the JobPacker object.
     * @details A raster job is a formatted block of data obtained compressing an image with a compression method compatible with the printer
     * @param[in] settings job configuration parameters
     * @param[in] mhdl memory buffer to contain job.
     * If NULL then the SDK creates a memory handler and will send the data to the printer. This connection will be in use 30 seconds after discarding this jobPacker.
     * In case the SDK is using this feature with other JobPacker then a RESULT_ERROR_CONNECTION will be return. So if your application wants to use the SDK for job submission
     * at least 30 seconds are needed between the endJob of the first job and the invocation to newJob of the second job.
     * @param[in] transmissionStatusCallback function pointer for the transmission callback. mhdl must be null so the SDK can call this function.
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
    virtual Types::Result newJob(IJobSettings* settings, IMemoryHandler * mhdl, transmissionStatusCallback callback, void *userData) = 0;

    /**
     * @brief endJob ends a raster job
     * @details This function comes after a valid job has been created and the command that generates is mandatory for the printer to process the job successfuly
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
     *- Types::RESULT_ERROR_SETTING_MANDATORY_NOT_SET;
     */
    virtual Types::Result endJob() = 0;

    /**
     * @brief jobCancel cancels the current job. All internal HPLFPSDK buffers will be released and a JOBCANCEL command will be sent to the printer in the plot data/signalization
     * @details in case a job has to be cancelled before its completion, it is mandatory to call  jobCancel to avoid fatal errors in the printer\n
     * please note that the MemoryHandler used for the job must be available (not deleted), the jobCancel() will use it to send the JOBCANCEL command to the printer.
     * @return result of the operation
     *- Types::RESULT_OK;
     *- Types::RESULT_ERROR_COMPRESSOR;
     *- Types::RESULT_ERROR_MEMORY;
     *- Types::RESULT_ERROR_INTERNAL;
     *- Types::RESULT_NOT_SUPPORTED;
     */
    virtual Types::Result jobCancel() = 0;


    /** @} */
    /** @name Page operations.
     *  @{ */

    /**
     * @brief addPage adds a page to the current job
     * @details a job contains pages of data, each one corresponding with the original image pages.
     * User can check the HasMultiPageSupport capabiltiy to know if it is possible to call this function more than one time per job packer instance.
     * @param[in] settings object pointer of an IPageSettings instance previously initialized by the user\n
     * @param[out] id identifier of the page. This pageId should be stored by the HPLFPSDK client to identify the page (preview, cancel...)
     * @return result of the operation
     *         - Types::RESULT_OK; If the page was added correctly.
     *         - Types::RESULT_ERROR_INVALID_USAGE_SEQUENCE; if there are more than one page on printers that does not support multipage, or the correct sequence is not followed.
     */
    virtual Types::Result addPage(IPageSettings* settings, pageid_t &id) = 0;

    /**
     * @brief addPreview adds a page preview
     * @details this is an optional command that allows to include in a job a preview image which will be shown in the rip application window or in the front panel
     * For multi-layer jobs (sandwich jobs), several previews can be added in a sequence, being the first one the layer that touch the printing surface.
     * @param[in] pageId page id
     * @param[in] preview object containing the page preview data
     * @return result of the operation
     *- Types::RESULT_OK;
     *- Types::RESULT_ERROR_INVALID_PARAMETER;
     *- Types::RESULT_ERROR_UNSUPPORTED_RASTER_FMT;
     *- Types::RESULT_ERROR_INVALID_USAGE_SEQUENCE;
     *- Types::RESULT_ERROR_COMPRESSOR;
     *- Types::RESULT_ERROR_MEMORY;
     *- Types::RESULT_NOT_SUPPORTED;
     *- Types::RESULT_ERROR_SETTING_MANDATORY_NOT_SET;
     *- Types::RESULT_ERROR_IN_MARGINS_SETTINGS;
     * -Types::RESULT_MEDIA_SOURCE_NOT_SUPPORTED;
     * -Types::RESULT_ERROR_FOLDER_SETTINGS;
     */

    virtual Types::Result addPreview(pageid_t pageId, const Preview& preview) = 0;

    /**
     * @brief endPage ends a page
     * @details once the page is formatted and included in a job, this command marks the end of the page. More pages will follow, or a job end if it is the last one.
     * @param[in] pageId page id
     * @return result of the operation
     *- Types::RESULT_OK;
     *- Types::RESULT_ERROR_INVALID_USAGE_SEQUENCE;
     *- Types::RESULT_ERROR_INTERNAL;
     *- Types::RESULT_ERROR;
     */
    virtual Types::Result endPage(pageid_t pageId) = 0;

    /** @} */
    /** @name Raster operations.
     *  @{ */

    /**
     * @brief startRaster starts a Raster, only allowed for contone rasters with same vertical and horizontal resolutions. Please consider using startRasterKey as your default entry point.
     * @details inside a page, data is sent via a raster block containing chunks of data
     * @param[in] pageId to help data processing, every raster is related to a page id, corresponding with the image page
     * @param[in] format this parameter shows the raster color format. The value must be the same for every raster inside a job, and must be accepted by the printer
     * @param[in] resolution image resolution
     * @param[in] width image width
     * @param[in] height image height
     * @param[in] bytesPerLine number of bytes per line (bytes per pixel * pixels per line)
     * @param[in] planeOrder (in case of planar images, there is a raster for each plane)
     * @param[in] numberOfPlanes (in case of planar images)
     * @return result of the operation
     *- Types::RESULT_OK;
     *- Types::RESULT_ERROR_UNSUPPORTED_RASTER_FMT;
     *- Types::RESULT_ERROR_INVALID_USAGE_SEQUENCE;
     *- Types::RESULT_ERROR_COMPRESSOR;
     *- Types::RESULT_ERROR_MEMORY;
     *- Types::RESULT_ERROR_INTERNAL;
     *- Types::RESULT_ERROR;
     */
    virtual Types::Result startRaster(pageid_t pageId, Types::RasterFormat format, uint32_t resolution, uint32_t width, uint32_t height, uint32_t bytesPerLine, uint8_t *planeOrder = (uint8_t *)"CMYK", uint32_t numberOfPlanes = 1) = 0;

    /**
     * @brief startRasterKey starts a Raster, valid for contone and halftone raster configurations.
     * @details inside a page, data is sent via a raster block containing chunks of data
     * @param[in] pageId to help data processing, every raster is related to a page id, corresponding with the image page
     * @param[in] rasterConfig this parameter shows the raster configuration. The value must be the same for every raster inside a job, and must be accepted by the printer. It must be taken from the printmodes/papermodes output.\n
     * It can be automatically obtained from the rasterConfiguration nodes of the printmodes/papermodes of the getMediaInformation output.\n
     * This parameter is a formatted string :UUU-XXX-YYY-ZZZ-TTT"\n
     *  -# UUU : the raster configuration type, CHUNKY, PLANAR, PLANAR_HT (for planar halftone layouts)
     *  -# XXX : the raster layout. How are the componentes ordered (i.e. : XRGB, XBGR, RGBX, KCMY, CMYK, CMYKW, KCMYkR, ....)
     *  -# YYY : the bits per pixels on each plane as an integer (i.e. : 2)
     *  -# ZZZ : the resolution, two formats are possible
     *      contone : one integer : the rendering resolution
     *      halftone : two integers separated by 'x' or 'X' (the horizontal and vertical halftone resolution)
     *  -# TTT : language and compression format {i.e. : RasterStream_BANDS_DESIGN or PCL3_HALFTONE}
     *  -
     *
     * i.e.:
     *  -CHUNKY-XRGB-32-600-PCL3_TAOS
     *  -CHUNKY-RGBX-32-1200-RasterStream_BANDS_DESIGN
     *  -PLANAR-CMYK-8-600-RasterStream_BANDS
     *  -PLANAR_HT-KCMYkR-2-1200x1200-PCL3_HALFTONE
     *
     * This format can (recommended) be read in the RasterConfig chapter in each printmode description as obtained from the \link HPLFPSDK::IMediaManager::getSupportedPrintmodes\endlink API.
     * @param[in] width image width in pixels
     * @param[in] height image height in pixels
     * @param[out] bytesPerLine number of bytes per line (bytes per pixel * pixels per line for contone rasters, bits per pixed * pixel per line / 8 for halftone rasters)
     * @return result of the operation
     * - Types::RESULT_OK;
     * - Types::RESULT_ERROR_UNSUPPORTED_RASTER_FMT;
     * - Types::RESULT_ERROR_INVALID_USAGE_SEQUENCE;
     * - Types::RESULT_ERROR_COMPRESSOR;
     * - Types::RESULT_ERROR_MEMORY;
     * - Types::RESULT_ERROR_INTERNAL;
     * - Types::RESULT_ERROR;
     */
    virtual Types::Result startRasterKey(pageid_t pageId, const char *rasterConfig, uint32_t width, uint32_t height, uint32_t *bytesPerLine) = 0;

    /**
     * @brief addRasterData add raster data for the page (chunky format version)
     * @details to maximize performance, image data is divided in chunks according to the printer type. Every chunk has a fixed width and is sent inside 'buffer' parameter
     * @param[in] pageId to help data processing, every chunk is related to a page id, corresponding with the image page
     * @param[in] bufferWidth length of a row in bytes
     * @param[in] rows number of rows included in a chunk
     * @param[in] startRow initial row - a raster can be divided in multiple chunks
     * @param[in] buffer contains the raster data to be processed. The buffer size must be bufferWidth*rows\n
     * @return result of the operation
     * - Types::RESULT_OK;
     * - Types::RESULT_ERROR_INVALID_PARAMETER;
     * - Types::RESULT_ERROR_UNSUPPORTED_RASTER_FMT;
     * - Types::RESULT_ERROR_INVALID_USAGE_SEQUENCE;
     * - Types::RESULT_ERROR_COMPRESSOR;
     * - Types::RESULT_ERROR_MEMORY;
     * - Types::RESULT_ERROR_INTERNAL;
     * - Types::RESULT_ERROR;
     */
    virtual Types::Result addRasterData(pageid_t pageId, unsigned int bufferWidth, unsigned int rows, unsigned int startRow, uint8_t *buffer) = 0;

    /**
     * @brief addRasterDataRSBuffer add raster data for the page (planar format version)
     * @details to maximize performance, image data is divided in chunks according to the printer type. Every chunk has a fixed width and is sent inside 'buffer' parameter
     * @param[in] pageId to help data processing, every chunk is related to a page id, corresponding with the image page
     * @param[in] bufferWidth length of a row
     * @param[in] rows number of rows included in a chunk
     * @param[in] startRow initial row - a raster can be divided in multiple chunks
     * @param[in] buffer contains the raster data to be processed. It is a struct with a dual dimension buffer that contains each pixel color level of each swath gathered per channel.\n
     * @return result of the operation
     * - Types::RESULT_OK;
     * - Types::RESULT_ERROR_INVALID_PARAMETER;
     * - Types::RESULT_ERROR_UNSUPPORTED_RASTER_FMT;
     * - Types::RESULT_ERROR_INVALID_USAGE_SEQUENCE;
     * - Types::RESULT_ERROR_COMPRESSOR;
     * - Types::RESULT_ERROR_MEMORY;
     * - Types::RESULT_ERROR_INTERNAL;
     * - Types::RESULT_ERROR;
     */
    virtual Types::Result addRasterDataRSBuffer(pageid_t pageId, unsigned int bufferWidth, unsigned int rows, unsigned int startRow, RS_buffer buffer) = 0;

    /**
     * @brief endRaster ends raster for the page
     * @details every raster block must end with an end page command
     * @param[in] pageId to help data processing, every raster is related to a page id, corresponding with the image page
     * @return result of the operation
     * - Types::RESULT_OK;
     * - Types::RESULT_ERROR_INVALID_PARAMETER;
     * - Types::RESULT_ERROR_UNSUPPORTED_RASTER_FMT;
     * - Types::RESULT_ERROR_INVALID_USAGE_SEQUENCE;
     * - Types::RESULT_ERROR_COMPRESSOR;
     * - Types::RESULT_ERROR_MEMORY;
     * - Types::RESULT_ERROR_INTERNAL;
     * - Types::RESULT_ERROR;
     */
    virtual Types::Result endRaster(pageid_t pageId) = 0;

    /** @} */
    /** @name Miscellanous.
     *  @{ */

    /**
     * @brief getJobPackerType returns current printer type
     * @return HPLFPSDK::IJobPacker::JobPackerType
     */
    virtual JobPackerType getJobPackerType() = 0;

    /**
     * @brief getState returns current operation state
     * @return HPLFPSDK::Types::RasterLibState
     */
    virtual Types::RasterLibState getState() = 0;

    /**
    * @brief getState returns the language used to communicate with the printer
    * @return HPLFPSDK::Types::JobLanguage
    */
    virtual Types::JobLanguage getLanguage() const = 0;

    /** @} */

protected:
    ~IJobPacker(){}
};

}
#endif // JOBPACKER_H

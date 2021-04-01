#ifndef HPLFPSDK_H
#define HPLFPSDK_H

//////////////////////////////////////////////////////////////////////////////
/**
 * @file   IHplfpsdk.h
 * @author David Tousaint (david.toussaint@hp.com)
 * @date   Tue May  24 19:27:33 CEST 2016
 * @brief  C++ SDK2 interface.
 *
 * @par &copy; Copyright Hewlett-Packard Company, 2000-2012.
 * All rights reserved. Copying or other reproduction of this program except
 * for archival purposes is prohibited without written consent of
 * Hewlett-Packard Company.
 */
//////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <cstring>
#include <iostream>

#include "HplfpsdkTypes.h"
#include "IManagers.h"
#include "IJobPacker.h"
#include "ISolPacker.h"
#include "IScanPacker.h"
#include "ISettings.h"

#ifdef _WIN32
    #ifdef HPLFPSDK_EXPORT
        #ifdef __GNUC__
            #define HPLFPSDK_API __attribute__((dllexport))
        #else
            #define HPLFPSDK_API __declspec (dllexport)
        #endif
    #else
        #ifdef __GNUC__
            #define HPLFPSDK_API __attribute__((dllimport))
        #else
            #define HPLFPSDK_API __declspec (dllimport)
        #endif
    #endif
#elif defined(__ELF__) && defined(__GNUC__) || defined(MACOSX)
    #ifdef HPLFPSDK_EXPORT
        #define HPLFPSDK_API __attribute__((visibility("default"))) // compilation flag -fvisibility=hidden
    #else
        #define HPLFPSDK_API
    #endif
#else
    #error "Unsupported platform"
#endif

namespace HPLFPSDK
{
    class IDevice;
}

extern "C"
{
    /*** Methods of the HP LFP SDK library **/

    /** \defgroup API_C_Methods HP LFP SDK Library main interface.
     * @{
     */

    /**
    * @brief hplfpsdk_init Initialize the SDK library and it dependencies
    * This method must be called before using the library
    * @param[in] logfile is a char array with the path of the desired log file.\n
    * NOTE: This represents the full path for the log file, the directory and the log file name.\n
    * If NULL, the logfile will be hplfpsdk.log in the execution path.
    * e.g.: C:\\route_to_log\\logfilename.log or UNIX style /route_to_log/logfilename.log
    * @return Result of the operation.
    * - RESULT_OK if every dependency has been properly initialized
    * - RESULT_ERROR if logging could not be initilized.
    * - RESULT_ERROR_INTERNAL if any dependency library could no be initialized
    * - RESULT_ERROR_FILE_NOT_FOUND if the file "Data/ModelFile.dat" could not be found.
    */
    HPLFPSDK_API HPLFPSDK::Types::Result hplfpsdk_init(const char *logfile = NULL);


    /**
    * @brief hplfpsdk_terminate terminates the dependency libraries and clears the SDK system resources.
    * This method must be called for instance when ending the application
    */
    HPLFPSDK_API void hplfpsdk_terminate();

    /**
    * @brief hplfpsdk_getVersion provides the SDK current library version
    * @param[out] majorVersion uint32_t pointer to major version number, this variable has to be created by the client and is set by te SDK library.
    * @param[out] minorVersion uint32_t pointer to minor version number, this variable has to be created by the client and is set by te SDK library.
    * @return Result of the operation:
    * - HPLFPSDK::Types::RESULT_OK
    */
    HPLFPSDK_API HPLFPSDK::Types::Result hplfpsdk_getVersion(uint32_t *majorVersion, uint32_t *minorVersion);

    /**
    * @brief hplfpsdk_getNetworkPrinters provides a list of the printers found in the local network.
    * @param[out] networkPrinters char array with the list of printers and their IP address in XML format.\n
    * See the following \link section_hplfpsdk_getNetworkPrinters reference\endlink.\n
    * Please note that the HPLFPSDK will allocate memory to hold the returned data\n
    * It is the responsibility of the HPFLPSDK client's to free the corresponding ressources using hplfpsdk_deleteBuffer() API.\n
    * In case of error, this output value is undefined.
    * @param[out] networkPrintersLength length in bytes of the networkPrinters array.
    * @return Result of the operation:
    * - Types::RESULT_OK
    * - Types::RESULT_ERROR_LIBRARY_NOT_INITIALIZED
    */
    HPLFPSDK_API HPLFPSDK::Types::Result hplfpsdk_getNetworkPrinters(char **networkPrinters,  size_t &networkPrintersLength);

    /**
    * @brief hplfpsdk_getNetworkPrintersExtended provides a list of the printers found in the local network with the configuration set by the user.
    * @param[in] queryTimeOut in seconds, defines the timeout for each network scanning queries.
    * @param[in] discoveryTimeOut in seconds, defines the total time in seconds of the whole procedure. This time should be a multiple of the queryTimeOut parameter to allow several scanning queries to be completed.
    * @param[in] supportedPrinters is a boolean flag that if true then only supported printers by this SDK will be return on the networkPrinter string.
    * if false, then all HP printers found on the network will be returned. Please be sure that the printer is supported with hplfpsdk_isPrinterModelSupported before using it.
    * @param[out] networkPrinters char array with the list of printers and their IP address in XML format.\n
    * See the following \link section_hplfpsdk_getNetworkPrinters reference\endlink.\n
    * Please note that the HPLFPSDK will allocate memory to hold the returned data\n
    * It is the responsibility of the HPFLPSDK client's to free the corresponding ressources using hplfpsdk_deleteBuffer() API.\n
    * In case of error, this output value is undefined.
    * @param[out] networkPrintersLength length in bytes of the networkPrinters array.
    * @return Result of the operation:
    * - Types::RESULT_OK
    * - Types::RESULT_ERROR_LIBRARY_NOT_INITIALIZED
    */
    HPLFPSDK_API HPLFPSDK::Types::Result hplfpsdk_getNetworkPrintersExtended(uint32_t queryTimeOut, uint32_t discoveryTimeOut, bool supportedPrinters, char **networkPrinters, size_t &networkPrintersLength);

    /**
    * @brief hplfpsdk_getNewPrinter creates a new IDevice object for the provided printer model using printerModelName parameter.
    * @details This method allocate the necessary memory for the IDevice Object, but also creates and initializes all it dependencies, so it can take long time to execute it.
    * After this method is called, you have a complete printer structure even if the printer cannot be reached over network.
    * please note that the printer must be deleted after use to free ressources using hplfpsdk_discardPrinter
    * @param[in] ipAddress ip address of the printer. It can be an empty string if the client just want to create offline jobs (not null pointer).
    * @param[in] printerModelName model of the printer.
    * @param[out] device return pointer to the Device object that implements IDevice interface. This object shall be deleted using hplfpsdk_discardPrinter.
    * @return Result of the operation:
    * - Types::RESULT_ERROR_DEVICE_ALREADY_EXISTS if the IP is currently in use by another IDevice instance.
    * - Types::RESULT_ERROR_PRINTER_MODEL_UNKNOWN if the printerModelName cannot be found in the ModelFile.dat file.
    * - Types::RESULT_ERROR if the printer cannot be initialized.
    * - Types::RESULT_OK if the printer is now available.
    */
    HPLFPSDK_API HPLFPSDK::Types::Result hplfpsdk_getNewPrinter(const char *ipAddress, const char *printerModelName, HPLFPSDK::IDevice* &device);

    /**
    * @brief hplfpsdk_discardPrinter is in charge to delete the IDevice instance resources and memory.
    * @param[in] device pointer to the IDevice instance to be discarded.
    * @return Result of the operation:
    * - HPLFPSDK::Types::RESULT_OK
    */
    HPLFPSDK_API HPLFPSDK::Types::Result hplfpsdk_discardPrinter(HPLFPSDK::IDevice* device);

    /**
    * @brief This API is in charge to free the previously allocated memory by the SDK \n
    *        This API provides a method non dependant from the compiler to free the allocated memory (char *)
    * @param[in] buffer pointer to the allocated memory to be free.
    */
    HPLFPSDK_API void hplfpsdk_deleteBuffer(char **buffer);

    /**
    * @brief hplfpsdk_setLogLevel changes the logging level (threshold) if the level is included in a valid \link HPLFPSDK::Types::LogLevel range\endlink.
    * @details It can be possible set the logging level even when the sdk library is not yet initilized. See the reference \link section_logging page\endlink for "how to use" example.
    * @param[in] level shall contain a valid level between HPLFPSDK::Types::LEVEL_NONE and HPLFPSDK::Types::LEVEL_ALL
    * @return Result of the operation:
    * - HPLFPSDK::Types::RESULT_OK if the log level can be changed.
    * - HPLFPSDK::Types::RESULT_ERROR otherwise. This usually means that there has been an error when the library was initilized.
    */
    HPLFPSDK_API HPLFPSDK::Types::Result hplfpsdk_setLogLevel(HPLFPSDK::Types::LogLevel level);

    /**
    * @brief hplfpsdk_getSupportedPrinterModels returns those printer models that are supported by the HPLFPSDK Library
    * @param[out] printerModels holds the list of printers that are supported by the HPLFPSDK Library in XML format.
    * See the following \link section_hplfpsdk_getSupportedPrinterModels reference\endlink.\n
    * Please note that the HPLFPSDK will allocate memory to hold the returned data\n
    * It is the responsibility of the HPFLPSDK client's to free the corresponding ressources using hplfpsdk_deleteBuffer() API.\n
    * In case of error, this output value is undefined.
    * @param[out] printerModelsLength lenght in bytes of the printerModels array
    * @return Result of the operation:
    * - HPLFPSDK::Types::RESULT_OK if printerModels were retrieved
    * - HPLFPSDK::Types::RESULT_ERROR otherwise. This usually means that modelFile.dat was not found
    */
    HPLFPSDK_API HPLFPSDK::Types::Result hplfpsdk_getSupportedPrinterModels(char **printerModels, size_t &printerModelsLength);

    /**
    * @brief hplfpsdk_isPrinterModelSupported returns true if the printer model name introduced is supported. False otherwise.
    * @param[in] modelName should be the printer model name that is wanted to know if is supported
    * @return Result of the operation:
    * - true / 1 if printerModel is supported
    * - false / 0 otherwise.
    */
    HPLFPSDK_API bool hplfpsdk_isPrinterModelSupported(const char *modelName);

    /**@}*/
}

namespace HPLFPSDK
{

/**
* @brief The IDevice class represents an unique printer and IP, and provides the different managers pointers.
*/
class IDevice
{
public:

    /**
    * @brief getPrinterModel provides the printer model associated with the Device object.
    * @param[out] modelName returns the model name using an array of char.\n
    * This memory allocation shall be deleted using hplfpsdk_deleteBuffer() interface.\n
    * In case of error, this output value is undefined.
    * @param[out] modelNameLength length of the former modelName parameter.
    */
    virtual void getPrinterModel(char **modelName, size_t &modelNameLength) = 0;

    /**
    * @brief Creates a new IJobPacker object accordingly to the provided raster configuration.
    *  The JobPacker object can be used to create standard jobs.
    *  The HPLFPSDK will create a new instance of JobPacker
    *  The HPLFPSDK client is responsible for freeing the resources using IDevice::discardJobPacker
    * @param[in] rasterConfig this parameter shows the raster configuration.\n
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
    * This format can be read in the RasterConfig chapter in each printmode description as obtained from the getMediaInformation API of the MediaManager.
    * @return IJobPacker pointer to the JobPacker object.
    */
    virtual IJobPacker *createJobPackerUsingRasterConfiguration(const char *rasterConfig) = 0;

    /**
    * @brief Creates a new IJobPacker object accordingly to the provided type information.
    *  The JobPacker object can be used to create standard jobs.
    *  The HPLFPSDK will create a new instance of JobPacker
    *  The HPLFPSDK client is responsible for freeing the ressources using IDevice::discardJobPacker
    * @param[in] jobPackerTypeInfo select the printer type of the desired JobPacker
    * @return IJobPacker pointer to the JobPacker object.
    */
    virtual IJobPacker *createJobPackerUsingPackerType(IJobPacker::JobPackerType jobPackerTypeInfo) = 0;

    /**
    * @brief Deletes the JobPacker object and free it resources
    * @param[in] packer a pointer to the IJobPacker object to be deleted.
    */
    virtual void discardJobPacker(IJobPacker* packer) = 0;

    /**
    * @brief Creates a new ISolPacker object accordingly to the provided raster configuration.
    *  The SolPacker object can be used to create jobs that use the spectrophotometer.
    *  The HPLFPSDK will create a new instance of SolPacker
    *  The HPLFPSDK client is responsible for freeing the resources using IDevice::discardSolPacker
    * @param[in] rasterConfig this parameter shows the raster configuration. \n
    * This parameter is a formatted string : XXX-YYY-ZZZ-TTT-UUU"\n
    *  -# XXX : the raster format (i.e. : XRGB, XBGR, RGBX, KCMY, CMYK, PLANAR, ....)
    *  -# YYY : the bits per pixels as an integer (i.e. : 2)
    *  -# ZZZ : the resolution, two formats are possible
    *      contone : one integer : the rendering resolution
    *      halftone : two integers separated by 'x' or 'X' (the horizontal and vertical halftone resolution)
    *  -# TTT : the compression format {i.e. : BANDS_DESIGN}
    *  -# UUU : the plane order as a string, for planar only (chunky format must come with an empty field)
    *
    * i.e.:
    *  -XRGB-8-600-TAOS
    *  -KCMY-8-300-BERT
    *  -PLANAR-8-600-PWAX-CMYKWOR
    *  -PLANAR_HT-2-1200x600-BANDS-CMYK
    *
    * This format can be read in the RasterConfig chapter in each printmode description as obtained from the getSupportedPrintmode API of the MediaManager.
    * @return ISolPacker pointer to the SolPacker object.
    */
    virtual ISolPacker *createSolPackerUsingRasterConfiguration(const char *rasterConfig) = 0;

    /**
    * @brief Creates a new ISolPacker object accordingly to the provided type information.
    *        The SolPacker object can be used to create jobs that use the spectrophotometer.
    * @param[in] jobPackerTypeInfo select the printer type of the desired SolPacker
    * @return ISolPacker pointer to the SolPacker object.
    */
    virtual ISolPacker *createSolPackerUsingPackerType(IJobPacker::JobPackerType jobPackerTypeInfo) = 0;

    /**
    * @brief Deletes the SolPacker object and free it resources
    * @param[in] packer a pointer to the ISobPacker object to be deleted.
    */
    virtual void discardSolPacker(ISolPacker* packer) = 0;

    /**
    * @brief Provides the Media Manager Object that implements the IMediaManager interface\n
    * This method returns a pointer to an pre-existing object. No allocation is done in the HPLFPSDK.\n
    * The HPLFPSDK should not call delete on the returned object.
    * @return a pointer to the Media Manager Object.
    */
    virtual IMediaManager *getMediaManager() = 0;

    /**
    * @brief Provides the Remote Manager Object that implements the IRemoteManager interface
    * This method returns a pointer to an pre-existing object. No allocation is done in the HPLFPSDK.\n
    * The HPLFPSDK should not call delete on the returned object.
    * @return a pointer to the Remote Manager Object
    */
    virtual IRemoteManager *getRemoteManager() = 0;

    /**
    * @brief Provides the Info Manager Object that implements the IInfoManager interface
    * This method returns a pointer to an pre-existing object. No allocation is done in the HPLFPSDK.\n
    * The HPLFPSDK should not call delete on the returned object.
    * @return a pointer to the Info Manager Object
    */
    virtual IInfoManager *getInfoManager() = 0;

    /**
    * @brief Provides the Accounting Manager Object that implements the IAccountingManager interface
    * This method returns a pointer to an pre-existing object. No allocation is done in the HPLFPSDK.\n
    * The HPLFPSDK should not call delete on the returned object.
    * @return a pointer to the Accounting Manager Object
    */
    virtual IAccountingManager *getAccountingManager() = 0;

    /**
    * @brief Provides the Usage Manager Object that implements the IUsageManager interface
    * This method returns a pointer to an pre-existing object. No allocation is done in the HPLFPSDK.\n
    * The HPLFPSDK should not call delete on the returned object.
    * @return A pointer to the Usage Manager Object
    */
    virtual IUsageManager *getUsageManager() = 0;

    /**
    * @brief Returns the capabilities of the initialized device in XML format\n
    * @param[out] capabilities is a return parameter where all the capabilities are written in xml format\n
    * Please note that the HPLFPSDK will allocate memory to hold the returned data\n
    * See the following \link section_capabilities reference\endlink.\n
    * It is the responsibility of the HPSLFPSDK's client to free the corresponding ressources using hplfpsdk_deleteBuffer() API.\n
    * In case of error, this output value is undefined.
    * @param[out] capabilitiesLength return parmeter with the length of former capabilities parameter.
    * @return RESULT_OK if the Device is properly initialized and all the capabilities could be read and the capabilities parameter is properly filled in.
    *         RESULT_ERROR otherwise (This usually means that the printer resource files are not available).
    */
    virtual Types::Result getCapabilities(char **capabilities, size_t &capabilitiesLength) = 0;

    /**
    * @brief Sets the desired language for the printer answers\n
    * @param[in] language the language to use for each printer call in IETF language tag format (RFC4647) (ISO 639-X codes). e.g. en-US\n
    * Available languages are: en-US, ca-ES, zh-TW, de-DE, fr-FR, it-IT, ko-KR, pt-PT, ru-RU, zh-CN, es-ES, ja-JP, nl-NL, tr-TR, sv-SE, pt-BR
    * Note: not all the printers supports all the former languages, you can refeer to the Printer Description Document
    * @return RESULT_OK if the language could be changed.
    *         RESULT_ERROR if the language is not supported by this printer.
    */
    virtual Types::Result setLanguage(const char* language) = 0;

    /**
    * @brief Gets the printer family\n
    * @return Types::Printer family enum values
    *         PRINTER_FAMILY_UNKNOWN if the printer family is not defined
    */
    virtual Types::PrinterFamily getPrinterFamily() = 0;

    /**
    * @brief Creates a new IScanPacker object that can be used to create scanning jobs.
    *  The HPLFPSDK will create a new instance of SolPacker
    *  The HPLFPSDK client is responsible for freeing the resources using IDevice::discardScanPacker
    * @return IScanPacker pointer to the ScanPacker object.
    */
    virtual IScanPacker *createScanPacker() = 0;

    /**
    * @brief Deletes the ScanPacker object and free it resources
    * @param[in] packer a pointer to the IScanPacker object to be deleted.
    */
    virtual void discardScanPacker(IScanPacker* packer) = 0;

protected:
    ~IDevice(){}
};

} //namespace HPLFPSDK

#endif // HPLFPSDK_H

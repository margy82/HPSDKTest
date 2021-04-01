#ifndef I_MANAGERS_H
#define I_MANAGERS_H

//////////////////////////////////////////////////////////////////////////////
/**
* @file   IManagers.h
* @author Jesus Lucas (jesus.lucas.natal@hp.com)
* @date   Mon Jun 03 09:51:59 CEST 2019
* @brief  C++ HP LFP SDK Managers interfaces.
*
* @par &copy; Copyright Hewlett-Packard Company, 2000-2019.
* All rights reserved. Copying or other reproduction of this program except
* for archival purposes is prohibited without written consent of
* Hewlett-Packard Company.
*/
//////////////////////////////////////////////////////////////////////////////

#include "HplfpsdkTypes.h"

namespace HPLFPSDK
{
    class IMediaManager
    {
    public:
        enum MediaEventType
        {
            EVENT_MEDIA_INFORMATION_COUNTER_CHANGE //!< Event raised when the media list version has changed
        };

        /**
        * Function pointer to the event callback
        * @param[in] type identifier of the type of event generated
        * @param[in] userData the same userData used in the corresponding subscribe function
        * @param[in] subscriptionId the same identifier of the subscription returned by the corresponding subscribe function.
        * @param[in] newValue char array new value of the element that generated the event.\
        * The corresponding format for this value depends on the MediaEventType
        * - EVENT_MEDIA_INFORMATION_COUNTER_CHANGE See the following \link section_mediaManager_mediaInformationCounter reference\endlink.
        * This allocated memory will be released automatically once the callback returns.
        * @param[in] xmlLength length of the newXmlValue char array in bytes.
        */
        typedef void(*onChangeCallback)(MediaEventType type, void *userData, uint32_t subscriptionId, const char *newValue, int length);

        /**
        * @brief creates a copy of a given media.
        * @param[in] mediaName name of the new custom media created.
        * @param[in] donorMediaID ID of the source medium
        * @param[out] cumstomMediaInformation returns an array of chars with the medium information. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenCustomMediaInformation length in bytes of the cumstomMediaInformation array parameter.
        * @return result of the operation.
        *- Types::RESULT_ERROR_MEDIUM_KEY_NOT_VALID if the medium ID is not valid.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the donor media ID is not valid.
        *- Types::RESULT_ERROR_NO_ROOM_FOR_MORE_MEDIA if the media limit has been reached.
        *- Types::RESULT_ERROR_MEDIUM_CANNOT_BE_CLONED if the donor media cannot be cloned.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_OK if the cumstomMediaInformation array was properly filled in.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result createCustomMedia(const char *mediaName, const char *donorMediaID, char **cumstomMediaInformation, size_t &lenCustomMediaInformation) = 0;

        /**
        * @brief creates a new medium based on a XML settings description.
        * @param[in] mediaSettingsXmlInfo XML that describes the new media being created. The XML format is not defined yet, because the current SDK does not support any printer with this feature.
        * @param[out] createNewMediaInfo returns an array of chars with the medium information. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] bufLength length in bytes of the createNewMediaInfo array parameter.
        * @return result of the operation.
        *- Types::RESULT_ERROR_MEDIUM_KEY_NOT_VALID if the medium ID is not valid.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the donor media ID is not valid.
        *- Types::RESULT_ERROR_MEDIUM_MISSING_NAME if the name of the new media is not specified.
        *- Types::RESULT_ERROR_NO_ROOM_FOR_MORE_MEDIA if the media limit has been reached.
        *- Types::RESULT_ERROR_MEDIUM_CANNOT_BE_CLONED if the donor media cannot be cloned.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_OK if the createNewMediaInfo array was properly filled in.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result createNewMedia(const char *mediaSettingsXmlInfo, char **createNewMediaInfo, size_t &bufLength) = 0;

        /**
        * @brief creates a new paper mode for a given medium based on a XML settings description.
        * @param[in] mediaSettingsXmlInfo XML that describes the new paper mode being created. The XML format is not defined yet, because the current SDK does not support any printer with this feature.
        * @param[out] createPaperMode returns an array of chars with the paper mode information. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] bufLength length in bytes of the createPaperMode array parameter.
        * @return result of the operation.
        *- Types::RESULT_ERROR_MEDIUM_KEY_NOT_VALID if the medium ID is not valid.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the media ID is not valid.
        *- Types::RESULT_ERROR_NO_ROOM_FOR_MORE_MODES if the paper modes limit has been reached for the given medium.
        *- Types::RESULT_ERROR_MODE_ALREADY_EXISTS if the paper mode already exists.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_OK if the createPaperMode array was properly filled in.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result createPaperMode(const char *mediaSettingsXmlInfo, char **createPaperMode, size_t &bufLength) = 0;

        /**
        * @brief returns the medium information for one or all mediums.
        * @param[in] mediaKey desired medium ID. If empty or NULL, this function returns the information for all media.
        * @param[out] mediaInformation returns an array of chars with the medium information.\n
        * See the following \link section_mediaManager_mediaInformation reference\endlink.\n
        * This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenMediaInformation length in bytes of the mediaInformation array parameter.
        * @return result of the operation.
        *- Types::RESULT_ERROR_MEDIUM_KEY_NOT_VALID if the medium ID is not valid.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        *- Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_OK if the mediaInformation array was properly filled in.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getMediaInformation(const char *mediaKey, char **mediaInformation, size_t &lenMediaInformation) = 0;

        /**
        * @brief returns the counter list for the specified medium.
        * @param[in] mediaKey medium ID.
        * @param[out] mediaInformation returns an array of chars with the counter list for the given media.\n
        * See the following \link section_mediaManager_mediaCounterList reference\endlink.\n
        * This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenMediaInformation length in bytes of the mediaInformation array parameter.
        * @return result of the operation.
        *- Types::RESULT_ERROR_MEDIUM_KEY_NOT_VALID if the medium ID is not valid.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_OK if the mediaInformation array was properly filled in.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getMediaCounterList(const char *mediaKey, char **mediaInformation, size_t &lenMediaInformation) = 0;

        /**
        * @brief returns the counter list for all media.
        * @param[out] mediaInfoCounter returns an array of chars with the counter list for all media. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenMediaInfoCounter length in bytes of the mediaInfoCounter array parameter.
        * @return result of the operation.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_OK if the mediaInfoCounter array was properly filled in.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getMediaInformationCounter(char **mediaInfoCounter, size_t &lenMediaInfoCounter) = 0;

        /**
        * @brief deletes the specified custom media.
        * @param[in] mediaID medium ID to be deleted.
        * @return result of the operation.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_OK if the media was properly deleted.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result deleteCustomMedia(const char *mediaID) = 0;

        /**
        * @brief deletes the specified custom media.
        * @param[in] mediumId medium ID that contains the paper mode to delete.
        * @param[in] ModeId paper mode ID to be deleted.
        * @return result of the operation.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the medium ID is not valid.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_OK if the media was properly deleted.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result deletePaperMode(const char *mediumId, const char *ModeId) = 0;

        /**
        * @brief restores the medium properties to the default values.
        * @param[in] mediumId medium ID that contains the paper mode to delete.
        * @param[in] ModeId paper mode ID to be deleted.
        * @return result of the operation.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the medium ID is not valid.
        *- Types::RESULT_ERROR_MODE_DOESNT_EXIST if the mode ID is not valid.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_OK if the media properties were properly set to default.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result setMediaPropertiesToDefault(const char *mediumId, const char *ModeId) = 0;

        /**
        * @brief changes a paper mode properties.
        * @param[in] mediumId medium ID that contains the paper mode to modify.
        * @param[in] ModeId paper mode ID to be modified.
        * @param[in] paramKey the key value to be changed. The supported values for paramKey are NAME, SELECTORS and DESCRIPTION. There are some examples:\n
        *- paramKey="SELECTORS" paramValue="Passes=12 InkDensity=130 EfficiencyMode=ON".
        *- paramKey="NAME" paramValue="New paper mode name".
        *- paramKey="DESCRIPTION" paramValue="New paper mode Description".\n
        *Note : Please make sure that syntax and case is followed
        * @param[in] paramValue new Param value which has to be set to the new param key. Based on the “paramKey” values the paramValues has to be specified as mentioned above.
        * @param[out] modifyPaperMode returns an array of chars with the modified paper mode. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] bufLength length in bytes of the modifyPaperMode array parameter.
        * @return result of the operation.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the medium ID is not valid.
        *- Types::RESULT_ERROR_MODE_DOESNT_EXIST if the mode ID is not valid.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_OK if the media properties were properly set to default.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result modifyPaperMode(const char *mediumId, const char *ModeId, const char *paramKey, const char *paramValue, char **modifyPaperMode, size_t &bufLength) = 0;

        /**
        * @brief sets the properties of a given medium.
        * @param[in] mediaID medium ID to modify.
        * @param[in] mediaSettingsXmlInfo XML with the new information. The XML format is not defined yet, because the current SDK does not support any printer with this feature.
        * @return result of the operation.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the medium ID is not valid.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_OK if the media was properly deleted.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result setMediumProperties(const char *mediaID, const char *mediaSettingsXmlInfo) = 0;

        /**
        * @brief sets the properties of a given medium.
        * @param[in] mediaSettingsXmlInfo XML with the new information. The XML format is not defined yet, because the current SDK does not support any printer with this feature.
        * @return result of the operation.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the medium ID is not valid.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_OK if the media was properly deleted.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result setMediumPropertiesEx(const char *mediaSettingsXmlInfo) = 0;

        /**
        * @brief provides the supported printmodes by the printer and by media.
        * @param[in] mediaKey media ID used to filter the supported printmodes associated to the media ID.
        * @param[out] supportedPrintmodes return parameter, char array with the supported printmodes information.\n
        * See the following \link section_mediaManager_supportedPrintModes reference\endlink.\n
        * This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenSupportedPrintmodes length in bytes of the supportedPrintmodes char array.
        * @return result of the operation.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        *- Types::RESULT_OK if the supportedPrintmodes array was properly filled in.
        */
        virtual Types::Result getSupportedPrintmodes(const char *mediaKey, char **supportedPrintmodes, size_t &lenSupportedPrintmodes) = 0;

        /**
        * @brief obtains the ICC profile for a given paper mode.
        * @param[in] mediaKey media ID that contains the paper mode.
        * @param[in] selectorList XML with the list of print mode selectors associated with the ICC. See the following \link section_mediaManager_IccProfileManagement reference\endlink.\n
        * @param[out] IccProfile return parameter, char array with the current ICC profile associated with the selectors. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenIccProfile length in bytes of the IccProfile char array.
        * @return result of the operation.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the medium ID is not valid.
        *- Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        *- Types::RESULT_OK if the IccProfile array was properly filled in.
        */
        virtual Types::Result getIccProfile(const char *mediaKey, const char *selectorList, char **IccProfile, size_t &lenIccProfile) = 0;

        /**
        * @brief copies the ICC profile for a given paper mode into another paper mode of the same media.
        * @param[in] mediaKey media ID that contains the paper modes.
        * @param[in] srcSelectorList XML with the list of print mode selectors associated with the source ICC. See the following \link section_mediaManager_IccProfileManagement reference\endlink.\n
        * @param[in] destSelectorList XML with the list of print mode selectors associated with the destination ICC. See the following \link section_mediaManager_IccProfileManagement reference\endlink.\n
        * @return result of the operation.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the medium ID is not valid.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        *- Types::RESULT_OK
        */
        virtual Types::Result copyIccProfile(const char *mediaKey, const char *srcSelectorList, const char *destSelectorList) = 0;

        /**
        * @brief deletes the ICC profile for a given paper mode.
        * @param[in] mediaKey media ID that contains the paper mode.
        * @param[in] selectorList XML with the list of print mode selectors associated with the ICC. See the following \link section_mediaManager_IccProfileManagement reference\endlink.\n
        * @return result of the operation.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the medium ID is not valid.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        *- Types::RESULT_OK.
        */
        virtual Types::Result deleteIccProfile(const char *mediaKey, const char *selectorList) = 0;

        /**
        * @brief sets the ICC profile for a given paper mode.
        * @param[in] mediaKey media ID that contains the paper mode.
        * @param[in] selectorList XML with the list of print mode selectors associated with the ICC. See the following \link section_mediaManager_IccProfileManagement reference\endlink.\n
        * @param[in] iccName name for the new ICC profile.
        * @param[in] profileContents it is the ICC profile data encoded in base64 format
        * @return result of the operation.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the medium ID is not valid.
        *- Types::RESULT_ERROR_INVALID_PARAMETER if the profile contents are empty.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        *- Types::RESULT_OK.
        */
        virtual Types::Result setIccProfile(const char *mediaKey, const char *selectorList, const char *iccName, const char *profileContents) = 0;

        /**
        * @brief gets the mechanical properties related to a specific media and printmode. Please refer to the PrinterDescription.pdf document for Product specific information
        * @param[in] mediaKey media ID to retrieve the mechanical properties.
        * @param[in] paperMode mode ID to  retrieve the mechanical properties. If NULL or empty the default values for the media will be retrieved 
        * @param[out] mechanicalProperties return parameter, char array with the mechanical properties. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenMechanicalProperties length in bytes of the mechanicalProperties char array.
        * @return result of the operation.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the medium ID is not valid.
        *- Types::RESULT_ERROR_MODE_DOESNT_EXIST if the mode ID is not valid.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        *- Types::RESULT_OK.
        */
        virtual Types::Result getMechanicalProperties(const char *mediaKey, const char *paperMode, char **mechanicalProperties, size_t &lenMechanicalProperties) = 0;

        /**
        * @brief changes de medium name
        * @param[in] mediaKey media ID to change the name.
        * @param[in] asciiName new name for the medium
        * @return result of the operation.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the medium ID is not valid.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        *- Types::RESULT_OK.
        */
        virtual Types::Result setIdentificationProperties(const char *mediaKey, const char *asciiName) = 0;

        /**
        * @brief obtains the ICC profile for a given paper mode.
        * @param[in] mediumKey media ID that contains the paper mode.
        * @param[in] selectorList XML with the list of print mode selectors associated with the ICC.
        * @param[out] profileVersion return parameter, char array with the current ICC profile associated with the paper mode. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] bufLength length in bytes of the profileVersion char array.
        * @return result of the operation.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the medium ID is not valid.
        *- Types::RESULT_ERROR_MODE_DOESNT_EXIST if the mode ID is not valid.
        *- Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        *- Types::RESULT_OK.
        */
        virtual Types::Result getIccProfileVersion(const char *mediumKey, const char *selectorList, char **profileVersion, size_t &bufLength) = 0;

        /**
        * @brief installs the Media preset (.oms) file onto the printer.
        * @param[in] uploadContent media preset file.
        * @param[in] uploadContentLength length of the media preset file.
        * @param[out] uploadMediaPresetStatus return parameter, char array with the status of the media preset. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenUploadMediaPreset length in bytes of the uploadMediaPresetStatus char array.
        * @return result of the operation.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the medium ID is not valid.
        *- Types::RESULT_ERROR_MODE_DOESNT_EXIST if the mode ID is not valid.
        *- Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        *- Types::RESULT_OK.
        */
        virtual Types::Result uploadMediaPreset(const char *uploadContent, size_t uploadContentLength, char **uploadMediaPresetStatus, size_t &lenUploadMediaPreset) = 0;

        /**
        * @brief downloads the Media preset (.oms) file onto the printer.
        * @param[in] mediaId media to download the preset file.
        * @param[out] downloadMediaPresetContent return parameter, char array with the preset content. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenDownloadMediaPresetContent length in bytes of the downloadMediaPresetContent char array.
        * @return result of the operation.
        *- Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized..
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the medium ID is not valid.
        *- Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        *- Types::RESULT_ERROR if there was any other problem when retrieving the data.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        *- Types::RESULT_OK.
        */
        virtual Types::Result downloadMediaPreset(const char *mediaId, char **downloadMediaPresetContent, size_t &lenDownloadMediaPresetContent) = 0;

        /**
        * @brief gets the look up table for the specified Media and Mode id. This API output should be used for Ink prediction feature.
        * @param[in] mediaKey media ID to retrieve the look up table.
        * @param[in] selectorList XML with the list of print mode selectors.
        * @param[out] lookuptable return parameter, char array with the look up table data. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] bufLength length in bytes of the lookuptable char array.
        * @return result of the operation.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the medium ID is not valid.
        *- Types::RESULT_ERROR_MODE_DOESNT_EXIST if the mode ID is not valid.
        *- Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        *- Types::RESULT_OK.
        */
        virtual Types::Result getLookUpTable(const char *mediaKey, const char *selectorList, char **lookuptable, size_t &bufLength) = 0;

        /**
        * @brief sets the ICC profile for the side B of a given paper mode. The printer and the paper mode should support sandwich mode
        * @param[in] mediaKey media ID that contains the paper mode.
        * @param[in] selectorList XML with the list of print mode selectors associated with the ICC. See the following \link section_mediaManager_IccProfileManagement reference\endlink.\n
        * @param[in] iccName name for the new ICC profile.
        * @param[in] profileContents it is the ICC profile data encoded in base64 format
        * @return result of the operation.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the medium ID is not valid.
        *- Types::RESULT_ERROR_SIDE_B_NOT_SUPPORTED if the paper mode does not support this function.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        *- Types::RESULT_OK.
        */
        virtual Types::Result setIccProfileSideB(const char *mediaKey, const char *selectorList, const char *iccName, const char *profileContents) = 0;

        /**
        * @brief obtains the ICC profile for the side B of a given paper mode. The printer and the paper mode should support sandwich mode
        * @param[in] mediaKey media ID that contains the paper mode.
        * @param[in] selectorList XML with the list of print mode selectors associated with the ICC. See the following \link section_mediaManager_IccProfileManagement reference\endlink.\n
        * @param[out] IccProfile return parameter, char array with the current ICC profile associated with the selectors. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenIccProfile length in bytes of the IccProfile char array.
        * @return result of the operation.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the medium ID is not valid.
        *- Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        *- Types::RESULT_ERROR_SIDE_B_NOT_SUPPORTED if the paper mode does not support this function.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        *- Types::RESULT_OK if the IccProfile array was properly filled in.
        */
        virtual Types::Result getIccProfileSideB(const char *mediaKey, const char *selectorList, char **IccProfile, size_t &lenIccProfile) = 0;

        /**
        * @brief deletes the ICC profile for the side B of a given paper mode. The printer and the paper mode should support sandwich mode
        * @param[in] mediaKey media ID that contains the paper mode.
        * @param[in] selectorList XML with the list of print mode selectors associated with the ICC. See the following \link section_mediaManager_IccProfileManagement reference\endlink.\n
        * @return result of the operation.
        *- Types::RESULT_ERROR_CONNECTION if the printer is not present.
        *- Types::RESULT_ERROR_MEDIUM_NOT_EXIST if the medium ID is not valid.
        *- Types::RESULT_ERROR_SIDE_B_NOT_SUPPORTED if the paper mode does not support this function.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        *- Types::RESULT_ERROR if there was any other error.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        *- Types::RESULT_OK.
        */
        virtual Types::Result deleteIccProfileSideB(const char *mediaKey, const char *selectorList) = 0;

        /**
        * @brief subscribeToMediaInformationCounter subscribes to receive media information counter events
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[out] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is successful
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToMediaInformationCounter(onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

        /**
        * @brief unsubscribe unsubscribes the subscription
        * @param[in] subscriptionId client ID for the subscription
        * @return Result of the operation:
        * - Types::RESULT_OK if the unsubscription is successful
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result unsubscribe(uint32_t subscriptionId) = 0;
    protected:
        ~IMediaManager(){}
    };

    /**
    * @brief The IRemoteManager class provides the methods to control the printer remotely.
    * @details A full explanation for the RemoteManager use cases can be found inside it user manual \link page_remoteManager page.\endlink
    */
    class IRemoteManager
    {
    public:
        class IReprintSettings;
        /**
        * @brief The result of calling this API is that the printer starts the mechanics and heaters. This is very useful when the application has to send multiple jobs.
        * @return Result of the operation:
        * - Types::RESULT_OK
        * - Types::RESULT_ERROR
        * - Types::RESULT_ERROR_PRINTER_BUSY
        * - Types::RESULT_ERROR_CONNECTION
        * - Types::RESULT_NOT_SUPPORTED
        */
        virtual Types::Result prepareToPrint() = 0;

        /**
        * @brief The Form Feed and Cut functionality can be used to cut the taped end of the paper while installing a new roll or otherwise. This is helpful in trimming the leading edge of the paper if it is damaged or not straight.
        * @return Result of the operation:
        * - Types::RESULT_ERROR_CONNECTION
        * - Types::RESULT_ERROR_NO_MEDIUM_LOADED
        * - Types::RESULT_OK
        * - Types::RESULT_NOT_SUPPORTED
        */
        virtual Types::Result formFeedAndCut() = 0;

        /**
        * @brief starts an internal printer calibration on printer. If the function call succeeds, it returns a Job ID for the new calibration process. Before triggering this call make sure the Printer has all the consumables like Media, Ink.
        * @details Note: For few of HP Designjet printers, triggerCalibration type “ADVANCE” is not supported. Please use triggerAdvanceCalibration api to acheive the same. Please refer the Printer Description.pdf document for more product specific details.
        * @param[in] calibrationType input parameter with a tCalibrationType value.
        * @param[out] jobStatusUUID Job UUID char array. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenJobStatusUUID length of the former parameter jobStatusUUID in bytes.
        * @return Result of the operation:
        * - Types::RESULT_ERROR_CONNECTION
        * - Types::RESULT_ERROR
        * - Types::RESULT_OK
        * - Types::RESULT_NOT_SUPPORTED
        */
        virtual Types::Result triggerCalibration(Types::CalibrationType calibrationType, char **jobStatusUUID, size_t &lenJobStatusUUID) = 0;

        /**
        * @brief starts an media calibration on printer. If the function call succeeds, it returns a Job ID for the new calibration process.
        * @param[in] destinationType defines the possible destinations for media advance calibration.
        * @param[out] jobStatusUUID Job status of the calibration process.\n
        * In case of error, this output value is undefined.
        * @param[out] lenJobStatusUUID length in bytes of the jobStatusUUID parameter.
        * @return Result of the operation:
        * - Types::RESULT_ERROR_CONNECTION
        * - Types::RESULT_ERROR
        * - Types::RESULT_OK
        * - Types::RESULT_NOT_SUPPORTED
        */
        virtual Types::Result triggerAdvanceCalibration(Types::CalibrationDestinationType destinationType, char **jobStatusUUID, size_t &lenJobStatusUUID) = 0;

        /**
        * @brief retrieves the status from all the jobs stored in the printer.
        * @param[out] jobStatusInfoXml  char array in XML format with the jobs status information.\n
        * See the following \link section_get_job_status_list reference\endlink.\n
        * This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenJobStatusInfoXml length in bytes of the jobStatusInfoXml parameter.
        * @return Result of the operation:
        * - Types::RESULT_ERROR_MEMORY
        * - Types::RESULT_ERROR_CONNECTION
        * - Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        * - Types::RESULT_ERROR if there was any other error.
        * - Types::RESULT_OK
        * - Types::RESULT_NOT_SUPPORTED
        */
        virtual Types::Result getJobStatusList(char **jobStatusInfoXml, size_t &lenJobStatusInfoXml) = 0;

        /**
        * @brief wakes up the printer in case the printer is in Energy Saving Mode
        * @details
        *  - NOTE*: This API will return success if the printer is reachable and it supports it.
        *  - NOTE**: Please wait for 15secs before sending any other API requests. This is to allow the Printer to get into the Ready state from Energy Savings state.
        *
        * @return Result of the operation:
        * - Types::RESULT_ERROR_CONNECTION
        * - Types::RESULT_ERROR
        * - Types::RESULT_OK
        * - Types::RESULT_NOT_SUPPORTED
        */
        virtual Types::Result wakePrinter() = 0;

        /**
        * @brief retrieves the status of a given job. Each print job should have a unique Job ID in UUID format. See \link section_get_job_status user manual\endlink
        * @param[in] jobId Id used to select the desired job to get the status information.
        * @param[out] jobStatusInfoXml char array in XML format with the job status information.\n
        * See the following \link section_get_job_status reference\endlink.\n
        * This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenJobStatusInfoXml length in bytes of the jobStatusInfoXml parameter.
        * @return Result of the operation:
        * - Types::RESULT_ERROR_CONNECTION
        * - Types::RESULT_ERROR_EMPTY_RESPONSE
        * - Types::RESULT_ERROR_MEMORY
        * - Types::RESULT_ERROR_INVALID_RESPONSE if there was a problem with the printer response.
        * - Types::RESULT_ERROR if there was any other error.
        * - Types::RESULT_OK
        * - Types::RESULT_NOT_SUPPORTED
        */
        virtual Types::Result getJobStatus(const char *jobId, char **jobStatusInfoXml, size_t &lenJobStatusInfoXml) = 0;

        /**
        * @brief cancels a job, which has been sent to the printer. Using this, we cancel only the job identified by job UUID.
        * @details Note: If the printer has already printed this job this API will fail with error code RESULT_ERROR_ELEMENT_NOT_FOUND.
        * @param[in] jobUUID Job Id of the job being cancelled. See \link page_appendix_UUID_format UUID format.\endlink
        * @return Result of the operation:
        * - Types::RESULT_ERROR_ELEMENT_NOT_FOUND
        * - Types::RESULT_ERROR_CONNECTION
        * - Types::RESULT_OK
        * - Types::RESULT_NOT_SUPPORTED
        */
        virtual Types::Result cancelPrintJob(const char *jobUUID) = 0;

        /**
        * @brief deletes a job from the Job Queue. Using this API we can delete only the job identified by job UUID.
        * @param[in] jobUUID Job Id of the job to be deleted. Refer \link page_appendix_UUID_format Apendix UUID format.\endlink
        * @return Result of the operation:
        * - Types::RESULT_ERROR_ELEMENT_NOT_FOUND
        * - Types::RESULT_ERROR_CONNECTION
        * - Types::RESULT_OK
        * - Types::RESULT_NOT_SUPPORTED
        */
        virtual Types::Result deletePrintJob(const char *jobUUID) = 0;

        /**
        * @brief reprints the job with the given identification
        * @param[in] jobUUID Job Id of the job to be reprinted. Refer \link page_appendix_UUID_format Apendix UUID format.\endlink
        * - Types::RESULT_ERROR_ELEMENT_NOT_FOUND
        * - Types::RESULT_ERROR_CONNECTION
        * - Types::RESULT_OK
        * - Types::RESULT_NOT_SUPPORTED
        */
        virtual Types::Result reprintJob(const char *jobUUID) = 0;

        /**
        * @brief pauses a job, which has been sent to the printer. Using this, we pause only the job identified by job UUID.\n
        * Note: if the job is already in pause state then this API will return HPLFPSDK::Types::RESULT_ERROR_NO_EFFECT.
        * @param[in] jobUUID Job Id of the job to be paused. Refer \link page_appendix_UUID_format Apendix UUID format.\endlink
        * - Types::RESULT_ERROR_NO_EFFECT
        * - Types::RESULT_ERROR_ELEMENT_NOT_FOUND
        * - Types::RESULT_ERROR_CONNECTION
        * - Types::RESULT_OK
        * - Types::RESULT_NOT_SUPPORTED
        */
        virtual Types::Result pausePrintJob(const char *jobUUID) = 0;

        /**
        * @brief resumes a paused job, which has been sent to the printer. Using this, we can resume only the job identified by job UUID.\n
        * Note: if the job is already in resume state then this API will return HPLFPSDK::Types::RESULT_ERROR.
        * @param[in] jobUUID Job Id of the job to be resumed. Refer \link page_appendix_UUID_format Apendix UUID format.\endlink
        * @return Result of the operation:
        * - Types::RESULT_ERROR_ELEMENT_NOT_FOUND
        * - Types::RESULT_ERROR_CONNECTION
        * - Types::RESULT_ERROR
        * - Types::RESULT_OK
        * - Types::RESULT_NOT_SUPPORTED
        */
        virtual Types::Result resumePrintJob(const char *jobUUID) = 0;

        /**
        * @brief resumes a job queue which is in pause state.\n
        * Note: if the job queue is already in resume state then this API will return HPLFPSDK::Types::RESULT_ERROR_NO_EFFECT.
        * @return Result of the operation:
        * - Types::RESULT_ERROR_NO_EFFECT
        * - Types::RESULT_ERROR_CONNECTION
        * - Types::RESULT_OK
        * - Types::RESULT_NOT_SUPPORTED
        */
        virtual Types::Result resumeJobQueue() = 0;

        /**
        * @brief pauses a job queue.\n
        * Note: if the job queue is already in pause state then this API will return HPLFPSDK::Types::RESULT_ERROR_NO_EFFECT.
        * @return Result of the operation:
        * - Types::RESULT_ERROR_NO_EFFECT
        * - Types::RESULT_ERROR_CONNECTION
        * - Types::RESULT_NOT_SUPPORTED
        * - Types::RESULT_OK
        */
        virtual Types::Result pauseJobQueue() = 0;

        /**
        * @brief promotes a job, which has been sent to the printer. Using this API, a specific job can be moved ahead in the Job Queue.
        * @param[in] jobUUID Job Id of the job to be promoted. Refer \link page_appendix_UUID_format Apendix UUID format.\endlink
        * @return Result of the operation:
        * - Types::RESULT_ERROR_ELEMENT_NOT_FOUND
        * - Types::RESULT_ERROR_CONNECTION
        * - Types::RESULT_OK
        * - Types::RESULT_NOT_SUPPORTED
        */
        virtual Types::Result promotePrintJob(const char *jobUUID) = 0;

        /**
        * @brief sets Job accounting ID.
        * @param[in] jobUUID new ID to use in accounting
        * @return Types::RESULT_NOT_SUPPORTED
        */
        virtual Types::Result setJobAccID(const char *jobUUID) = 0;

        /**
        * @brief provides the folder capability and it properties. Not supported in this version.
        * @param[out] folderCapability XML with the capabilities and properties.\n
        * This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.\n
        * NOTE: The function is currently not supported
        * @param[out] lenFolderCapabilities Length of the returned XML in bytes
        * @param [in] AccName accounting name for identification purposes
        * @param [in] Lang language of the returned XML
        * @return Types::RESULT_NOT_SUPPORTED
        */
        virtual Types::Result getFolderCapability(char **folderCapability, size_t &lenFolderCapabilities, const char *AccName, const char *Lang) = 0;

        /**
        * @brief retrieves the spectrophotometer standard used by the printer.
        * @param[out] solStandard XML with the spectrophotometer data.\n
        * This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.\n
        * NOTE: The function is currently not supported
        * @param[out] bufLength length of the returned XML in bytes
        * @return Types::RESULT_NOT_SUPPORTED
        */
        virtual Types::Result getSolStandard(char **solStandard, size_t &bufLength) = 0;

        /**
        * @brief starts a job to calibrate the ink density value.
        * @param[out] jobStatusId ID of the job. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] bufLength length in bytes of the jobStatusId parameter.
        * @return Types::RESULT_NOT_SUPPORTED
        */
        virtual Types::Result triggerInkDensityCalibration(char **jobStatusId, size_t &bufLength) = 0;

        /**
        * @brief getReprintSettingsContainer requests for an object containing reprint setting parameters
        * @details The client is not responsible for the cleaning of JobSettings.\n
        * Instead, the resource of a IReprintSettings object are released by the HPLFKSDK when a new IReprintSettings 
        * container is requested by the client.\n
        * As a consequence, the pointer returned in a previous call will no longer be valid
        * after the next call to this method.
        * @return IReprintSettings object or NULL if unable to create the object
        */
        virtual IReprintSettings* getReprintSettingsContainer() = 0;

        /**
        * @brief reprints the job with the given identification
        * @param[in] jobUuid Job Id of the job to be reprinted. Refer \link page_appendix_UUID_format Apendix UUID format.\endlink
        * @param[in] newJobUuid UUID for the new job. Refer \link page_appendix_UUID_format Apendix UUID format.\endlink
        * @param[in] settings 
        * - Types::RESULT_ERROR_ELEMENT_NOT_FOUND
        * - Types::RESULT_ERROR_CONNECTION
        * - Types::RESULT_OK
        * - Types::RESULT_NOT_SUPPORTED
        */
        virtual Types::Result reprintJobAdvanced(const char *jobUuid, const char *newJobUuid, const IRemoteManager::IReprintSettings *settings) = 0;

    protected:
        ~IRemoteManager(){}
    };

    /**
    * @brief The IInfoManager class
    */
    class IInfoManager
    {
    public:

        enum InfoEventType
        {
            EVENT_PRINTER_STATUS,                   //!< Event raised when the printer status has changed
            EVENT_DRAWER_STATUS,                    //!< Event raised when a drawer status has changed
            EVENT_MEDIA_INPUT_DEVICE_STATUS,        //!< Event raised when a media input device status has changed
            EVENT_MEDIA_OUTPUT_DEVICE_STATUS,       //!< Event raised when a media output device status has changed
            EVENT_ALERT_STATUS,                     //!< Event raised when an alert has changed status
            EVENT_INK_SLOT_GROUP_STATUS,            //!< Event raised when an ink slot group status has changed
            EVENT_INK_SLOT_STATUS,                  //!< Event raised when a media ink slot status has changed
            EVENT_PRINTHEAD_SLOT_STATUS,            //!< Event raised when a printhead slot status has changed
            EVENT_MEDIA_CUTTING_DEVICE_STATUS,      //!< Event raised when a media cutting device status has changed
            EVENT_MAINTENANCE_CARTRIDGE_STATUS,     //!< Event raised when a maintenance cartridge status has changed
            EVENT_LIQUID_TANK_STATUS,               //!< Event raised when a liquid tank status has changed
            EVENT_PREVENTIVE_KIT_STATUS,            //!< Event raised when a preventive kit status has changed
            EVENT_CONDENSATION_COLLECTOR_STATUS,    //!< Event raised when a condensation collector status has changed
            EVENT_WASTE_COLLECTOR_STATUS,           //!< Event raised when a waste collector status has changed
            EVENT_AIRFLOWS_KIT_STATUS            //!< Event raised when a airflows kit status has changed
        };

        enum InfoAlertFilter
        {
            FILTER_SINGLE_ALERT,       //!< Filter for a single alert
            FILTER_OUTSTANDING_ALERTS, //!< Filter in the collection alerts that have the Raised state set as true.
            FILTER_ALL_ALERTS          //!< Filter for any alert
        };

        enum InfoInputDevice
        {
            MEDIA_INPUT_DEFAULT,       //!< Media input not defined
            MEDIA_INPUT_ROLL,          //!< Media input.
            MEDIA_INPUT_ROLL_1,        //!< Roll 1 media input.
            MEDIA_INPUT_ROLL_2,        //!< Roll 2 media input.
            MEDIA_INPUT_ROLL_3,        //!< Roll 3 media input.
            MEDIA_INPUT_ROLL_4,        //!< Roll 4 media input.
            MEDIA_INPUT_ROLL_5,        //!< Roll 5 media input.
            MEDIA_INPUT_ROLL_6,        //!< Roll 6 media input.
            MEDIA_INPUT_MANUAL_SHEET,  //!< manual sheet media input.
            MEDIA_INPUT_SHEET_TRAY_1,  //!< Tray1 media input.
            MEDIA_INPUT_SHEET_TRAY_2,  //!< Tray2 media input.
            MEDIA_INPUT_RIGID,         //!< Rigid media input.
            MEDIA_INPUT_UNKNOWN        //!< unknown
        };

        /**
        * Function pointer to the event callback
        * @param[in] type identifier of the type of event generated
        * @param[in] userData the same userData used in the corresponding subscribe function
        * @param[in] subscriptionId the same identifier of the subscription returned by the corresponding subscribe function.
        * @param[in] newXmlValue char array in XML format with the new status of the element that generated the event.\
        * The corresponding format for this XML depends on the InfoEventType
        * - EVENT_PRINTER_STATUS See the following \link section_printerStatus reference\endlink.
        * - EVENT_DRAWER_STATUS See the following \link section_drawerStatus reference\endlink.
        * - EVENT_MEDIA_INPUT_DEVICE_STATUS See the following \link section_inputDevicesStatus reference\endlink.
        * - EVENT_MEDIA_OUTPUT_DEVICE_STATUS See the following \link section_outputDevicesStatus reference\endlink.
        * - EVENT_ALERT_STATUS See the following \link section_alerts reference\endlink.
        * - EVENT_INK_SLOT_GROUP_STATUS See the following \link section_ink_system_status reference\endlink.
        * - EVENT_INK_SLOT_STATUS See the following \link section_ink_slots reference\endlink.
        * - EVENT_PRINTHEAD_SLOT_STATUS See the following \link section_printheadStatus reference\endlink.\n
        * This allocated memory will be released automatically once the callback returns.
        * @param[in] xmlLength length of the newXmlValue char array in bytes.
        */
        typedef void(*onChangeCallback)(InfoEventType type, void *userData, uint32_t subscriptionId, const char *newXmlValue, int xmlLength);

        /**
        * @brief getPrinterConfiguration retrives the configuration of the printer in XML format.
        * @param[out] printerConfiguration char array in XML format with the printer configuration. See the following \link section_printerConfiguration reference\endlink. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenPrinterConfiguration length of the printerConfiguration char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the printerConfiguration char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getPrinterConfiguration(char **printerConfiguration, size_t &lenPrinterConfiguration) = 0;

        /**
        * @brief getMediaStatus returns the status for all media defined in the printer in XML format.
        * /remark This API is not supported and will be deprecated
        * @param[out] mediaStatus char array in XML format filled in with the status for all medias. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenMediaStatus length of the mediaStatus char array.
        * @return
        * - Types::RESULT_OK (TODO) nowadays it's not already developed.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getMediaStatus(char **mediaStatus, size_t &lenMediaStatus) = 0;

        /**
        * @brief getInkSystemStatus returns the status of the printer inks in XML format.
        * @param[out] inkSystemStatus char array in XML format that contains the status of the printer inks. See the following \link section_ink_system_status reference\endlink. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenInkSystemStatus length of the inkSystemStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the printerConfiguration char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getInkSystemStatus(char **inkSystemStatus, size_t &lenInkSystemStatus) = 0;

        /**
        * @brief getInkSlotGroupStatus returns the status of the specified ink slot group in XML format.
        * @param[in] inkSlotGroupId identifier of the ink slot group. It can be retrieved from the data returned in \link getInkSystemStatus getInkSystemStatus\endlink
        * @param[out] inkSlotGroupStatus char array in XML format that contains the status of the specified ink slot group. See the following \link section_ink_system_status reference\endlink. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenInkSlotGroupStatus length of the inkSystemStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the printerConfiguration char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getInkSlotGroupStatus(uint32_t inkSlotGroupId, char **inkSlotGroupStatus, size_t &lenInkSlotGroupStatus) = 0;

        /**
        * @brief getInkSlotStatus returns the status of the printer inks in XML formats.
        * @param[in] inkSlotId identifier of the ink slot. It can be retrieved from the data returned in \link getInkSystemStatus() getInkSystemStatus\endlink or \link getInkSlotGroupStatus() getInkSlotGroupStatus \endlink
        * @param[out] inkSlotStatus char array in XML format that contains the status of the printer inks. See the following \link section_ink_slots reference\endlink. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenInkSlotStatus length of the inkSystemStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the printerConfiguration char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getInkSlotStatus(uint32_t inkSlotId, char **inkSlotStatus, size_t &lenInkSlotStatus) = 0;

        /**
        * @brief getPrinterStatus retrives the status of the printer in XML format.
        * @param[out] printerStatusInfoXml char array in XML format that contains the status of the printer.\n
        * See the following \link section_printerStatus reference\endlink.\n
        * This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenPrinterStatusInfoXml length of the printerStatusInfoXml char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the printerConfiguration char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getPrinterStatus(char **printerStatusInfoXml, size_t &lenPrinterStatusInfoXml) = 0;

        /**
        * @brief getInkCollectionUnitStatus returns the status of the printer inks in XML format.
        * @param[out] inkCollectionUnitStatusInfoXml char array in XML format that contains the status of the printer inks. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenInkCollectionUnitStatusInfoXml length of the inkCollectionUnitStatusInfoXml char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK (TODO) nowadays it's not already developed.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getInkCollectionUnitStatus(char **inkCollectionUnitStatusInfoXml, size_t &lenInkCollectionUnitStatusInfoXml) = 0;

        /**
        * @brief getDrawersStatus returns the status of every drawer and media input device in XML format.
        * @param[out] drawerStatus char array in XML format that contains the status of the devices. See the following \link section_drawerStatus reference\endlink. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenDrawerStatus length of the drawerStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the drawerStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getDrawersStatus(char **drawerStatus, size_t &lenDrawerStatus) = 0;

        /**
        * @brief getDrawerStatus returns the status of the selected drawer and its media input devices in XML format.
        * @param[in] drawerId Identifier of the drawer. It can be retrieved from the data returned in \link getDrawersStatus getDrawersStatus\endlink
        * @param[out] drawerStatus char array in XML format that contains the status of the selected device.\n
        * See the following \link section_drawerStatus reference\endlink. \n
        * This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenDrawerStatus length of the drawerStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the inputDeviceStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getDrawerStatus(uint32_t drawerId, char **drawerStatus, size_t &lenDrawerStatus) = 0;

        /**
        * @brief getInputDevicesStatus returns the status of every media input device in XML format.
        * @param[out] inputDeviceStatus char array in XML format that contains the status of all the devices. See the following \link section_inputDevicesStatus reference\endlink. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenInputDeviceStatus length of the inputDeviceStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the inputDeviceStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getInputDevicesStatus(char **inputDeviceStatus, size_t &lenInputDeviceStatus) = 0;

        /**
        * @brief getInputDeviceStatus returns the status of the selected media input device in XML format.
        * @param[in] inputDeviceId Identifier of the input device. It can be retrieved from the data returned in \link getInputDevicesStatus getInputDevicesStatus\endlink
        * @param[in] inputDeviceStatus char array in XML format that contains the status of the selected device.\n
        *  See the following \link section_inputDevicesStatus reference\endlink. \n
        *  This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.
        * @param[in] lenInputDeviceStatus length of the inputDeviceStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the inputDeviceStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getInputDeviceStatus(const char *inputDeviceId, char **inputDeviceStatus, size_t &lenInputDeviceStatus) = 0;

        /**
        * @brief getOutputDevicesStatus returns the status of every media output device in XML format.
        * @param[out] outputDeviceStatus char array in XML format that contains the status of all the devices. See the following \link section_outputDevicesStatus reference\endlink. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenOutputDeviceStatus length of the outputDeviceStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the inputDeviceStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getOutputDevicesStatus(char **outputDeviceStatus, size_t &lenOutputDeviceStatus) = 0;

        /**
        * @brief getOutputDeviceStatus returns the status of the selected media output device in XML format.
        * @param[in] outputDeviceId Identifier of the output device. It can be retrieved from the data returned in \link getOutputDevicesStatus getOutputDevicesStatus\endlink
        * @param[out] outputDeviceStatus char array in XML format that contains the status of the selected device.\n
        * See the following \link section_outputDevicesStatus reference\endlink. \n
        * This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenOutputDeviceStatus length of the outputDeviceStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the inputDeviceStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getOutputDeviceStatus(const char *outputDeviceId, char **outputDeviceStatus, size_t &lenOutputDeviceStatus) = 0;

        /**
        * @brief getPrintheadSlotStatus returns the status of all the printhead slots in XML format.
        * @param[out] printheadSlotStatus char array in XML format that contains the status printhead slots.\n
        * See the following \link section_printheadStatus reference\endlink. \n
        * This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenPrintheadSlotStatus length of the printheadSlotStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the inputDeviceStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getPrintheadSlotsStatus(char **printheadSlotStatus, size_t &lenPrintheadSlotStatus) = 0;

        /**
        * @brief getPrintheadSlotStatus returns the status of the selected printhead slot in XML format.
        * @param[in] printheadSlotId Identifier of the printhead slot. It can be retrieved from the data returned in \link getPrintheadSlotsStatus getPrintheadSlotsStatus\endlink
        * @param[out] printheadSlotStatus char array in XML format that contains the status of the selected printhead slot.\n
        * See the following \link section_printheadStatus reference\endlink. \n
        * This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenPrintheadSlotStatus length of the printheadSlotStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the inputDeviceStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getPrintheadSlotStatus(uint32_t printheadSlotId, char **printheadSlotStatus, size_t &lenPrintheadSlotStatus) = 0;

        /**
        * @brief getAlertStatus returns the status of the alarms raised in the printer in XML format.
        * @param[in] filterType indicates if the filter should search for a single alert, any outstanding alert (the alerts currently raised) or any alert
        * @param[in] alertFilter char array that defines the pattern that the returning alerts must comply.
        * @param[out] alertStatus char array in XML format that contains the status of the alerts. See the following \link section_alerts reference\endlink. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenAlertStatus length of the alertStatus char array in bytes units.
        * @return Result of the operation:
        * - Types::RESULT_OK if the alertFilter char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getAlertStatus(InfoAlertFilter filterType, const char *alertFilter, char **alertStatus, size_t &lenAlertStatus) = 0;

        /**
        * @brief subscribeToPrinterStatus subscribes to receive printer status events
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[out] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is succesful
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToPrinterStatus(onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

        /**
        * @brief subscribeAlertStatus subscribes to receive alert events
        * @param[in] alertFilter pattern to identify the alerts to subscribe. The pattern should be a Perl regular expression. An empty string will match every alert.
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[out] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is succesful
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToAlertStatus(const char *alertFilter, onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

        /**
        * @brief subscribeToDrawersStatus subscribes to receive all drawers status events
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[out] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is succesful
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToDrawersStatus(onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

        /**
        * @brief subscribeToDrawerStatus subscribes to receive drawer status events
        * @param[in] drawerId Identifier of the drawer. It can be retrieved from the data returned in \link getDrawersStatus getDrawersStatus\endlink
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[out] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is succesful
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToDrawerStatus(uint32_t drawerId, onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

        /**
        * @brief subscribeToInputDevicesStatus subscribes to receive all input devices status events
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[in] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is succesful
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToInputDevicesStatus(onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

        /**
        * @brief subscribeToInputDeviceStatus subscribes to receive input device status events
        * @param[in] deviceId Identifier of the input device. It can be retrieved from the data returned in \link getInputDevicesStatus getInputDevicesStatus\endlink
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[in] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is succesful
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToInputDeviceStatus(const char *deviceId, onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

        /**
        * @brief subscribeToOutputDevicesStatus subscribes to receive all output devices status events
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[out] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is succesful
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToOutputDevicesStatus(onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

        /**
        * @brief subscribeToOutputDeviceStatus subscribes to receive output device status events
        * @param[in] deviceId Identifier of the output device. It can be retrieved from the data returned in \link getOutputDevicesStatus getOutputDevicesStatus\endlink
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[out] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is succesful
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToOutputDeviceStatus(const char *deviceId, onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

        /**
        * @brief subscribeToInkSystemStatus subscribes to receive every ink slot and ink slot group status events
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[out] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is succesful
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToInkSystemStatus(onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

        /**
        * @brief subscribeToInkSlotGroupStatus subscribes to receive ink slot group status events
        * @param[in] inkSlotGroupId identifier of the ink slot group. It can be retrieved from the data returned in \link getInkSystemStatus getInkSystemStatus\endlink
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[out] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is succesful
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToInkSlotGroupStatus(uint32_t inkSlotGroupId, onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

        /**
        * @brief subscribeToInkSlotStatus subscribes to receive ink slot status events
        * @param[in] inkSlotId identifier of the ink slot . It can be retrieved from the data returned in \link getInkSystemStatus getInkSystemStatus\endlink
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[out] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is succesful
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToInkSlotStatus(uint32_t inkSlotId, onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

        /**
        * @brief subscribeToPrintheadSlotsStatus subscribes to receive all printhead slots status events
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[out] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is succesful
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToPrintheadSlotsStatus(onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

        /**
        * @brief subscribeToPrintheadSlotStatus subscribes to receive printhead slot status events.
        * @param[in] printheadSlotId Identifier of the output device. It can be retrieved from the data returned in \link getPrintheadSlotsStatus getPrintheadSlotsStatus\endlink
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[out] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is succesful
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToPrintheadSlotStatus(uint32_t printheadSlotId, onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

        /**
        * @brief unsubscribe unsubscribes the subscription
        * @param[in] subscriptionId client ID for the supscription
        * @return Result of the operation:
        * - Types::RESULT_OK if the unsubscription is succesful
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result unsubscribe(uint32_t subscriptionId) = 0;

        /**
        * @brief getCuttingDevicesStatus returns the status of all the cutting devices in XML format.
        * @param[out] cuttingDevicesStatus char array in XML format that contains the status of the cutting devices.\n
        * See the following \link section_cuttingDevicesStatus reference\endlink. \n
        * This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenCuttingDevicesStatus length of the cuttingDevicesStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the inputDeviceStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getCuttingDevicesStatus(char **cuttingDevicesStatus, size_t &lenCuttingDevicesStatus) = 0;

        /**
        * @brief getCuttingDeviceStatus returns the status of all the cutting devices in XML format.
        * @param[in] cuttingDeviceId Identifier of the cutting device. It can be retrieved from the data returned in \link getCuttingDevicesStatus getCuttingDevicesStatus\endlink
        * @param[out] cuttingDeviceStatus char array in XML format that contains the status of the cutting devices.\n
        * See the following \link section_cuttingDeviceStatus reference\endlink. \n
        * This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenCuttingDeviceStatus length of the cuttingDevicesStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the inputDeviceStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getCuttingDeviceStatus(uint32_t cuttingDeviceId, char **cuttingDeviceStatus, size_t &lenCuttingDeviceStatus) = 0;

        /**
        * @brief subscribeToCuttingDevicesStatus subscribes to receive all cutting devices status events
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[out] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is succesful
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToCuttingDevicesStatus(onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

        /**
        * @brief subscribeToCuttingDeviceStatus subscribes to receive cutting device status events
        * @param[in] deviceId Identifier of the cutting device. It can be retrieved from the data returned in \link getCuttingDevicesStatus getCuttingDevicesStatus\endlink
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[out] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is succesful
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToCuttingDeviceStatus(uint32_t deviceId, onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

        /**
        * @brief getMaintenanceSystemStatus returns the status of every maintenance component in XML format.
        * @param[out] maintenanceSystemStatus char array in XML format that contains the status of the devices. See the following \link section_maintenanceSystem reference\endlink. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenMaintenanceSystemStatus length of the maintenanceSystemStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the maintenanceSystemStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getMaintenanceSystemStatus(char **maintenanceSystemStatus, size_t &lenMaintenanceSystemStatus) = 0;

        /**
        * @brief getMaintenanceCartridgesStatus returns the status of all maintenance cartridges in XML format.
        * @param[out] maintenanceCartridgesStatus char array in XML format that contains the status of the devices. See the following \link section_maintenanceCartridges reference\endlink. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenMaintenanceCartridges length of the maintenanceCartridgesStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the maintenanceCartridgesStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getMaintenanceCartridgesStatus(char **maintenanceCartridgesStatus, size_t &lenMaintenanceCartridges) = 0;

        /**
        * @brief getMaintenanceCartridgeStatus returns the status of the selected maintenance cartridge in XML format.
        * @param[out] maintenanceCartridgeId Identifier of the maintenance cartridge. It can be retrieved from the data returned in \link getMaintenanceCartridgesStatus getMaintenanceCartridgesStatus\endlink
        * @param[out] maintenanceSystemStatus char array in XML format that contains the status of the devices. See the following \link section_maintenanceCartridges reference\endlink. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenMaintenanceCartridge length of the maintenanceCartridgeStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the maintenanceCartridgeStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getMaintenanceCartridgeStatus(const char* maintenanceCartridgeId, char **maintenanceCartridgeStatus, size_t &lenMaintenanceCartridge) = 0;

        /**
        * @brief getLiquidTanksStatus returns the status of all liquid tanks in XML format.
        * @param[out] liquidTanksStatus char array in XML format that contains the status of the devices. See the following \link section_liquidTanks reference\endlink. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenLiquidTanksStatus length of the liquidTanksStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the liquidTanksStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getLiquidTanksStatus(char **liquidTanksStatus, size_t &lenLiquidTanksStatus) = 0;

        /**
        * @brief getLiquidTanksStatus returns the status of the selected liquid tank in XML format.
        * @param[out] liquidTankId Identifier of the liquid tank. It can be retrieved from the data returned in \link getLiquidTanksStatus getLiquidTanksStatus\endlink
        * @param[out] liquidTanksStatus char array in XML format that contains the status of the device. See the following \link section_liquidTanks reference\endlink. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenLiquidTanksStatus length of the liquidTankStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the liquidTankStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getLiquidTankStatus(const char* liquidTankId, char **liquidTankStatus, size_t &lenLiquidTankStatus) = 0;

        /**
        * @brief getCondensationCollectorsStatus returns the status of all condensation collectors in XML format.
        * @param[out] condensationCollectorsStatus char array in XML format that contains the status of the devices. See the following \link section_condensationCollectors reference\endlink. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenCondensationCollectorsStatus length of the condensationCollectorsStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the condensationCollectorsStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getCondensationCollectorsStatus(char **condensationCollectorsStatus, size_t &lenCondensationCollectorsStatus) = 0;

        /**
        * @brief getCondensationCollectorsStatus returns the status of the selected condensation collector in XML format.
        * @param[out] condensationCollectorId Identifier of the condensation collector It can be retrieved from the data returned in \link getCondensationCollectorsStatus getCondensationCollectorsStatus\endlink
        * @param[out] condensationCollectorStatus char array in XML format that contains the status of the devices. See the following \link section_condensationCollectors reference\endlink. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenCondensationCollectorStatus length of the condensationCollectorStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the condensationCollectorStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getCondensationCollectorStatus(const char* condensationCollectorId, char **condensationCollectorStatus, size_t &lenCondensationCollectorStatus) = 0;

        /**
        * @brief subscribeToMaintenanceCartridgesStatus subscribes to receive maintenance cartridges status events
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[out] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is succesful
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToMaintenanceCartridgesStatus(onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

        /**
        * @brief subscribeToLiquidTanksStatus subscribes to receive liquid tanks status events
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[out] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is succesful
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToLiquidTanksStatus(onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

        /**
        * @brief subscribeToCondensationCollectorsStatus subscribes to receive condensation collectors status events
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[out] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is succesful
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToCondensationCollectorsStatus(onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

        /**
        * @brief getCondensationCollectorsStatus returns the status of all waste collectors in XML format.
        * @param[out] wasteCollectorsStatus char array in XML format that contains the status of the devices. See the following \link section_wasteCollectors reference\endlink. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenCondensationCollectorsStatus length of the wasteCollectorsStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the wasteCollectorsStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getWasteCollectorsStatus(char **wasteCollectorsStatus, size_t &lenWasteCollectorsStatus) = 0;

        /**
        * @brief getCondensationCollectorsStatus returns the status of the selected waste collector in XML format.
        * @param[out] wasteCollectorId Identifier of the waste collector It can be retrieved from the data returned in \link getWasteCollectorsStatus getWasteCollectorsStatus\endlink
        * @param[out] wasteCollectorStatus char array in XML format that contains the status of the devices. See the following \link section_wasteCollectors reference\endlink. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenWasteCollectorStatus length of the wasteCollectorStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the wasteCollectorStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getWasteCollectorStatus(int wasteCollectorId, char **wasteCollectorStatus, size_t &lenWasteCollectorStatus) = 0;

        /**
        * @brief subscribeToCondensationCollectorsStatus subscribes to receive waste collectors status events
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[out] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is succesful
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToWasteCollectorsStatus(onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

        /**
        * @brief getAirflowsKitsStatus returns the status of all airflows in XML format.
        * @param[out] airflowsKitsStatus char array in XML format that contains the status of the devices. See the following \link section_airflowsKits reference\endlink. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenAirflowsKitsStatus length of the airflowsKitsStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the airfowsKitsStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getAirflowsKitsStatus(char **airfowsKitsStatus, size_t &lenAirflowsKitsStatus) = 0;

        /**
        * @brief getAirflowsKitStatus returns the status of the selected airflow in XML format.
        * @param[out] airflowsKitId Identifier of the condensation collector It can be retrieved from the data returned in \link getAirflowsKitsStatus getAirflowsKitsStatus\endlink
        * @param[out] airflowsKitsStatus char array in XML format that contains the status of the devices. See the following \link section_airflowsKits reference\endlink. This allocated memory shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenAirflowsKitStatus length of the airflowsKitStatus char array in bytes.
        * @return Result of the operation:
        * - Types::RESULT_OK if the airflowsKitStatus char array was properly filled in.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getAirflowsKitStatus(const char* airflowsKitId, char **airflowsKitStatus, size_t &lenAirflowsKitStatus) = 0;
        /**
        * @brief subscribeToAirflowsKitsStatus subscribes to receive airflows kits status events
        * @param[in] callback function that will be called when a new event is generated.
        * @param[in] userData pointer to user defined data. It will be returned on every event generated by the subscription.
        * @param[out] subscriptionId if the subscription is successful this will store an ID for the subscription that should be used on the unsubscribe function
        * @return Result of the operation:
        * - Types::RESULT_OK if the subscription is succesful
        * - Types::RESULT_ERROR_NOT_YET_INITIALIZED if any of the internal modules of the SDK has not been properly initilized.
        * - Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        * - Types::RESULT_ERROR_INVALID_PARAMETER if the callback is NULL
        * - Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result subscribeToAirflowsKitsStatus(onChangeCallback callback, void *userData, uint32_t *subscriptionId) = 0;

    protected:
        ~IInfoManager(){}
    };

    /**
    * @brief The IAccountingManager class provides the interface to retreive the job accounting information.
    */
    class IAccountingManager
    {
    public:
        /**
        * @brief getJobAccountingInfo gives the accounting information for a job ID.
        * @param[in] jobId desired jobID, if null or empty then the full job list will be retrieved.
        * @param[out] jobAccountingInfoXml returns the accounting information for the job ID using an char array formatted in XML defined in this \link section_accountingManager_JobAccountingInfo page\endlink. This memory allocation shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenJobAccountingInfoXml length of the jobAccountingInfoXml array in bytes.
        * @return Result of the operation:
        *- Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if the response from the printer could not be parsed properly.
        *- Types::RESULT_ERROR if any of the response fields can not be evaluated.
        *- Types::RESULT_ERROR_EMPTY_RESPONSE if the response from the printer is empty.
        *- Types::RESULT_ERROR_CONNECTION if the printer cannot be connected.
        *- Types::RESULT_OK if the mediaInformation array was properly filled in.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getJobAccountingInfo(const char *jobId, char **jobAccountingInfoXml, size_t &lenJobAccountingInfoXml) = 0;

        /**
        * @brief getJobAccountingInfoByDate returns the accounting information for the jobs included in the date range.
        * @param[in] startDate start date to retrive the job list. It can be NULL or empty.
        * @param[in] endDate end date to take into account for the job list. It can be NULL or empty.
        * @param[out] jobAccountingInfoXml returns the accounting information for the job ID using an char array formatted in XML defined in this \link section_accountingManager_JobAccountingInfo page\endlink. This memory allocation shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenJobAccountingInfoXml length of the jobAccountingInfoXml array in bytes.
        * @return Result of the operation:
        *- Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if the response from the printer could not be parsed properly.
        *- Types::RESULT_ERROR if any of the response fields can not be evaluated.
        *- Types::RESULT_ERROR_EMPTY_RESPONSE if the response from the printer is empty.
        *- Types::RESULT_ERROR_CONNECTION if the printer cannot be connected.
        *- Types::RESULT_OK if the jobAccountingInfoXml array was properly filled in.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getJobAccountingInfoByDate(const char *startDate, const char *endDate, char **jobAccountingInfoXml, size_t &lenJobAccountingInfoXml) = 0;

        /**
        * @brief getJobAccountingInfoByNumber returns the accounting information for the last jobs selected by numberOfJobs.
        * @param[in] numberOfJobs input parameter that indicates the number of the jobs to retrive the accounting information.
        * @param[out] jobAccountingInfoXml returns the accounting information for the last numberOfJobs jobs, using an char array formatted in XML defined in this \link section_accountingManager_JobAccountingInfo page\endlink. This memory allocation shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenJobAccountingInfoXml length of the jobAccountingInfoXml array in bytes
        * @return Result of the operation:
        *- Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if the response from the printer could not be parsed properly.
        *- Types::RESULT_ERROR if any of the response fields can not be evaluated.
        *- Types::RESULT_ERROR_EMPTY_RESPONSE if the response from the printer is empty.
        *- Types::RESULT_ERROR_CONNECTION if the printer cannot be connected.
        *- Types::RESULT_OK if the jobAccountingInfoXml array was properly filled in.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result getJobAccountingInfoByNumber(uint32_t numberOfJobs, char **jobAccountingInfoXml, size_t &lenJobAccountingInfoXml) = 0;
    protected:
        ~IAccountingManager(){}
    };

    /**
    * @brief The IUsageManager class Printer usage includes useful information about global usage during the whole life of the printer,
    * such as media usage and ink usage counters. Please note that, due to the limited accuracy of some sensors, some information does not have a high degree of accuracy.
    */
    class IUsageManager
    {
    public:

        /**
        * @brief getPrinterUsageInfo provides the printer usage information in XML format. See the \link page_usageManager usage manager section.\endlink
        * @param[out] printerUsageInfoXml returns the printer usage information, using an char array formatted in XML. This memory allocation shall be deleted using hplfpsdk_deleteBuffer() interface.\n
        * In case of error, this output value is undefined.
        * @param[out] lenPrinterUsageInfoXml length of the printerUsageInfoXml array in bytes
        * @return Result of the operation:
        *- Types::RESULT_ERROR_MEMORY if there was a problem with the memory allocation.
        *- Types::RESULT_ERROR_INVALID_RESPONSE if the response from the printer could not be parsed properly.
        *- Types::RESULT_ERROR if any of the response fields can not be evaluated.
        *- Types::RESULT_ERROR_EMPTY_RESPONSE if the response from the printer is empty.
        *- Types::RESULT_ERROR_CONNECTION if the printer cannot be connected.
        *- Types::RESULT_OK if the printerUsageInfoXml array was properly filled in.
        *- Types::RESULT_NOT_SUPPORTED if the printer does not support this function.
        */
        virtual Types::Result  getPrinterUsageInfo(char **printerUsageInfoXml, size_t &lenPrinterUsageInfoXml) = 0;
    protected:
        ~IUsageManager(){}
    };

} //namespace HPLFPSDK

#endif
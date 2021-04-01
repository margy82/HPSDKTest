#ifndef SETTINGS_H
#define SETTINGS_H
//////////////////////////////////////////////////////////////////////////////
/*
*
*  @par &copy; Copyright Hewlett-Packard Company, 2000-2011.
*  All rights reserved. Copying or other reproduction of this program except
*  for archival purposes is prohibited without written consent of
*  Hewlett-Packard Company.
* 
*  david.toussaint@hp.com
* 
**/ 
//////////////////////////////////////////////////////////////////////////////

#include "IJobPacker.h"
#include "ISolPacker.h"
#include "IScanPacker.h"
#include "IManagers.h"

namespace HPLFPSDK
{
class IJobPacker::IJobSettings 
{ 
public: 

   /**
     * @brief This method meant to be used for debugging purpose
     * it returns the settings in a readable format
     * @param settings returns an array of chars with the settings information. This allocated memory shall be deleted using hplfpsdk_deleteBuffer interface.
     * @param settingsLength length in bytes of the settings array parameter.
     */
    virtual Types::Result dumpToChar( char **settings, long *settingsLength) = 0;

   /**  
     * @brief Enable disable printing the job in attended mode  
     */ 
    virtual Types::Result setAttendedMode( const Types::BooleanPlusDefault &value ) = 0;

   /**  
     * @brief Job collation  
     */ 
    virtual Types::Result setJobCollate( const Types::JobCollate &value ) = 0;

   /**  
     * @brief Cutter enabled. Note that if media is not cutable this setting is ignored It applies to a job level.  
     */ 
    virtual Types::Result setCutter( const Types::Cutter &value ) = 0;

   /**  
     * @brief Printing order, so the first page gets on top or bottom.
     */ 
    virtual Types::Result setPrintingOrder( const Types::PrintingOrder &value ) = 0;

   /**  
     * @brief User provided tag used to group several jobs, for instance, to label jobs belonging to the same account for billing purposes. Used also for accounting and reporting (i.e. to Fibonacci)  
     */ 
    virtual Types::Result setAccountId( const char *value ) = 0;

   /**  
     * @brief Application Name. The SDK will fill this job setting up with the value + partner ID + SDK name + SDK version.  
     */ 
    virtual Types::Result setApplicationName( const char *value ) = 0;

   /**  
     * @brief Application Unique Identifier. Set the application UUID that will be used to facilitate identification of jobs. 
     */ 
    virtual Types::Result setApplicationUuid( const char *value ) = 0;

   /**  
     * @brief Application Version. Set the application version that will be displayed in the FP and Web. Used also for accounting and reporting (i.e. to Fibonacci)  
     */ 
    virtual Types::Result setApplicationVersion( const char *value ) = 0;

   /**  
     * @brief The Partner ID as provided by the Partners team. It should start with "PID". Used also for accounting and reporting (i.e. to Fibonacci)  
     */ 
    virtual Types::Result setPartnerId( const char *value ) = 0;

   /**  
     * @brief Specifies if the attribute BILLABLE for the job must be set to true or false Used also for accounting (i.e. Beck workflow)  
     */ 
    virtual Types::Result setFMBillable( const Types::BooleanPlusDefault &value ) = 0;

   /**  
     * @brief Sets the FM token to the job Ticket Provider: Beck driver (got it from Beck server)  
     */ 
    virtual Types::Result setFMToken( const char *value ) = 0;

   /**  
     * @brief User provided tag used to group several jobs, for instance, to label jobs belonging to the same project. Used also for accounting and reporting (i.e. to Fibonacci)  
     */ 
    virtual Types::Result setProjectId( const char *value ) = 0;

   /**  
     * @brief Job name  
     */ 
    virtual Types::Result setJobName( const char *value ) = 0;

   /**  
     * @brief Number of copies for a Job, between 1 and 9999. Multiplicative with the surface copies.  
     */ 
    virtual Types::Result setJobCopies( const Types::NumCopies &value ) = 0;

   /**  
     * @brief Time Stamp format supported: YYYYMMDDHHMMSS  
     */ 
    virtual Types::Result setTimeStamp( const char *value ) = 0;

   /**  
     * @brief User name  
     */ 
    virtual Types::Result setUserName( const char *value ) = 0;

   /**  
     * @brief Job UUID set by the application or job creator  
     */ 
    virtual Types::Result setJobUuid( const char *value ) = 0;

   /**  
     * @brief Sets the behavior when printing pages in dual side mode.  
     */ 
    virtual Types::Result setDualSideOrder(const Types::DualSideOrder &value) = 0;

protected:

    virtual ~IJobSettings() {} 
}; 
 
class IJobPacker::IPageSettings 
{ 
public: 

   /**
     * @brief This method meant to be used for debugging purpose
     * it returns the settings in a readable format
     * @param settings returns an array of chars with the settings information. This allocated memory shall be deleted using hplfpsdk_deleteBuffer interface.
     * @param settingsLength length in bytes of the settings array parameter.
     */
    virtual Types::Result dumpToChar( char **settings, long *settingsLength) = 0;

   /**
     * @brief This method is used to program selectors in the page settings
     * Selectors are used by the printer firmware to choose the printmode used for printing
     * each printmode corresponds to a set of keyXvalue pairs 
     * sets of keyXvalue pairs correponding to each printmode can be obtained with the IMediaManager::getSupportedPrintmode
     */
    virtual Types::Result setSelector(const char *key, const char *value) = 0;
 
   /**  
     * @brief Defines how to deal with borderless method  
     */ 
    virtual Types::Result setBorderlessMethod( const Types::BorderlessMethod &value ) = 0;

   /**  
     * @brief Physical bottom printer margin to be applied by the printing process. A printer may allow different margin configurations (e.g. full bleed i.e. 0mm, 5mm)  
     */ 
    virtual Types::Result setBottomMargin(const Types::MetricDistance &value) = 0;

    /**
    * Sets the value of Copies
    * Number of copies of this surface, between 1 and 9999. This should be 1 if JobCollate is on.
    *
    * @param value the value for the setting
    * @return whether the setting has been set or not
    */
    virtual Types::Result setCopies(const Types::NumCopies &value) = 0;

   /**  
     * @brief Color Mode. This setting reflects the ink supplies to be used on the printing process.
     */ 
    virtual Types::Result setColorMode( const Types::ColorMode &value ) = 0;

   /**  
     * @brief Page dry time mode  
     */ 
    virtual Types::Result setDryTimeMode( const Types::DryTimeMode &value ) = 0;

   /**  
     * @brief Dual side.  
     */ 
    virtual Types::Result setDualSide( const Types::DualSide &value ) = 0;

   /**  
     * @brief Duplex. This setting is intended to be used only on some multi function printers that can turn the page over automatically.
     */ 
    virtual Types::Result setDuplex( const Types::BooleanPlusDefault &value ) = 0;

   /**  
     * @brief Page economode, to select print mode  
     */ 
    virtual Types::Result setEconomode( const Types::Economode &value ) = 0;

   /**  
     * @brief Efficiency mode.  
     */ 
    virtual Types::Result setEfficiencyMode( const Types::EfficiencyMode &value ) = 0;

   /**  
     * @brief Extended PrintMode setting. Some HP Printers accepts extended printmodes settings to index them.  
     */ 
    virtual Types::Result setExtendedPM( const Types::ExtendedPM &value ) = 0;

   /**  
     * @brief Extra Passes printmode selector  
     */ 
    virtual Types::Result setExtraPasses( const Types::ExtraPasses &value ) = 0;

   /**  
     * @brief Folder specific folding style when FoldingStyle is Standard 0: Do not fold 1: User Defined 2: Folder Selected 3: Stack 4 - 255: Reserved, Do Not Use 256 - 65535: Use freely  
     */ 
    virtual Types::Result setStandardFoldingStyle( const int32_t &value ) = 0;

   /**  
     * @brief Folding Style: User Defined or Custom  
     */ 
    virtual Types::Result setFoldingStyle( const Types::FoldingStyle &value ) = 0;

   /**  
     * @brief Gloss Enhancer.  
     */ 
    virtual Types::Result setGlossEnhancer( const Types::GlossEnhancer &value ) = 0;

   /**  
     * @brief High Speed.  
     */ 
    virtual Types::Result setHighSpeed( const Types::HighSpeed &value ) = 0;

   /**  
     * @brief InkDensity level to be applied.  
     */ 
    virtual Types::Result setInkDensity( const Types::InkDensity &value ) = 0;

   /**  
     * @brief InkDensity level to be applied (Side B).  
     */ 
    virtual Types::Result setInkDensityB( const Types::InkDensity &value ) = 0;

   /**  
     * @brief Physical left printer margin to be applied by the printing process. A printer may allow different margin configurations (e.g. full bleed i.e. 0mm, 5mm)  
     */ 
    virtual Types::Result setLeftMargin( const Types::MetricDistance &value ) = 0;

   /**  
     * @brief Margins layout defining what to do on the image that might be in the margins, whether to printed shifting it or clipping  
     */ 
    virtual Types::Result setMarginLayout( const Types::MarginLayout &value ) = 0;

   /**  
     * @brief Margins types which define the default margins that the pritner would apply  
     */ 
    virtual Types::Result setMarginType( const Types::MarginSetting &value ) = 0;

   /**  
     * @brief Horizontal content alignment used when switching to a source with paper of a different width  
     */ 
    virtual Types::Result setAutomaticContentAlignment( const Types::ContentAlignment &value ) = 0;

   /**  
     * @brief Maximum detail printmode selector  
     */ 
    virtual Types::Result setMaxDetail( const Types::MaxDetail &value ) = 0;

   /**  
     * @brief String (32 chars) in quotes (Pending to implement in Drivers if required)  
     */ 
    virtual Types::Result setMediaCategory( const char *value ) = 0;

   /**  
     * @brief Specifies the destination for this printed surface once printed.  
     */ 
    virtual Types::Result setMediaDestination( const Types::MediaDestination &value ) = 0;

   /**  
     * @brief Media ID as provided by printer interface, identifies a media for any DJ printer model  
     */ 
    virtual Types::Result setMediaId( const char *value ) = 0;

   /**  
     * @brief Specifies the source from which the media will be fed into the printer for printing. It corresponds to the PJL MEDIASORCE setting. Not setting the MediaSource is different from selecting "AUTO". If the media source is not specified, some printer models may decide to behave like if AUTO was sent, others may decide to select only one of the sources, depending on build or run time configurations.  
     */ 
    virtual Types::Result setMediaSource( const Types::MediaSource &value ) = 0;

   /**  
     * @brief Algorithm used for automatic roll switch  
     */ 
    virtual Types::Result setAutomaticRollSwitchPolicy( const Types::RollSwitchPolicy &value ) = 0;

   /**  
     * @brief Surface length; in the case of printing, this is the length of the physical page being printed. Determines the length of media cut by the cutter if printing from a roll or indicates the sheet length if printing from cut sheets. In the case of ripping to save to file, this is the size of the page to be generated.  
     */ 
    virtual Types::Result setLength( const Types::MetricDistance &value ) = 0;

   /**  
     * @brief Surface width; in the case of printing, this is the width of the physical page being printed. Equal to the roll width if printing from a roll or to the sheet width if printing from cut sheets. In the case of ripping to save to file, this is the size of the page to be generated.  
     */ 
    virtual Types::Result setWidth( const Types::MetricDistance &value ) = 0;

   /**  
     * @brief Use selectable pretreatmentlevel  
     */ 
    virtual Types::Result setPreTreatementLevel( const int32_t &value ) = 0;

   /**  
     * @brief Print the whole surface or only the imageable area. Some printer might restrict to remove only top/bottom  
     */ 
    virtual Types::Result setPrintArea( const Types::PrintArea &value ) = 0;

   /**  
     * @brief Page print quality, to select print mode  
     */ 
    virtual Types::Result setPrintQuality( const Types::PrintQuality &value ) = 0;

   /**  
     * @brief Intent to be used by the printer when the transport space is not device, e.g. sRGB. likely to be RELATIVE_COLORIMETRIC. Don't change it unless you know what you are doing!
     */ 
    virtual Types::Result setOutputRenderIntent( const Types::RenderIntent &value ) = 0;

   /**  
     * @brief Page print mode: Color, Grayscale, pure black and white. Different from the rendering render mode, in the future it probably needs to have a different type since the render mode for printing is different.
     */ 
    virtual Types::Result setRenderMode( const Types::RenderMode &value ) = 0;

   /**  
     * @brief Sets the original raster color space per page. This settings allows to the printer to know when to apply the ICC profile. In some languages is used to populate PJL COLORSPACE 
     */ 
    virtual Types::Result setColorSpace( const Types::ColorSpace &value ) = 0;

   /**  
     * @brief Page rendering resolution  
     */ 
    virtual Types::Result setRenderingResolution( const Types::RenderingResolution &value ) = 0;

   /**  
     * @brief Specifies the Resolution Enhancement Technology (RET). Aplied for CAD print modes. If not defined, the default value (OFF) is used.
     */ 
    virtual Types::Result setRetMode( const Types::RetMode &value ) = 0;

   /**  
     * @brief Physical right printer margin to be applied by the printing process. A printer may allow different margin configurations (e.g. full bleed i.e. 0mm, 5mm)  
     */ 
    virtual Types::Result setRightMargin( const Types::MetricDistance &value ) = 0;

   /**  
     * @brief Physical top printer margin to be applied by the printing process. A printer may allow different margin configurations (e.g. full bleed i.e. 0mm, 5mm)  
     */ 
    virtual Types::Result setTopMargin( const Types::MetricDistance &value ) = 0;

   /**  
     * @brief Unidirectional printmode selector  
     */ 
    virtual Types::Result setUnidirectional( const Types::Unidirectional &value ) = 0;

   /**  
     * @brief White Mode.  
     */ 
    virtual Types::Result setWhiteMode( const Types::WhiteMode &value ) = 0;

   /**  
     * @brief White Opacity level specifies the InkDensity level to be applied to White ink. Initial definition expects value between 0 and 100.  
     */ 
    virtual Types::Result setWhiteOpacity( const int32_t &value ) = 0;

   /**  
     * @brief Enables/disables the vertical trimmer feature. Used for models with vertical trimmer Default value is OFF  
     */ 
    virtual Types::Result setYCutter( const Types::YCutter &value ) = 0;

    /**
    * @brief Sets the value of WhiteShrink algorithm status.
    * Indicates whether the white shrink algorithm shall be executed for the given page or not
    *
    * @param value the value for the setting can be WHITESHRINK_ENABLE or WHITESHRINK_DISABLE
    * @return RESULT_OK if the page setting has been set.
    *         RESULT_NOT_SUPPORTED if the page setting is not supported on this printer model.
    */
    virtual Types::Result setWhiteShrink(const Types::WhiteShrink &value) = 0;

    /**
    * @brief Sets the value of WhiteShrinkPixelsAmount
    * Number of pixels to shrink in the white plane by the white shrink algorithm
    *
    * @param value the value for the setting
    * @return RESULT_OK if the page setting has been set.
    *         RESULT_NOT_SUPPORTED if the page setting is not supported on this printer model.
    */
    virtual Types::Result setWhiteShrinkPixelsAmount(const uint32_t &value) = 0;

    /**
    * @brief Sets the value of WhiteShrinkProtectPixelsAmount
    * In case there are several thin lines or letters in white plane, thinner than the specified shrink pixels,
    * The algorithm will protect the skeleton of this content, to avoid them to disappear.
    * The skeleton is the center 1 or 2 pixels of each connected component.
    *
    * @param value the value for the setting
    * @return RESULT_OK if the page setting has been set.
    *         RESULT_NOT_SUPPORTED if the page setting is not supported on this printer model.
    */
    virtual Types::Result setWhiteShrinkProtectPixelsAmount(const uint32_t &value) = 0;

    /**
    * @brief Sets the value of UseNonWhiteInfo
    * If false all pixels in white plane are eligible to be shrunk,
    * If true only pixels that have a non 0 value in any of non-white planes are eligible to be shrunk
    * In other words, if true, the shrink algorithm is only applied to those pixels that has color (CMYK) information.
    *
    * @param value should be true to use the rest of the colored layers information of false for not using them.
    * @return RESULT_OK if the page setting has been set.
    *         RESULT_NOT_SUPPORTED if the page setting is not supported on this printer model.
    */
    virtual Types::Result setWhiteShrinkUseNonWhiteInfo(const bool &value) = 0;

    /**
    * @brief Sets the value of Overcoat
    *
    * @param value 
    * @return RESULT_OK if the page setting has been set.
    *         RESULT_NOT_SUPPORTED if the page setting is not supported on this printer model.
    */
    virtual Types::Result setOvercoat(const Types::Overcoat &value) = 0;

    /**
    * @brief Sets the expected thickness of the media for the page in 1/3600 of inch. 
    *
    * @param value
    * @return RESULT_OK if the page setting has been set.
    *         RESULT_NOT_SUPPORTED if the page setting is not supported on this printer model.
    */
    virtual Types::Result setThickness(const HPLFPSDK::Types::MetricDistance &value) = 0;

    /**
    * @brief Indicates which edge will be used when flipping the page in dual side jobs
    *
    * @param value
    * @return RESULT_OK if the page setting has been set.
    *         RESULT_NOT_SUPPORTED if the page setting is not supported on this printer model.
    */
    virtual Types::Result setFlipEdge(const Types::FlipEdge &value) = 0;

protected:

    virtual ~IPageSettings() {}
}; 

/**
* @brief The IScanSettings provides the settings required to precisely define the scan job.
* All the settings are optional and the support and accepted values of any single setting is defined in the getScannerCapabilities() API.
*/
class IScanPacker::IScanSettings
{
public:
    /**
    * @brief Sets the intent of the scan.
    */
    virtual Types::Result setScanIntent(Types::ScanIntent value) = 0;

    /**
    * @brief Adds a new region to scan
    * @param[in] width Width of the scan region.
    * @param[in] length Length of the scan region.
    * @param[in] horizontalOffset Horizontal distance from the top-left origin point. Expressed in the coordinate space. the offset + width MUST be lesser or equal to the maximum width supported by the scanner in getScannerCapabilities().
    * @param[in] verticalOffset Vertical distance from the top-left origin point. Expressed in the coordinate space. the offset + length MUST be lesser or equal to the maximum length supported by the scanner in getScannerCapabilities().
    * @param[in] units Units of the scan region. The only value supported is Types::LENGTH_UNIT_300THINCH, that is equivalent to 1/300 of an inch.
    */
    virtual Types::Result addScanRegion(size_t width, size_t length, size_t horizontalOffset, size_t verticalOffset, Types::LengthUnits units = Types::LENGTH_UNIT_300THINCH) = 0;

    /**
    * @brief Sets the document format.
    */
    virtual Types::Result setDocumentFormat(Types::ScanDocumentFormat value) = 0;

    /**
    * @brief Sets the content of the scan. If the intent is set, this setting can be ignored.
    */
    virtual Types::Result setContentType(Types::ScanContentType value) = 0;

    /**
    * @brief Sets the source of the scan
    */
    virtual Types::Result setInputSource(Types::ScanInputSource value) = 0;

    /**
    * @brief Some scanners having a larger scannable area such as A3 may have trouble with the orientation
    * of the smaller sized scans depending on how the media is positioned on the input source . For example,
    * user can place a Letter-sized media on an A3 size scanbed in two different orientations - the long edge
    * feed or the short edge feed. If the scanner is unable to edge detect, it is likely that the scanner
    * produces a final image with the wrong orientation. Client can mention the feed direction of the media
    * to avoid getting the final image in the wrong orientation.
    * Note that the client SHOULD take into consideration the feed direction while passing the Width and Height
    * of the scan area. The Width in a SCAN_FEED_DIRECTION_LONG_EDGE scan would be the Height in a
    * SCAN_FEED_DIRECTION_SHORT_EDGE scan and viceversa
    */
    virtual Types::Result setFeedDirection(Types::ScanFeedDirection value) = 0;

    /**
    * @brief Sets the horizontal resolution in dots per inch
    */
    virtual Types::Result setHorizontalResolution(uint32_t value) = 0;

    /**
    * @brief Sets the vertical resolution in dots per inch
    */
    virtual Types::Result setVerticalResolution(uint32_t value) = 0;

    /**
    * @brief Sets the color mode and bits depth
    */
    virtual Types::Result setColorMode(Types::ScanColorMode value) = 0;

    /**
    * @brief Sets the color autodetection mode
    */
    virtual Types::Result setColorAutodetectionMode(Types::ScanColorAutodetectionMode value) = 0;

    /**
    * @brief Sets the color space
    */
    virtual Types::Result setColorSpace(Types::ScanColorSpace value) = 0;

    /**
    * @brief Scanners usually have a white background. Some scanners can mechanically switch to a black background by removing the white stripe so that no background light is reflected back to the image sensor. Clients can enable black background by setting this field to ‘true’.
    */
    virtual Types::Result setBlackBackground(bool value) = 0;

    /**
    * @brief This value can be set if the scanner supports special media processing. Some media (paper or not) may require special handling.
    */
    virtual Types::Result setMediaType(Types::ScanMediaType value) = 0;

    /**
    * @brief Indicates which CCD color channel to use for grayscale and monochrome scanning. It can also be a mix of all three channels.
    */
    virtual Types::Result setCcdChannel(Types::ScanCcdChannel value) = 0;

    /**
    * @brief This is used when the ColorMode is set to SCAN_COLOR_MODE_BLACK_AND_WHITE_1.
    */
    virtual Types::Result setBinaryRendering(Types::ScanBinaryRendering value) = 0;

    /**
    * @brief adjusts the threshold level for binary monochrome rendering.
    */
    virtual Types::Result setBinaryRenderingThreshold(int32_t value) = 0;

    /**
    * @brief Duplex mode can be requested if the scanner has hardware duplexer.
    */
    virtual Types::Result setDuplex(bool value) = 0;

    /**
    * @brief Enables or disables the multipick detection support
    */
    virtual Types::Result setMultipickDetection(bool value) = 0;

    /**
    * @brief Multipick detection can be ignored for the first sheet alone in an ADF scan job. This Boolean setting is valid only if MultipickDetection is set to true. This setting is needed for the case where a multipick error occurs,
    * and the user wants to resolve by ignoring the error on that page. The user reloads the page, and SW submits a new job with this setting set to true
    */
    virtual Types::Result setMultipickDetectionIgnoreFirstPage(bool value) = 0;

    /**
    * @brief Prior to scanning, the device front panel can show a list of options (off, ignore next, ignore all, cancel etc.,) to the user on how to handle the multipick error.
    * Setting this Boolean to true will allow device to show the user options. This setting is valid if MultipickDetection is set to true.
    */
    virtual Types::Result setShowMultipickResolveDialog(bool value) = 0;

    /**
    * @brief Some scanners have the need to ignore multipick detection for a certain length of the sheet in the Y-axis.
    * For example, documents scanned with a sticky note should not be reported as multipicks. This length is defined in coordinates specified by the coordinate space
    */
    virtual Types::Result setMultipickExclusionLength(uint32_t value) = 0;

    /**
    * @brief If the ADF is able to detect and pick a predetermined number of pages, the client can specify how many pages to scan.
    */
    virtual Types::Result setNumberOfPages(uint32_t value) = 0;

    /**
    * @brief If set to true, the scanner should deskew the image, and crop to the detected edges.
    */
    virtual Types::Result setAutoCrop(bool value) = 0;

    /**
    * @brief When Auto-Exposure is set to true, the device SHOULD automatically adjust the histogram of the scanned image for a better viewing experience and provide the histogram-adjusted image to the client.
    * If the ColorMode is set to SCAN_COLOR_MODE_BLACK_AND_WHITE_1, AutoExposure is implemented as auto threshold.
    */
    virtual Types::Result setAutoExposure(bool value) = 0;

    /**
    * @brief Moire’ patterns can occur in scanned images when scanning halftoned or printed images. Some scanners have the capability to de-screen these patterns through a series of algorithms applied to the scanned data.
    * This Boolean setting tells the scanner if de-screening should be performed.
    */
    virtual Types::Result setDeScreen(bool value) = 0;

    /**
    * @brief Stored job requests are scan job requests sent to the scanner along with a job name to identify the request and an optional PIN to reserve the job.
    * The job request is stored on the scanner without actually moving the scan bar. The actual scan job is started when user chooses the job name at the scanner
    * control panel from the list of stored job requests and activates the stored job request by also keying in the PIN if sent by the client.
    * With stored scan job requests, the documents are always with the user and hence the documents and the contents are safeguarded.
    * @param[in] jobName Name of the job
    * @param[in] pin PIN selected. It should be an alphanumeric string. Admitted characters: a-z, A-Z and 0-9
    */
    virtual Types::Result setStoredJobRequest(const char *jobName, const char *pin = nullptr) = 0;

    /**
    * @brief Device can detect blank scan pages. If a blank page is detected, the page should still be returned to the client.
    */
    virtual Types::Result setBlankPageDetection(bool value) = 0;

    /**
    * @brief Device can detect blank scan pages and ignore them from sending them to the destination.
    * When blank pages are detected by scanners that do not buffer the scan data, the scanner may wait for a longer time before sending the next page.
    */
    virtual Types::Result setBlankPageDetectionAndRemoval(bool value) = 0;

    /**
    * @brief Defines the percentage of blank pixels that are allowed before the page is considered blank.
    * This element is only valid if BlankPageDetection or BlankPageDetectionAndRemoval is specified.
    */
    virtual Types::Result setBlankPageSensitivity(int32_t value) = 0;

    /**
    * @brief Defines the percentage of color pixels that are allowed out of the entire image before categorizing the image as color.
    * This is valid only when ColorMode is not set.
    */
    virtual Types::Result setColorSensitivity(int32_t value) = 0;

    /**
    * @brief Defines how far from zero the chroma values of a pixel are allowed before categorizing the pixel as color.
    * This is valid only when ColorMode is not set.
    */
    virtual Types::Result setColorRange(int32_t value) = 0;

    /**
    * @brief This is used to adjust the brightness of the image. Min-Max ranges and default value are defined in getScanCapabilities().
    * Lower values (than normal) give darker images; higher values give brighter images.
    */
    virtual Types::Result setBrightness(int32_t value) = 0;

    /**
    * @brief Lower numbers produce higher quality (at the expense of less compression). The absence of this field means that the
    * scanner can decide the best compression/image-quality tradeoff, based on the intent (and/or other parameters). A value of 0
    * denotes the best image quality. This would mean that clients can do post-processing on the scanner output. Any value greater
    * than 0 will produce a final image not intended to be processed by the client.
    */
    virtual Types::Result setCompressionFactor(int32_t value) = 0;

    /**
    * @brief For adjusting the contrast. Min-Max ranges and default value are defined in Scan Capabilities.
    * Lower values (than normal) generate less contrast; higher values generate more contrast.
    */
    virtual Types::Result setContrast(int32_t value) = 0;

    /**
    * @brief the gamma value g used in the transform y=x^(1/g); Min-Max ranges and default value are defined in getScanCapabilities().
    */
    virtual Types::Result setGamma(int32_t value) = 0;

    /**
    * @brief The inflection point of image "highlights"; lower values lighten highlights.
    */
    virtual Types::Result setHighlight(int32_t value) = 0;

    /**
    * @brief The inflection point of image "shadows"; lower values darken shadows.
    */
    virtual Types::Result setShadow(int32_t value) = 0;

    /**
    * @brief Defines the level of noise removal.
    */
    virtual Types::Result setNoiseRemoval(int32_t value) = 0;

    /**
    * @brief Adjusts the sharpening level.
    */
    virtual Types::Result setSharpen(int32_t value) = 0;

    /**
    * @brief Enables the auto deskew.
    */
    virtual Types::Result setAutoDeskew(bool value) = 0;

    /**
    * @brief Removes the background color.
    */
    virtual Types::Result setBackgroundColorRemoval(bool value) = 0;

    /**
    * @brief Removes background noise.
    */
    virtual Types::Result setBackgroundNoiseRemoval(bool value) = 0;

    /**
    * @brief Inverts blueprint.
    */
    virtual Types::Result setBlueprintInversion(bool value) = 0;

    /**
    * @brief Sets the media as translucent.
    */
    virtual Types::Result setTranslucentMedia(bool value) = 0;

    /**
    * @brief Scanners might be able to scan additional area at both edges of the sheet in the direction of scan.
    * This additional scan area could be used for improving certain auto-X features supported by the scanner like
    * auto-crop, auto-exposure, DeScreen etc., This setting takes a boolean value. If this setting is set to true,
    * the scanner will go into overscan mode and can allow scan jobs for a height that is more than the MaxHeight value.
    * This setting may increase the height of the scan output by the OverscanLength mentioned in the ScannerCapabilities
    * for each edge supporting overscan. (i.e, if scanner supports overscans on both top and bottom edges, the new
    * height while scanning through the Y-axis becomes Height + OverscanLengthSupport * 2).
    */
    virtual Types::Result setOverscan(bool value) = 0;

    /**
    * @brief Though a scan job ID is generated by the device, the remote scan client may generate a unique identifier
    * that can be used across all applications to track the job from an end-to-end solution perspective. This allows
    * tracking of the job from its source, through intermediaries, and ultimately to its final destination, as well
    * as for accounting/auditing purposes.
    * @return RESULT_OK if the job UUID could be set
    *         RESULT_ERROR_PARAM_SIZE_OUT_OF_RANGE if the UUID has an invalid length
    */
    virtual Types::Result setJobUuid(const char *value) = 0;

    /**
    * @brief Sets the current user name
    */
    virtual Types::Result setUserName(const char *value) = 0;

    /**
    * @brief Sets the current user domain
    */
    virtual Types::Result setUserDomain(const char *value) = 0;

    /**
    * @brief Authentication token
    */
    virtual Types::Result setAuthenticationToken(const char *value) = 0;

    /**
    * @brief Machine name.
    */
    virtual Types::Result setMachineName(const char *value) = 0;

    /**
    * @brief The name of the application that initiates the scan job
    */
    virtual Types::Result setApplicationName(const char *value) = 0;

    /**
    * @brief Additional user data for job accounting.
    * @return RESULT_OK if the data could be added
    *         RESULT_ERROR_PARAM_SIZE_OUT_OF_RANGE if any of the inputs has an invalid length
    *         RESULT_ERROR_TOO_MANY_ELEMENTS if the maximum data limit (16 elements) has been reached
    */
    virtual Types::Result addKeyValuePair(const char *key, const char *value) = 0;

protected:

    virtual ~IScanSettings() {}
};

class IRemoteManager::IReprintSettings
{
public:
    /**
    * @brief Set the number of copies.
    */
    virtual Types::Result setNumCopies(uint16_t numCopies) = 0;

    /**
    * @brief Add a new page to reprint. If there are no pages, the reprint will reprint the entire job.
    */
    virtual Types::Result addPage(uint64_t pageId) = 0;

    /**
    * @brief Set the media source of the job. If not set, the job will use the same input source
    * as the original job
    */
    virtual Types::Result setMediaSource(Types::MediaSource source) = 0;

    /**
    * @brief Set the media destination of the job. If not set, the job will use the same output source
    * as the original job
    */
    virtual Types::Result setMediaDestination(Types::MediaDestination destination) = 0;

    /**
    * @brief If the access control is enabled in the printer, the job token is required to reprint.
    */
    virtual Types::Result setJobToken(const char *jobToken) = 0;

    /**
    * @brief Sets the user name of the job. Only valid if the job token is provided.
    */
    virtual Types::Result setUserName(const char *userName) = 0;

    /**
    * @brief Sets the project ID of the job. Only valid if the job token is provided.
    */
    virtual Types::Result setProjectId(const char *projectId) = 0;

    /**
    * @brief Sets the account ID of the job. Only valid if the job token is provided.
    */
    virtual Types::Result setAccountId(const char *accountId) = 0;

    /**
    * @brief Sets a comment for the job. Only valid if the job token is provided.
    */
    virtual Types::Result setComment(const char *comment) = 0;

    /**
    * @brief Sets if the job should be billable. Only valid if the job token is provided.
    */
    virtual Types::Result setBillable(bool billable) = 0;
};


}
#endif 

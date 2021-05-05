#include <iostream>
#include <string>
#include "IHplfpsdk.h"

using namespace std;

string ret;
extern "C" __declspec(dllexport) const char* GetSupplies(unsigned char* ip, unsigned char* pn)
{
    try
    {
        char* ipAddress = (char*)ip;
        char* printerName = (char*)pn;
        hplfpsdk_setLogLevel(HPLFPSDK::Types::LOG_LEVEL_NONE);
        HPLFPSDK::Types::Result result = hplfpsdk_init();
        if (result == HPLFPSDK::Types::RESULT_OK)
        {
            cout << "Libreria inizializzata correttamente!" << "\n";
        }
        else
        {
            cout << "Libreria non inizializzata!" << "\n";
            ret = "LIBRERIA NON INIZIALIZZATA";
            return ret.c_str();
        }
        HPLFPSDK::IDevice* printer = NULL;
        HPLFPSDK::Types::Result resultPrinter;
        resultPrinter = hplfpsdk_getNewPrinter(ipAddress, printerName, printer);
        if (resultPrinter != HPLFPSDK::Types::RESULT_OK)
        {
            hplfpsdk_discardPrinter(printer);
            hplfpsdk_terminate();
            ret = "STAMPANTE NON DISPONIBILE";
            return ret.c_str();
        }
        HPLFPSDK::IInfoManager* infoManager = printer->getInfoManager();
        char* printerLog = NULL;
        rsize_t printerLogLenght = 0;
        HPLFPSDK::Types::Result resultLog = HPLFPSDK::Types::RESULT_ERROR;
        while (resultLog != HPLFPSDK::Types::RESULT_OK)
        {
            resultLog = infoManager->getPrinterConfiguration(&printerLog, printerLogLenght);
        };
        ret = (string)printerLog;
        ret.append("FINE_LOG");
        resultLog = infoManager->getInkSystemStatus(&printerLog, printerLogLenght);
        ret.append((string)printerLog);
        ret.append("FINE_LOG");
        resultLog = infoManager->getPrintheadSlotsStatus(&printerLog, printerLogLenght);
        ret.append((string)printerLog);
        ret.append("FINE_LOG");
        resultLog = infoManager->getMaintenanceCartridgesStatus(&printerLog, printerLogLenght);
        ret.append((string)printerLog);
        hplfpsdk_deleteBuffer(&printerLog);
        hplfpsdk_discardPrinter(printer);
        hplfpsdk_terminate();
        return ret.c_str();
    }
    catch (exception)
    {
        ret = "STAMPANTE NON DISPONIBILE";
        return ret.c_str();
    }
}

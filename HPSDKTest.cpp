// HPSDKTest.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include <string>
#include "IHplfpsdk.h"

using namespace std;

extern "C" __declspec(dllexport) unsigned char* GetCartridges(unsigned char* ip, unsigned char* pn)
{
    try
    {
        //cout << "Hello World!\n";
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
            return (unsigned char*)"LIBRERIA NON INIZIALIZZATA";
        }
        HPLFPSDK::IDevice* printer = NULL;
        HPLFPSDK::Types::Result resultPrinter;
        resultPrinter = hplfpsdk_getNewPrinter(ipAddress, printerName, printer);
        if (resultPrinter != HPLFPSDK::Types::RESULT_OK)
        {
            hplfpsdk_discardPrinter(printer);
            hplfpsdk_terminate();
            return (unsigned char*)"STAMPANTE NON DISPONIBILE";
        }
        //GETTING REMOTE MANAGER OBJECT
        //HPLFPSDK::IAccountingManager* accountingManager = printer->getAccountingManager();
        char* info = NULL;
        rsize_t longLength = 0;
        HPLFPSDK::IInfoManager* infoManager = printer->getInfoManager();
        result = infoManager->getPrinterStatus(&info, longLength);
        string s = (string)info;
        //while (s.find("Not initialized") != std::string::npos)
        //{
        //    result = infoManager->getPrinterStatus(&info, longLength);
        //    s = (string)info;
        //    //cout << index << endl;
        //}
        char* infoLog = NULL;
        rsize_t longLengthLog = 0;
        HPLFPSDK::Types::Result resultLog = HPLFPSDK::Types::RESULT_ERROR;
        while (resultLog != HPLFPSDK::Types::RESULT_OK)
        {
            resultLog = infoManager->getInkSystemStatus(&infoLog, longLengthLog);
            //resultLog = infoManager->getPrintheadSlotsStatus(&infoLog, longLengthLog);
            //resultLog = infoManager->getMaintenanceCartridgesStatus(&infoLog, longLengthLog);
        }
        hplfpsdk_discardPrinter(printer);
        hplfpsdk_terminate();
        return (unsigned char*)infoLog;
    }
    catch (exception)
    {
        return (unsigned char*)"STAMPANTE NON DISPONIBILE";
    }
}
//extern "C" __declspec(dllexport) unsigned char* GetPrintheads(unsigned char* ip, unsigned char* pn)
//{
//    try
//    {
//        //cout << "Hello World!\n";
//        char* ipAddress = (char*)ip;
//        char* printerName = (char*)pn;
//        hplfpsdk_setLogLevel(HPLFPSDK::Types::LOG_LEVEL_NONE);
//        HPLFPSDK::Types::Result result = hplfpsdk_init();
//        if (result == HPLFPSDK::Types::RESULT_OK)
//        {
//            cout << "Libreria inizializzata correttamente!" << "\n";
//        }
//        else
//        {
//            cout << "Libreria non inizializzata!" << "\n";
//            return (unsigned char*)"LIBRERIA NON INIZIALIZZATA";
//        }
//        HPLFPSDK::IDevice* printer = NULL;
//        HPLFPSDK::Types::Result resultPrinter;
//        resultPrinter = hplfpsdk_getNewPrinter(ipAddress, printerName, printer);
//        if (resultPrinter != HPLFPSDK::Types::RESULT_OK)
//        {
//            //cout << "Stampante inizializzata" << endl;
//
//            //cout << "Error: " << resultPrinter << endl;
//            hplfpsdk_discardPrinter(printer);
//            hplfpsdk_terminate();
//            return (unsigned char*)"STAMPANTE NON DISPONIBILE";
//        }
//        //GETTING REMOTE MANAGER OBJECT
//        //HPLFPSDK::IAccountingManager* accountingManager = printer->getAccountingManager();
//        char* info = NULL;
//        rsize_t longLength = 0;
//        HPLFPSDK::IInfoManager* infoManager = printer->getInfoManager();
//        result = infoManager->getPrinterStatus(&info, longLength);
//        string s = (string)info;
//        while (s.find("Not initialized") != std::string::npos)
//        {
//            result = infoManager->getPrinterStatus(&info, longLength);
//            s = (string)info;
//            //cout << index << endl;
//        }
//        char* infoLog = NULL;
//        rsize_t longLengthLog = 0;
//        HPLFPSDK::Types::Result resultLog = HPLFPSDK::Types::RESULT_OK;
//        //resultLog = infoManager->getInkSystemStatus(&infoLog, longLengthLog);
//        resultLog = infoManager->getPrintheadSlotsStatus(&infoLog, longLengthLog);
//        //resultLog = infoManager->getMaintenanceCartridgesStatus(&infoLog, longLengthLog);
//        if (resultLog == HPLFPSDK::Types::RESULT_OK)
//        {
//            hplfpsdk_discardPrinter(printer);
//            hplfpsdk_terminate();
//            return (unsigned char*)infoLog;
//        }
//        else
//        {
//            hplfpsdk_discardPrinter(printer);
//            hplfpsdk_terminate();
//            return (unsigned char*)"STAMPANTE NON DISPONIBILE";
//        }
//    }
//    catch (exception)
//    {
//        return (unsigned char*)"STAMPANTE NON DISPONIBILE";
//    }
//}

//extern "C" __declspec(dllexport) unsigned char* GetMaintanance(unsigned char* ip, unsigned char* pn)
//{
//    try
//    {
//        //cout << "Hello World!\n";
//        char* ipAddress = (char*)ip;
//        char* printerName = (char*)pn;
//        hplfpsdk_setLogLevel(HPLFPSDK::Types::LOG_LEVEL_NONE);
//        HPLFPSDK::Types::Result result = hplfpsdk_init();
//        if (result == HPLFPSDK::Types::RESULT_OK)
//        {
//            cout << "Libreria inizializzata correttamente!" << "\n";
//        }
//        else
//        {
//            cout << "Libreria non inizializzata!" << "\n";
//            return (unsigned char*)"LIBRERIA NON INIZIALIZZATA";
//        }
//        HPLFPSDK::IDevice* printer = NULL;
//        HPLFPSDK::Types::Result resultPrinter;
//        resultPrinter = hplfpsdk_getNewPrinter(ipAddress, printerName, printer);
//        if (resultPrinter != HPLFPSDK::Types::RESULT_OK)
//        {
//            //cout << "Stampante inizializzata" << endl;
//
//            //cout << "Error: " << resultPrinter << endl;
//            hplfpsdk_discardPrinter(printer);
//            hplfpsdk_terminate();
//            return (unsigned char*)"STAMPANTE NON DISPONIBILE";
//        }
//        //GETTING REMOTE MANAGER OBJECT
//        //HPLFPSDK::IAccountingManager* accountingManager = printer->getAccountingManager();
//        char* info = NULL;
//        rsize_t longLength = 0;
//        HPLFPSDK::IInfoManager* infoManager = printer->getInfoManager();
//        result = infoManager->getPrinterStatus(&info, longLength);
//        string s = (string)info;
//        while (s.find("Not initialized") != std::string::npos)
//        {
//            result = infoManager->getPrinterStatus(&info, longLength);
//            s = (string)info;
//            //cout << index << endl;
//        }
//        char* infoLog = NULL;
//        rsize_t longLengthLog = 0;
//        HPLFPSDK::Types::Result resultLog = HPLFPSDK::Types::RESULT_OK;
//        //resultLog = infoManager->getInkSystemStatus(&infoLog, longLengthLog);
//        //resultLog = infoManager->getPrintheadSlotsStatus(&infoLog, longLengthLog);
//        resultLog = infoManager->getMaintenanceCartridgesStatus(&infoLog, longLengthLog);
//        if (resultLog == HPLFPSDK::Types::RESULT_OK)
//        {
//            hplfpsdk_discardPrinter(printer);
//            hplfpsdk_terminate();
//            return (unsigned char*)infoLog;
//        }
//        else
//        {
//            hplfpsdk_discardPrinter(printer);
//            hplfpsdk_terminate();
//            return (unsigned char*)"STAMPANTE NON DISPONIBILE";
//        }
//    }
//    catch (exception)
//    {
//        return (unsigned char*)"STAMPANTE NON DISPONIBILE";
//    }
//}

// Per eseguire il programma: CTRL+F5 oppure Debug > Avvia senza eseguire debug
// Per eseguire il debug del programma: F5 oppure Debug > Avvia debug

// Suggerimenti per iniziare: 
//   1. Usare la finestra Esplora soluzioni per aggiungere/gestire i file
//   2. Usare la finestra Team Explorer per connettersi al controllo del codice sorgente
//   3. Usare la finestra di output per visualizzare l'output di compilazione e altri messaggi
//   4. Usare la finestra Elenco errori per visualizzare gli errori
//   5. Passare a Progetto > Aggiungi nuovo elemento per creare nuovi file di codice oppure a Progetto > Aggiungi elemento esistente per aggiungere file di codice esistenti al progetto
//   6. Per aprire di nuovo questo progetto in futuro, passare a File > Apri > Progetto e selezionare il file con estensione sln

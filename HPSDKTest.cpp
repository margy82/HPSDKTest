// HPSDKTest.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include <string>
#include "IHplfpsdk.h"
using namespace std;

void main()
{
    cout << "Hello World!\n";
    const char* ipAddress = "192.168.5.180";
    const char* printerName = "HP Latex 700 W";
    hplfpsdk_setLogLevel(HPLFPSDK::Types::LOG_LEVEL_NONE);
    HPLFPSDK::Types::Result result = hplfpsdk_init();
    if (result == HPLFPSDK::Types::RESULT_OK)
    {
        cout << "Libreria inizializzata correttamente!" << "\n";
    }
    else
    {
        cout << "Libreria non inizializzata!" << "\n";
    }
    HPLFPSDK::IDevice* printer = NULL;
    HPLFPSDK::Types::Result resultPrinter;
    resultPrinter = hplfpsdk_getNewPrinter(ipAddress, printerName, printer);
    if (resultPrinter == HPLFPSDK::Types::RESULT_OK)
    {
        cout << "Stampante inizializzata" << endl;
        //hplfpsdk_discardPrinter(printer);
    }
    else
    {
        cout << "Error: " << resultPrinter << endl;
        hplfpsdk_terminate();
        return;
    }

    HPLFPSDK::IInfoManager* infoManager = printer->getInfoManager();
    char* info;
    string res;
    size_t logLength = 0;
    result = infoManager->getPrinterStatus(&info, logLength);
    res = (string)info;
    while (res.find("Not initialized") != std::string::npos)
    {
        result = infoManager->getPrinterStatus(&info, logLength);
        res = (string)info;
        //cout << index << endl;
    }
    HPLFPSDK::Types::Result resultInfoManager = infoManager->getInkSystemStatus(&info, logLength);
    if (resultInfoManager == HPLFPSDK::Types::RESULT_OK)
    {
        res = info;
        hplfpsdk_deleteBuffer(&info);
    }
    else
    {
        cout << "Error: " << resultInfoManager << endl;
        return;
    }
    resultInfoManager = infoManager->getPrintheadSlotsStatus(&info, logLength);
    if (resultInfoManager == HPLFPSDK::Types::RESULT_OK)
    {
        res.append("FINE_LOG");
        res.append((string)info);
        hplfpsdk_deleteBuffer(&info);
    }
    else
    {
        cout << "Error: " << resultInfoManager << endl;
        return;
    }
    resultInfoManager = infoManager->getMaintenanceCartridgesStatus(&info, logLength);
    if (resultInfoManager == HPLFPSDK::Types::RESULT_OK)
    {
        res.append("FINE_LOG");
        res.append((string)info);
        hplfpsdk_deleteBuffer(&info);
    }
    else
    {
        cout << "Error: " << resultInfoManager << endl;
        return;
    }
    cout << res << endl;
    hplfpsdk_discardPrinter(printer);
    hplfpsdk_terminate();
}

// Per eseguire il programma: CTRL+F5 oppure Debug > Avvia senza eseguire debug
// Per eseguire il debug del programma: F5 oppure Debug > Avvia debug

// Suggerimenti per iniziare: 
//   1. Usare la finestra Esplora soluzioni per aggiungere/gestire i file
//   2. Usare la finestra Team Explorer per connettersi al controllo del codice sorgente
//   3. Usare la finestra di output per visualizzare l'output di compilazione e altri messaggi
//   4. Usare la finestra Elenco errori per visualizzare gli errori
//   5. Passare a Progetto > Aggiungi nuovo elemento per creare nuovi file di codice oppure a Progetto > Aggiungi elemento esistente per aggiungere file di codice esistenti al progetto
//   6. Per aprire di nuovo questo progetto in futuro, passare a File > Apri > Progetto e selezionare il file con estensione sln

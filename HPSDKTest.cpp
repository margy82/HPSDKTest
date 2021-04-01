// HPSDKTest.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include "IHplfpsdk.h"
using namespace std;

int main()
{
    cout << "Hello World!\n";
    hplfpsdk_setLogLevel(HPLFPSDK::Types::LOG_LEVEL_ALL);
    HPLFPSDK::Types::Result result = hplfpsdk_init();
    if (result == HPLFPSDK::Types::RESULT_OK)
    {
        cout << "Libreria inizializzata correttamente!" << "\n";
    }
    else
    {
        cout << "Libreria non inizializzata!" << "\n";
    }
    cout << hplfpsdk_isPrinterModelSupported("HP DesignJet T1700") << "\n";
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

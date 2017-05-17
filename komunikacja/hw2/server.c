/*
 * @author Tomasz Piątek
 * @brief HW 06.05 - client/server chat - server
 */

#include <stdio.h>

/*
Treść zadania

Zaimplementować prosty "czat" międzyprocesowy.
    2. Serwer - przyjmuje połączenia, wypisuje następujące informacje na standardowe wyjście albo do pliku:
        1. Wypisuje następujące informacje na standardowe wyjście albo do pliku:
            1. Czas nadania wiadomości.
            2. Czas odebrania wiadomości.
            3. Identyfikator nadawcy.
            4. Wiadomość.
        2. Wysyła potwierdzenie odebrania wiadomości do klienta.
        3. Rozsyła otrzymane wiadomości do połączonych klientów. (* nadobowiązkowe)
*/
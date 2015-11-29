#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

#define rozmMagazyn 8
int Magazyn[rozmMagazyn];
//sem_t Mutex;
sem_t Zapelnione;
sem_t Puste;
sem_t Mutex;
int licznik;

// PRODUCENT
void* producent (void *attr) {
    int liczba;

    do {
        // GENEROWANIE LOSOWEJ LICZBY
        srand(time(NULL));
        liczba = rand()% 100;
        // CZY WOLNY BUFOR
        sem_wait(&Puste);
        sem_wait(&Mutex);
        //UMIESZCZANIE ELEMENTU W MAGAZYNIE
        Magazyn[licznik] = liczba;
        printf ("Zapisano na %d pozycji\n", licznik);
        licznik++;

        sem_post(&Mutex);
        sem_post(&Zapelnione);


    } while(1);
    //printf("cos");
}

void* konsument (void *attr) {
    int liczba;
    do {
        sem_wait(&Zapelnione);
        sem_wait(&Mutex);
        // POBIERANIE ELEMENTU
        liczba = Magazyn[licznik];
        printf(" Odczytano na %d pozycji \n", licznik);
        licznik--;
        sem_post(&Mutex);
        sem_post(&Puste);

        //sleep(2);
    } while(1);



}


int main()
{
    licznik = 0;
    sem_init(&Puste, 0, rozmMagazyn);
    sem_init(&Zapelnione, 0, 0);
    sem_init(&Mutex, 0, 1);
    pthread_t ptProducent;
    pthread_t ptKonsument;
    pthread_create(&ptProducent, NULL, producent, NULL);
    pthread_create(&ptKonsument, NULL, konsument, NULL);
    pthread_exit(NULL);
    return 0;
}

/*
* Laboratorio #5 - Adelanto de Proyecto #2
* Bryan España - 21550
* Javier Prado - 21486
* Angel Perez - 21298
*/

#include <iostream>
#include <string>
#include <pthread.h>
#define MAX_THREAD 3
using namespace std;
pthread_mutex_t mutex;
int part = 0;
struct datosRestaurante
    {
        string nombre;
        int Salario;
        int trabajadores;
    };
 
    datosRestaurante *Restaurante = new datosRestaurante[3];
 
void *PedirRestaurante(void *arg)
{
        int thread_part = part++;
        pthread_mutex_lock(&mutex);
        cout << "Ingrese el nombre del restaurante #" << thread_part +1 <<":" << endl;
        cin >> Restaurante[thread_part].nombre;
        cout << "Ingrese el salario del trabajador #" << thread_part +1 <<":"<< endl;
        cin >> Restaurante[thread_part].Salario;
        cout << "Ingrese el numero de trabajadores #" << thread_part +1<<":" << endl;
        cin >> Restaurante[thread_part].trabajadores;
        cout << "\n" << endl;
        pthread_mutex_unlock(&mutex);
        
}

int main()
{
    pthread_t threads[MAX_THREAD];
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < MAX_THREAD; i++)
    {
        pthread_create(&threads[i], NULL, PedirRestaurante, (void *)NULL);
    }
    for (int i = 0; i < MAX_THREAD; i++)
    {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);

    //Imprimir datos
    for (int i = 0; i < 3; i++)
    {
        cout << "Nombre del restaurante #" << i +1<<": "<< Restaurante[i].nombre << endl;
        cout << "Salario del trabajador #" << i +1<<": "<< Restaurante[i].Salario << endl;
        cout << "Numero de trabajadores #" << i +1 <<": " << Restaurante[i].trabajadores << endl;
        cout << "\n" <<endl;
    }

 
    return 0;
}
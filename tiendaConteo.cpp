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
int gpart = 0;
int ppart = 0;


struct datosRestaurante
    {
        string nombre;
        int Salario;
        int trabajadores;
        int ganancias[10000]; // Arreglo de ganancias
        int perdidas[10000]; // Arreglo de perdidas
        int gananciasTotales = 0; 
        int perdidasTotales = 0;    
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


//Funcion para generar y calcular las ganancias totales de cada restaurante
void *generarGananciasRandom(void *arg)
{
    int thread_part = gpart++;
    pthread_mutex_lock(&mutex);
    cout << "Obteniendo ganancias de la base de datos del restaurante: " << Restaurante[thread_part].nombre <<"..." << endl;
    for (int i = 0; i < 10000; i++)
    {
        Restaurante[thread_part].ganancias[i] = rand() % 1000;
    }
    //Sumar todas las ganancias y guardar resultado en gananciasTotales{
    for (int i = 0; i < 10000; i++)
    {
        Restaurante[thread_part].gananciasTotales += Restaurante[thread_part].ganancias[i];
    }
    cout << "Se obtuvo con exito las ganancias de la base de datos para restaurante " << Restaurante[thread_part].nombre << endl;
    cout << "\n" << endl;
    pthread_mutex_unlock(&mutex);
}

//Funcion para generar y calcular las perdidas totales de cada restaurante
void *generarPerdidasRandom(void *arg)
{
    int thread_part = ppart++;
    pthread_mutex_lock(&mutex);
    cout << "Obteniendo perdidas de la base de datos del restaurante: " << Restaurante[thread_part].nombre <<"..." << endl;

    for (int i = 0; i < 10000; i++)
    {
        Restaurante[thread_part].perdidas[i] = rand() % 300;
    }
    //Sumar todas las perdidas y guardar resultado en perdidasTotales
    for (int i = 0; i < 10000; i++)
    {
        Restaurante[thread_part].perdidasTotales += Restaurante[thread_part].perdidas[i];
    }
    cout << "Se obtuvo con exito las perdidas de la base de datos para restaurante " << Restaurante[thread_part].nombre << endl;
    cout << "\n" << endl;
    pthread_mutex_unlock(&mutex);
}

int main()
{
    pthread_t threads[MAX_THREAD];
    pthread_mutex_init(&mutex, NULL);
    cout << "----------------------------------------\n Sistema de Contabilidad \n----------------------------------------\n"<<endl;
    for (int i = 0; i < MAX_THREAD; i++)
    {
        pthread_create(&threads[i], NULL, PedirRestaurante, (void *)NULL);
        pthread_create(&threads[i], NULL, generarGananciasRandom, (void *)NULL);  
        pthread_create(&threads[i], NULL, generarPerdidasRandom, (void *)NULL);  
    }

    for (int i = 0; i < MAX_THREAD; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    //Imprimir datos
    cout << "----------------------------------------\nContabilidad de Restaurantes\n----------------------------------------\n" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "Nombre del restaurante #" << i +1<<": "<< Restaurante[i].nombre << endl;
        cout << "Salario del trabajador #" << i +1<<": "<< Restaurante[i].Salario << endl;
        cout << "Numero de trabajadores #" << i +1 <<": " << Restaurante[i].trabajadores << endl;
        cout << "\n----------------------------------------\n" <<endl;
    }

//ordenar los datos de mayor a menor "GANANCIAS"
    for (int i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < 3; j++)
        {
            if (Restaurante[i].gananciasTotales < Restaurante[j].gananciasTotales)
            {
                datosRestaurante temp = Restaurante[i];
                Restaurante[i] = Restaurante[j];
                Restaurante[j] = temp;
            }
        }
    }



//imprimir Gananacias totales de cada restaurante de mayor a menor
    cout << "------------------------------------------------------------\nEl orden de restaurantes de mayor a menos en ganancias son: \n------------------------------------------------------------" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "Nombre del restaurante #" << i +1<<": "<< Restaurante[i].nombre << endl;
        cout << "Ganancias totales del restaurante #" << i +1<<": "<< Restaurante[i].gananciasTotales << endl;
        cout << "\n----------------------------------------\n" <<endl;
    }

//ordenar los datos de mayor a menor "PERDIDAS"
    for (int i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < 3; j++)
        {
            if (Restaurante[i].perdidasTotales < Restaurante[j].gananciasTotales)
            {
                datosRestaurante temp = Restaurante[i];
                Restaurante[i] = Restaurante[j];
                Restaurante[j] = temp;
            }
        }
    }

//imprimir Gananacias totales de cada restaurante de mayor a menor
    cout << "------------------------------------------------------------\nEl orden de restaurantes de mayor a menos en perdidas son: \n------------------------------------------------------------" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "Nombre del restaurante #" << i +1<<": "<< Restaurante[i].nombre << endl;
        cout << "Perdidas totales del restaurante #" << i +1<<": "<< Restaurante[i].perdidasTotales << endl;
        cout << "\n----------------------------------------\n" <<endl;
    }

   


 
    return 0;
}

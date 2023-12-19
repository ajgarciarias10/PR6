#include <iostream>
#include "VuelaFlight.h"
/**
 * @file MAIN.h
 * @date 19/12/2023
 * @author Antonio José Garcia Arias, ajga001@red.ujaen.es
 * @author Abraham Garcia Hurtado, agh00040@red.ujaen.es
 * @brief main
 */
float haversine(float lat1, float lon1, float lat2, float lon2) {
    float R = 6378.0;
    float IncrLat = (lat2 - lat1)*(M_PI/180);
    float IncrLon = (lon2 - lon1)*(M_PI/180);
    float a = pow(sin(IncrLat/2),2) + (cos(lat1*(M_PI/180))*cos(lat2*(M_PI/180))* pow(sin(IncrLon/2),2));
    float c = 2 * atan2 (sqrt (a), sqrt (1-a));
    float d = R * c;
    return d;
}
int main() {
    try {
        cout<<"------------------Cargando Practica 5------------------"<< endl;
        VuelaFlight vuelaFlightPR5;


#pragma  region Parte Practica 5
#pragma  region Prueba de Rendimiento 1
        //Vector de Aeropuertos
        vector<Aeropuerto*> aeros =  vuelaFlightPR5.getAeros();
#pragma region Prueba con la tabla hash
        clock_t tiempoprueba2= clock();
        for (int i = 0; i <1000000 ; ++i) {
            vuelaFlightPR5.buscaAeropuerto(aeros[rand()%aeros.size()]->getIata());
        }
        std::cout << "Tiempo lectura de la prueba 2 con tabla: " << ((clock() - tiempoprueba2) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
#pragma endregion
#pragma region Prueba con el mapaaa
        map<string,Aeropuerto*> mapitaAeros;
        for (int i = 0; i < aeros.size(); ++i) {
            mapitaAeros.insert(pair<string,Aeropuerto*>(aeros[i]->getIata(),aeros[i]) );
        }
        clock_t tiempoprueba2lista= clock();
        for (int i = 0; i <1000000 ; ++i)  {
            mapitaAeros.find(aeros[rand()%aeros.size()]->getIata());
        }
        std::cout << "Tiempo lectura de la prueba 2 con el mapa : " << ((clock() - tiempoprueba2lista) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
#pragma endregion

#pragma endregion
#pragma region Programa de prueba 2
        vuelaFlightPR5.mostrarEstadoTabla();
        Aeropuerto *aeropuerto = vuelaFlightPR5.buscaAeropuerto("00AS");
        if(aeropuerto){
            cout<< "Nombre: " << aeropuerto->getNombre() <<  " IATA: " << aeropuerto->getIata()<<
                " Pais: "<<  aeropuerto->getIsoPais()  <<endl;
            vuelaFlightPR5.eliminarAeropuerto("00AS");
            Aeropuerto* aeropuerto2 = vuelaFlightPR5.buscaAeropuerto("00AS");
            if(!aeropuerto2){
                cout<< " Ha sido borrado con exito " <<endl;
                cout << "Realizando reinserccion del aeropuerto"<<endl;

                vuelaFlightPR5.addAeropuerto(*aeropuerto);
                vuelaFlightPR5.mostrarEstadoTabla();
                vuelaFlightPR5.eliminarAeropuertoInactivo();
                vuelaFlightPR5.mostrarEstadoTabla();
            }
        }
        else {
            cout << "No existe" << endl;
        }
#pragma endregion
#pragma  region Redispersion
        cout<<endl<<"---------------REDISPERSION---------------"<<endl;
        vuelaFlightPR5.redispersar();
        vuelaFlightPR5.mostrarEstadoTabla();

#pragma  endregion
#pragma  endregion

#pragma  region Practica 6
        cout<<"------------------Cargando Practica 6------------------"<< endl;
        VuelaFlight vuelaFlightPR6;
        cout<<"------------------Buscar Aeropuertos radio 300 kms ------------------"<< endl;
        UTM utm = UTM(37.7692200,-3.7902800);
        vector<Aeropuerto*> vAeriosRad =  vuelaFlightPR6.buscarAeropuertosRadio(utm,300);
        Aeropuerto* mascercano;
        float aux=3000;
        for (int i = 0; i < vAeriosRad.size(); ++i) {
            float dis= haversine(37.7692200,-3.7902800,vAeriosRad[i]->getLatitud(),vAeriosRad[i]->getLongitud());
            if (dis<aux){
                aux=dis;
                mascercano=vAeriosRad[i];
            }
            cout<< i << ": " <<" IATA : " << vAeriosRad[i]->getIata()<< " Nombre: "<< vAeriosRad[i]->getNombre() << " Distancia: " << dis << " km" <<endl;
        }
        cout<<"El aeropuerto mas cercano a Jaen Capital es: "<<mascercano->getNombre()<<endl;

        cout<<"Buscar nombres de los 5 aeropuertos con más vuelos salientes en un radio de 800KM de Madrid capital"<< endl;
        UTM madrid(40.471926,-3.56264);
        vector<Aeropuerto*> aerosMadrid=vuelaFlightPR6.aeropuertosMasSalidas(madrid,800);
        for (int i = 0; i < aerosMadrid.size(); ++i) {
            cout<< i+1 << ": " <<" IATA : " << aerosMadrid[i]->getIata()<< " Nombre: "<< aerosMadrid[i]->getNombre()<<endl;
        }

        cout<<"------------------Concentra mas aeropuertos LONDRES O VENECIA------------------"<< endl;
        UTM londres(51.510636,-0.303172 ),venecia(12.221751,45.515483);
        vector<Aeropuerto*> aerosLondres=vuelaFlightPR6.buscarAeropuertosRadio(londres,400);
        vector<Aeropuerto*> aerosVenecia=vuelaFlightPR6.buscarAeropuertosRadio(venecia,400);
        if (aerosLondres.size()>aerosVenecia.size()){
            cout<<"El aeropuerto de Londres concentra mas aeropuertos en un radio de 400km con un total de: "<<aerosLondres.size()<<endl;
        }else{
            cout<<"El aeropuerto de Venecia concentra mas aeropuertos en un radio de 400km con un total de: "<<aerosVenecia.size()<<endl;
        }


        cout<<"------------------TRABAJO PAREJAS------------------"<< endl;

        Aeropuerto aeroJaen("0000","JEN","small_airport","JAEN airport","EU","ES",-3.7902800,37.7692200);
        vuelaFlightPR6.addAeropuerto(aeroJaen);
        Aerolinea iberia=vuelaFlightPR6.buscaAerolinea("IBE");

        Aeropuerto* m=vuelaFlightPR6.buscaAeropuerto("MAD");
        Aeropuerto* barcelona=vuelaFlightPR6.buscaAeropuerto("BCN");
        Aeropuerto* jaen2=vuelaFlightPR6.buscaAeropuerto("JEN");

        vuelaFlightPR6.addNuevaRuta(m,jaen2,&iberia);
        vuelaFlightPR6.addNuevaRuta(jaen2,m,&iberia);
        vuelaFlightPR6.addNuevaRuta(barcelona,jaen2,&iberia);
        vuelaFlightPR6.addNuevaRuta(jaen2,barcelona,&iberia);

        vuelaFlightPR6.rellenaMallaPar(*jaen2);
        UTM antequera(37.0193800, -4.5612300);
        vector<Aeropuerto*> aerosAntequera=vuelaFlightPR6.buscarAeropuertosRadio(antequera,300);
        for (int i = 0; i < aerosAntequera.size(); ++i) {
            if(aerosAntequera[i]->getIata() == "JEN") {
                cout<<"El aeropuerto de Jaen se encuentra dentro de un radio de 300km de Antequera"<<endl;
                cout<<" IATA : " << aerosAntequera[i]->getIata()<< " Nombre: "<< aerosAntequera[i]->getNombre() << " Coordenadas("<<aerosAntequera[i]->getLatitud() <<","<< aerosAntequera[i]->getLongitud() << ")" <<endl;
            }

        }
#pragma  endregion
    }catch (invalid_argument &e){
        e.what();
    }

    return 0;
}

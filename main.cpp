#include <iostream>
#include "VuelaFlight.h"
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
        VuelaFlight vuelaFlight;
/*
#pragma  region Parte Practica 5
#pragma  region Prueba de Rendimiento 1
        //Vector de Aeropuertos
        vector<Aeropuerto*> aeros =  vuelaFlight.getAeros();
#pragma region Prueba con la tabla hash
        clock_t tiempoprueba2= clock();
        for (int i = 0; i <1000000 ; ++i) {
            vuelaFlight.buscaAeropuerto(aeros[rand()%aeros.size()]->getIata());
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
        vuelaFlight.mostrarEstadoTabla();
        Aeropuerto *aeropuerto = vuelaFlight.buscaAeropuerto("00AS");
        if(aeropuerto){
            cout<< "Nombre: " << aeropuerto->getNombre() <<  " IATA: " << aeropuerto->getIata()<<
                " Pais: "<<  aeropuerto->getIsoPais()  <<endl;
            vuelaFlight.eliminarAeropuerto("00AS");
            Aeropuerto* aeropuerto2 = vuelaFlight.buscaAeropuerto("00AS");
            if(!aeropuerto2){
                cout<< " Ha sido borrado con exito " <<endl;
                cout << "Realizando reinserccion del aeropuerto"<<endl;

                vuelaFlight.addAeropuerto(*aeropuerto);
                vuelaFlight.mostrarEstadoTabla();
                vuelaFlight.eliminarAeropuertoInactivo();
                vuelaFlight.mostrarEstadoTabla();
            }
        }
        else {
            cout << "No existe" << endl;
        }
#pragma endregion
#pragma  region Redispersion
        cout<<endl<<"---------------REDISPERSION---------------"<<endl;
         vuelaFlight.redispersar();
         vuelaFlight.mostrarEstadoTabla();

#pragma  endregion
#pragma  endregion
*/
#pragma  region Practica 6
UTM utm = UTM(37.7692200,-3.7902800);
        vector<Aeropuerto*> vAeriosRad =  vuelaFlight.buscarAeropuertosRadio(utm,300);
        Aeropuerto* mascercano;
        float aux=3000;
        for (int i = 0; i < vAeriosRad.size(); ++i) {
            float dis= haversine(37.7692200,-3.7902800,vAeriosRad[i]->getLatitud(),vAeriosRad[i]->getLongitud());
            if (dis<aux){
                aux=dis;
                mascercano=vAeriosRad[i];
            }
            cout<< i << ": " <<" IATA : " << vAeriosRad[i]->getIata()<< " Nombre: "<< vAeriosRad[i]->getNombre()<<endl;
        }
        cout<<"El aeropuerto mas cercano a Jaen Capital es: "<<mascercano->getNombre()<<endl;

        UTM madrid(40.471926,-3.56264);
        vector<Aeropuerto*> aerosMadrid=vuelaFlight.aeropuertosMasSalidas(madrid,800);
        for (int i = 0; i < aerosMadrid.size(); ++i) {
            cout<< i+1 << ": " <<" IATA : " << aerosMadrid[i]->getIata()<< " Nombre: "<< aerosMadrid[i]->getNombre()<<endl;
        }

        UTM londres(51.4706,-0.46194),venecia(-34.8117287,-56.1633936907258);
        vector<Aeropuerto*> aerosLondres=vuelaFlight.buscarAeropuertosRadio(londres,400);
        vector<Aeropuerto*> aerosVenecia=vuelaFlight.buscarAeropuertosRadio(venecia,400);
        if (aerosLondres.size()>aerosVenecia.size()){
            cout<<"El aeropuerto de Londres concentra mas aeropuertos en un radio de 400km con un total de: "<<aerosLondres.size()<<endl;
        }else{
            cout<<"El aeropuerto de Venecia concentra mas aeropuertos en un radio de 400km con un total de: "<<aerosVenecia.size()<<endl;
        }

        Aeropuerto aeroJaen("0000","JEN","small_airport","JAEN airport","EU","ES",37.7692200,-3.7902800);
        vuelaFlight.addAeropuerto(aeroJaen);
        Aerolinea iberia=vuelaFlight.buscaAerolinea("IBE");

        Aeropuerto* m=vuelaFlight.buscaAeropuerto("MAD");
        Aeropuerto* barcelona=vuelaFlight.buscaAeropuerto("BCN");
        Aeropuerto* jaen2=vuelaFlight.buscaAeropuerto("JEN");

        vuelaFlight.addNuevaRuta(m,jaen2,&iberia);
        vuelaFlight.addNuevaRuta(jaen2,m,&iberia);
        vuelaFlight.addNuevaRuta(barcelona,jaen2,&iberia);
        vuelaFlight.addNuevaRuta(jaen2,barcelona,&iberia);
        
        vuelaFlight.rellenaMallaPar(*jaen2);
        UTM antequera(37.0193800, -4.5612300);
        vector<Aeropuerto*> aerosAntequera=vuelaFlight.buscarAeropuertosRadio(antequera,300);
        for (int i = 0; i < aerosAntequera.size(); ++i) {
            if(aerosAntequera[i]->getIata() == "JEN") {
                cout<<"El aeropuerto de Jaen se encuentra dentro de un radio de 300km de Antequera"<<endl;
                cout<< i << ": " <<" IATA : " << aerosAntequera[i]->getIata()<< " Nombre: "<< aerosAntequera[i]->getNombre()<<endl;
            }

        }
#pragma  endregion
    }catch (invalid_argument &e){
        e.what();
    }

    return 0;
}

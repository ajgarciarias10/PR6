#include "VuelaFlight.h"
/**
 * @brief VuelaFlight
 */
VuelaFlight::VuelaFlight() : airportsID(),routesOrig(),routesDest(),airlines(), airportsUTM(){

    cargaAeropuertos("aeropuertos_v3.csv");
    cargaAerolineas("aerolineas_v1.csv");
    cargarRutas("rutas_v1.csv");
    cargarVuelos("infovuelos_v1.csv");

    cout<< "Tamaño Aerolineas: " << tamaAirlines() <<endl
        << "Tamaño aeropuertos: " << tamaAeropuertos() << endl
        << "Tamaño rutas: " << tamaRutasOrig() << endl
        <<"Tamaño Vuelos: "<< tamaVuelos() << endl <<endl;

    rellenaMalla();
}
/**
 * @brief Constructor parametrizado
 * @param vector
 * @param ruta
 */

/**
 * @brief Destructor
 */
VuelaFlight::~VuelaFlight() {
}
/**
 * @brief BuscarRutasOrigenDestino
 * @param idAerOrig
 * @param idAerDest
 * @return
 */
Ruta &VuelaFlight::buscarRutasOriDeS(string idAerOrig, string idAerDest) {
    multimap<string,Ruta>::iterator origen=routesOrig.find(idAerOrig);
    if(origen!=routesOrig.end()){
        for ( ; origen!=routesOrig.end() ; origen++) {
            if (origen->second.getOrigin()->getIata()==idAerOrig &&
            origen->second.getDestination()->getIata()==idAerDest)
                return *(&origen->second);
        }
    }

    throw invalid_argument("Error::buscarRutasOriDeS:No se ha encontrado la ruta");
}
/**
 * @brief BuscarRutasOrigen
 * @param idAerOrig
 * @return
 */
list<Ruta *> VuelaFlight::buscarRutasOrigen(string idAerOrig) {
    multimap<string,Ruta>::iterator i;
    list<Ruta *> lista;
    //Recorremos todos los aeropuertos
    for(i=routesOrig.begin(); i!=routesOrig.end();i++){
        //En caso de que se encuentre
        if(i->second.getOrigin()->getIata()==idAerOrig){
            lista.push_back(&((*i).second));
        }
    }
    return  lista;
}

/**
 * @brief Buscar Aeropuerto por Pais
 * @param pais
 * @return
 */
vector<Aeropuerto * > VuelaFlight::buscarAeropuertoPais(string pais) {
    //Donde lo vamos a meter
    vector<Aeropuerto*> encontrado;


    return  encontrado;


}
/**
 * @brief Metodo para añadir nueva ruta
 * @param idAerOrig
 * @param idAerDest
 * @param aerolinea
 */
void VuelaFlight::addNuevaRuta(Aeropuerto* AerOrig, Aeropuerto* AerDest, Aerolinea* aerolineaEncontrada) {
    //Añadimos las rutas ya con la aerolinea  y los aeropertos
    Ruta ruta(AerDest,AerOrig,aerolineaEncontrada);
    pair<string,Ruta> orig(AerOrig->getIata(),ruta);
    Ruta* r=&routesOrig.insert(orig)->second;
    pair<string,Ruta*> dest(AerDest->getIata(),r);
    routesDest.insert(dest);
    aerolineaEncontrada->linkAerolRuta(r);

}

/**
 * @brief Constructor Copia
 * @param vl
 */

VuelaFlight::VuelaFlight(const VuelaFlight &vl) : airportsID(vl.airportsID), routesDest(vl.routesDest),routesOrig(vl.routesOrig),airlines(vl.airlines),
                                                  airportsUTM(vl.airportsUTM){}
/**
 * @brief Añade aeropuerto
 * @param aeropuerto
 */

void VuelaFlight::addAeropuerto(const  Aeropuerto &aeropuerto2) {
    pair<string,Aeropuerto> parAero = pair(aeropuerto2.getIata(),aeropuerto2);
    airportsID.insert(parAero);
}
/**
 * @brief Metodo AddAerolinea
 * @param aerolinea
 */
void VuelaFlight::addAerolinea(string icao,Aerolinea aerolinea) {
    airlines.insert( pair<string , Aerolinea>(icao,aerolinea));
}
/**
 * @brief Metodo Buscar Aerolinea por Icao
 * @param icaoAerolinea
 * @return
 */
Aerolinea &VuelaFlight::buscaAerolinea(std::string icaoAerolinea) {
    map<string,Aerolinea>:: iterator it = airlines.find(icaoAerolinea);
    //El metodo find devuelve end en caso de que no encuentra nada
    if(it == airlines.end()){
        throw std::invalid_argument("No se ha encontrado la aerolinea");
    }
    //Devolvemos en caso contrario si la ha encontrado
    return  it->second;
}
/**
 * @brief Metodo que busca las Aerolineas Activas
 * @return
 */
vector<Aerolinea*> VuelaFlight::buscaAerolineasActiva() {
    //Utilizamos un iterador en el mapa
    map<string,Aerolinea>::iterator itBuscaAerolinea  ;
    //Este sera el vector de aerolineas activas
    vector<Aerolinea*> aeroActivas;
    for (itBuscaAerolinea = airlines.begin(); itBuscaAerolinea != airlines.end(); ++itBuscaAerolinea) {
        if(itBuscaAerolinea->second.isActivo()){
            //Devolvemos la direccion de memoria de la aerolinea activa
            aeroActivas.push_back(&(itBuscaAerolinea->second));
        }
    }
    return  aeroActivas;
}
/**
 * @brief Metodo que busca la Aerolinea por el pais
 * @param idPais
 * @return
 */
vector<Aerolinea*> VuelaFlight::getAerolineasPais(std::string idPais) {
    //Idem aerolineas Activas
    map<string,Aerolinea>::iterator  itBuscaAero ;
    vector<Aerolinea*> aerolineaPais;
    for (itBuscaAero = airlines.begin(); itBuscaAero != airlines.end(); ++itBuscaAero) {
        if(itBuscaAero->second.getPais() == idPais){
            aerolineaPais.push_back(&(itBuscaAero->second));
        }
    }
    return  aerolineaPais;
}
/**
 * @brief Metodo que carga las rutas que leemos
 * @param icaoRuta
 * @param origen2
 * @param destino2
 */
void VuelaFlight::addRutas(string icaoRuta, string origen2, string destino2){
#pragma  region   Buscar en tiempo logarítmico la aerolínea que hace la ruta en VuelaFlight::airlines en este caso en el mapa
    map<string ,Aerolinea>::iterator aerolineaEncontrada= airlines.find(icaoRuta);
#pragma  endregion
#pragma region Buscar en tiempo logarítmico en  PR2 + añadir nueva ruta
    //Buscamos el aeropuerto de origen
   unordered_map<string ,Aeropuerto>::iterator iteradorDeOrig =  airportsID.find(origen2);
    //Buscamos el aeropuerto de destino
    unordered_map<string ,Aeropuerto>::iterator iteradorDeDest =  airportsID.find(destino2);
    if(iteradorDeOrig != airportsID.end() && iteradorDeDest != airportsID.end() && aerolineaEncontrada!=airlines.end()){
        //Añadimos nueva ruta a partir del origen el destino y el icao
        addNuevaRuta(&iteradorDeOrig->second, &iteradorDeDest->second,&aerolineaEncontrada->second);
    }
}

/**
 * @brief Metodo que devuelve el tamaño del vector
 */
long VuelaFlight::tamaAeropuertos() {
    return airportsID.size();
}
/**
 * @brief Metodo que devuelve el tamaño de la lista de rutas de origen
 */
long VuelaFlight::tamaRutasOrig() {
    return routesOrig.size();
}

/**
 * @brief Metodo que devuelve el tamaño de la lista de rutas de destino
 */
long VuelaFlight::tamaRutasDest() {
    return routesDest.size();
}
/**
 * @brief Metodo que devuelve el tamaño del arbol
 */
long VuelaFlight::tamaAirlines() {
    return airlines.size();
}
bool VuelaFlight::registrarVuelo(std::string fNumber, std::string iataAeroOrig, std::string iataAeroDest,std::string plane, std::string datosMeteo, Fecha f) {
    //Obtenemos la aeriolinea
    map<string,Aerolinea>::iterator mapaEncuentraVuelos;
    mapaEncuentraVuelos=airlines.find(fNumber.substr(0,3));
    //Buscamos el aeropuerto de origen
    unordered_map<string ,Aeropuerto>::iterator iteradorDeOrig =  airportsID.find(iataAeroOrig);
    //Buscamos el aeropuerto de destino
    unordered_map<string ,Aeropuerto>::iterator iteradorDeDest =  airportsID.find(iataAeroDest);

    if(mapaEncuentraVuelos!=airlines.end() && iteradorDeOrig != airportsID.end() && iteradorDeDest != airportsID.end()){
        Vuelo v(fNumber,plane,datosMeteo,f,&iteradorDeOrig->second,&iteradorDeDest->second,&(mapaEncuentraVuelos->second));
        mapaEncuentraVuelos->second.addVuelo(v);
        return true;
    }
    else{
        return  false;
    }
}
/**
 * @brief Metodo para cargar Vuelos pasandole un ficheroVuelos
 * @param fichVuelos
 */
void VuelaFlight::cargarVuelos(string fichVuelos) {
    clock_t lecturaRutas = clock();

    ifstream is;
    stringstream  columnas;
    string fila;

    string flightnumber = "";
    string  departurePlane = "";
    string  arrivalPlane = "";
    string plane = "";
    string datoMeteo = "";
    string fecha = "";

    is.open(fichVuelos); //carpeta de proyecto
    if ( is.good() ) {
        while (getline(is, fila)) {
            //¿Se ha leído una nueva fila?
            if (fila != "") {
                columnas.str(fila);
                getline(columnas, flightnumber, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, departurePlane, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, arrivalPlane, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, plane, ';');
                getline(columnas, datoMeteo, ';');
                getline(columnas, fecha, ';');
                //Posicion //Longuitud
                int dia = stoi(fecha.substr(0, 2));
                int mes = stoi(fecha.substr(3, 2));
                int año = stoi(fecha.substr(6, 2));
                fila = "";
                columnas.clear();
                if(registrarVuelo(flightnumber,departurePlane,arrivalPlane,plane,datoMeteo,Fecha(dia,mes,año))){
                    tamaVuelo++;
                }
            }
        }

    } else{
        std::cout << "Error de apertura en archivo" << std::endl;
    }
    tamaVuelos();

    is.close();
    std::cout << "Tiempo lectura de los vuelos: " << ((clock() - lecturaRutas) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

}
/**
 * @brief Metodo que carga los Aeropuertos
 */
void VuelaFlight::cargaAeropuertos(string fichAeropuertos) {
    clock_t lecturaAero = clock();

    ifstream is;
    stringstream  columnas;
    string fila;

    string id = "";
    string iata = "";
    string tipo="";
    string nombre="";
    string latitud_str="";
    string longitud_str="";
    string continente="";
    string iso_pais="";

    is.open(fichAeropuertos); //carpeta de proyecto
    if ( is.good() ) {
        while (getline(is, fila)) {
            //¿Se ha leído una nueva fila?
            if (fila != "") {
                columnas.str(fila);
                //formato de fila: id;ident;tipo;nombre;latitud;longitud;continente;iso_pais
                getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, iata, ';');
                getline(columnas, tipo, ';');
                getline(columnas, nombre, ';');
                getline(columnas, latitud_str, ';');
                getline(columnas, longitud_str, ';');
                getline(columnas, continente, ';');
                getline(columnas, iso_pais, ';');
                //  Transformamos la latitud y longitud a float
                fila = "";
                columnas.clear();
                //Insertamos en la tabla hash
                float latitud = stof(latitud_str);
                float longitud = stof(longitud_str);
                Aeropuerto aero = Aeropuerto(id,iata,tipo,nombre,continente,iso_pais, longitud, latitud);
                addAeropuerto(aero);
            }
        }
        //Tras leer ordenamos el vector por Codigo Iata
        is.close();
    }else{
        std::cout << "Error de apertura en archivo" << std::endl;
    }
    std::cout << "Tiempo lectura de aeropuertos: " << ((clock() - lecturaAero) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
}
/**
 * @brief Metodo que cargaLasAerolineas
 */
void VuelaFlight::cargaAerolineas(string fichAerolineas) {
    clock_t lecturaAerolineas = clock();

    ifstream is;
    stringstream  columnas;
    string fila;

    string idAerolineaStr;
    string icao = "";
    string nombreAero="";
    string pais="";
    string activo="";

    is.open(fichAerolineas); //carpeta de proyecto
    if(is.good()){
        while (getline(is, fila)){
            //¿Se ha leído una nueva fila?
            if (fila != "") {
                columnas.str(fila);
                getline(columnas, idAerolineaStr, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, icao, ';');
                getline(columnas, nombreAero, ';');
                getline(columnas, pais, ';');
                getline(columnas, activo, ';');
                bool activoBool;
                //condición ? valor_si_verdadero : valor_si_falso;
                activo=="Y" ? activoBool = true : activoBool = false;
                int id = stoi(idAerolineaStr);
                addAerolinea(icao,Aerolinea(id,icao,nombreAero,pais,activoBool));
                fila = "";
                columnas.clear();
            }
        }
    }
    else{
        std::cout << "Error de apertura en archivo" << std::endl;
    }
    is.close();
    std::cout << "Tiempo lectura de las aerolineas: " << ((clock() - lecturaAerolineas) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
}
/**
 * @brief Metodo que cargaLasRutas
 */
void VuelaFlight::cargarRutas(string fichRutas) {
    clock_t lecturaRutas = clock();

    ifstream is;
    stringstream  columnas;
    string fila;

    string icaoRuta = "";
    string  origen2 = "";
    string destino2 = "";

    is.open(fichRutas); //carpeta de proyecto
    if ( is.good() ) {
        while (getline(is, fila)) {
            //¿Se ha leído una nueva fila?
            if (fila != "") {
                columnas.str(fila);
                getline(columnas, icaoRuta, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, origen2, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, destino2, ';'); //leemos caracteres hasta encontrar y omitir ';'
                fila = "";
                columnas.clear();
                addRutas(icaoRuta, origen2, destino2);

            }
        }

    } else{
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    is.close();
    std::cout << "Tiempo lectura de las rutas: " << ((clock() - lecturaRutas) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
}
/**
 * @brief Devuelve el tamaño de los vuelos
 * @param nvuelos
 * @return
 */
int VuelaFlight::tamaVuelos() {
    return tamaVuelo;
}
/**
 * @brief Metodo que busca los vuelos y los devuelve
 * @param fNumber
 * @return
 */
vector<Vuelo *> VuelaFlight::buscaVuelos(string fNumber) {
    map<string,Aerolinea>::iterator  iteraAirlines;
    vector<Vuelo*> vuelosADev;
    for (iteraAirlines = airlines.begin();iteraAirlines!=airlines.end(); ++iteraAirlines) {
        vector<Vuelo*> aux = iteraAirlines->second.getVuelos(fNumber);
        //Concatenamos el vector
        vuelosADev.insert(vuelosADev.end(),aux.begin(),aux.end());
    }
    return vuelosADev;
}
/**
 * @brief BuscaVuelosOperados por icao y fecha
 * @param icaoAerolinea
 * @param f
 * @return
 */
vector<Vuelo *> VuelaFlight::vuelosOperadosPor(string icaoAerolinea, Fecha f) {
    map<string,Aerolinea>::iterator  iteraAirlines;
    vector<Vuelo*> vuelosADev;
    for (iteraAirlines = airlines.lower_bound(icaoAerolinea);iteraAirlines!=airlines.end(); ++iteraAirlines) {
        vector<Vuelo*> aux = iteraAirlines->second.getVuelos(f,f);
        //Concatenamos el vector
        vuelosADev.insert(vuelosADev.end(),aux.begin(),aux.end());
    }
    return vuelosADev;
}
/**
 * @brief Metodo que buscaVuelosDestAerop
 * @param paisOrig
 * @param iataAeroDest
 * @return
 */
set<string > VuelaFlight::buscaVuelosDestAerop(string paisOrig, string iataAeroDest) {
    //Primero obtengo los aeropuertos por pais
    list<Ruta*> rutasAeropuertosdePaisOrigen = buscarRutasPaisOrig(paisOrig);
    //Conjunto set con los identifcadores del vuelo
    set<string> identificadores;

    //Recorremos las rutas
    list<Ruta*>::iterator itrutas = rutasAeropuertosdePaisOrigen.begin();
    for (itrutas;itrutas!=rutasAeropuertosdePaisOrigen.end(); ++itrutas) {
        if(iataAeroDest == (*itrutas)->getDestination()->getIata()){
            for (Vuelo *vuelo : (*itrutas)->getVuelos()) {
                identificadores.insert(vuelo->getFlightNumber());
            }
        }
    }

    return  identificadores;

}
/**
 * @brief Mismo metodo que getRutasOrig por iata pero este por pais
 * @param pOrig
 * @return
 */
list<Ruta *> VuelaFlight::buscarRutasPaisOrig(string pOrig) {
    multimap<string,Ruta>::iterator i;
    list<Ruta *> lista;
    //Recorremos todos los aeropuertos
    for(i=routesOrig.begin(); i!=routesOrig.end();i++){
        //Obtenemos los datos
        string origenBusq = i->second.getOrigin()->getIsoPais();
        //En caso de que se encuentre
        if(origenBusq==pOrig){
            //Devolvemos el dato

            //El iterador no es como un puntero y entonces lo que hacemos es devolver el dato * y su direccion &
            lista.push_back(&(i->second));
        }
    }
    return  lista;


}

/**
 * @brief Ejercicio Por Pareja buscar Aeropuertos dentro de Aerolinea por icao
 * @param icaoAerolinea
 * @return
 */

vector<Aeropuerto *> VuelaFlight::buscaAeropuertosAerolinea(string icaoAerolinea) {
    set<Aeropuerto*> setAeros;
    vector<Aeropuerto*> vAeroports;
    vector<Vuelo*> vVuelos;
    vector<Vuelo*>::iterator itVuelos;
    Aerolinea aaero = buscaAerolinea(icaoAerolinea);
    vVuelos = aaero.getFlights();
    itVuelos = vVuelos.begin();
    for (;itVuelos!=vVuelos.end();itVuelos++) {
        setAeros.insert((*itVuelos)->getAirpOrigin());
        setAeros.insert((*itVuelos)->getAirpDest());
    }
    for (Aeropuerto *aero : setAeros) {
        vAeroports.push_back(aero);
    }
    return vAeroports;
}
/**
 * @brief Metodo que muestra el estado de la tabla
 */
void VuelaFlight::mostrarEstadoTabla() {
    cout<<"El numero maximo de colisiones es: "<<airportsID.bucket_count()<<endl;
    cout<<"El factor de carga es: "<<airportsID.load_factor()<<endl;
    cout<<"El numero de aeropuertos existentes "<<airportsID.size()<<" elementos"<<endl;

}
/**
 * @brief Metodo que eliminaElAeropuerto
 * @param IATA
 */
void VuelaFlight::eliminarAeropuerto(string IATA) {

    map<string,Aerolinea>::iterator  itAerolinea;
    for (itAerolinea = airlines.begin(); itAerolinea!= airlines.end() ; ++itAerolinea) {
            itAerolinea->second.bajaAeropuerto(IATA);
    }

    multimap<string,Ruta*>::iterator  itRutasDest;
    for (itRutasDest = routesDest.begin(); itRutasDest!= routesDest.end() ; ++itRutasDest) {
        if(itRutasDest->second->getDestination()->getIata() == IATA ||
                itRutasDest->second->getOrigin()->getIata() == IATA) {
            routesDest.erase(itRutasDest);
        }
    }
    multimap<string,Ruta>::iterator  itRutasOrigen;
    for (itRutasOrigen = routesOrig.begin(); itRutasOrigen!= routesOrig.end() ; ++itRutasOrigen) {
       if(itRutasOrigen->second.getOrigin()->getIata() == IATA) {
           routesOrig.erase(itRutasOrigen);
       }
    }

    if(!airportsID.erase(IATA)){
        throw invalid_argument("Error en el borrado");
    }


}

Aeropuerto *VuelaFlight::buscaAeropuerto(string IATAAirport) {
    unordered_map<string, Aeropuerto>::iterator  iteraAeros = airportsID.find(IATAAirport);
    if(iteraAeros != airportsID.end()){
        return  &(iteraAeros->second);
    }
    return nullptr;
}

void VuelaFlight::eliminarAeropuertoInactivo() {
    cout<<"Eliminando inactivos: "<<endl;
    unordered_map<string,Aeropuerto>::iterator iterAeros ;
    for (iterAeros = airportsID.begin(); iterAeros != airportsID.end(); ++iterAeros) {
        multimap<string,Ruta*>::iterator  itDest;
        itDest = routesDest.find(iterAeros->first);
        multimap<string,Ruta>::iterator  itOrig;
        itOrig = routesOrig.find(iterAeros->first);

        if( itOrig == routesOrig.end() || itDest == routesDest.end()){
            airportsID.erase(iterAeros->first);
        }
    }
}

/**
 * @brief Metodo que inserta los aeropuertos leidos ->  en la malla
 */
void VuelaFlight::rellenaMalla() {
    unordered_map<string ,Aeropuerto>::iterator  iteraLeidos = airportsID.begin();
    for (iteraLeidos;iteraLeidos!=airportsID.end(); ++iteraLeidos) {
        airportsUTM.insertarCasilla(iteraLeidos->second.getUtm().getLatitud(),iteraLeidos->second.getUtm().getLongitud(),&iteraLeidos->second);
    }
}

vector<Aeropuerto *> VuelaFlight::buscarAeropuertosRadio(UTM &pos, float radioKm) {
   vector<Aeropuerto*> radAeros ;
    for(Aeropuerto **aero : airportsUTM.buscarRadio(pos.getLatitud(),pos.getLongitud(),radioKm)) {
        radAeros.push_back(*aero);
    }
    return  radAeros;
}

vector<Aeropuerto *> VuelaFlight::aeropuertosMasSalidas(UTM pos, float radioKm) {
    vector <Aeropuerto*> aeroSal;
    priority_queue<pair<long,Aeropuerto*>> cola;
    for(Aeropuerto **aero : airportsUTM.buscarRadio(pos.getLatitud(),pos.getLongitud(),radioKm)) {
        aeroSal.push_back(*aero);
    }
    for (int i = 0; i < aeroSal.size(); ++i) {
        list<Ruta*> rutasOrig = buscarRutasOrigen(aeroSal[i]->getIata());
        list<Ruta*>::iterator  iteRutas;
        long numVuelos;
        for (iteRutas = rutasOrig.begin();iteRutas != rutasOrig.end() ; ++iteRutas) {
         numVuelos +=  (*iteRutas)->getNumVuelos();
        }
        pair<long,Aeropuerto*> par(numVuelos,aeroSal[i]);
        cola.push(par);
    }
    for (int i = 0; i < 5; ++i) {
        while(!cola.empty()){
            cout<<"Posicion :" << i << "Aeropuerto:" << cola.top().second->getNombre()<< "Numero de Vuelos:" << cola.top().first<< endl;
            aeroSal.push_back(cola.top().second);
        }

    }
    return  aeroSal;
}

vector<Aeropuerto *> VuelaFlight::getAeros() {
    vector<Aeropuerto*> pAdev ;
    unordered_map <string,Aeropuerto>::iterator itpAdv ;
    for (itpAdv= airportsID.begin(); itpAdv!=airportsID.end();itpAdv++) {
        pAdev.push_back(&(itpAdv->second));
    }
    return pAdev;
}

//
// Created by AntonioJR on 15/12/2023.
//
#include <list>
#include <vector>
#include "Aeropuerto.h"
#include <cmath>
using  namespace std;

#ifndef PR6_MALLAREGULAR_H
#define PR6_MALLAREGULAR_H

/**
 * @file MallaRegular.h
 * @date 17/12/2023
 * @author Antonio José Garcia Arias, ajga001@red.ujaen.es
 * @author Abraham Garcia Hurtado, agh00040@red.ujaen.es
 * @brief MALLAREGULAR
 */

template<typename T>
class MallaRegular {
    class Casilla{
        std::list<T> puntos;
        public:
            Casilla(): puntos() {}
            void insertar(const T &dato) {
                   puntos.push_back(dato);
            }
            T *buscar(const T& dato) {
                typename list<T>::iterator it;

                for (  it = puntos.begin();it != puntos.end(); ++it){
                    if (*it == dato)
                        return &(*it);
                }
                return 0;
            }
            bool borrar(const T& dato){
                typename list<T>::iterator it;
                it = puntos.begin();
                for (;it != puntos.end(); ++it){
                    if (*it == dato) {
                        puntos.erase(it);
                        return true;
                    }
                }
                return false;
            }
            typename list<T>::iterator  inicio(){
                return puntos.begin();
            }
            typename list<T>::iterator  fin(){
                return puntos.end();
            }
        int  tamano(){
            return puntos.size();
        }
    };
    float xMin, yMin, xMax, yMax; // Tamaño real global
    float tamaCasillaX, tamaCasillaY; // Tamaño real de cada casilla
    vector<vector<Casilla> > mr; // Vector 2D de casillas
    unsigned nDiv,tamlog;
    Casilla *obtenerCasilla(float x, float y);
    float haversine(float lat1, float lon1, float lat2, float lon2);

public:

    MallaRegular(float aXMin=0.0, float aYMin=0.0, float aXMax=0.0, float aYMax=0.0, int aNDiv=0);
    void insertarCasilla(float x, float y, const T &dato);
    T *buscarCasilla(float x, float y, const T &dato);
    bool borrarCasilla(float x, float y, const T &dato);
    vector<T> buscarRadio(float xcentro, float ycentro, float radio);
    unsigned maxElementosPorCelda();
    float promedioElementosPorCelda();

    ~MallaRegular(){}
};

template<typename T>
float MallaRegular<T>::promedioElementosPorCelda() {
    int casillasLlenas=0;
    int suma=0;
    for (int i = xMin; i < xMax; i+=tamaCasillaX) {
        for (int j = yMin; j < yMax; j+=tamaCasillaY) {
            if(mr[i][j].puntos.size()!=0)
                casillasLlenas++;
        }
    }
    return float(tamlog)/casillasLlenas;
}

template<typename T>
unsigned MallaRegular<T>::maxElementosPorCelda() {
    int maximo=0;
    for (int i = 0; i < nDiv; ++i) {
        for (int j = 0; j < nDiv; ++j) {
            if(mr[i][j].puntos.size()>maximo)
                maximo=mr[i][j];
        }
    }
    return maximo;
}
/**
 * @brief Metodo Buscar Radio
 * @post Obtenemos la  latiMax y  latiMin
 * @post Obtenemos el longMin y longMax
 * @post Finalidad: Encontrar todos lo aeropuertos en un radio concentrado
 * @tparam T
 * @param xcentro
 * @param ycentro
 * @param radio
 * @return
 */
template<typename T>
vector<T> MallaRegular<T>::buscarRadio(float xcentro, float ycentro, float radio) {
    vector<T> aeroRad;
    typename list<T>::iterator itRad;
    double radioAkm= (radio/111.1);
    float longMin=xcentro- radioAkm;
    float latiMin= ycentro -radioAkm;
    float longMax = xcentro +radioAkm;
    float latiMax = ycentro +radioAkm;
    for (float i = longMin; i <=longMax ; i+=tamaCasillaX) {
        for (float j = latiMin; j <=latiMax ; j+=tamaCasillaY) {
            if(j >= yMin && j<=yMax  && i>=xMin  && i<=xMax){
                Casilla *casil = obtenerCasilla(i,j);
                for (itRad =casil->inicio(); itRad != casil->fin();itRad++) {
                    float dist;
                    dist = haversine( ycentro,xcentro ,(*itRad)->getLatitud(),(*itRad)->getLongitud());
                    if (dist <= radio) {
                        aeroRad.push_back(*itRad);
                    }
                }
            }
        }
    }
    return aeroRad;
}
/**
 * @brief Metodo para obtener la casilla
 * @tparam T
 * @param x
 * @param y
 * @return
 */
template<typename T>
typename  MallaRegular<T>::Casilla *MallaRegular<T>::obtenerCasilla(float x, float y) {
    int i = (x - xMin) / tamaCasillaX;
    int j = (y - yMin) / tamaCasillaY;
    return &mr[i][j];


}
/**
 * @brief Metodo para medir la distancia entre varias coordenadas mediante el algoritmo de haversine
 * @tparam T
 * @param lat1
 * @param lon1
 * @param lat2
 * @param lon2
 * @return
 */
template<typename T>
float MallaRegular<T>::haversine(float lat1, float lon1, float lat2, float lon2) {
    float R = 6378.0;
    float IncrLat = (lat2 - lat1)*(M_PI/180);
    float IncrLon = (lon2 - lon1)*(M_PI/180);
    float a = pow(sin(IncrLat/2),2) + (cos(lat1*(M_PI/180))*cos(lat2*(M_PI/180))* pow(sin(IncrLon/2),2));
    float c = 2 * atan2 (sqrt (a), sqrt (1-a));
    float d = R * c;
    return d;
}
/**
 * @brief Metodo para borrar la Casilla
 * @tparam T
 * @param x
 * @param y
 * @param dato
 * @return
 */
template<typename T>
bool MallaRegular<T>::borrarCasilla(float x, float y, const T &dato) {
    Casilla  *c = obtenerCasilla(x,y);
    return c->borrar(dato);
}
/**
 * @brief Metodo para buscar una casilla determinada
 * @tparam T
 * @param x
 * @param y
 * @param dato
 * @return
 */
template<typename T>
T *MallaRegular<T>::buscarCasilla(float x, float y, const T &dato) {
   Casilla *casil = obtenerCasilla(x,y);
    return casil->buscar(dato);
}
/**
 * @brief Metodo para insertar una casilla en la Malla
 * @tparam T
 * @param x
 * @param y
 * @param dato
 */
template<typename T>
void MallaRegular<T>::insertarCasilla(float x, float y, const T& dato) {
    Casilla *c = obtenerCasilla(x,y);
    //Comprobamos si la casilla esta en la malla
    //Si no esta lo metemos
   if(!c->buscar(dato)){
        c->insertar(dato);
    }
    tamlog++;
}
/**
 * @brief Constructor parametrizado de la Malla donde creamos la Malla
 * @tparam T
 * @param x
 * @param y
 * @param dato
 */
template<typename T>
MallaRegular<T>::MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int aNDiv):
xMin(aXMin), yMin(aYMin), xMax(aXMax), yMax(aYMax), nDiv(aNDiv),tamlog(0){
    tamaCasillaX = (xMax - xMin)/aNDiv;
    tamaCasillaY = (yMax - yMin)/aNDiv;
    mr.insert(mr.begin(), aNDiv, vector<Casilla>(aNDiv));
    mr.resize(aNDiv,  vector<Casilla>(aNDiv));
}


#endif //PR6_MALLAREGULAR_H

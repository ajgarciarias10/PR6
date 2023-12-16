#ifndef PRACTICA_1B_UTM_H
#define PRACTICA_1B_UTM_H
/**
 * @file UTM.h
 * @date 04/10/2023
 * @author Antonio José Garcia Arias, ajga001@red.ujaen.es
 * @author Abraham Garcia Hurtado, agh00040@red.ujaen.es
 * @brief UTM
 */

class UTM {
private:
    float latitud;

    float longitud;
public:


    UTM();

    UTM( float  latitud, float longitud);

    float getLatitud() ;

    void setLatitud(float latitud);

    float getLongitud() ;

    void setLongitud(float longitud);
    virtual ~UTM();
};


#endif //PRACTICA_1B_UTM_H

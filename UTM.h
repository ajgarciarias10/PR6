#ifndef PRACTICA_1B_UTM_H
#define PRACTICA_1B_UTM_H

#include <iostream>

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

    UTM(float latitud, float longitud) : latitud(latitud), longitud(longitud) {
    }
    UTM():latitud(0.0),longitud(0.0){};

    virtual ~UTM() {}

    float getLatitud() const {
        return latitud;
    }

    void setLatitud(float latitud) {
        UTM::latitud = latitud;
    }

    float getLongitud() const {
        return longitud;
    }

    void setLongitud(float longitud) {
        UTM::longitud = longitud;
    }
};


#endif //PRACTICA_1B_UTM_H

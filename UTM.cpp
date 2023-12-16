#include "UTM.h"

UTM::UTM( float latitudj,  float longitudj):
latitud(latitudj),longitud(longitudj) {}
float UTM::getLatitud()  {
    return latitud;
}

void UTM::setLatitud(float latitud) {
    UTM::latitud = latitud;
}

float UTM::getLongitud()  {
    return longitud;
}

void UTM::setLongitud(float longitud) {
    UTM::longitud = longitud;
}

UTM::~UTM() {

}

UTM::UTM():latitud(0.0),longitud(0.0) {

}

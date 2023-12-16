cmake_minimum_required(VERSION 3.26)
project(PR6)

set(CMAKE_CXX_STANDARD 17)

add_executable(PR6 main.cpp  Ruta.h Ruta.cpp VuelaFlight.cpp VuelaFlight.h   UTM.h Aeropuerto.cpp Aerolinea.cpp Aeropuerto.h Aerolinea.h
        Vuelo.cpp Vuelo.h  fecha.cpp fecha.h
        MallaRegular.h)

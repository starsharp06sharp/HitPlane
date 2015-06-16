#include "Sky.h"

float nowSCALE = 0.8;

int main( void ) {
    Sky sky;

    if ( sky.showStartInterface() ) {
        while( sky.mainLoop() )
            ;
    }

    return 0;
}

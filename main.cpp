#include "Sky.h"

float nowSCALE = SCALE;

int main( void ) {
    Sky sky;

    if ( sky.showStartInterface() ) {
        while( sky.mainLoop() )
            ;
    }

    return 0;
}

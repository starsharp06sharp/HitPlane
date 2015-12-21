#include "Sky.h"

float nowSCALE = SCALE;

int main( void ) {
    Sky* sky = Sky::getInstance();

    if ( sky -> showStartInterface() ) {
        while( sky -> mainLoop() )
            ;
    }

    return 0;
}

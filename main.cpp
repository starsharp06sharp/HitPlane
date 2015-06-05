#include "Sky.h"


int main( void ) {
    Sky sky;

    if (sky.showStartInterface()) {
        do {
            sky.mainLoop();
        }while(sky.showGameOverInterface());
    }

    return 0;
}

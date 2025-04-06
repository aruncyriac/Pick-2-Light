/*
 * File:   ssd.c
 * Author: arunc
 *
 * Created on 28 January, 2025, 11:21 AM
 */
#include "main.h"

void display(unsigned char *ssd) {

    for (char i = 0; i < 4; i++) {

        PORTD = ssd[i]; //set data data to port d
        PORTA = (PORTA & 0xf0) | (1 << i); //control line to one each 7 seg. display
        for (unsigned int wait = 1000; wait--;);//blocking delay
    }


}
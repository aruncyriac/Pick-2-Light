/*
 * File:   digital_key.c
 * Author: arunc
 *
 * Created on 28 January, 2025, 11:18 AM
 */

#include "main.h"
unsigned char read_dkp_edge()
{
    static unsigned char once = 1;
    if((PORTC & 0x0f) != 0x0f && once)
    {
        once = 0;
        return (PORTC & 0x0f);
    }
    else if((PORTC & 0x0f) == 0x0f)
    {
        once = 1;
    }
    return 0x0f;
}
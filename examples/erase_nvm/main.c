/*
 * Copyright (c) 2021 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 *
 * This example can be used to erase the NVM storage on a device.
 *
 */

#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "pico/lorawan.h"
#include "tusb.h"

// pin configuration for SX12xx radio module
const struct lorawan_sx12xx_settings sx12xx_settings = {
        .spi = {
                .inst = spi1,
                .mosi = 11,
                .miso = 12,
                .sck  = 10,
                .nss  = 3
        },
        .reset = 15,
        .busy = 2,
        // .dio0  = 7,
        .dio1  = 20
};

// LoRaWAN region to use, full list of regions can be found at:
//   http://stackforce.github.io/LoRaMac-doc/LoRaMac-doc-v4.5.1/group___l_o_r_a_m_a_c.html#ga3b9d54f0355b51e85df8b33fd1757eec
#define LORAWAN_REGION LORAMAC_REGION_US915

int main( void )
{
    // initialize stdio and wait for USB CDC connect
    stdio_init_all();

    while (!tud_cdc_connected()) {
        tight_loop_contents();
    }
    printf("Pico LoRaWAN - Erase NVRAM\n\n");

    // initialize the LoRaWAN stack
    printf("Initilizating LoRaWAN ... ");
    if (lorawan_init(&sx12xx_settings, LORAWAN_REGION) < 0) {
        printf("failed!!!\n");
        while (1) {
            tight_loop_contents();
        }
    } else {
        printf("success!\n");
    }

    printf("Erasing NVM ... ");
    if (lorawan_erase_nvm() < 0) {
        printf("failed!!!\n");
    } else {
        printf("success!\n");
    }

    while (1) {
        tight_loop_contents();
    }
}

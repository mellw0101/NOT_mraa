/*
 * Author: Lay, Kuan Loon <kuan.loon.lay@intel.com>
 * Copyright (c) 2015 Intel Corporation.
 *
 * SPDX-License-Identifier: MIT
 */

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../include/api/common.h"
#include "../include/intel_sofia_3gr.h"

#define PLATFORM_NAME "SoFIA 3GR"

mraa_board_t *
mraa_intel_sofia_3gr()
{
    mraa_board_t *b = (mraa_board_t *)calloc(1, sizeof(mraa_board_t));
    if (b == NULL)
    {
        return NULL;
    }

    b->platform_name = PLATFORM_NAME;
    b->phy_pin_count = MRAA_INTEL_SOFIA_3GR_PINCOUNT;

    b->adv_func = (mraa_adv_func_t *)calloc(1, sizeof(mraa_adv_func_t));
    if (b->adv_func == NULL)
    {
        goto error;
    }

    b->pins = (mraa_pininfo_t *)calloc(MRAA_INTEL_SOFIA_3GR_PINCOUNT, sizeof(mraa_pininfo_t));
    if (b->pins == NULL)
    {
        free(b->adv_func);
        goto error;
    }

    strncpy(b->pins[0].name, "I2C1SCL", 8);
    b->pins[0].capabilities  = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 1, 0, 0};
    b->pins[0].i2c.pinmap    = 1;
    b->pins[0].i2c.mux_total = 0;

    strncpy(b->pins[1].name, "I2C1SDA", 8);
    b->pins[1].capabilities  = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 1, 0, 0};
    b->pins[1].i2c.pinmap    = 1;
    b->pins[1].i2c.mux_total = 0;

    strncpy(b->pins[2].name, "I2C2SCL", 8);
    b->pins[2].capabilities  = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 1, 0, 0};
    b->pins[2].i2c.pinmap    = 1;
    b->pins[2].i2c.mux_total = 0;

    strncpy(b->pins[3].name, "I2C2SDA", 8);
    b->pins[3].capabilities  = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 1, 0, 0};
    b->pins[3].i2c.pinmap    = 1;
    b->pins[3].i2c.mux_total = 0;

    strncpy(b->pins[4].name, "I2C3SCL", 8);
    b->pins[4].capabilities  = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 1, 0, 0};
    b->pins[4].i2c.pinmap    = 1;
    b->pins[4].i2c.mux_total = 0;

    strncpy(b->pins[5].name, "I2C3SDA", 8);
    b->pins[5].capabilities  = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 1, 0, 0};
    b->pins[5].i2c.pinmap    = 1;
    b->pins[5].i2c.mux_total = 0;

    strncpy(b->pins[6].name, "I2C4SCL", 8);
    b->pins[6].capabilities  = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 1, 0, 0};
    b->pins[6].i2c.pinmap    = 1;
    b->pins[6].i2c.mux_total = 0;

    strncpy(b->pins[7].name, "I2C4SDA", 8);
    b->pins[7].capabilities  = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 1, 0, 0};
    b->pins[7].i2c.pinmap    = 1;
    b->pins[7].i2c.mux_total = 0;

    return b;
error:
    syslog(LOG_CRIT, "SoFIA 3GR: Platform failed to initialise");
    free(b);
    return NULL;
}

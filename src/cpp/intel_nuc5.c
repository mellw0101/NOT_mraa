/*
 * Author: Brendan Le Foll <brendan.le.foll@intel.com>
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
#include "../include/intel_nuc5.h"

#define PLATFORM_NAME    "Intel NUC5"
#define SYSFS_CLASS_GPIO "/sys/class/gpio"
#define I2CNAME          "designware"

mraa_board_t *
mraa_intel_nuc5()
{
    mraa_board_t *b = (mraa_board_t *)calloc(1, sizeof(mraa_board_t));
    if (b == NULL)
    {
        return NULL;
    }

    b->platform_name = PLATFORM_NAME;
    b->phy_pin_count = MRAA_INTEL_NUC5_PINCOUNT;

    b->adv_func = (mraa_adv_func_t *)calloc(1, sizeof(mraa_adv_func_t));
    if (b->adv_func == NULL)
    {
        goto error;
    }

    b->pins = (mraa_pininfo_t *)calloc(MRAA_INTEL_NUC5_PINCOUNT, sizeof(mraa_pininfo_t));
    if (b->pins == NULL)
    {
        free(b->adv_func);
        goto error;
    }

    strncpy(b->pins[0].name, "1.8v", 8);
    b->pins[0].capabilities = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 0, 0, 0};

    strncpy(b->pins[1].name, "GND", 8);
    b->pins[1].capabilities = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 0, 0, 0};
    strncpy(b->pins[2].name, "HDMIcec", 8);
    b->pins[2].capabilities = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 0, 0, 0};
    strncpy(b->pins[3].name, "DMICclk", 8);
    b->pins[3].capabilities = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 0, 0, 0};
    strncpy(b->pins[4].name, "3.3v", 8);
    b->pins[4].capabilities = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 0, 0, 0};
    strncpy(b->pins[5].name, "DMICda", 8);
    b->pins[5].capabilities = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 0, 0, 0};
    strncpy(b->pins[6].name, "Key", 8);
    b->pins[6].capabilities = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 0, 0, 0};
    strncpy(b->pins[7].name, "SMB-A", 8);
    b->pins[7].capabilities = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 0, 0, 0};
    strncpy(b->pins[8].name, "5v", 8);
    b->pins[8].capabilities = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 0, 0, 0};
    strncpy(b->pins[9].name, "SCI", 8);
    b->pins[9].capabilities = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 0, 0, 0};

    strncpy(b->pins[10].name, "PWM0", 8);
    b->pins[10].capabilities  = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 0, 0, 0};
    b->pins[10].pwm.pinmap    = 0;
    b->pins[10].pwm.parent_id = 0;
    b->pins[10].pwm.mux_total = 0;

    strncpy(b->pins[11].name, "PWM1", 8);
    b->pins[11].capabilities  = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 0, 0, 0};
    b->pins[11].pwm.pinmap    = 0;
    b->pins[11].pwm.parent_id = 1;
    b->pins[11].pwm.mux_total = 0;

    strncpy(b->pins[12].name, "I2C0SCL", 8);
    b->pins[12].capabilities  = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 1, 0, 0};
    b->pins[12].i2c.pinmap    = 1;
    b->pins[12].i2c.mux_total = 0;

    strncpy(b->pins[13].name, "I2C0SDA", 8);
    b->pins[13].capabilities  = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 1, 0, 0};
    b->pins[13].i2c.pinmap    = 1;
    b->pins[13].i2c.mux_total = 0;

    strncpy(b->pins[14].name, "I2C1SCL", 8);
    b->pins[14].capabilities  = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 1, 0, 0};
    b->pins[14].i2c.pinmap    = 1;
    b->pins[14].i2c.mux_total = 0;

    strncpy(b->pins[15].name, "I2C1SDA", 8);
    b->pins[15].capabilities  = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 1, 0, 0};
    b->pins[15].i2c.pinmap    = 1;
    b->pins[15].i2c.mux_total = 0;

    strncpy(b->pins[16].name, "SMB_CLK", 8);
    b->pins[16].capabilities = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 0, 0, 0};
    strncpy(b->pins[17].name, "SMB_SDA", 8);
    b->pins[17].capabilities = (mraa_pincapabilities_t) {1, 0, 0, 0, 0, 0, 0, 0};

    b->i2c_bus_count = 0;
    int i2c_num      = -1;
    int i;
    for (i = 0; i < 2; i++)
    {
        i2c_num = mraa_find_i2c_bus(I2CNAME, i2c_num + 1);
        if (i2c_num == -1)
        {
            break;
        }
        b->i2c_bus_count++;
        b->i2c_bus[i].bus_id = i2c_num;
        b->i2c_bus[i].sda    = 12 + (i * 2);
        b->i2c_bus[i].scl    = 13 + (i * 2);
    }

    if (b->i2c_bus_count > 0)
    {
        b->def_i2c_bus = b->i2c_bus[0].bus_id;
    }

    return b;
error:
    syslog(LOG_CRIT, "nuc5: Platform failed to initialise");
    free(b);
    return NULL;
}

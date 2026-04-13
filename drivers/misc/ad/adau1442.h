/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * ADAU1442 SigmaDSP Audio Processor - Register Definitions & ioctl Interface
 */

#ifndef ADAU1442_H
#define ADAU1442_H

#include <linux/miscdevice.h>

struct adau1442_priv {
    struct regmap *regmap;
    struct miscdevice	 miscdev;
    struct device *dev;
};

int adau1442_load_firmware(struct adau1442_priv *priv, unsigned int reg, const unsigned char *val, unsigned int val_cnt);

#endif

//#include "firmware/OP-ILAPU_DSP_VER10_20260406_IC_1.h"
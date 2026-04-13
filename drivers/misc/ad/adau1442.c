// SPDX-License-Identifier: GPL-2.0 only
/*
 * Copyright 2026 ONPOOM Corp.
 */

#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/regmap.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/bsearch.h>
#include <linux/firmware.h>
#include <linux/types.h>
#include <linux/ioctl.h>
#include <asm/unaligned.h>

#include "adau1442.h"

 // int adau1442_load_firmware(struct adau1442_priv *priv, unsigned int reg, const ADI_REG_TYPE *val, size_t val_cnt);

 // #define ADI_REG_TYPE    u8
 // #define SIGMA_WRITE_REGISTER_BLOCK(pv, addr, size, data)
 //     adau1442_load_firmware(pv, addr, size, (const ADI_REG_TYPE *)data)

#include "firmware/OP-ILAPU_DSP_VER10_20260406_IC_1.h"

/* -----------------------------------------------------------------------
 * regmap configuration
 *   - 16-bit register address, 32-bit value
 *   - accessible registers defined by adau1442_reg_list[] (not a range)
 *   - regmap_raw_write() used for safeload (multi-word parameter writes)
 * ----------------------------------------------------------------------- */
 // static const struct regmap_config adau1442_regmap_config = {
 //     .reg_bits = 16,
 //     .val_bits = 32,
 //     .max_register = ADAU1442_SOFT_RESET,   /* highest addr in reg_list */
 //     .readable_reg = adau1442_accessible_reg,
 //     .writeable_reg = adau1442_accessible_reg,
 //     .cache_type = REGCACHE_NONE,
 // };

int adau1442_load_firmware(struct adau1442_priv *priv, unsigned int reg, const unsigned char *val, unsigned int val_cnt)
{
    // const struct firmware *fw;
    // const u8 *p, *end;
    // u8 instr;
    // u32 payload_len;
    // u16 addr;
    int ret;

    dev_info(priv->dev, "loading firmware %s (reg=%u, val_cnt=%u)\n",
        "adau1442", reg, val_cnt);

    ret = regmap_noinc_write(priv->regmap, reg, val, val_cnt);
    if (ret) {
        dev_err(priv->dev, "loading firmware failed (dev=%s, reg=%u, val_cnt=%u)\n",
            "adau1442", reg, val_cnt);
        return ret;
    }

    dev_info(priv->dev, "firmware loaded successfully\n");

    return ret;
}

/* -----------------------------------------------------------------------
 * File operations
 * ----------------------------------------------------------------------- */
static int adau1442_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int adau1442_release(struct inode *inode, struct file *file)
{
    return 0;
}

static long adau1442_ioctl(struct file *file, unsigned int cmd,
    unsigned long arg)
{
    // struct adau1442_priv *priv =
    //     container_of(file->private_data, struct adau1442_priv, miscdev);
    // void __user *argp = (void __user *)arg;
    // struct adau1442_reg_io rio;
    // struct adau1442_safeload_io sio;
    // unsigned int val;
    // int ret;

    // switch (cmd) {
    // case ADAU1442_REG_READ:
    //     if (copy_from_user(&rio, argp, sizeof(rio)))
    //         return -EFAULT;
    //     ret = regmap_read(priv->regmap, rio.reg, &val);
    //     if (ret)
    //         return ret;
    //     rio.val = (u8)val;
    //     return copy_to_user(argp, &rio, sizeof(rio)) ? -EFAULT : 0;

    // case ADAU1442_REG_WRITE:
    //     if (copy_from_user(&rio, argp, sizeof(rio)))
    //         return -EFAULT;
    //     return regmap_write(priv->regmap, rio.reg, rio.val);

    // case ADAU1442_SAFELOAD:
    //     if (copy_from_user(&sio, argp, sizeof(sio)))
    //         return -EFAULT;
    //     return adau1442_safeload(priv, sio.addr, sio.data, sio.len);

    // default:
    //     return -ENOTTY;
    // }
    return 0;
}

static const struct file_operations adau1442_fops = {
    .owner = THIS_MODULE,
    .open = adau1442_open,
    .release = adau1442_release,
    .unlocked_ioctl = adau1442_ioctl,
};

/* -----------------------------------------------------------------------
 * Probe / Remove  (called from adau1442-i2c.c)
 * ----------------------------------------------------------------------- */
int adau1442_probe(struct device *dev, struct regmap *regmap)
{
    struct adau1442_priv *priv;
    int ret;

    priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
    if (!priv)
        return -ENOMEM;

    priv->dev = dev;
    priv->regmap = regmap;

    priv->miscdev.minor = MISC_DYNAMIC_MINOR;
    priv->miscdev.name = "adau1442";
    priv->miscdev.fops = &adau1442_fops;
    priv->miscdev.parent = dev;

    ret = misc_register(&priv->miscdev);
    if (ret) {
        dev_err(dev, "misc_register failed: %d\n", ret);
        return ret;
    }

    dev_set_drvdata(dev, priv);
    dev_info(dev, "ADAU1442 registered as /dev/%s\n", priv->miscdev.name);

    //ret = adau1442_load_firmware(priv);
    default_download_IC_1(priv);
    // if (ret < 0) {
    //     misc_deregister(&priv->miscdev);
    //     return ret;
    // }
    return 0;
}
EXPORT_SYMBOL_GPL(adau1442_probe);

void adau1442_remove(struct device *dev)
{
    struct adau1442_priv *priv = dev_get_drvdata(dev);

    misc_deregister(&priv->miscdev);
}
EXPORT_SYMBOL_GPL(adau1442_remove);

MODULE_DESCRIPTION("ADAU1442 SigmaDSP audio processor driver");
MODULE_AUTHOR("ojw");
MODULE_LICENSE("GPL");

// SPDX-License-Identifier: GPL-2.0-only
/*
 * ADAU1442 SigmaDSP Audio Processor - I2C bus glue
 */

#include <linux/i2c.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>
#include <linux/regmap.h>

#include "adau1442.h"

 /* forward declarations from adau1442.c */
int  adau1442_probe(struct device *dev, struct regmap *regmap);
void adau1442_remove(struct device *dev);

static bool adau1442_volatile_reg(struct device *dev, unsigned int reg)
{
    return true;
}

static const struct regmap_config adau1442_i2c_regmap_config = {
    .reg_bits = 16,
    .val_bits = 8,
    // .max_register = 0x081F,
    // .cache_type = REGCACHE_RBTREE,
    .volatile_reg = adau1442_volatile_reg,
    .cache_type = REGCACHE_NONE,
};

static int adau1442_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    struct regmap *regmap;

    regmap = devm_regmap_init_i2c(client, &adau1442_i2c_regmap_config);
    if (IS_ERR(regmap))
        return PTR_ERR(regmap);

    return adau1442_probe(&client->dev, regmap);
}

static int adau1442_i2c_remove(struct i2c_client *client)
{
    adau1442_remove(&client->dev);

    return 0;
}

static const struct i2c_device_id adau1442_i2c_ids[] = {
    { "adau1442", 0 },
    { }
};
MODULE_DEVICE_TABLE(i2c, adau1442_i2c_ids);

static const struct of_device_id adau1442_of_ids[] = {
    {.compatible = "adi,adau1442" },
    { }
};
MODULE_DEVICE_TABLE(of, adau1442_of_ids);

static struct i2c_driver adau1442_i2c_driver = {
    .driver = {
        .name = "adau1442",
        .of_match_table = adau1442_of_ids,
    },
    .probe = adau1442_i2c_probe,
    .remove = adau1442_i2c_remove,
    .id_table = adau1442_i2c_ids,
};
module_i2c_driver(adau1442_i2c_driver);

MODULE_DESCRIPTION("ADAU1442 SigmaDSP audio processor I2C driver");
MODULE_AUTHOR("ojw");
MODULE_LICENSE("GPL");

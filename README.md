# Linux kernel

There are several guides for kernel developers and users. These guides can
be rendered in a number of formats, like HTML and PDF. Please read
Documentation/admin-guide/README.rst first.

In order to build the documentation, use ``make htmldocs`` or
``make pdfdocs``.  The formatted documentation can also be read online at:

    https://www.kernel.org/doc/html/latest/

There are various text files in the Documentation/ subdirectory,
several of them using the Restructured Text markup notation.

Please read the Documentation/process/changes.rst file, as it contains the
requirements for building and running the kernel, and information about
the problems which may result by upgrading your kernel.

===========================================================================


## som-8gb_board

Brought-up by ONPOOM Corp.

This board is based on NXP Corp's imx8m-plus EVK and consists of 
imx8m-plus AP(CPU: A53 x4 & M7 x1), 8GB RAM, 32GB eMMC, etc.

### 1. LPDDR 8GB bring-up

### 2. DWC USB3.0(compatible USB2.0) bring-up
- dwc3_usb0 is set otg port. type-C subsystem is configured by extcon subsystem 
used ptn5150. if host mode, ptn5150 is required vbus-gpio pin which supply voltage to device. So vbus-gpio pin is set. Unfortunately kernel version 5.15.71 supports unstable extcon subsystem, so kernel code is modified with reference to kernel version 6.6.
- dwc3_usb1 is set host port.

===========================================================================

## jig_board

Brought-up by ONPOOM Corp.

This board is based on ONPOOM Corp's imx8m-plus som-8gb_board and consists of various interfaces(usb, uart, usdhc, i2c, i2s, spi, mipi-csi, mipi-=dsi, lvds, etc.) for testing.

### 1. Ethernet bring-up
- Enabled internal pull-up for reset pin. Both eqos and fec.
- AR8031 E-PHY address is 0x4. Both eqos and fec.
- Assert and deassert time is set respectively 10ms and 20ms.
Recommended by AR8031 datasheet.

### 2. SD/MMC bring-up
- vsel pin is set floating for default mode. Refer to op-imx8mp10 schematics.
- switch reg pin is set usdhc2 vmmc reg pin. Refer to op-imx8mp10 schematics.

### 3. Backlight driver bring-up
- Use MP3309C backlight ic.
- MP3309C driver is added from kernel version 6.6. because now kernel version is not included it.
- Partially modified driver why is not compatible.

### 4. MIPI-DSI bring-up
- mipi-dsi panel, mipi-dsi port is written in devicetree. (arch/arm64/boot/dts/freescale/imx8mp-onpoom-jig.dts)

### 5. 10.1 inch LCD panel bring-up
- Panel configuration is set in driver. (driver/gpu/drm/panel/panel-simple.c)
- Panel compatible name is "solics,ec101-1024600w-d024".
- Configuration info is written in datasheet.
- Set panel regulator pin in devicetree. because of internal pull-up required by H/W Team.

### 6. Touch IC bring-up
- Use GT928 touch ic.
- Set configuration goodix driver 'y'.
- Set interrupt pin in devicetree.
- Set reset pin in devicetree.
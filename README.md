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


## jig_board

Brought-up by ONPOOM Corp.

This board is based on ONPOOM Corp's imx8m-plus som-8gb_board and consists of 
various interfaces(usb, uart, usdhc, i2c, i2s, spi, mipi-csi, mipi-dsi, lvds, 
etc.) for testing.

# Ethernet bring-up
- Mismatch address with schematics. 
In case of address(0x4), normally operates. (hardware team must check.)
- Reset pin operates abnormally. Pull-up voltage be dropped. 
When internal pull-up manually enabled 
and chanegs gpio active flags in source code(in order to low to high), 
ethernet phy chip is enabled. (may be suspected short.)

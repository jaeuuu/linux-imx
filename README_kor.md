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

주식회사 온품에 의해 개발됨.

이 보드는 NXP사의 imx8m-plus EVK 보드를 기반으로 하며, imx8m-plus AP, 8GB RAM, 32GB eMMC
등으로 구성됨.

### 1. LPDDR 8GB bring-up

### 2. DWC USB3.0(compatible USB2.0) bring-up
- dwc3_usb0은 otg port로 설정됨. type-C 서브시스템은 ptn5150을 사용하여 extcon 서브시스템에 의해 구성됨.
host mode 일 경우, ptn5150은 device에게 전원 공급을 위해 vbus-gpio 설정이 필요함. 
아쉽게도 kernel version 5.15.71에서 extcon 서브시스템을 불안정하게 지원하여, kernel version 6.6을 참고하여 
kernel code가 일부 수정됨.
- dwc3_usb1은 host port로 설정됨.

===========================================================================

## jig_board

주식회사 온품에 의해 개발됨.

이 보드는 온품사의 imx8m-plus som-8gb 보드를 기반으로 하며, 여러 인터페이스를(usb, usdhc, i2c, uart, i2s, spi, mipi-csi, mipi-dsi, lvds etc.) 테스트하기 위해 구성됨.

### 1. Ethernet bring-up
- 리셋 핀을 위해 내부 풀업을 활성화함. eqos와 fec 모두에 적용.
- AR8031 E-PHY 주소는 0x4임. eqos와 fec 모두에 적용.
- assert 와 deassert 시간은 각각 10ms와 20ms로 설정됨. 데이터시트에서 권장하는 값임.

### 2. SD/MMC bring-up
- vsel 핀은 디폴트 모드를 위해 플로팅상태로 설정됨. op-imx8mp10 회로도 참고.
- 스위칭 레귤레이터 핀은 vmmc 레귤레이터 핀으로 설정됨. op-imx8mp10 회로도 참고.

### 3. Backlight driver bring-up
- MC3309C backlight ic를 사용함.
- MP3309C 드라이버는 kernel version 6.6에서 가져와 추가함. 현재 5.15.71 에서는 포함되어 있지 않기 때문임.
- 드라이버 호환성 때문에 부분적으로 수정됨.

### 4. MIPI-DSI bring-up
- mipi-dsi 패널, mipi-dsi port에 대해 디바이스 트리에 작성함.

### 5. 10.1 inch LCD panel bring-up (MIPI-DSI)
- 패널 설정은 드라이버에 추가됨.
- 패널 compatible 이름은 "solics,ec101-1024600w-d024".
- 설정 정보는 데이터시트에 기재되어 있음.
- 패널 리셋 핀을 레귤레이터로 설정함. 하드웨어 팀 요청으로 내부 풀업 설정함.

### 6. Touch IC bring-up
- GT928 touch ic 사용함.
- goodix 드라이버 설정 'y'로 함.
- 인터럽트 핀을 디바이스 트리에 작성함.
- 리셋 핀을 디바이스 트리에 작성함.

### 7. LVDS bring-up
- lvds 패널, lvds 포트는 디바이스 트리에 작성됨.

### 8. 10.1 inch LCD panel bring-up (LVDS)
- 패널 설정은 드라이버에 작성됨.
- 패널 compatible 이름은 "solics,ec101-1024600w-d025".
- 설정 정보는 데이터시트에 기재되어 있음.
- 패널 리셋 핀을 레귤레이터로 설정함. 하드웨어 팀 요청으로 내부 풀업 설정함. (MIPI-DSI 패널과 공유함.)

### 9. I2C-IO bring-up
- pca6416 ic 사용함.
- I2C-IO 설정은 디바이스 트리에 작성됨.

### 10. SPI-IO bring-up
- mcp23s17 ic 사용함.
- SPI-IO 설정은 디바이스 트리에 작성됨.

### 11. PCIe to UART bring-up
- Use AX99100 Multi-I/O ic.

### 12. Audio Out bring-up
- Use sai3 interface.

### 13. Audio In bring-up
- Use sai2 interface.

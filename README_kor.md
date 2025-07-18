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

먼저, 디바이스트리를 확인하여 변경사항을 비교해볼 것.

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
- codec으로 max98357a ic 사용함. i2s-to-hcg 변환 ic.

### 13. Audio In bring-up
- Use sai2 interface.
- codec으로 dir9001 ic 사용함. spdif-to-i2s 변환 ic.
- 반드시 sai 노드에 "fsl,sai-asynchronous" 속성을 활성화 해야한다.

### 14. Supervisor current & voltage bring-up
- Use ina260 ic.
- INA260 드라이버는 커널 6.16을 참고하여 기존 INA2XX 시리즈 드라이버에 추가함. (drivers/hwmon/ina2xx.c)
- INA260 ic 를 적용하기 위해 다소 많은 부분이 수정됨. (drivers/hwmon/ina2xx.c)
- INA260 ic는 sysfs를 통해 값을 설정 및 확인함.
- 제한 값에 따라 ALERT LED 및 ALARM bit 확인.
- 다른 INA2XX 시리즈와 다르게 INA260은 shunt voltage 레지스터를 current 레지스터로 사용함.
- curr1_crit, curr1_input, curr1_lcrit, curr1_crit_alarm, curr1_lcrit_alarm 등의 sysfs 속성을 추가하여,
기존 shunt voltage 관련 레지스터를 current 관련 레지스터로 사용토록 함.

### 15. MIPI-CSI bring-up
- NXP사의 ov5640 ic를 사용한 카메라 기능을 통해 인터페이스 확인함.
- ov5640 ic 드라이버가 module로서 존재하므로 모듈 로딩을 위해 /lib/modules/xxx 경로명을 'uname -a'로 출력되는 이름과 일치시켜야 함.
- vt4l2-ctl 명령어를 사용하여 캡처 기능을 통해 카메라의 동작을 확인함.
- 명령어는 다음과 같으며, 출력된 이미지를 png형식으로 변환하여 확인 함.
```
v4l2-ctl --device /dev/video3 \
        --set-fmt-video=width=640,height=480,pixelformat=YUYV \
        --stream-mmap \
        --stream-to=frame.raw \
        --stream-count=1
```

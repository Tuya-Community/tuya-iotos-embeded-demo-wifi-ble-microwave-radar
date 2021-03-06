# Tuya IoTOS Embeded Demo WiFi & BLE microwave rader

[English](./README.md) | [中文](./README_zh.md)

## Introduction 


This Demo is based on Tuya Smart Cloud Platform, Tuya Smart APP, IoTOS Embeded WiFi &Ble SDK, using Tuya WiFi/WiFi+BLE series modules to quickly set up a microwave radar sensor demo that can sense the presence of the human body and upload the situation to the mobile APP.
## Quick start

### Compile and burn-in
+ Download [Tuya IoTOS Embeded WiFi & BLE sdk](https://github.com/tuya/tuya-iotos-embeded-sdk-wifi-ble-bk7231n) 

+ Download the demo to the apps directory of the SDK 

  ```bash
  $ cd apps
  $ git clone https://github.com/Tuya-Community/tuya-iotos-embeded-demo-wifi-ble-microwave-radar.git
  ```
  
+ Execute the following command in the SDK root directory to start compiling.

  ```bash
  sh build_app.sh apps/bk7231n_radar_demo bk7231n_radar_demo 1.0.0 
  ```

+ Firmware burn-in license information please refer to: [Wi-Fi + BLE series module burn-in license](https://developer.tuya.com/cn/docs/iot/device-development/burn-and-authorization/burn-and-authorize-wifi-ble-modules/burn-and-authorize-wb-series-modules?id=Ka78f4pttsytd) 



### File description
```
├── src	
|    |
|    ├── app_soc                  
|    ├── tuya_device.c          
|    ├── app_radar.c               
|    └── app_control.c           
|
├── include			
|    |
|    ├── app_soc
|    ├── tuya_device.h
|    ├── app_radar.h
|    └── app_control.h
|
└── output        
```

<br>

### Application entry
Entry file: tuya_device.c

Important functions: device_init()

+ Call tuya_iot_wf_soc_dev_init_param() interface to initialize the SDK, configure the operating mode, the mating mode, and register various callback functions and store the firmware key and PID.
+ Calling the tuya_iot_reg_get_wf_nw_stat_cb() interface to register the device network status callback functions.
+ Calling the application layer initialization function app_radar_init()

<br>

### dp point related

+ Send down dp point data stream: dev_obj_dp_cb() -> deal_dp_proc()
+ Report dp point interface: dev_report_dp_json_async()

| function name | OPERATE_RET dev_report_dp_json_async(IN CONST CHAR_T *dev_id,IN CONST TY_OBJ_DP_S *dp_data,IN CONST UINT_T cnt)|
| ---|--|
| devid | device id (if it is a gateway, MCU, SOC class device then devid = NULL; if it is a sub-device, then devid = sub-device_id)|
| dp_data | dp structure array name|
| cnt | number of elements of the dp structure array|
| return | OPRT_OK: Success Other: Failure |

### I/O List

|radar sensor||
| --- | --- |
|radar `TXD` : soc `RXD2`||




<br>


## Related Documents

Tuya Demo Center: https://developer.tuya.com/demo


<br>


## Technical Support

You can get support for Tuya by using the following methods:

- Developer Center: https://developer.tuya.com
- Help Center: https://support.tuya.com/help
- Technical Support Work Order Center: [https://service.console.tuya.com](https://service.console.tuya.com/) 


<br>



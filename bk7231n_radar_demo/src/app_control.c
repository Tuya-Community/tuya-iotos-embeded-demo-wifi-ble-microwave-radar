/*
 * @Author: zgw
 * @email: liang.zhang@tuya.com
 * @LastEditors: zgw
 * @file name: sht21.h
 * @Description: SHT21 IIC drive src file
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2020-12-16 18:51:29
 * @LastEditTime: 2021-03-12 17:23:11
 */

#include "app_control.h"
#include "tuya_gpio.h"
#include "tuya_uart.h"
#include "BkDriverUart.h"
#include "sys_timer.h"
#include "uni_time.h"
/***********************************************************
*************************types define***********************
***********************************************************/
typedef enum
{
    LOW = 0,
    HIGH,
}default_level;

APP_CTRL_DATA_T app_ctrl_data = {0};
/***********************************************************
*************************IO control device define***********
***********************************************************/


/***********************************************************
*************************about adc init*********************
***********************************************************/


/***********************************************************
*************************about iic init*********************
***********************************************************/

/***********************************************************
*************************function***************************
***********************************************************/

STATIC VOID __ctrl_gpio_init(CONST TY_GPIO_PORT_E port, CONST BOOL_T high)
{   
    //Set IO port as output mode
    tuya_gpio_inout_set(port, FALSE);
    //Set IO port level
    tuya_gpio_write(port, high);
}


VOID app_device_init(VOID)
{
    INT_T op_ret = 0;


}

STATIC CHAR_T get_radar_data(UCHAR_T *data, UCHAR_T size)
{
    UCHAR_T buffer[100];
    UCHAR_T i,j;
    memset(buffer, 0, sizeof(buffer));
    bk_uart_recv(TY_UART1, buffer, 99, 50);
    for(i = 0; i < 100; i++) {
        if((buffer[i] == 'S')&&((i + size) < 100)) {
            for(j = 0; j < size; j++) {
                if(buffer[i+j] != 'L') {
                    data[j] = buffer[i+j];
                }else{
                    return 0;
                }
            }
            //未找到换行符
            return -1;
        }
    }
    //未找到'S'
    return -1;
}

VOID app_get_sensor_data(VOID)
{   
    UCHAR_T data[50];
    memset(data, 0, sizeof(data));

    CHAR_T opt;
    opt = get_radar_data(data,50);
    if(opt == 0){
        UCHAR_T i;
        if((data[0] == 'S')&&(data[6] == ':')) {
            if(data[8] == '[') {
                app_ctrl_data.presence_state = presence;
            }else {
                app_ctrl_data.presence_state = peaceful;
                app_ctrl_data.target_distance = 1000;
                PR_NOTICE("--------NO MAN AROUND-----------");
            }  
        }
        if(app_ctrl_data.presence_state == peaceful) {
            return ;
        }
        for(i=0;i<50;i++) {
            if(data[i]=='R') {
                if((data[i+8] >= '0')&&(data[i+8] <= '9')) {
                    app_ctrl_data.target_distance = ((data[i+7] - '0') * 10) + (data[i+8] - '0');
                }else {
                    app_ctrl_data.target_distance = (data[i+7] - '0');
                }
                PR_NOTICE("--------Human_distance = %d-----------",app_ctrl_data.target_distance);
                return ;        
            }    
        }
    }
}


VOID app_ctrl_all_off(VOID)
{   

}

 
#### 说明

本工程为大一参加学校电协的寒假考核做的超声波避障小车。
基于STM32F103C8T6，三轮差速转向。L298N电机驱动，SPI-OLED屏幕显示，HC-SR04超声波模块

#### 引脚使用：
|  外设   |              引脚               |
| :-----: | :-----------------------------: |
|   led   |              PB12               |
| usart1  | PA9(USART1_TX), PA10(USART1_RX) |
|   pwm   |      PA6(TIM3),  PB6(TIM4)      |
|  motor  |        PB0,PB1, PB3,PB4         |
|  oled   |       PB12,PB13,PB14,PB15       |
| hc-sr04 |  PA0, PA1, PA2, PA3, PA4, PA5   |

#### 硬件连接

1. 超声波0

| 硬件管脚 | 单片机引脚 |
| :------: | :--------: |
|  trig0   |    PA0     |
|  echo0   |    PA1     |


2. 超声波1

| 硬件管脚 | 单片机引脚 |
| :------: | :--------: |
|  trig1   |    PA2     |
|  echo1   |    PA3     |


3. 超声波2

| 硬件管脚 | 单片机引脚 |
| :------: | :--------: |
|  trig2   |    PA4     |
|  echo2   |    PA5     |

4. 蓝牙串口

| 硬件管脚 | 单片机引脚 |
| :------: | :--------: |
|     RX   |    PA9     |
|  TX      |    PA10    |

5. 电机

| 硬件管脚 |                   单片机引脚                    |
| :------: | :---------------------------------------------: |
|  通道A   |                   PA6（pwm）                    |
|  通道B   |                   PB6（pwm）                    |
|  电机A   |   PB0,PB1（正转向前走，PB0低电平，PB1高电平）   |
|  电机B   | PB10,PB11（正转向前走，PB10低电平，PB11高电平） |

6. OLED

| 硬件管脚 | 单片机引脚 |
| :------: | :--------: |
|  D0/SCK  |    PB12    |
|  D1/SDA  |    PB13    |
| RET/RES  |    PB14    |
|    DC    |    PB15    |
|    CS    |    GND     |


# led.c文件

这次led.c文件是在上次跑马灯的代码的基础上增加了电平切换函数得来的，共同的部分请参考跑马灯实验，这里仅对电平切换函数做一个说明。

## 1. 函数源码

```c
//切换红色LED灯电平
void RED_TOGGLE(void)
{
  if(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8))                  //PA.8输出低，LED亮
  {
    GPIO_SetBits(GPIOA,GPIO_Pin_8);
  }
  else
  {
    GPIO_ResetBits(GPIOA,GPIO_Pin_8);
  }
}

//切换绿色LED灯电平
void GREED_TOGGLE(void)
{
  if(!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2))                  //PD.2输出低，LED亮
  {
    GPIO_SetBits(GPIOD,GPIO_Pin_2);
  }
  else
  {
    GPIO_ResetBits(GPIOD,GPIO_Pin_2);
  }
}

```

## 2. 所调用的官方库函数

### 2.1 GPIO_ReadInputDataBit()函数

功能:

函数原型：

```c/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @param  GPIO_Pin:  specifies the port bit to read.
  *   This parameter can be GPIO_Pin_x where x can be (0..15).
  * @retval The input port pin value.
  */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
```
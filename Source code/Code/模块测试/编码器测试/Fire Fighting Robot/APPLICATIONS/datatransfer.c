#include "main.h"


u8 data_to_send[50];                                  //发送数据缓存
MotorData __Motordata={0,0,0,0,0,0,0,0};
SensorData __Sensordata={0,0,0,0,0,0,0,0,0};

/**
  * @brief 协议中所有发送数据功能使用到的发送函数
  */
static void Data_Send(u8 *DataToSend, u8 length)
{
#ifdef USART1_SEND
  Usart1_Send(DataToSend, length);
#else
  Usart2_Send(DataToSend, length);
#endif

}

/**
  * @brief 将数据传回地面站，以方便调试
  * @param 
  * @retval None
  * @details 传输电机数据，传感器数据
  */
void DatatransferTask(void)
{
  static u16 flag=0;
  flag++;
  if(flag%2==1)
  {
    ANO_DT_Send_MotoPWM(__Motordata.motor_right,
                        __Motordata.motor_left ,
                        __Motordata.motor_fan  ,
                        __Motordata.motor4     ,
                        __Motordata.motor5     ,
                        __Motordata.motor6     ,
                        __Motordata.motor7     ,
                        __Motordata.motor8
                        );
  }
  else if(flag%2==0)
  {
    ANO_DT_Send_Senser(__Sensordata.dis_front  ,
                      __Sensordata.dis_right  ,
                      __Sensordata.dis_left   ,
                      __Sensordata.fire_sensor,
                      __Sensordata.wheel_left ,
                      __Sensordata.wheel_right,
                      __Sensordata.POS_X      ,
                      __Sensordata.POS_Y      ,
                      __Sensordata.MAG_Z      
                    );
  }
}

void ANO_DT_Send_Senser(s16 a_x,s16 a_y,s16 a_z,s16 g_x,s16 g_y,s16 g_z,s16 m_x,s16 m_y,s16 m_z)
{
  u8 _cnt=0;
  vs16 _temp;
  
  data_to_send[_cnt++]=0xAA;
  data_to_send[_cnt++]=0xAA;
  data_to_send[_cnt++]=0x02;
  data_to_send[_cnt++]=0;
  
  _temp = a_x;
  data_to_send[_cnt++]=BYTE1(_temp);
  data_to_send[_cnt++]=BYTE0(_temp);
  _temp = a_y;
  data_to_send[_cnt++]=BYTE1(_temp);
  data_to_send[_cnt++]=BYTE0(_temp);
  _temp = a_z;
  data_to_send[_cnt++]=BYTE1(_temp);
  data_to_send[_cnt++]=BYTE0(_temp);
  
  _temp = g_x;
  data_to_send[_cnt++]=BYTE1(_temp);
  data_to_send[_cnt++]=BYTE0(_temp);
  _temp = g_y;
  data_to_send[_cnt++]=BYTE1(_temp);
  data_to_send[_cnt++]=BYTE0(_temp);
  _temp = g_z;
  data_to_send[_cnt++]=BYTE1(_temp);
  data_to_send[_cnt++]=BYTE0(_temp);

  _temp = m_x;
  data_to_send[_cnt++]=BYTE1(_temp);
  data_to_send[_cnt++]=BYTE0(_temp);
  _temp = m_y;
  data_to_send[_cnt++]=BYTE1(_temp);
  data_to_send[_cnt++]=BYTE0(_temp);
  _temp = m_z;
  data_to_send[_cnt++]=BYTE1(_temp);
  data_to_send[_cnt++]=BYTE0(_temp);
  
  data_to_send[3] = _cnt-4;
  
  u8 sum = 0;
  for(u8 i=0;i<_cnt;i++)
    sum += data_to_send[i];
  data_to_send[_cnt++] = sum;

  Data_Send(data_to_send, _cnt);
}

void ANO_DT_Send_MotoPWM(u16 m_1,u16 m_2,u16 m_3,u16 m_4,u16 m_5,u16 m_6,u16 m_7,u16 m_8)
{
  u8 _cnt=0;
  
  data_to_send[_cnt++]=0xAA;
  data_to_send[_cnt++]=0xAA;
  data_to_send[_cnt++]=0x06;
  data_to_send[_cnt++]=0;
  
  data_to_send[_cnt++]=BYTE1(m_1);
  data_to_send[_cnt++]=BYTE0(m_1);
  data_to_send[_cnt++]=BYTE1(m_2);
  data_to_send[_cnt++]=BYTE0(m_2);
  data_to_send[_cnt++]=BYTE1(m_3);
  data_to_send[_cnt++]=BYTE0(m_3);
  data_to_send[_cnt++]=BYTE1(m_4);
  data_to_send[_cnt++]=BYTE0(m_4);
  data_to_send[_cnt++]=BYTE1(m_5);
  data_to_send[_cnt++]=BYTE0(m_5);
  data_to_send[_cnt++]=BYTE1(m_6);
  data_to_send[_cnt++]=BYTE0(m_6);
  data_to_send[_cnt++]=BYTE1(m_7);
  data_to_send[_cnt++]=BYTE0(m_7);
  data_to_send[_cnt++]=BYTE1(m_8);
  data_to_send[_cnt++]=BYTE0(m_8);

  data_to_send[3] = _cnt-4;
  
  u8 sum = 0;
  for(u8 i=0;i<_cnt;i++)
    sum += data_to_send[i];
  
  data_to_send[_cnt++]=sum;
  
  Data_Send(data_to_send, _cnt);
}

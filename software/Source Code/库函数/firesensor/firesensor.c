 #include "firesensor.h"



void ADC1_Configuration(void) //adc1配置
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟
 
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M 
		//PA1 作为模拟通道输入引脚  接SIG1                        
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
  //PA2作为模拟通道输入引脚  接SIG2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
  ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //ADC工作模式:ADC1和ADC2工作在独立模式
ADC_InitStructure.ADC_ScanConvMode =ENABLE; //模数转换工作在扫描模式
ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; //模数转换工作在连续转换模式
ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //外部触发转换关闭
ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //ADC数据右对齐
ADC_InitStructure.ADC_NbrOfChannel = 2; //顺序进行规则转换的ADC通道的数目
ADC_Init(ADC1, &ADC_InitStructure); //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器

//设置指定ADC的规则组通道，设置它们的转化顺序和采样时间
//ADC1,ADC通道x,规则采样顺序值为y,采样时间为239.5周期
ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );
ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 2, ADC_SampleTime_239Cycles5 );



ADC_Cmd(ADC1, ENABLE); //使能指定的ADC1

ADC_ResetCalibration(ADC1); //复位指定的ADC1的校准寄存器

while(ADC_GetResetCalibrationStatus(ADC1)); //获取ADC1复位校准寄存器的状态,设置状态则等待

ADC_StartCalibration(ADC1); //开始指定ADC1的校准状态

while(ADC_GetCalibrationStatus(ADC1)); //获取指定ADC1的校准程序,设置状态则等待

ADC_SoftwareStartConvCmd(ADC1, ENABLE);//软件开启 ADC 转换
}


void DMA_Configuration()   //DMA配置
{
	

DMA_InitTypeDef DMA_InitStructure;
	
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输时钟

DMA_DeInit(DMA1_Channel1); //将DMA的通道1寄存器重设为缺省值
	
	
DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)&ADC1->DR;//DMA外设ADC基地址
DMA_InitStructure.DMA_MemoryBaseAddr =(u32)&AD_Value; //DMA内存基地址
DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//内存作为数据传输的目的地
DMA_InitStructure.DMA_BufferSize =N*M; //DMA通道的DMA缓存的大小
DMA_InitStructure.DMA_PeripheralInc =DMA_PeripheralInc_Disable; //外设地址寄存器不变
DMA_InitStructure.DMA_MemoryInc =DMA_MemoryInc_Enable; //内存地址寄存器递增
DMA_InitStructure.DMA_PeripheralDataSize =DMA_PeripheralDataSize_HalfWord; //数据宽度为16位
DMA_InitStructure.DMA_MemoryDataSize =DMA_MemoryDataSize_HalfWord; //数据宽度为16位
DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;   //工作在循环缓存模式
DMA_InitStructure.DMA_Priority =DMA_Priority_High; //DMA通道 x拥有高优先级
DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMA通道x没有设置为内存到内存传输
DMA_Init(DMA1_Channel1, &DMA_InitStructure);//根据DMA_InitStruct中指定的参数初始化DMA的通道

// 开启ADC的DMA支持（要实现DMA功能，还需独立配置DMA通道等参数）
ADC_DMACmd(ADC1, ENABLE);

DMA_Cmd(DMA1_Channel1, ENABLE); //启动DMA通道

}

u16 GetVolt(u16 advalue)  //将数字信号转换成模拟信号

{
   return (u16)(advalue * 330 / 4096); //求的结果扩大了100倍，方便下面求出小数

}



void filter(void)   //把SIG1和SIG2转换后的数字信号，采样N次后求平均值，让数据更加稳定
{
int i;
int sum = 0;
u8 count;
for(i=0;i<M;i++)
{
for ( count=0;count<N;count++)
 sum += AD_Value[count][i];
After_filter[i]=sum/N;
sum=0;
}
}



/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ILI93xx.h"
#include "string.h"
#include "stdio.h"
#include "stm32_dsp.h"
#include "table_fft.h"
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */


#define NPT 1024   				         //一次采集的点数
#define PI2 6.28318530717959

uint16_t i;
uint32_t adcx[NPT];					      //存储adc数据
uint32_t adcmax = 0;					    //最大值
uint32_t adcmin = 3300;				    //最小值
uint16_t vpp = 0;					        //峰峰值变量
int long fftin [NPT];			        //FFT输入
int long fftout[NPT];			        //FFT输出
uint32_t magout[NPT];
uint32_t magout2[NPT];
uint16_t t = 0;			              //定时器中断3计数变量
uint16_t Set_T = 1000;	          //TIM3自动重装载值
uint16_t Show_T = 1;		          //采样率变量，单位KHZ
uint32_t F = 0;			              //频率值
double U = 40.96;			            //计算转化值
uint16_t V = 660;		              //分度单位660mv/div
uint16_t get_v=0;	              	//获得显示电压
uint16_t save_v=0;	            	//存储电压
uint8_t  flag=0;			            //采集频率标志
uint8_t  adc_flag=0;	          	//采集允许标志位
uint8_t  clear_flag=1;	          //Hold on标志位，0——>Hold on
uint16_t table[25] ={16,32,48,64,80,96,112,128,144,160,176,192,208,224,240,256,272,288,304,320,336,352,368,384,400};//刻度X坐标数组
uint16_t h=0;			//数组下标


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
 
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_FSMC_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
 	TFTLCD_Init();                                        	//屏幕初始化
  
  __HAL_TIM_ENABLE_IT(&htim3 , TIM_IT_UPDATE);	          //允许更新中断	
  HAL_TIM_Base_Start(&htim3);	                            //打开定时器tim3

	POINT_COLOR=RED;                                        //屏幕测试
	LCD_ShowString(60,40,210,24,24,"Elite STM32F1 ^_^"); 
	LCD_ShowString(82,80,200,24,24,"Mini OSC TEST");
	LCD_ShowString(107,120,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(117,145,200,16,16,"By YYQ");
	LCD_ShowString(137,170,200,12,12,"2021/7/22");	 
	HAL_Delay(1000);

	LCD_Clear(WHITE);                                       //清屏为白色
	lcd_init(); 			                                      //画好示波器基本屏幕
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		while(adc_flag == 0);			                           //等待数据采集完成
        adc_flag=0;			
		for(i=0;i<NPT;i++)				                           //NPT，一次采集1024个点，确定max与min
		{
			fftin[i] = 0;
			fftin[i] = adcx[i] << 16;
		}
		GetPowerMag();                                       //进行快速傅里叶变换
		adcmax=adcmax*3300/4096;
		adcmin=adcmin*3300/4096;   	                         //将ADC值转化为电压值，单位 mv
    LCD_ShowNum(430,122,adcmax,4,16);                    //显示最大值
		LCD_ShowNum(430,157,adcmin,4,16);                    //显示最小值

		vpp=adcmax-adcmin;
	  LCD_ShowNum(430,87,vpp,4,16);				                 //显示峰峰值				
		clear_point();    							                     //更新显示屏当前列
		
	
			
	  HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin)	;        //翻转LED电平，采集一次灯闪一下
		
		__HAL_TIM_ENABLE(&htim3);   						             //使能定时器3			
		adcmax = 0;	adcmin = 3300;		    		               //清除极值
		  
		
 }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */


void lcd_init(void)
{
	POINT_COLOR=RED;
	
	LCD_ShowString(150,8,200,24,24,"Mini_OSC");	      //示波器
	LCD_ShowString(320,18,200,16,16,"INPUT:PA1");     //采集端口（PA1）
	LCD_ShowString(410,35,200,16,16,"mV/div:");		    //毫伏/每格
	LCD_ShowString(410,70,200,16,16,"vpp/mv:");		    //峰峰值/毫伏
	LCD_ShowString(410,105,200,16,16,"max/mv:");		  //最大值
	LCD_ShowString(410,140,200,16,16,"min/mv:");	    //最小值
	LCD_ShowString(410,175,200,16,16,"f/Hz:");	      //频率/Hz
	LCD_ShowString(410,210,200,16,16,"OSR:");  		    //采样率
	
  LCD_ShowString(410,245,200,16,16,"THD=");         //总谐波失真度
	/*
	LCD_ShowString(20,280,200,168,24,"uo1=");
  LCD_ShowString(300,280,200,168,24,"uo2=");
	LCD_ShowString(20,310,200,168,24,"uo3=");
	LCD_ShowString(300,310,200,168,24,"uo4=");
	LCD_ShowString(168,340,200,168,24,"uo5=");		
 */  
	POINT_COLOR=BLUE;
	lcd_huaxian(0,0,0,240);				                    //画4条边框线
	lcd_huaxian(400,0,400,240);
	lcd_huaxian(0,0,400,0);		
	lcd_huaxian(0,240,400,240);

  POINT_COLOR=BLUE;		
	LCD_ShowString(448,227,120,16,16,"kHz");	
	LCD_ShowString(420,10,200,16,16,"WORK");      

	LCD_ShowNum(420,227,Show_T,3,16);		              //首次ADC采样频率
	LCD_ShowNum(430,52,V,3,16);				                //分度单位660mv/div
}


void clear_point(void)                              //更新显示屏当前列
{
	uint16_t x=0;
	
	for(x=0;x<400 && clear_flag;x++)
	{	
		POINT_COLOR=WHITE;	
		lcd_huaxian(x  ,3,x  ,237);		                  //删除原始线条，除上下两条边框

		POINT_COLOR=BLUE;
		lcd_huaxian(0,0,0,240);			                    //画左边框
		lcd_huadian(x,120);				                      //画中线
				
		if(x == table[h])				                        //画刻度，横上、中、下线
		{
			lcd_huaxian(x,1,x,3);
			lcd_huaxian(x,121,x,123);
			lcd_huaxian(x,237,x,239);
			h++;
			if(h>=25) h=0;
		}	
		if(x==200) 						                          //画刻度竖中线
		{
			lcd_huaxian(x,1,x,239);
			for(i=20;i<240;i+=20)
			{
				lcd_huaxian(198,i,200,i);
			}
		}
				
		get_v = adcx[x]/U+(120-((adcmax-adcmin)/(2*U)));
		
//		lcd_huadian(x,get_v);					                //画点
		lcd_huaxian(x,save_v,x+1,get_v);	            	//画线，方便观察
		save_v = get_v;							                    //存储待用
//     HAL_Delay(10);	
	}
}


void lcd_huadian(uint16_t a,uint16_t b)			                        //坐标原点重定义画点，重定义在280处
{							    
	LCD_Fast_DrawPoint(a,280-b,BLUE);
}

void lcd_huaxian(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)	 //坐标原点重定义画线
{
	LCD_DrawLine(x1,280-y1,x2,280-y2);
}

/******************************************************************
函数名称:GetPowerMag()
函数功能:计算各次谐波幅值
参数说明:
备　　注:先将lBufOutArray分解成实部(X)和虚部(Y)，然后计算幅值(sqrt(X*X+Y*Y)
*******************************************************************/
void GetPowerMag(void)
{
	uint16_t temp = 0;
	int THD;
	float THD_1=0;
  float X,Y;
	float ret;
	double Mag,magmax[5]={0};
  unsigned short i,j,min=0;
	cr4_fft_1024_stm32(fftout, fftin, NPT);  	   //调用自cr4_fft_1024_stm32
    for(i=1; i<NPT/2; i++)
    {
        X  = (fftout[i] << 16) >> 16;
        Y  = (fftout[i] >> 16);
        Mag = sqrt(X * X + Y * Y);     
		if(Mag>magmax[min])                       //新数大于第五大数
		{
			magmax[min]=Mag;                        //第五大数换成新数
			temp = i;
			for(j=0;j<5;j++)
			{                                       //找到新的第五大数
				if(magmax[j]<magmax[min])
					{
  						min=j;
					}
			}
		}				
    }
		for(i=1;i<5;i++)
		{
				ret=magmax[i]/magmax[0];
			  if(ret>0.01)				                  //提高精度
				THD_1=THD_1+ret*ret;
		}
	THD_1=sqrt(THD_1);
	//计算频率
	if(Set_T==1000)		F=(uint32_t)((double)temp/NPT*1000  );	
	if(Set_T==100)		F=(uint32_t)((double)temp/NPT*10010 );
	if(Set_T==10)	    F=(uint32_t)((double)temp/NPT*100200);
	if(Set_T==2)		  F=(uint32_t)((double)temp/NPT*249760);
	 
	LCD_ShowNum(420,192,F,5,16);                      //显示频率
  THD=THD_1*10000;	
  POINT_COLOR=BLUE;                                 //显示总谐波失真度
	LCD_ShowNum(420,262,THD/100,2,16);
	LCD_ShowString(438,262,16,16,16,".");
	LCD_ShowNum(444,262,THD%100,2,16);
	LCD_ShowString(462,262,16,16,16,"%");
	/*		
  LCD_ShowNum(80,280,sqrt(magmax[0]*7260),5,24);    //计算并显示一次谐波分量
	LCD_ShowNum(380,280,sqrt(magmax[1]*7260),5,24);   //计算并显示二次谐波分量
	LCD_ShowNum(80,310,sqrt(magmax[2]*7260),5,24);    //计算并显示三次谐波分量
	LCD_ShowNum(380,310,sqrt(magmax[3]*7260),5,24);   //计算并显示四次谐波分量
	LCD_ShowNum(228,340,sqrt(magmax[4]*7260),5,24);   //计算并显示五次谐波分量
	*/	
}

//定时器3中断服务程序	
//每隔采样频率采样一次
void  TIM3_IRQHandler(void)
{
	
	if( __HAL_TIM_GET_FLAG(&htim3,1))
	{
	//	adcx[t]=Get_Adc(ADC_CH1);		    	 	          //单次采样
		adcx[t]=getADC(&hadc1, 3 );		                  //多次采样取均值
		
		if(adcx[t] >= adcmax)		adcmax = adcx[t];       //获取极值
		if(adcx[t] <= adcmin)		adcmin = adcx[t];
		
		t++;
		if(t==NPT) 
		{
			t=0;
			adc_flag = 1;
			__HAL_TIM_DISABLE(&htim3);                    //失能定时器3				
		}
	}
   __HAL_TIM_CLEAR_FLAG(&htim3, 1);                 //清除定时器的中断标志位 

}

//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	HAL_Delay(10);                   	               //消抖
	POINT_COLOR=BLUE;
	if(KEY1==0)	 	                                   //按键KEY1
	{				 
		if(clear_flag == 1)
		{
			__HAL_TIM_DISABLE(&htim3);                   //失能定时器3		
     		
			clear_flag=0;
			LCD_ShowString(420,10,200,16,16,"STOP  ");			
		}
		else
		{
			__HAL_TIM_ENABLE(&htim3);                    //使能定时器3
			  			
			clear_flag=1;
			LCD_ShowString(420,10,200,16,16,"WORK");
		}
	}		   
	__HAL_GPIO_EXTI_CLEAR_FLAG(KEY1_Pin);           //清除LINE3上的中断标志位 
}

//外部中断4服务程序
void EXTI4_IRQHandler(void)
{
	HAL_Delay(10);	                               //消抖
	if(KEY0==0)	 	                                 //按键KEY0
	{
		POINT_COLOR=BLUE;		
		flag++;
		if(flag==1)
		{
			Set_T = 100;
			Show_T = 10;
		}
		else if(flag==2) 
		{
			Set_T=10;
			Show_T = 100;
		}
		else if(flag==3)
		{
			Set_T=2;
			Show_T = 500;
		}
		else if(flag==4)
		{
			Set_T=1000;
			Show_T = 1;
			flag=0;
		}
		LCD_ShowNum(420,227,Show_T,3,16);		
    __HAL_TIM_SET_AUTORELOAD(&htim3,Set_T-1);		//设定计数器自动重装值 
		
	} 
	__HAL_GPIO_EXTI_CLEAR_FLAG(KEY0_Pin);  		  	//清除LINE4上的中断标志位  
}		 


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

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


#define NPT 1024   				         //һ�βɼ��ĵ���
#define PI2 6.28318530717959

uint16_t i;
uint32_t adcx[NPT];					      //�洢adc����
uint32_t adcmax = 0;					    //���ֵ
uint32_t adcmin = 3300;				    //��Сֵ
uint16_t vpp = 0;					        //���ֵ����
int long fftin [NPT];			        //FFT����
int long fftout[NPT];			        //FFT���
uint32_t magout[NPT];
uint32_t magout2[NPT];
uint16_t t = 0;			              //��ʱ���ж�3��������
uint16_t Set_T = 1000;	          //TIM3�Զ���װ��ֵ
uint16_t Show_T = 1;		          //�����ʱ�������λKHZ
uint32_t F = 0;			              //Ƶ��ֵ
double U = 40.96;			            //����ת��ֵ
uint16_t V = 660;		              //�ֶȵ�λ660mv/div
uint16_t get_v=0;	              	//�����ʾ��ѹ
uint16_t save_v=0;	            	//�洢��ѹ
uint8_t  flag=0;			            //�ɼ�Ƶ�ʱ�־
uint8_t  adc_flag=0;	          	//�ɼ������־λ
uint8_t  clear_flag=1;	          //Hold on��־λ��0����>Hold on
uint16_t table[25] ={16,32,48,64,80,96,112,128,144,160,176,192,208,224,240,256,272,288,304,320,336,352,368,384,400};//�̶�X��������
uint16_t h=0;			//�����±�


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
 	TFTLCD_Init();                                        	//��Ļ��ʼ��
  
  __HAL_TIM_ENABLE_IT(&htim3 , TIM_IT_UPDATE);	          //��������ж�	
  HAL_TIM_Base_Start(&htim3);	                            //�򿪶�ʱ��tim3

	POINT_COLOR=RED;                                        //��Ļ����
	LCD_ShowString(60,40,210,24,24,"Elite STM32F1 ^_^"); 
	LCD_ShowString(82,80,200,24,24,"Mini OSC TEST");
	LCD_ShowString(107,120,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(117,145,200,16,16,"By YYQ");
	LCD_ShowString(137,170,200,12,12,"2021/7/22");	 
	HAL_Delay(1000);

	LCD_Clear(WHITE);                                       //����Ϊ��ɫ
	lcd_init(); 			                                      //����ʾ����������Ļ
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		while(adc_flag == 0);			                           //�ȴ����ݲɼ����
        adc_flag=0;			
		for(i=0;i<NPT;i++)				                           //NPT��һ�βɼ�1024���㣬ȷ��max��min
		{
			fftin[i] = 0;
			fftin[i] = adcx[i] << 16;
		}
		GetPowerMag();                                       //���п��ٸ���Ҷ�任
		adcmax=adcmax*3300/4096;
		adcmin=adcmin*3300/4096;   	                         //��ADCֵת��Ϊ��ѹֵ����λ mv
    LCD_ShowNum(430,122,adcmax,4,16);                    //��ʾ���ֵ
		LCD_ShowNum(430,157,adcmin,4,16);                    //��ʾ��Сֵ

		vpp=adcmax-adcmin;
	  LCD_ShowNum(430,87,vpp,4,16);				                 //��ʾ���ֵ				
		clear_point();    							                     //������ʾ����ǰ��
		
	
			
	  HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin)	;        //��תLED��ƽ���ɼ�һ�ε���һ��
		
		__HAL_TIM_ENABLE(&htim3);   						             //ʹ�ܶ�ʱ��3			
		adcmax = 0;	adcmin = 3300;		    		               //�����ֵ
		  
		
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
	
	LCD_ShowString(150,8,200,24,24,"Mini_OSC");	      //ʾ����
	LCD_ShowString(320,18,200,16,16,"INPUT:PA1");     //�ɼ��˿ڣ�PA1��
	LCD_ShowString(410,35,200,16,16,"mV/div:");		    //����/ÿ��
	LCD_ShowString(410,70,200,16,16,"vpp/mv:");		    //���ֵ/����
	LCD_ShowString(410,105,200,16,16,"max/mv:");		  //���ֵ
	LCD_ShowString(410,140,200,16,16,"min/mv:");	    //��Сֵ
	LCD_ShowString(410,175,200,16,16,"f/Hz:");	      //Ƶ��/Hz
	LCD_ShowString(410,210,200,16,16,"OSR:");  		    //������
	
  LCD_ShowString(410,245,200,16,16,"THD=");         //��г��ʧ���
	/*
	LCD_ShowString(20,280,200,168,24,"uo1=");
  LCD_ShowString(300,280,200,168,24,"uo2=");
	LCD_ShowString(20,310,200,168,24,"uo3=");
	LCD_ShowString(300,310,200,168,24,"uo4=");
	LCD_ShowString(168,340,200,168,24,"uo5=");		
 */  
	POINT_COLOR=BLUE;
	lcd_huaxian(0,0,0,240);				                    //��4���߿���
	lcd_huaxian(400,0,400,240);
	lcd_huaxian(0,0,400,0);		
	lcd_huaxian(0,240,400,240);

  POINT_COLOR=BLUE;		
	LCD_ShowString(448,227,120,16,16,"kHz");	
	LCD_ShowString(420,10,200,16,16,"WORK");      

	LCD_ShowNum(420,227,Show_T,3,16);		              //�״�ADC����Ƶ��
	LCD_ShowNum(430,52,V,3,16);				                //�ֶȵ�λ660mv/div
}


void clear_point(void)                              //������ʾ����ǰ��
{
	uint16_t x=0;
	
	for(x=0;x<400 && clear_flag;x++)
	{	
		POINT_COLOR=WHITE;	
		lcd_huaxian(x  ,3,x  ,237);		                  //ɾ��ԭʼ�����������������߿�

		POINT_COLOR=BLUE;
		lcd_huaxian(0,0,0,240);			                    //����߿�
		lcd_huadian(x,120);				                      //������
				
		if(x == table[h])				                        //���̶ȣ����ϡ��С�����
		{
			lcd_huaxian(x,1,x,3);
			lcd_huaxian(x,121,x,123);
			lcd_huaxian(x,237,x,239);
			h++;
			if(h>=25) h=0;
		}	
		if(x==200) 						                          //���̶�������
		{
			lcd_huaxian(x,1,x,239);
			for(i=20;i<240;i+=20)
			{
				lcd_huaxian(198,i,200,i);
			}
		}
				
		get_v = adcx[x]/U+(120-((adcmax-adcmin)/(2*U)));
		
//		lcd_huadian(x,get_v);					                //����
		lcd_huaxian(x,save_v,x+1,get_v);	            	//���ߣ�����۲�
		save_v = get_v;							                    //�洢����
//     HAL_Delay(10);	
	}
}


void lcd_huadian(uint16_t a,uint16_t b)			                        //����ԭ���ض��廭�㣬�ض�����280��
{							    
	LCD_Fast_DrawPoint(a,280-b,BLUE);
}

void lcd_huaxian(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)	 //����ԭ���ض��廭��
{
	LCD_DrawLine(x1,280-y1,x2,280-y2);
}

/******************************************************************
��������:GetPowerMag()
��������:�������г����ֵ
����˵��:
������ע:�Ƚ�lBufOutArray�ֽ��ʵ��(X)���鲿(Y)��Ȼ������ֵ(sqrt(X*X+Y*Y)
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
	cr4_fft_1024_stm32(fftout, fftin, NPT);  	   //������cr4_fft_1024_stm32
    for(i=1; i<NPT/2; i++)
    {
        X  = (fftout[i] << 16) >> 16;
        Y  = (fftout[i] >> 16);
        Mag = sqrt(X * X + Y * Y);     
		if(Mag>magmax[min])                       //�������ڵ������
		{
			magmax[min]=Mag;                        //���������������
			temp = i;
			for(j=0;j<5;j++)
			{                                       //�ҵ��µĵ������
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
			  if(ret>0.01)				                  //��߾���
				THD_1=THD_1+ret*ret;
		}
	THD_1=sqrt(THD_1);
	//����Ƶ��
	if(Set_T==1000)		F=(uint32_t)((double)temp/NPT*1000  );	
	if(Set_T==100)		F=(uint32_t)((double)temp/NPT*10010 );
	if(Set_T==10)	    F=(uint32_t)((double)temp/NPT*100200);
	if(Set_T==2)		  F=(uint32_t)((double)temp/NPT*249760);
	 
	LCD_ShowNum(420,192,F,5,16);                      //��ʾƵ��
  THD=THD_1*10000;	
  POINT_COLOR=BLUE;                                 //��ʾ��г��ʧ���
	LCD_ShowNum(420,262,THD/100,2,16);
	LCD_ShowString(438,262,16,16,16,".");
	LCD_ShowNum(444,262,THD%100,2,16);
	LCD_ShowString(462,262,16,16,16,"%");
	/*		
  LCD_ShowNum(80,280,sqrt(magmax[0]*7260),5,24);    //���㲢��ʾһ��г������
	LCD_ShowNum(380,280,sqrt(magmax[1]*7260),5,24);   //���㲢��ʾ����г������
	LCD_ShowNum(80,310,sqrt(magmax[2]*7260),5,24);    //���㲢��ʾ����г������
	LCD_ShowNum(380,310,sqrt(magmax[3]*7260),5,24);   //���㲢��ʾ�Ĵ�г������
	LCD_ShowNum(228,340,sqrt(magmax[4]*7260),5,24);   //���㲢��ʾ���г������
	*/	
}

//��ʱ��3�жϷ������	
//ÿ������Ƶ�ʲ���һ��
void  TIM3_IRQHandler(void)
{
	
	if( __HAL_TIM_GET_FLAG(&htim3,1))
	{
	//	adcx[t]=Get_Adc(ADC_CH1);		    	 	          //���β���
		adcx[t]=getADC(&hadc1, 3 );		                  //��β���ȡ��ֵ
		
		if(adcx[t] >= adcmax)		adcmax = adcx[t];       //��ȡ��ֵ
		if(adcx[t] <= adcmin)		adcmin = adcx[t];
		
		t++;
		if(t==NPT) 
		{
			t=0;
			adc_flag = 1;
			__HAL_TIM_DISABLE(&htim3);                    //ʧ�ܶ�ʱ��3				
		}
	}
   __HAL_TIM_CLEAR_FLAG(&htim3, 1);                 //�����ʱ�����жϱ�־λ 

}

//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	HAL_Delay(10);                   	               //����
	POINT_COLOR=BLUE;
	if(KEY1==0)	 	                                   //����KEY1
	{				 
		if(clear_flag == 1)
		{
			__HAL_TIM_DISABLE(&htim3);                   //ʧ�ܶ�ʱ��3		
     		
			clear_flag=0;
			LCD_ShowString(420,10,200,16,16,"STOP  ");			
		}
		else
		{
			__HAL_TIM_ENABLE(&htim3);                    //ʹ�ܶ�ʱ��3
			  			
			clear_flag=1;
			LCD_ShowString(420,10,200,16,16,"WORK");
		}
	}		   
	__HAL_GPIO_EXTI_CLEAR_FLAG(KEY1_Pin);           //���LINE3�ϵ��жϱ�־λ 
}

//�ⲿ�ж�4�������
void EXTI4_IRQHandler(void)
{
	HAL_Delay(10);	                               //����
	if(KEY0==0)	 	                                 //����KEY0
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
    __HAL_TIM_SET_AUTORELOAD(&htim3,Set_T-1);		//�趨�������Զ���װֵ 
		
	} 
	__HAL_GPIO_EXTI_CLEAR_FLAG(KEY0_Pin);  		  	//���LINE4�ϵ��жϱ�־λ  
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

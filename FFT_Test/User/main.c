#include "stm32f10x.h"
#include "USART1.h"
#include "delay.h"
#include "fft_calculate.h"
#include "stm32_dsp.h"
#include <string.h>
#include <math.h>

#define PI2 6.28318530717959
#define FS 44800

extern long InBufArray[NPT];
extern long OutBufArray[NPT/2];
extern long MagBufArray[NPT/2];

void InitBufInArray(void);

int main(void){
	delay_init();
	USART_Config();
	InitBufInArray();
	cr4_fft_256_stm32(OutBufArray,InBufArray,NPT);
	GetPowerMag();
	unsigned short i;
	for(i=0;i<NPT;i++)printf("P:%d %d \r\n",i*175,(int)MagBufArray[i]);
	while(1){
	}
}

void InitBufInArray(void)
{
	unsigned short i=0;
	float fx;
	for(i=0;i<NPT;i++){
		fx=1500*sin(PI2*i*350.0/FS)+2700*sin(PI2*i*8400.0/FS)+4000*sin(PI2*i*18725.0/FS);
		InBufArray[i]=((signed short)fx)<<16;
	}
}



#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <sys/stat.h>
#include <time.h>
#include <math.h>

typedef uint16_t INT16U;
typedef uint8_t INT8U;

/********************************************************************//**
* @brief		Use PWM To Get Slow Charge Current
* @param[in]	&Pwmnum	 should be address of the DutyTrtion  
* 				
* @return 		Get Current Error	could be:
* 				-  0:  function no use
* 				- -1:  Disable Charge 
* 				- -2: need digicom  if no digicom charge is disable
* 				- -3: NC
* @return   Get Current Ok
* 				- num: Imax num			
*********************************************************************/

int GetSlowChargeCurrent(INT16U *Pwmnum)
{
	int Imax = 0;
	INT16U Pwm=0;
	Pwm=*Pwmnum;

	if((Pwm<3)||((Pwm>7)&&(Pwm<8))||(Pwm>97)){
		*Pwmnum= 0xff;
		return -1; 
	}
	else if((Pwm>=3)&&(Pwm<=7)){
		*Pwmnum= 0xff;
		return -2;
	}
	else if((Pwm>=8)&&(Pwm<10)){
		Imax = 6;                         
	}
	else if((Pwm>=10)&&(Pwm<=85)){
		Imax = ((Pwm)*6)/10;                       
	}
	else if((Pwm>85)&&(Pwm<=90)){
		Imax = (Pwm-64)*2.5;
		if(Imax>63)Imax = 63;
	}
	else if((Pwm>90)&&(Pwm<=97)){
		*Pwmnum= 0xff;
		return -3;  			
	}
	*Pwmnum= 0xff;
	return Imax;
}



void main()
{
	int ret = 0;
	INT16U num =0;
	for(num=0;num<99;num++){
		ret = GetSlowChargeCurrent(&num);
		printf("%d  ",ret);
		printf("%d\n  ",num);
	
	}

	system("pause");
}
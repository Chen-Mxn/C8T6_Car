#ifndef __HCSR04_
#define __HCSR04_
#include "sys.h"

#define trig0 PAout(3)
#define echo0 PAin(0)



float Senor_Using(void);  //��ຯ��������ֵ��Ϊ����
void HCSR_Init(u16 arr, u16 psc);



#endif


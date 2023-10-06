#include <stdint.h>

uint32_t volatile flag1;
uint32_t volatile flag2;

void delay( uint32_t count )
{
    for (; count!=0; count--);
}

int main(void) {

	while(1) {
		flag1 = 1;
		delay( 1000 );
		flag1 = 0;
		delay( 1000 );

	}
}

// EX 6_3

#include <avr/io.h>
#include <util/delay.h>
#define FAN_PIN PB1

uint8_t fanPWM[4] = {0, 85, 170, 255};  // OFF, LOW, MEDIUM, HIGH

void PWM_init(){
	DDRB |= (1 << FAN_PIN);
	TCCR1A |= (1 << COM1A1) | (1 << WGM10);
	TCCR1B |= (1 << WGM12) | (1 << CS10);
}

void setPWM(uint8_t duty){
	OCR1A = duty;
}

// Dummy function for report
float readTemperature(){
	return 28.0;  
}

uint8_t fanStateFromTemp(float temp){
	if(temp < 25) return 0;
	else if(temp < 30) return 1;
	else if(temp < 35) return 2;
	else return 3;
}

int main(void){
	PWM_init();
	while(1){
		float temp = readTemperature();
		uint8_t state = fanStateFromTemp(temp);
		setPWM(fanPWM[state]);
		_delay_ms(2000);
	}
}

#include <wiringPi.h>
const int LedRed[8] = { 4, 17, 18, 27, 22, 23, 24, 25 };
const int Keypad[5] = { 6, 12, 13, 16, 19};

int KeypadRead()
{
	int i, keypadnum=-1;
	for(i=0; i<8; i++) {
		if(!digitalRead(Keypad[i])) {
			keypadnum = i; break;
		}
	}
	return keypadnum;
}
void LedControl(int num)
{
	int i;
	for(i=0; i<8; i++) {
		if(i==num)
			digitalWrite(LedRed[i], HIGH);
		else
			digitalWrite(LedRed[i], LOW);
	}
}
int main(void)
{
	int i, keypadnum=-1;
	if(wiringPiSetupGpio() == -1)
		return 1;
	for(i=0; i<8; i++) {
		pinMode(LedRed[i], OUTPUT);
		digitalWrite(LedRed[i], LOW);
	}
	for(i=0; i<2; i++)
		pinMode(Keypad[i], INPUT);
	while(1) {
		keypadnum = KeypadRead();
		if(keypadnum== 3) {
			for(i=0; i<8; i++) {
				LedControl(i);
				delay(500);
			}
			digitalWrite(LedRed[i-1], LOW);
		} else if(keypadnum== 4) {
			for(i=7; i>=0; i--) {
				LedControl(i);
				delay(500);
			}
			digitalWrite(LedRed[i+1], LOW);
		} else if(keypadnum==0) {
			while(1) {
				for (i=0; i<8; i++) {
					LedControl(i);
					delay(500);
					if (KeypadRead() == 2)
						return 1;
				}
				digitalWrite(LedRed[i-1], LOW);
			}
		} else if(keypadnum==1) {
			while(1) {
				for (i=7; i>=0; i--) {
					LedControl(i);
					delay(500);
					if (KeypadRead() == 2)
						return 1;
				}
				digitalWrite(LedRed[i+1], LOW);
			}
		}
	}
	return 0;
}

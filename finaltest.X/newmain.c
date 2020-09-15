/*   倒數計時---> 馬達--> 變頻蜂鳴器
 * File:   main.c
 * Author: jeff8
 *
 * Created on 2019年12月26日, 下午 4:12
 */
#pragma config OSC = INTIO67    // Oscillator Selection bits (Internal oscillator block, port function on RA6 and RA7)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      //


#include <xc.h> // Include Header for PIC18F4550
#define switch1 PORTAbits.RA3 // Switch on RA3
//#define led1 LATDbits.LATD0 // led1
#define SW1 PORTCbits.RC0
#define _XTAL_FREQ 8000000
#define seg_port LATD
#define seg_unit LATAbits.LA1
#define seg_decade LATAbits.LA0
#define seg_hundred LATAbits.LA2
#define seg_thousand LATAbits.LA3
unsigned int i=0,j=0,k=0;
unsigned char  const value[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned int count,num0,num1,num2,num3,num4,time,delay_forsecond;

void count_digit();
void display();
void SetDutyCycleTo(float Duty_cycle, int Period)
{
    int PWM10BitValue;
    PWM10BitValue = 4.0 * ((float)Period + 1.0) * (Duty_cycle/100.0);
    CCPR1L = (PWM10BitValue >> 2);
    CCP1CON = ((PWM10BitValue & 0x03) << 4) | 0x0C;
}

void delay(unsigned int val)
{
     unsigned int i,j;
        for(i=0;i<val;i++)
            for(j=0;j<10;j++);
}
void main (void)
{
 /*for seven segement display code*/      
  TRISD = 0x00;                   //Set Portd to all outputs
  TRISCbits.RC0=0x01;             //Set PortC.0 asinput
  OSCCON = 0X76;                  //SET fOR INTERNAL OSCCILATOR
  char digit=0;
 /*seven segment display end*/     
 /*setting motor*/
    TRISBbits.TRISB0=1;
    PORTBbits.RB0 =1;
    TRISCbits.TRISC2 = 0;  /* Set CCP1 pin as output for PWM out */
    CCP1CON = 0x0C;        /* Set PWM mode */ //0000 1100
    CCP1CON = 0x0C;        /* Set PWM mode */ //0000 1100
    int Period = ((float)500000 / (4.0 * (float)16* (float)50)) - 1.0;
    PR2 = (int)Period;
    T2CON = 2;
    TMR2 = 0;
    T2CONbits.TMR2ON = 1;  /* Turn ON Timer2 */
    SetDutyCycleTo(2.5, Period);    /* 2.5% duty cycle */
    delay(800);
    SetDutyCycleTo(12.0, Period);    /* 12% duty cycle */
    delay(800);
    TRISCbits.TRISC2 = 1;   
    
/*  for infrared sensor code                          */    
/* If you want your microcontroller to work at 1MHZ then comment the three lines below */
time = 60;    
RCONbits.IPEN = 1;
TRISD = 0;
/* Input output settings*/
TRISA=0;
TRISAbits.RA4 = 0;
TRISAbits.TRISA3 = 0; 
TRISDbits.TRISD0 = 0; // Port D pins output
TRISCbits.RC3 = 1;
CMCON = 0x07; // Disable Comparator
ADCON1bits.PCFG0 = 1; // These 4 settings below determines the analog or digital input
ADCON1bits.PCFG1 = 1; // In our case we are making all the pins digital
ADCON1bits.PCFG2 = 1; // by setting them as 1111
ADCON1bits.PCFG3 = 1; // Check with the datasheet for a nice desc of these bits and config.
ADCON0bits.ADON = 0; // Disabled ADC
TRISCbits.RC0=0x01; 
INTCONbits.GIE = 1;
INTCONbits.INT0IE = 1;
INTCONbits.INT0IF = 0;
TRISBbits.TRISB0=1;		/* Make INT0 pin as an input pin*/

    /* Also make PBADEN off in Configuration file or
    clear ADON in ADCON0 so as to set analog pin as digital*/
  
INTCON2=0x00;		/* Set Interrupt on falling Edge*/
count = 0;
delay_forsecond = 0;
LATAbits.LA4 = 0;
while(time>0)
{   
    count_digit();
    display();
    if(delay_forsecond==5){
       time = time -1 ;
       delay_forsecond = 0;
    }
    else{
       time = time;
       delay_forsecond ++;
    }
} 

  /*infrared sensor end*/
    
    
    

}
/* THE END */
void __interrupt() ISR(void)
{
    if(INTCONbits.INT0IF == 1) {
      LATAbits.LA4 = 1;
      __delay_ms(100);
      LATAbits.LA4 = 0;
      count = count + 1;
      count_digit();
      display();
      INTCONbits.INT0IF = 0;
    }
    return ; 
}

void count_digit(){
        num0= count;//1
        num1=num0%10;	//num=1		// Extract the value of unit digit
		num0=num0-num1; //num0=0
		num0=num0/10; //num=0

		num2=num0%10;	//num2=0		// Extract the value of decade digit             
        
        num0 = time;    
		num3=num0%10;			// Extract the value of hundred digit
		num0=num0-num3;
		num0=num0/10;
                  
		num4=num0%10;			// Extract the value of thousand digit
		num0=num0-num4;
		num0=num0/10; 
        return;
  }
void display(){
    /*multiplex*/
    for(i=0;i<10;i++)		// Delay= ((5msx4)x10) = 200ms between two consecutive counts
		{
			          //count digit
			           
                       seg_unit=1;seg_decade=0;seg_hundred=0;seg_thousand=0;		// Display unit digit
                        seg_port=value[num1];
                        __delay_ms(5);
                        
                        seg_unit=0;seg_decade=1;seg_hundred=0;seg_thousand=0;		// Display decade digit
                        seg_port=value[num2];
                        __delay_ms(5);
                        //count time
                        seg_unit=0;seg_decade=0;seg_hundred=0;seg_thousand=1;		// Display hundred digit
                        seg_port=value[num3];
                        __delay_ms(5);
                        
                        seg_unit=0;seg_decade=0;seg_hundred=1;seg_thousand=0;		// Display thousand digit
                        seg_port=value[num4];
                        __delay_ms(5);
		}
    return;
  }
void count_down(unsigned int time){
    int count = 0;
    for(int i = time ;i>0;i--){
        
        display();
    }
  }

void display_sound(){//buzzer
    
    
    
}

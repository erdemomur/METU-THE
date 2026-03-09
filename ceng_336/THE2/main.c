// ============================ //
// Do not edit this part!!!!    //
// ============================ //
// 0x300001 - CONFIG1H
#pragma config OSC = HSPLL      // Oscillator Selection bits (HS oscillator,
                                // PLL enabled (Clock Frequency = 4 x FOSC1))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit
                                // (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit
                                // (Oscillator Switchover mode disabled)
// 0x300002 - CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out
                                // Reset disabled in hardware and software)
// 0x300003 - CONFIG1H
#pragma config WDT = OFF        // Watchdog Timer Enable bit
                                // (WDT disabled (control is placed on the SWDTEN bit))
// 0x300004 - CONFIG3L
// 0x300005 - CONFIG3H
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit
                                // (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled;
                                // RE3 input pin disabled)
// 0x300006 - CONFIG4L
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply
                                // ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit
                                // (Instruction set extension and Indexed
                                // Addressing mode disabled (Legacy mode))

#pragma config DEBUG = OFF      // Disable In-Circuit Debugger

#define KHZ 1000UL
#define MHZ (KHZ * KHZ)
#define _XTAL_FREQ (40UL * MHZ)

// ============================ //
//             End              //
// ============================ //

#include <xc.h>
#include <stdint.h>

#define T_PRELOAD_LOW 0xC3
#define T_PRELOAD_HIGH 0x3C

#define ZERO 0x3F
#define ONE 0x06
#define TWO 0x5B
#define THREE 0x4F
#define FOUR 0x66
#define FIVE 0x6D
#define SIX 0x7D
#define SEVEN 0x07
#define EIGHT 0x7F
#define NEIN 0x6F

uint8_t count_blink = 0;
uint8_t count_gravity = 0;
uint8_t count_score = 0;
uint8_t count_display = 0;
uint8_t displayIt = 0;
uint8_t totalScore1 = 0;
uint8_t totalScore2 = 0;
uint8_t totalScore3 = 0;
uint8_t currScore = 10;
uint8_t count_reset1 = 0;
uint8_t count_reset2 = 0;
uint8_t sonFlag = 0;



typedef struct {
    uint8_t size;       // Size 
    uint8_t bit_pos;    // Bit position (top)
} hippo;
hippo hip;

uint8_t softResetFlag = 0;
uint8_t hardResetFlag = 0;
void Init()
{
    // B
    TRISB = 0x01; LATB = 0x00; PORTB = 0x00;
    // J
    TRISJ = 0x00; LATJ = 0x00; PORTJ = 0x00;
    // H
    TRISH = 0x00; LATH = 0x00; PORTH = 0x00;
    // D
    TRISD = 0x00; LATD = 0x00; PORTD = 0x00;
}

void InitializeTimerAndInterrupts()
{
    // Enable pre-scalar
    // Full pre-scale
    // we also need to do in-code scaling
    T0CON = 0x00;
    T0CONbits.PSA = 1;
    T0CONbits.TMR0ON = 1;
    T0CONbits.T0PS2 = 1;
    T0CONbits.T0PS1 = 0;
    T0CONbits.T0PS0 = 1;
    // Pre-load the value
    TMR0H = T_PRELOAD_HIGH;
    TMR0L = T_PRELOAD_LOW;

    RCONbits.IPEN = 0;
    INTCON = 0x00;
    INTCONbits.TMR0IE = 1;
    INTCONbits.RBIE = 1;
    INTCONbits.GIE = 1;
    INTCONbits.INT0IE = 1;
    INTCON2bits.INTEDG0 = 1;
}




void handleBlink(){
    LATDbits.LATD0 = ~LATDbits.LATD0;
    count_blink = 0;
    
    return;
}

void handleGravity(){
    if ((hip.size + hip.bit_pos) <= 7) hip.bit_pos++;
    count_gravity = 0;
    
    return;
}

void hotNcold(){
    //SOFT AND HARD RESET FUNCTION
    totalScore1 += currScore;
    if (totalScore1 > 9){
        totalScore1 -= 10;
        totalScore2++;
    }
    
    if (totalScore2 > 9){
        totalScore2 -= 10;
        totalScore3++;
    }
    
    if (totalScore3 > 9){
        totalScore3 -= 10;
    }
    
    if (hardResetFlag) hip.size = 1;
    else hip.size++;
    hip.bit_pos = 8 - hip.size;
    return;
}


void displayHippoHelper1(){
    if (hip.size == 1){
        if (LATDbits.LATD0) LATD = 0b00000011;
        else LATD = 0b00000010;
    }
    else if (hip.size == 2){
        if (LATDbits.LATD0) LATD = 0b00000111;
        else LATD = 0b00000110;
    }
    else if (hip.size == 3){
        if (LATDbits.LATD0) LATD = 0b00001111;
        else LATD = 0b00001110;
    }
    else if (hip.size == 4){
        if (LATDbits.LATD0) LATD = 0b00011111;
        else LATD = 0b00011110;        
    }
    else if (hip.size == 5){
        if (LATDbits.LATD0) LATD = 0b00111111;
        else LATD = 0b00111110;          
    }
    return;
}
void displayHippoHelper2(){
    if (hip.size == 1){
        if (LATDbits.LATD0) LATD = 0b00000101;
        else LATD = 0b00000100;
    }
    else if (hip.size == 2){
        if (LATDbits.LATD0) LATD = 0b00001101;
        else LATD = 0b00001100;
    }
    else if (hip.size == 3){
        if (LATDbits.LATD0) LATD = 0b00011101;
        else LATD = 0b00011100;
    }
    else if (hip.size == 4){
        if (LATDbits.LATD0) LATD = 0b00111101;
        else LATD = 0b00111100;
    }
    else if (hip.size == 5){
        if (LATDbits.LATD0) LATD = 0b01111101;
        else LATD = 0b01111100;
    }
    return;
}
void displayHippoHelper3(){
    if (hip.size == 1){
        if (LATDbits.LATD0) LATD = 0b00001001;
        else LATD = 0b00001000;        
    }
    else if (hip.size == 2){
        if (LATDbits.LATD0) LATD = 0b00011001;
        else LATD = 0b00011000; 
    }
    else if (hip.size == 3){
        if (LATDbits.LATD0) LATD = 0b00111001;
        else LATD = 0b00111000; 
    }
    else if (hip.size == 4){
        if (LATDbits.LATD0) LATD = 0b01111001;
        else LATD = 0b01111000; 
    }
    else if (hip.size == 5){
        if (LATDbits.LATD0) LATD = 0b11111001;
        else LATD = 0b11111000; 
    }  
    return;
}
void displayHippoHelper4(){
    if (hip.size == 1){
        if (LATDbits.LATD0) LATD = 0b00010001;
        else LATD = 0b00010000; 
    }
    else if (hip.size == 2){
        if (LATDbits.LATD0) LATD = 0b00110001;
        else LATD = 0b00110000; 
    }
    else if (hip.size == 3){
        if (LATDbits.LATD0) LATD = 0b01110001;
        else LATD = 0b01110000; 
    }
    else if (hip.size == 4){
        if (LATDbits.LATD0) LATD = 0b11110001;
        else LATD = 0b11110000; 
    }
    return;
}
void displayHippoHelper5(){
    if (hip.size == 1){
        if (LATDbits.LATD0) LATD = 0b00100001;
        else LATD = 0b00100000; 
    }
    else if (hip.size == 2){
        if (LATDbits.LATD0) LATD = 0b01100001;
        else LATD = 0b01100000; 
    }
    else if (hip.size == 3){
        if (LATDbits.LATD0) LATD = 0b11100001;
        else LATD = 0b11100000; 
    }
    return;
}
void displayHippoHelper6(){
    if (hip.size == 1){
        if (LATDbits.LATD0) LATD = 0b01000001;
        else LATD = 0b01000000; 
    }
    else if (hip.size == 2){
        if (LATDbits.LATD0) LATD = 0b11000001;
        else LATD = 0b11000000; 
    }
    return;
}
void displayHippoHelper7(){
    if (LATDbits.LATD0) LATD = 0b10000001;
    else LATD = 0b10000000;
    return;
}

void displayHippo(){
    if (hip.bit_pos == 1) displayHippoHelper1();
    else if (hip.bit_pos == 2) displayHippoHelper2(); 
    else if (hip.bit_pos == 3) displayHippoHelper3(); 
    else if (hip.bit_pos == 4) displayHippoHelper4(); 
    else if (hip.bit_pos == 5) displayHippoHelper5(); 
    else if (hip.bit_pos == 6) displayHippoHelper6(); 
    else if (hip.bit_pos == 7) displayHippoHelper7(); 
    return;    
}


void displayScore(){
    
    if (count_display == 0){
        LATH = 0x08;
        displayIt = 0;
    }
    else if (count_display == 1){
        LATH = 0x04;
        displayIt = totalScore1;
    }
    else if (count_display == 2){
        LATH = 0x02;
        displayIt = totalScore2;
    }
    else if (count_display == 3){
        LATH = 0x01;
        displayIt = totalScore3;
    }
    
    switch(displayIt){
        case 0: LATJ = ZERO; 
            break;
        case 1: LATJ = ONE; 
            break;
        case 2: LATJ = TWO; 
            break;
        case 3: LATJ = THREE; 
            break;
        case 4: LATJ = FOUR; 
            break;
        case 5: LATJ = FIVE; 
            break;
        case 6: LATJ = SIX; 
            break;
        case 7: LATJ = SEVEN; 
            break;
        case 8: LATJ = EIGHT; 
            break;
        case 9: LATJ = NEIN; 
            break;
    }
    
    return;
}

void mesgul_bekleme(){
    for(uint8_t i = 0; i < 201; i++){
        for (uint8_t j = 0; j < 141; j++){
            for (uint8_t k = 0; k < 43; k++){
                __nop();
            }
        }
    }
    return;
}

void reset_blinker0(){
    if (count_reset2 == 0){
        PORTD = 0x00;
    }
    count_reset2++;
    if (count_reset2 == 80){
        count_reset1++;
        count_reset2 = 0;
    }
    return;
}

void reset_blinker1(){
    if (count_reset2 == 0){
        PORTD = 0xFF;
    }
    count_reset2++;
    if (count_reset2 == 80){
        count_reset1++;
        count_reset2 = 0;
    }
    return;
}

void reset_blinker2(){
    if (count_reset2 == 0){
        PORTD = 0xFF;
    }
    count_reset2++;
    if (count_reset2 == 80){
        count_reset1 = 0;
        count_reset2 = 0;
        softResetFlag = 0x00;
        hardResetFlag = 0x00;
        count_blink = 0;
        count_gravity = 0;
        count_score = 0;
        currScore = 10;
        displayHippo();
    }
    return;
}

// ============================ //
//   INTERRUPT SERVICE ROUTINE  //
// ============================ //
__interrupt(high_priority)
void HandleInterrupt()
{
    // Timer overflowed (333 ms)
    if(INTCONbits.TMR0IF)
    {
        INTCONbits.TMR0IF = 0;
        // Pre-load the value
        TMR0H = T_PRELOAD_HIGH;
        TMR0L = T_PRELOAD_LOW;
        if (sonFlag && (softResetFlag || hardResetFlag)){
            if (count_reset1 == 0) {
                if (count_reset2 == 0){
                    PORTD = 0xFF;
                    hotNcold();
                }
                count_reset2++;
                if (count_reset2 == 80){
                    count_reset1++;
                    count_reset2 = 0;
                }
            }
            
            else if (count_reset1 == 1) {
                reset_blinker0();
            }
            
            else if (count_reset1 == 2) {
                reset_blinker1();
            }
            
            else if (count_reset1 == 3) {
                reset_blinker0();
            }
            
            else if (count_reset1 == 4) {
                reset_blinker2();
            }
        }
        else if (sonFlag) {
            count_blink++;
            if (count_blink == 100) handleBlink();

            count_gravity++;
            if (count_gravity == 70) handleGravity();
            
            count_score++;
            if (count_score == 200){
                if (currScore != 0) currScore--;
                count_score = 0;
            }    
            
            displayHippo();

        }
        count_display++;
        if (count_display == 4) count_display = 0;
        displayScore();
    }
    if(INTCONbits.INT0IF)
    {
        if(!softResetFlag && !hardResetFlag){
            if (hip.bit_pos == 1){
                if (hip.size < 5) softResetFlag = 0xff;
                else hardResetFlag = 0xff;
            }
            else hip.bit_pos--;
        }
        // Then clear the bit
        
        
        
        INTCONbits.INT0IF = 0;
    }
    
}

__interrupt(low_priority)
void HandleInterrupt2()
{

}
// ============================ //
//            MAIN              //
// ============================ //
void main()
{
    Init();
    LATD = 0xFF;
    InitializeTimerAndInterrupts();
    mesgul_bekleme();
    sonFlag = 1;
    //__delay_ms(1000);
    
    hip.size = 1;
    hip.bit_pos = 7;
    
    LATD = 1;
    
    
    // Main Loop
    while(1)
    {
        
        //...
    }
}

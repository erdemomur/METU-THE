#include "pragmas.h"
#include <xc.h>
#include <stdint.h>

#define T_PRELOAD_LOW 0xC3
#define T_PRELOAD_HIGH 0x3C

typedef enum {INBUF = 0, OUTBUF = 1} buf_t;

#define BUFSIZE 128       /* Static buffer size. Maximum amount of data */
uint8_t inbuf[BUFSIZE];   /* Preallocated buffer for incoming data */
uint8_t outbuf[BUFSIZE];  /* Preallocated buffer for outgoing data  */
uint8_t head[2] = {0, 0}; /* head for pushing, tail for popping */
uint8_t tail[2] = {0, 0}; 
uint8_t counter_msg = 0; //counter for message timing (100ms)
uint8_t counter_fee = 0; //counter for fee timing (250ms)
uint8_t counter_adc = 0; //counter for adc timing (500ms)
uint8_t inputIndex = 0; //Index for received message string
uint8_t checkBitsOnPark; //bitwise check for available spots. we are shifting this variable. read parkSpots array for better understanding
uint8_t ASpace = 10; //spaces on floors
uint8_t BSpace = 10;
uint8_t CSpace = 10;
uint8_t DSpace = 10;
uint8_t AReserved = 0; //reserved but empty slots on floors
uint8_t BReserved = 0;
uint8_t CReserved = 0;
uint8_t DReserved = 0;
uint8_t qSize = 0; //car number in the queue
uint8_t qTail = 0; 
uint8_t qHead = 0;
uint8_t count_display_floor = 0; //counter for display timing of floor
uint8_t count_display_money = 0; //counter for display timing of money
uint8_t current_floor = 0; //current selected floor
char str_exp[12]; //used this char array for fetching the string of the buffer that has received message
char queue1[16]; //first numbers of the plate that cars on the queue
char queue2[16];    //second numbers of the plate that cars on the queue
char queue3[16];    //third numbers of the plate that cars on the queue
char plate1[40]; //first numbers of the plate that cars on the parking spots
char plate2[40]; //second numbers of the plate that cars on the parking spots
char plate3[40]; //third numbers of the plate that cars on the parking spots
char rez1[40]; //first numbers of the plate that cars have reserved spots
char rez2[40]; //second numbers of the plate that cars have reserved spots
char rez3[40]; //third numbers of the plate that cars have reserved spots
char c; //used in the fetching received string from buffer
int money = 0;
uint8_t feeTime = 0; //time variable for fee
uint8_t slotTime[40]; //the of entrances (index is spot)
uint8_t parkSpots[5] = {0, 0, 0, 0, 0}; // There are 40 parking slots A01 to D10. 5 integer each 8 bits

uint8_t SSNumbers[10] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

uint8_t SSDisplayFlag = 0xFF;


uint8_t goFlag = 0x00; //flag for GO message

inline void disable_rxtx( void ) { PIE1bits.RC1IE = 0;PIE1bits.TX1IE = 0;}
inline void enable_rxtx( void )  { PIE1bits.RC1IE = 1;PIE1bits.TX1IE = 1;}

/* Check if a buffer had data or not */
uint8_t buf_isempty( buf_t buf ) { return (head[buf] == tail[buf])?1:0; }

/* Place new data in buffer */
//#pragma interrupt_level 2 // Prevents duplication of function
void buf_push( uint8_t v, buf_t buf) {
    if (buf == INBUF) inbuf[head[buf]] = v;
    else outbuf[head[buf]] = v;
    head[buf]++;
    if (head[buf] == BUFSIZE) head[buf] = 0;
}
/* Retrieve data from buffer */
uint8_t buf_pop( buf_t buf ) {
    uint8_t v;

    if (buf == INBUF) v = inbuf[tail[buf]];
    else v = outbuf[tail[buf]];
    tail[buf]++;
    if (tail[buf] == BUFSIZE) tail[buf] = 0;
    return v;
    
}
// push the plate number to queue
void push_queue(char *plate){
    if (qSize == 16) return;
    
    queue1[qTail] = plate[0];
    queue2[qTail] = plate[1];
    queue3[qTail] = plate[2];
    
    qTail++;
    if (qTail == 16) qTail = 0;
    qSize++;
    return;
}
// push the message to the buffer
void output_str( char *str ) {
    uint8_t ind = 0;
    
    while (str[ind] != 0) {
        disable_rxtx();
        buf_push(str[ind++], OUTBUF);
        enable_rxtx();
    }
    
    if (!buf_isempty(OUTBUF)) {
        TXREG1 = buf_pop(OUTBUF);  // Push the first byte now
        PIE1bits.TX1IE = 1;        // Enable interrupt for the rest
    }
}

//initialization for registers
void Init()
{
    // B
    TRISB = 0x10; LATB = 0x00; PORTB = 0x00;
    // J
    TRISJ = 0x00; LATJ = 0x00; PORTJ = 0x00;
    // H
    TRISH = 0x10; LATH = 0x00; PORTH = 0x00; // AN12 input RH4 
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
    INTCONbits.PEIE = 1;
    //INTCONbits.INT0IE = 1;
    
    //INTCON2bits.INTEDG0 = 1; //Falling edge trigger
    
}

//initialization for serial com.
// Choose SPBRG from Table 20.3
#define SPBRG_VAL (21)
void init_serial() {
    // We will configure EUSART1 for 57600 baud
    // SYNC = 0, BRGH = 0, BRG16 = 1. Simulator does not seem to work 
    // very well with BRGH=1
    
    TXSTA1bits.TX9 = 0;    // No 9th bit
    TXSTA1bits.TXEN = 0;   // Transmission is disabled for the time being
    TXSTA1bits.SYNC = 0; 
    TXSTA1bits.BRGH = 0;
    RCSTA1bits.SPEN = 1;   // Enable serial port
    RCSTA1bits.RX9 = 0;    // No 9th bit
    RCSTA1bits.CREN = 1;   // Continuous reception
    BAUDCON1bits.BRG16 = 1;

    SPBRGH1 = (SPBRG_VAL >> 8) & 0xff;
    SPBRG1 = SPBRG_VAL & 0xff;
    
    PIE1bits.TX1IE = 0; // Interrupt enable
    PIE1bits.RC1IE = 1;
    TXSTA1bits.TXEN = 1;
}

//initialization for adc communication
void init_adc(){
  // Configure ADC
  ADCON0 = 0x31; // Channel 12; Turn on AD Converter
  ADCON1 = 0x00; // All analog pins
  ADCON2 = 0xA6; // Right Align | 12 Tad | Fosc/64
  ADRESH = 0x00;
  ADRESL = 0x00;
  
  PIE1bits.ADIE = 1;
  PIR1bits.ADIF = 0;

}
// 7-segment display for total money
void displayMoney(){
    uint8_t displayIt;
    
    if (count_display_money == 0){
        LATHbits.LATH0 = 0;
        LATHbits.LATH1 = 0;
        LATHbits.LATH2 = 0;
        LATHbits.LATH3 = 1;
        displayIt = money % 10;
    }
    else if (count_display_money == 1){
        LATHbits.LATH0 = 0;
        LATHbits.LATH1 = 0;
        LATHbits.LATH2 = 1;
        LATHbits.LATH3 = 0;
        displayIt = (money / 10) % 10;
    }
    else if (count_display_money == 2){
        LATHbits.LATH0 = 0;
        LATHbits.LATH1 = 1;
        LATHbits.LATH2 = 0;
        LATHbits.LATH3 = 0;
        displayIt = (money / 100) % 10;
    }
    else if (count_display_money == 3){
        LATHbits.LATH0 = 1;
        LATHbits.LATH1 = 0;
        LATHbits.LATH2 = 0;
        LATHbits.LATH3 = 0;
        displayIt = money / 1000;
    }
    
    LATJ = SSNumbers[displayIt];
    
    count_display_money++;
    if (count_display_money == 4) count_display_money = 0;
    return;
}

// 7-segment display for floors
void displaySpace(){
    uint8_t displayIt;
    uint8_t floorSpace;
    
    if (current_floor == 0) floorSpace = ASpace + AReserved;
    
    else if (current_floor == 1) floorSpace = BSpace + BReserved;
    
    else if (current_floor == 2) floorSpace = CSpace + CReserved;
    
    else floorSpace = DSpace + DReserved;
    
    if (count_display_floor == 0){
        LATHbits.LATH0 = 0;
        LATHbits.LATH1 = 0;
        LATHbits.LATH2 = 0;
        LATHbits.LATH3 = 1;
        displayIt = floorSpace % 10;
    }
    else if (count_display_floor == 1){
        LATHbits.LATH0 = 0;
        LATHbits.LATH1 = 0;
        LATHbits.LATH2 = 1;
        LATHbits.LATH3 = 0;
        displayIt = (floorSpace / 10) % 10;
    }
    else if (count_display_floor == 2){
        LATHbits.LATH0 = 0;
        LATHbits.LATH1 = 1;
        LATHbits.LATH2 = 0;
        LATHbits.LATH3 = 0;
        LATJ = 0;
        count_display_floor++;
        return;
    }
    else if (count_display_floor == 3){
        LATHbits.LATH0 = 1;
        LATHbits.LATH1 = 0;
        LATHbits.LATH2 = 0;
        LATHbits.LATH3 = 0;
        LATJ = 0;
        count_display_floor = 0;
        return;
    }
    
    LATJ = SSNumbers[displayIt];
    
    count_display_floor++;
    return;
}

//popping the received message from buffer to the parameter string
void input_str( char *str ) {
    
    c = 0;
    
    while (!buf_isempty(INBUF) && c != '#') {
        c = buf_pop(INBUF);
        str[inputIndex++] = c; 
    }
    
    if (c == '#'){
        str[inputIndex] = 0;
        inputIndex = 0;
    }
    
}

/* **** ISR functions **** */
void receive_isr() {    
    buf_push(RCREG1, INBUF); // Buffer incoming byte
     
}
void transmit_isr() {
    if (!buf_isempty(OUTBUF)) {
        TXREG1 = buf_pop(OUTBUF); // send byte by byte
    } else {
        PIE1bits.TX1IE = 0;
    }
}

//check reservation arrays for plate.
uint8_t is_reserved(char* plate){
    uint8_t i = 0;
    while(i<40){
        if(plate[0] == rez1[i] && plate[1] == rez2[i] && plate[2] == rez3[i]) return (i+1); //if reserved return slot number 
        i++;
    }
    return 0; // othw. return 0
}

void park_helper(){
    checkBitsOnPark = 1; //bitwise control for parkingSlots array
    uint8_t slt = 0; //slot number 
    uint8_t i = 0;
    uint8_t j = 0;
    char message[12] = {'$', 'S', 'P', 'C','0', '0', '0', '0', '0', '0', '0', 0};
    char plate[3];
    message[4] = str_exp[4]; //insert plate numbers
    message[5] = str_exp[5];
    message[6] = str_exp[6];
    
    if (qSize == 16) return;
    
    plate[0] = str_exp[4]; //setting parameter array plate[]
    plate[1] = str_exp[5];
    plate[2] = str_exp[6];
    
    slt = is_reserved(plate); //return slot number or 0
    
    if (slt){ 
        //if reserved
        switch ((slt-1)/10){ //finding the which floor the spot is
            case 0:
                ASpace++;
                AReserved--;
                break;
            case 1:
                BSpace++;
                BReserved--;
                break;
            case 2:
                CSpace++;
                CReserved--;
                break;
            case 3:
                DSpace++;
                DReserved--;
                break;
        }
        
    }
    
    else{ //if not reserved
        if (ASpace + BSpace + CSpace + DSpace == 0){
            push_queue(plate); //if there is not available place push queue
            return;
        }
        
        while(parkSpots[i] & checkBitsOnPark){ //bitwise AND 
            //enter if spot available
            //i is index of parkSlots , j is index of bit of integer parkSlots[i]
            j++;
            if (j == 8){
                i++;
                j = 0;
                checkBitsOnPark = 1;
            }
            else {

                checkBitsOnPark = checkBitsOnPark << 1; //shift for the bitwise control
            }
            if (i == 5) break;
        }
        
        checkBitsOnPark = parkSpots[i] | checkBitsOnPark;
        parkSpots[i] = checkBitsOnPark; //set the corresponding bit

        slt = (i * 8) + j + 1; //convert i and j to the number of slot (between 0 and 40)
    }
    
    plate1[slt - 1] = str_exp[4]; //insert plate number to the message
    plate2[slt - 1] = str_exp[5];
    plate3[slt - 1] = str_exp[6];
    slotTime[slt - 1] = feeTime;
    //converting spot number to string
    if (slt < 10){
        message[7] = 'A';
        message[8] = '0';
        message[9] = 48 + slt;
        
        ASpace--;
    }
    
    else if (slt == 10){
        message[7] = 'A';
        message[8] = '1';
        message[9] = '0';
        
        ASpace--;
    }
    
    
    else if (slt < 20){
        message[7] = 'B';
        message[8] = '0';
        message[9] = 38 + slt;
        
        BSpace--;
    }
    
    else if (slt == 20){
        message[7] = 'B';
        message[8] = '1';
        message[9] = '0';
        
        BSpace--;
    }
    
    
    else if (slt < 30){
        message[7] = 'C';
        message[8] = '0';
        message[9] = 28 + slt;
        
        CSpace--;
    }
    
    else if (slt == 30){
        message[7] = 'C';
        message[8] = '1';
        message[9] = '0';
        
        CSpace--;
    }
    
    else if (slt < 40){
        message[7] = 'D';
        message[8] = '0';
        message[9] = 18 + slt;
        
        DSpace--;
    }
    
    else {
        message[7] = 'D';
        message[8] = '1';
        message[9] = '0';
        
        DSpace--;
    }
    
    message[10] = '#';
    //send message
    output_str(message);
    return;
}

void exit_helper(){
    char message[12] = {'$', 'F', 'E', 'E','0', '0', '0', '0', '0', '0', '0', 0};
    char plate[3];
    uint8_t i = 0;
    uint8_t slotNumber = 0;
    uint8_t fee = 0;
    uint8_t controlBits = 1; //bitwise control variable
    uint8_t index = 0; //index for parkSpots
    char digit0; // least significant digit of fee number
    char digit1;
    char digit2; // most significant digit of fee number
    message[4] = str_exp[4];
    message[5] = str_exp[5];
    message[6] = str_exp[6];
    plate[0] = str_exp[4];
    plate[1] = str_exp[5];
    plate[2] = str_exp[6];
    if(!(is_reserved(plate))){ //if not reserved
        for (i = 0; i<40 ; i++){
            if (plate1[i] == plate[0] && plate2[i] == plate[1] && plate3[i] == plate[2]){ 
                slotNumber = i + 1; //find the slot number of the car 
                break;
            }
        }
        
        fee = feeTime - slotTime[slotNumber] + 1; 
        money += fee;
        digit2 = (fee/100) + 48; //converting every digit to string
        digit1 = ((fee/10) % 10) + 48 ;
        digit0 = (fee % 10) + 48;
        
        message[7] = digit2; //insert fee digits to message
        message[8] = digit1;
        message[9] = digit0;
        //determine the floor
        if(slotNumber <= 10) ASpace++;
        else if(slotNumber <= 20) BSpace++;
        else if(slotNumber <= 30) CSpace++;
        else if(slotNumber <= 40) DSpace++;
        //determine the exact bit and index of the spot on parkSpots[]
        if(slotNumber <= 8){
            controlBits = controlBits << (slotNumber - 1);
            index = 0;
        }
        else if (slotNumber <= 16){
            controlBits = controlBits << (slotNumber - 9);
            index = 1;
        }
        else if (slotNumber <= 24){
            controlBits = controlBits << (slotNumber - 17);
            index = 2;
        }
        else if (slotNumber <= 32){
            controlBits = controlBits << (slotNumber - 25);
            index = 3;
        }
        else if (slotNumber <= 40){
            controlBits = controlBits << (slotNumber - 33);
            index = 4;
        }
        controlBits = ~controlBits;       
        parkSpots[index] = parkSpots[index] & controlBits; //set the corresponding bit 0
    }
    else{ //if reserved
        slotNumber = is_reserved(plate);
        if(slotNumber <= 10) AReserved++;
        else if(slotNumber <= 20) BReserved++;
        else if(slotNumber <= 30) CReserved++;
        else if(slotNumber <= 40) DReserved++;
    }
    message[10] = '#';
    //send message
    output_str(message);
    
    return;
}

void sub_helper(){
    uint8_t controlBits = 1; //bitwise control register
    uint8_t slotNumber = 0;
    uint8_t lastNumber = 0;
    uint8_t index = 0; //index for parkSpots
    //determine the spot number
    if (str_exp[7] == 'B') slotNumber += 10; 
    else if (str_exp[7] == 'C') slotNumber += 20;
    else if (str_exp[7] == 'D') slotNumber += 30;
    
    if (str_exp[8] == '1') slotNumber += 10;
    else{
        lastNumber = str_exp[9] - 48;
        slotNumber += lastNumber;
    }
    //determining the exact bit on parkSpots[]
    if(slotNumber <= 8){
        controlBits = controlBits << (slotNumber - 1);
        index = 0;
    }
    else if (slotNumber <= 16){
        controlBits = controlBits << (slotNumber - 9);
        index = 1;
    }
    else if (slotNumber <= 24){
        controlBits = controlBits << (slotNumber - 17);
        index = 2;
    }
    else if (slotNumber <= 32){
        controlBits = controlBits << (slotNumber - 25);
        index = 3;
    }
    else if (slotNumber <= 40){
        controlBits = controlBits << (slotNumber - 33);
        index = 4;
    }
    
    
    char message[11] = {'$', 'R', 'E', 'S','0', '0', '0', '0', '0', '0', 0};
    
    
    if (!(parkSpots[index] & controlBits)){ //if available  reserve the parking spot
        message[7]  =  '5'; 
        money += 50;
        parkSpots[index] = parkSpots[index] | controlBits ;
        if (slotNumber <= 10) {ASpace--; AReserved++;} 
        else if (slotNumber <= 20) {BSpace--; BReserved++;} 
        else if (slotNumber <= 30) {CSpace--; CReserved++;} 
        else if (slotNumber <= 40) {DSpace--; DReserved++;} 
        
        rez1[slotNumber - 1] = str_exp[4];
        rez2[slotNumber - 1] = str_exp[5];
        rez3[slotNumber - 1] = str_exp[6];
    }
    
    
    
    message[4] = str_exp[4];
    message[5] = str_exp[5];
    message[6] = str_exp[6];
    
    
    message[9] = '#';
    
    output_str(message);
    return ; 
}

void empty_helper(){
    char message[8] = {'$', 'E', 'M', 'P','0', '0', '#', 0};
    uint8_t ttl;
    ttl = ASpace + BSpace + CSpace + DSpace + AReserved + BReserved + CReserved + DReserved;
    
    message[4] += ttl / 10;
    message[5] += ttl % 10;
    
    output_str(message);
    str_exp[0] = 0;
    return;
}

void check_level(){
    ADCON0bits.GO = 1;
    while (ADCON0bits.GO);
    unsigned int adc_val = (ADRESH << 8) + ADRESL;
    if (adc_val < 256) current_floor = 0;
    else if (adc_val < 512) current_floor = 1;
    else if (adc_val < 768) current_floor = 2;
    else current_floor = 3;
}

// ============================ //
//   INTERRUPT SERVICE ROUTINE  //
// ============================ //
__interrupt(high_priority)
void HandleInterrupt()
{
    // Timer overflowed (5 ms)
    if(INTCONbits.TMR0IF)
    {
        
        INTCONbits.TMR0IF = 0;
        // Pre-load the value
        TMR0H = T_PRELOAD_HIGH;
        TMR0L = T_PRELOAD_LOW;
        
        if(goFlag){
            counter_msg++ ;
            counter_fee++;
            counter_adc++;
        
            if(counter_msg == 20){
                input_str(str_exp);
                if (str_exp[0] == '$' && str_exp[1] == 'P' && str_exp[2] == 'R' && str_exp[3] == 'K') park_helper();
                else if (str_exp[0] == '$' && str_exp[1] == 'E' && str_exp[2] == 'N' && str_exp[3] == 'D') goFlag = 0x00;
                else if (str_exp[0] == '$' && str_exp[1] == 'E' && str_exp[2] == 'X' && str_exp[3] == 'T') exit_helper();
                else if (str_exp[0] == '$' && str_exp[1] == 'S' && str_exp[2] == 'U' && str_exp[3] == 'B') sub_helper();
                else if ((ASpace + BSpace + CSpace + DSpace) > 0 && qSize > 0){
                    str_exp[4] = queue1[qHead];
                    str_exp[5] = queue2[qHead];
                    str_exp[6] = queue3[qHead];
                    
                    qHead++;
                    if(qHead == 16) qHead = 0;
                    qSize--;
                    
                    park_helper();
                }
                else empty_helper();
                str_exp[0] = 0;

                counter_msg = 0;
            }
            
            if(counter_fee == 50){
                feeTime++; 
                counter_fee = 0;
            }
            
            if(counter_adc == 100){
                counter_adc = 0;
                check_level();
            }
            
            if (SSDisplayFlag) displayMoney();
            
            else displaySpace();
            
        }
        
        else{
            input_str(str_exp);
            if (str_exp[0] == '$' && str_exp[1] == 'G' && str_exp[2] == 'O') 
                goFlag = 0xFF;
        }
        
    }
    
    if(INTCONbits.RBIF)
    {
        // Then clear the bit
        if (!PORTB) {
            SSDisplayFlag = ~SSDisplayFlag;
        }
        INTCONbits.RBIF = 0;
    }
    
    if (PIR1bits.RC1IF) {receive_isr();}//LATD = 0xFF;
    if (PIR1bits.TX1IF) transmit_isr(); //LATA = 0xFF;
    
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
    LATD = 0x00;
    InitializeTimerAndInterrupts();
    init_serial();
    str_exp[0] = 0;
    init_adc();
    
    // Main Loop
    while(1)
    {
        
        //...
    }
}

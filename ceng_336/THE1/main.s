PROCESSOR 18F8722

#include <xc.inc>

; CONFIGURATION (DO NOT EDIT)
; CONFIG1H
CONFIG OSC = HSPLL      ; Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
CONFIG FCMEN = OFF      ; Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
CONFIG IESO = OFF       ; Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
; CONFIG2L
CONFIG PWRT = OFF       ; Power-up Timer Enable bit (PWRT disabled)
CONFIG BOREN = OFF      ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
; CONFIG2H
CONFIG WDT = OFF        ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
; CONFIG3H
CONFIG LPT1OSC = OFF    ; Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
CONFIG MCLRE = ON       ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
; CONFIG4L
CONFIG LVP = OFF        ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
CONFIG XINST = OFF      ; Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))
CONFIG DEBUG = OFF      ; Disable In-Circuit Debugger


GLOBAL var1
GLOBAL var2
GLOBAL var3
GLOBAL digit0    
GLOBAL digit1    
GLOBAL digit2    
GLOBAL digit3    
GLOBAL digit4    
GLOBAL digit5    
GLOBAL flag0   
GLOBAL flag1   
GLOBAL flag2   
GLOBAL flag3   
GLOBAL flag4   
GLOBAL flag5   
GLOBAL flag7  
GLOBAL counter_c
GLOBAL pause
GLOBAL for_initial
GLOBAL for_initial_2
GLOBAL var4
GLOBAL var5
GLOBAL var6
GLOBAL var7
GLOBAL result

; Define space for the variables in RAM
PSECT udata_acs
var1:
    DS 1 ; Allocate 1 byte for var1
var2:
    DS 1
var3:
    DS 1
var4:
    DS 1
var5:
    DS 1
var6:
    DS 1
var7:
    DS 1
digit0:
    DS 1    
digit1:
    DS 1 
digit2:
    DS 1
digit3:
    DS 1 
digit4:
    DS 1
digit5:
    DS 1
flag0:
    DS 1
flag1:
    DS 1
flag2:
    DS 1
flag3:
    DS 1
flag4:
    DS 1
flag5:
    DS 1
flag7:
    DS 1
counter_c:
    DS 1
pause:
    DS 1
for_initial:
    DS 1
for_initial_2:
    DS 1
result: 
    DS 1


PSECT resetVec,class=CODE,reloc=2
resetVec:
    goto       main

PSECT CODE
main:
    clrf var1	; var1 = 0		
    clrf var2   ; var2 = 0
    clrf var3   ;
    clrf var4
    clrf var5
    clrf result ; result = 0
    
    clrf flag0
    clrf flag1
    clrf flag2
    clrf flag3
    clrf flag4
    clrf flag5
    clrf flag7
    
    clrf counter_c
    clrf pause
    clrf for_initial
    clrf for_initial_2
    
    
    clrf TRISC  ; PORT C is output
    clrf TRISD	; PORT D is output
    setf TRISE  ; PORT E is input
    
    setf PORTC  ; PORT C is 11111111
    setf PORTD  ; PORT D is 11111111
    
    

    
    movlw 10
    movwf var1
    
    movlw 10
    movwf var2
    
    movlw 2
    movwf digit0
    
    movlw 5
    movwf digit1
    
    movlw 8
    movwf digit2
    
    movlw 0
    movwf digit3
    
    movlw 8
    movwf digit4
    
    movlw 2
    movwf digit5
    
    call busy_wait
    
    clrf PORTD
    clrf PORTC
    
    clrf flag0
    clrf flag7
    
    
initial_outer_loop:
    
    movlw 40
    movwf var4
    
    movlw 40
    movwf var5
    
    movff digit0, PORTC
    goto main_inner_loop
    
main_outer_loop:
    
    movlw 40
    movwf var4
    
    movlw 40
    movwf var5
   
    movlw 0
    subwf pause, 0
    bnz gec ; pause ise counter_c yi arttirma
    
    incf counter_c
    
    gec:
    goto output_digits
    donus:
    btg PORTD , 0
    
main_inner_loop:
	inner_loop1:
	    decf var4
	    bz main_outer_loop
	    inner_loop2:
		decf var5
		bz inner_loop1
		
		call check_input
		call check_flag
		
		goto inner_loop2

    
    
output_digits:
    movlw 0
    subwf counter_c, 0
    bz output_digit0
    movlw 1
    subwf counter_c, 0
    bz output_digit1
    movlw 2
    subwf counter_c, 0
    bz output_digit2
    movlw 3
    subwf counter_c, 0
    bz output_digit3
    movlw 4
    subwf counter_c, 0
    bz output_digit4
    movlw 5
    subwf counter_c, 0
    bz output_digit5
    
    movlw 6
    subwf counter_c, 0
    bz output_digit0_with_overflow
    
    goto donus
    
output_digit0:
    movff digit0, PORTC
    bra donus
output_digit1:
    movff digit1, PORTC
    bra donus
output_digit2:
    movff digit2, PORTC
    bra donus
output_digit3:
    movff digit3, PORTC
    bra donus
output_digit4:
    movff digit4, PORTC
    bra donus
output_digit5:
    movff digit5, PORTC
    bra donus
output_digit0_with_overflow:
    movff digit0, PORTC
    clrf counter_c
    bra donus
    
re0_release:
    movlw 9
    subwf digit0, 0
    bz of_digit0
    incf digit0
    clrf flag0
    return
    of_digit0:
    clrf digit0
    clrf flag0
    return
re1_release:
    movlw 9
    subwf digit1, 0
    bz of_digit1
    incf digit1
    clrf flag1
    return
    of_digit1:
    clrf digit1
    clrf flag1
    return
re2_release:
    movlw 9
    subwf digit2, 0
    bz of_digit2
    incf digit2
    clrf flag2
    return
    of_digit2:
    clrf digit2
    clrf flag2
    return
re3_release:
    movlw 9
    subwf digit3, 0
    bz of_digit3
    incf digit3
    clrf flag3
    return
    of_digit3:
    clrf digit3
    clrf flag3
    return
re4_release:
    movlw 9
    subwf digit4, 0
    bz of_digit4
    incf digit4
    clrf flag4
    return
    of_digit4:
    clrf digit4
    clrf flag4
    return
re5_release:
    movlw 9
    subwf digit5, 0
    bz of_digit5
    incf digit5
    clrf flag5
    return
    of_digit5:
    clrf digit5
    clrf flag5
    return
re7_release:
    btg pause, 0
    clrf flag7
    return

   
    
is_re0_released:
    btfss PORTE, 0 ; check if flag0 = 0
    rcall re0_release
    return
is_re1_released:    
    btfss PORTE, 1 ; check if flag1 = 0
    rcall re1_release
    return
is_re2_released:    
    btfss PORTE, 2 ; check if flag2 = 0
    rcall re2_release
    return
is_re3_released:    
    btfss PORTE, 3 ; check if flag3 = 0
    rcall re3_release
    return
is_re4_released:    
    btfss PORTE, 4 ; check if flag4 = 0
    rcall re4_release
    return
is_re5_released:    
    btfss PORTE, 5 ; check if flag5 = 0
    rcall re5_release
    return
is_re7_released:    
    btfss PORTE, 7 ; check if flag7 = 0
    rcall re7_release
    return
    
    

re0_pressed:
    movlw 1
    movwf flag0
    return
re1_pressed:
    movlw 1
    movwf flag1
    return
re2_pressed:
    movlw 1
    movwf flag2
    return
re3_pressed:
    movlw 1
    movwf flag3
    return
re4_pressed:
    movlw 1
    movwf flag4
    return
re5_pressed:
    movlw 1
    movwf flag5
    return
re7_pressed:
    movlw 1
    movwf flag7
    return
not_pressed:
    nop
    nop
    nop
    nop
    nop
    nop
    bra r_check_input
    
check_input:
	btfsc PORTE, 0 ; check if RE0 = 1
	rcall re0_pressed
	btfsc PORTE, 1 ; check if RE1 = 1
	rcall re1_pressed
	btfsc PORTE, 2 ; check if RE2 = 1
	rcall re2_pressed
	btfsc PORTE, 3 ; check if RE3 = 1
	rcall re3_pressed
	btfsc PORTE, 4 ; check if RE4 = 1
	rcall re4_pressed
	btfsc PORTE, 5 ; check if RE5 = 1
	rcall re5_pressed
	btfsc PORTE, 7 
	rcall re7_pressed
	
	movlw 0
	subwf PORTE, 0
	bz not_pressed  ; tusa basilmadiginda delay için
	r_check_input:
	return

check_flag:
	btfsc flag0, 0 ; check if flag0 = 1
	rcall is_re0_released

	
	btfsc flag1, 0 ; check if flag1 = 1
	rcall is_re1_released

	
	btfsc flag2, 0 ; check if flag2 = 1
	rcall is_re2_released

	
	btfsc flag3, 0 ; check if flag3 = 1
	rcall is_re3_released

	
	btfsc flag4, 0 ; check if flag4 = 1
	rcall is_re4_released

	
	btfsc flag5, 0 ; check if flag5 = 1
	rcall is_re5_released

	
	btfsc flag7, 0 
	rcall is_re7_released

	return
	
    
    
busy_wait:
    loop1:
	incf var1
	bc exit_loop
	loop2:
	    incf var2
	    bc loop1
	    loop3:
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		goto loop2
    exit_loop:
    return  
end resetVec

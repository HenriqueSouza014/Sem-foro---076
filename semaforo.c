 /* EVENTS */

#include "Cpu.h" #include "Events.h"

#ifdef __cplusplus extern "C" { #endif

extern int tempo, flagLDR,countnoite, countdia, ajuste; //variaveis utilizadas na main e em events

void Cpu_OnNMIINT(void) { }

void piscar(void) { tempo++; //variavel de temporização para controle do semáforo

if(flagLDR<100) {		//quando esta em modo noturno 
  countnoite++;			//contador para modo noturno
} 

else {				//quando esta em modo diurno
  countdia++;
  countnoite = 0;		
}

if (countdia < 10 && ajuste == 1) {	//executa o if caso esteja noite
  Vermelho_pedestre_ClrVal();
  Verde_pedestre_ClrVal();
  Vermelho_ClrVal();
  Verde_ClrVal(); 
  Amarelo_NegVal();
  tempo = 0;
}

if(countnoite>=10) {			//executa o if apos um tempo de 5s, temporizado pelo countnoite
  Vermelho_pedestre_ClrVal();
  Verde_pedestre_ClrVal();
  Vermelho_ClrVal();
  Verde_ClrVal(); 
  tempo=0;
  countdia = 0;
  ajuste=1;				//seta variavel de controle
} 

}

void EInt1_OnInterrupt(void) { if((countdia>=10) && (tempo>=0) && (tempo<5)){ tempo = 4; } }

void AD1_OnEnd(void) { }

void AD1_OnCalibrationEnd(void) { }

/* END Events */

/* MAIN */

#ifdef __cplusplus } /* extern "C" */ #endif

#include "Cpu.h" #include "Events.h" #include "Verde.h" #include "BitIoLdd1.h" #include "TI1.h" #include "TimerIntLdd1.h" #include "TU1.h" #include "Amarelo.h" #include "BitIoLdd2.h" #include "Vermelho.h" #include "BitIoLdd3.h" #include "Verde_pedestre.h" #include "BitIoLdd4.h" #include "Vermelho_pedestre.h" #include "BitIoLdd5.h" #include "EInt1.h" #include "ExtIntLdd1.h" #include "AD1.h" #include "AdcLdd1.h" #include "PE_Types.h" #include "PE_Error.h" #include "PE_Const.h" #include "IO_Map.h"

static uint8_t valor; int flagLDR=0; int tempo=0, z=0; int ajuste=0; int countnoite=0, countdia=10;

int main(void) { PE_low_level_init();

#ifdef PEX_RTOS_START PEX_RTOS_START(); /* Startup of the selected RTOS. Macro is defined by the RTOS component. */ #endif

 for(;;){
  (void)AD1_Measure(TRUE);
  (void)AD1_GetValue8(&valor);		//obtem o valor da saida do LDR
	  
  flagLDR=valor; 
	  
	
	  if(countdia>=10) {				//executa o if apos 5s temporizado, pelo countdia
	    ajuste = 0;
	    
	      if((tempo>=0) && (tempo<5) ){		
		 Amarelo_ClrVal();
		 Vermelho_ClrVal();
		 Verde_SetVal();
		 Verde_pedestre_ClrVal();
		 Vermelho_pedestre_SetVal();	      
	      }
		 	      
	      if((tempo>=5) && (tempo<7)){
		 Verde_ClrVal();
		 Amarelo_SetVal();
	      }
		 	      
	      if((tempo>=7) && (tempo<12)){
		 Amarelo_ClrVal();
		 Vermelho_SetVal();
		 Vermelho_pedestre_ClrVal();
		 Verde_pedestre_SetVal();	 	  	
	      }

	      if(tempo==12){
		 tempo=0;
	      }

	 }

}


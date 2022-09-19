#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <time.h>





#include "./avr_common/uart.h" 


typedef struct {
  uint8_t status: 1; 
  uint8_t key:   7;

} KeyEvent;


uint16_t key_status; 

uint8_t keyScan(KeyEvent* events){
  uint16_t new_status=0; 
  int num_events=0;      
  uint8_t key_num=0;       
  for (int r=0; r<4; ++r){

  
    uint8_t row_mask= ~(1<<(r+4));
    
    PORTA =row_mask;

    _delay_us(300);

 
    uint8_t row= ~(0x0F & PINA);
    
    for (int c=0;c<4;++c){
     
      uint16_t key_mask=1<<key_num;
      uint16_t col_mask=1<<c;
      
      uint8_t cs=(row & col_mask)!=0; 
      
      if (cs){
        new_status |= key_mask;
      }
      
      uint8_t ps=(key_mask&key_status)!=0;

      // if different from before, shoot an event;
      if (cs!=ps){
        KeyEvent e;
        e.key=key_num;
        e.status = cs;
        events[num_events]=e;
        ++num_events;
      }
      ++key_num;
    }
    row_mask=row_mask<<1;
  }
  key_status=new_status;
  return num_events;
}
static char* note []=
  {
      "Do",  
      "RE",  
     "MI",  
     "FA",  
     "SOL", 
     "LA",  
     "SI",  
     
    };

#define MAX_EVENTS 16

int main(void){
 
  printf_init(); 

  DDRA=0xF0; 
  PORTA=0x0F;

  KeyEvent events[MAX_EVENTS];
  int tempo = 0;
   int prova[16]; 
  while(1){
  system("espeak --stdout 'test' | paplay" );
    tempo +=1 ;
    //printf("ciao");
    uint8_t num_events=keyScan(events);
    for (uint8_t k=0; k<num_events; ++k){
      
        
      KeyEvent e=events[k];
    
      if (e.status == 1 )  { prova[(int)e.key] = tempo ; printf("inizio nota %s  al tempo = %d \n" , note[(int)e.key], prova[(int)e.key] );}
      
      
      if (e.status == 0 )  {int tempoFine = tempo-prova[(int)e.key] ; printf("durata della nota %s : %d \n" , note[(int) e.key], tempoFine ); }
     
      
      //system("canberra-gtk-play -f pp.wav");
     // PlaySound("./pp.wav", NULL , SND_SYNC);
      
    } 
  }
}

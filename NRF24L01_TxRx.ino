#include <SPI.h>
    #include "nRF24L01.h"
    #include "RF24.h"

    RF24 radio(9,10);

    const uint64_t pipes[2] = { 0xF0F0F0F0E0LL, 0xF0F0F0F0D2LL };
    unsigned long Command = 23;
    char data_in;
    typedef enum { role_ping_out = 1, role_pong_back } role_e;

    const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

    role_e role = role_pong_back;
    char out;
    unsigned long data = 0;
    
    void setup()
    {
    Serial.begin(57600);
    radio.begin();
    
    radio.setRetries(15,15);
    radio.openReadingPipe(1,pipes[1]);
    
    radio.startListening();
    radio.printDetails();
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1,pipes[0]);
    radio.startListening();
    
   
    }

    void loop(void)
    {

      if(Serial.available())
      {
      radio.openWritingPipe(pipes[0]);
      radio.openReadingPipe(1,pipes[1]);
      radio.stopListening();
       
        data_in = Serial.read();
        Command = data_in;
        Serial.print(data_in);
       // radio.stopListening();

        radio.write( &Command, sizeof(unsigned long) );
    
     
    radio.openReadingPipe(1,pipes[1]);
    radio.startListening();
    radio.printDetails();
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1,pipes[0]);
    radio.startListening();
    
        
      }
    
     
     else if ( radio.available() )
    {
      
    
    radio.read( &data, sizeof(unsigned long) );
    out=data;
    Serial.print(out);
    }
    }
    

  
    

   

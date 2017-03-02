void portB() {
  if (!bools.disablePortB) {

t=s>>0002;

        
    if (t < portBlength && bools.portBticker) {                                                       //set length of drum sounds
      
      beatSeqSelex = (64 - selex) % 16;  //invert selex to read binary number from left to right


      if (bitRead(BDseq, beatSeqSelex) == 1) {
        PORTB = (PORTB & ~mask) | t * (t >> 3) >> (t >>4) & mask;//B00000010 ;
        //       PORTB = (PORTB & B11111101) | B11111111 ;//& B00000010);
        //t++;
        //PORTB = (PORTB & B11111101) | t * (t >> 2) >> (t >> x);// disty bd x was 6
      }


      if (bitRead(SDseq, beatSeqSelex) == 1 && t<(portBlength>>1)) {
int SDt = t+100000;
        PORTB = (PORTB & ~mask) | (SDt * (SDt >> 3) >> (t >> x)) & mask;
      }


      if (bitRead(HHseq, beatSeqSelex) == 1) {
        PORTB = (PORTB & ~mask) | (s>>1 * (s>>1 >> 7 | s>> x >> 9 )) & mask;
      }


	   
    }
  }
}


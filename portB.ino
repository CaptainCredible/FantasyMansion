void portB() {
  if (!bools.disablePortB && bootMode != 1) {

t=s>>mood;

        
    if (t < portBlength && bools.portBticker) {                                                       //set length of drum sounds
      
      beatSeqSelex = (64 - selex) % 16;  //invert selex to read binary number from left to right


      if (bitRead(BDseq, beatSeqSelex) == 1) {
        PORTB = (PORTB & B11111101) | t * (t >> 3) >> (t >> 4) & mask ;
        //PORTB = (PORTB & B11111101) | t * (t >> 2) >> (t >> x);// disty bd x was 6
      }


      if (bitRead(SDseq, beatSeqSelex) == 1 && t<(portBlength>>1)) {
        PORTB = (PORTB & B11111101) | (s * (t >> 3) >> (t >> 7)) & mask ;
      }


      if (bitRead(HHseq, beatSeqSelex) == 1) {
        PORTB = (PORTB & B11111101) | (s>>1 * (s>>1 >> 7 | s>>1 >> 9 )) & mask ; //( t * (t >> 3) >> (t >> 6))& B00000010;
      }


    }
  }
}

void portB() {
  if (!disablePortB) {

    if (t < portBlength && portBticker) {                                                       //set length of drum sounds
      beatSeqSelex = (64 - selex)%16;    //invert selex to read binary number from left to right

      if (bitRead(BDseq, beatSeqSelex) == 1) {
        PORTB = (PORTB & B11111101) | t * (t >> 3) >> (t >> 4);
        //PORTB = (PORTB & B11111101) | t * (t >> 2) >> (t >> x);// disty bd x was 6
        t++;

        if bitRead(modsSeq, beatSeqSelex == 1) {
          t++;                                                                                      //mod / tweak-code goes here
        }
      }

      if (bitRead(SDseq, beatSeqSelex) == 1) {
        //int tee = t+10;
        PORTB = (PORTB & B11111101) | (t * (t >> 3) >> (t >> 7));
        t++;

      }

      if (bitRead(HHseq, beatSeqSelex) == 1) {
        PORTB = (PORTB & B11111101) | t * (t >> 7 | t >> 9);//( t * (t >> 3) >> (t >> 6));
        t++;
      }

    }
  }
}

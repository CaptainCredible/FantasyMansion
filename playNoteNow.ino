
void playNoteNow(int Hz, int oct, int distortion){
   sei();                                                          // Allow interrupts
   WDTCR |= 1 << WDIE;                                             //no idea what this is
      Freq[Chan] = Hz>>oct;                  //look up the notes frequency and shift the octave as per the array
      Amp[Chan] = 1 + distortion << (10);                               // change to 2 for epic dist
      Chan = (Chan + 1) % (Channels - 1);      
}


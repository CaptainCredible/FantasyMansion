// Watchdog interrupt plays notes
ISR(WDT_vect) {                                                  //interupt triggered by watchdog timer
if (play){
playNextNote();
}
if(slolo){
chordSolo(x);
}

if(Blink){
  blinkTicker = !blinkTicker;
  digitalWrite(LED, blinkTicker);
}

}

void playNextNote(){
  if(writeNote){
    digitalWrite(LED,HIGH);
    int EXX = (x*-1)+600;
    EXX = EXX/10;
    if(EXX<0){
      EXX = 0;
    }else if(EXX>31){
        EXX=31;
      }
    
       bitSet(Chords[selex],EXX);
  }
  if(eraseNote){
    Chords[selex]=0;
  }



if(beatWrite){
   byte beatSeqSelexLookahead = (beatSeqSelex-1)%16;
//  if(beatSeqSelexLookahead<0){   //replaced by modulo 
//    beatSeqSelexLookahead = 15;
//  }
  
  if(x<300){ //BD
    digitalWrite(LED,HIGH);
    bitSet(BDseq,beatSeqSelexLookahead);
  } else if(x<400){ //SD
    bitSet(HHseq,beatSeqSelexLookahead);
    
  } else {
    digitalWrite(LED,LOW);
    bitSet(SDseq,beatSeqSelexLookahead);
  }
}

if(beatErase){
  byte beatSeqSelexLookahead = (beatSeqSelex-1)%16;
  bitClear(BDseq,beatSeqSelexLookahead);
  bitClear(SDseq,beatSeqSelexLookahead);
  bitClear(HHseq,beatSeqSelexLookahead);
}


  
  //Tempo = 3 + slowMo;                                    //half the tempo on every other bar
   WDTCR = 1<<WDIE | Tempo<<WDP0; // 4 Hz interrupt
  sei();                                                          // Allow interrupts
  WDTCR |= 1 << WDIE;                                             //no idea what this is
  unsigned long Chord = (Chords[selex]) << ((barTicker % 2)*melodyOffset)+((partTicker%(modulationinterval))*melodyOffsetOffset);                    //>> counter  (or barTicker % 2) is modulation Modulate
 
  for (int Note = 0; Note < 32; Note++) {                         //step through each bit of the 32bit number
    if ((Chord & 0x80000000) != 0) {                              //check if there are any notes in this chord ?
      Freq[Chan] = Scale[Note]>>octArray[selex];                  //look up the notes frequency and shift the octave as per the array
      Amp[Chan] = 1 + dist << (Decay + 5);                               // change to 2 for epic dist
      Chan = (Chan + 1) % (Channels - 1);
    }
    Chord = Chord << 1;
  }
  
  selex++;
  if (selex >= initBarLength) {
    barTicker++;
    //t=0;
    selex = 0;
    
  }
  if(barTicker>2){
    barTicker = 1;
    if(!myFirstSongMode){
    addNote();
    partTicker++;
    }
    //deleteRandom();
  }
  if(partTicker>4){
    songTicker++;
    if(!myFirstBeatMode){
    gener8BDbeat();
    gener8SDbeat();
    gener8hats();
    }
    partTicker = 1;
  }
  t = 0;
}



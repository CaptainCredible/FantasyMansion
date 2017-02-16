void chordSolo(int X){
  
  X = X/60; //scale X down to 10
  
if(bools.rightSwitch){
  X=X+10; //select other scale
}
 
 int freqToBePlayed = pgm_read_word_near(Scale + (pgm_read_byte_near(soloScales+X))); //Scale[soloScales[X]];
 
 //playNoteNow(freqToBePlayed, octaveselect, 1);
 

 
 }
 




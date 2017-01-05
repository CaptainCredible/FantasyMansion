void chordSolo(int X){
  
  X = X/60; //scale X down to 10
  
if(rightSwitch){
  X=X+10; //select other scale
}
 
 int freqToBePlayed = Scale[soloScales[X]];
 
 playNoteNow(freqToBePlayed, octaveselect, 1);
 
 //int Note = currentScale[nert];
 
 }
 




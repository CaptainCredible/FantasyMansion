void chordSolo(int X){
  
  X = X/20; //scale X down to something
  
if(bools.rightSwitch){
  X=(X+5)%15; //select other scale
}
 
int freqToBePlayed = Scale[x];
playNoteNow(freqToBePlayed, octaveselect, 1);
 }
 
//put this in a function so it can be called by other than the watchdog
void generatePolyTones(){
// Generate square waves on 4 channels
  signed char Temp, Mask, Env, Note, Sum=0;
  for (int c = 0; c < Channels; c++) {
    int fraqwancy = (Freq[c]);//+bender);//>>2);
    Acc[c] = Acc[c] + (fraqwancy<<(octOffset));  
    Amp[c] = Amp[c] - (Amp[c] != 0)+ distAmount;       //
    Temp = Acc[c] >> 8;
    Mask = Temp >>  7;
    Env = Amp[c] >> Decay;
    Note = (Env ^ Mask) + (Mask & 1);
    Sum = Sum + Note;
  }
  OCR1B = Sum + 128;//128;
  
}

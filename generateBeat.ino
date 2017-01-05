void clearDrums(){
  BDseq=0;
  SDseq=0;
  HHseq=0;
}

void gener8BDbeat(){
  BDseq = 0;

for (int i = 15; i > -1; i--) {
  if(i%2 == 0){
  if (random(0,3) == 0){             //each even step has a 1 in 4 chance of generating a BD
    bitSet(BDseq,i);                //set this seq step high
  }
//  if(random(0,10) == 0){
//    bitSet(BDseq,i);                //each odd step has a 1 in 10 chance
//  }
  }                 
  }
}

void gener8SDbeat() {
  SDseq = 0;
  for (int i = 15; i > -1; i--) {
  if (random(0,4) == 0){             //each step has a 1 in 4 chance of generating a BD
    bitSet(SDseq,i);                  //set current bit high
  }    
    //SDarray[i] = random(0, 4);                
  }
}

void gener8hats() {
  HHseq=0;
  for (int i = 15; i > -1; i--) {
     if (random(0,4) == 0){             //each step has a 1 in 3 chance of generating a BD
    bitSet(HHseq,i);                    //set the bit for current step to high
  }
                   
  }
}

void gener8hatsStraight(){
  HHseq = 0;
  for(int i = 15; i > -1; i--){
   if(i%2 == 0){
    bitSet(HHseq,i);
   }
  }
}

void newDrums(){
  gener8BDbeat();
  gener8SDbeat();
  gener8hats();
}


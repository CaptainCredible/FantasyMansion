void clearDrums() {
  BDseq = 0;
  SDseq = 0;
  HHseq = 0;
}

void gener8BDbeat() {
  BDseq = 0;

  for (int i = 15; i > -1; i--) {
    if (i % 4 == 0) {
      if (random(5) < 4) {           //each 4th step has a 3 in 4 chance of generating a BD
        bitSet(BDseq, i);               //set this seq step high
      }
    }
  }
}

void gener8SDbeat() {
  SDseq = 0;
  for (int i = 15; i > -1; i--) {
    if (random(0, 4) == 0) {           //each step has a 1 in 4 chance of generating a BD
      bitSet(SDseq, i);                 //set current bit high
    }
  }
}

void gener8hats() {
  HHseq = 0;
  for (int i = 15; i > -1; i--) {
    if (random(0, 4) == 0) {           //each step has a 1 in 3 chance of generating a BD
      bitSet(HHseq, i);                   //set the bit for current step to high
    }
  }
}

void gener8hatsStraight() {
  HHseq = 0;
  for (int i = 15; i > -1; i--) {
    if (i % 2 == 0) {
      bitSet(HHseq, i);
    }
  }
}

void newDrums() {
  gener8BDbeat();
  gener8SDbeat();
  gener8hats();
}

/*
void generatePortBLenghts(){
  for(int i = 0;i<8;i++){
    portBlengths[i]=random(500,50000);
  }
}
*/

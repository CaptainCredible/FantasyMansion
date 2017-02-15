void modeSelect() {
  switch (mode) {

    case 1:
      musicbox();   //INIT STATE, WILL GENERATE ITS OWN BEAT AND MELODY WHEN IT CANT FIND A USER MADE CONTENT
      break;

    case 2:
      myFirstSong();
      break;

    case 3:
      myFirstBeat();
      break;

    case 4:
      musicbox();   // will use myBeat and myMelody
      break;


    case 5: //mad solo , trig on note change
      trigOnChangeSolo();
      break;

    case 6:
      trigOnPurifySolo();
      break;


    case 7:
    trigOnPurifySolo();
      break;

    case 8:
      if (bools.firstRun) {
        gener8Melody();
        bools.firstRun = false;
      }
      musicbox();
      break;

    case 9:
      buttonSolos();
      break;

    case 10:  //DEBUGMODE

      //musicbox();
      test();
      break;

    default:
      //digitalWrite(LED, HIGH);
      break;
  }
}

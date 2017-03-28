void portB() {
	if (!bools.disablePortB) {

		t = s >> 2;


		if (t < portBlength && bools.portBticker) {                                                       //set length of drum sounds
			if (bitRead(BDseq, selex % 16) == 1) {
				PORTB = (PORTB & ~mask) | t * (t >> 3) >> (t >> 4) & mask;//B00000010 ;
			}


			if (bitRead(SDseq, selex % 16) == 1 && t < (portBlength >> 1)) {
				int SDt = t + 100000;
				PORTB = (PORTB & ~mask) | (SDt * (SDt >> 3) >> (t >> x)) & mask;
			}


			if (bitRead(HHseq, selex % 16) == 1) {
				PORTB = (PORTB & ~mask) | (s >> 1 * (s >> 1 >> 7 | s >> x >> 9)) & mask;
			}
		}
		else {
			PORTB = (PORTB & ~mask) | 0;
		}
	}
}


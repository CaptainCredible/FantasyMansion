void clearDrums() {
	BDseq = 0;
	SDseq = 0;
	HHseq = 0;
}

void gener8BDbeat() {
	//if(random(2)){
	if (true) {
		//BDseq = 0B1000100010001000;
		BDseq = 0B0001000100010001;
	}
	else {
		//BDseq = 0B1001001001001010;
		BDseq = 0B0101001001001001;
	}
}

void gener8SDbeat() {
	if (bools.portBMode) {
		SDseq = 0;
		for (int i = 15; i > -1; i--) {
			if (random(0, 6) == 0) {           //each step has a 1 in 5 chance of generating a BD
				bitSet(SDseq, i);                 //set current bit high
			}
		}
	}
}

void gener8hats() {
	if (bools.portBMode) {      //deactivate this shit is we arent making portbs cos it is slow
		HHseq = 0;
		if (a > 10) {
			HHseq = 0B0101010101010101;
		}
		else {
			HHseq = 0B1001001001001001;
		}
	}
}


void newDrums() {
	gener8BDbeat();
	gener8SDbeat();
	gener8hats();
}

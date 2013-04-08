#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    
    soundStream.setup(this, 0, 1, 44100, 256, 4);
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(86,157,204);
    ofEnableSmoothing();
    
	
	for (int i = 0; i < 1000; i++){
		particle myParticle;
		myParticle.setInitialCondition(ofRandom(0,1000),ofRandom(1000,0),0,0);
		// more interesting with diversity :)
		// uncomment this: 
		myParticle.damping = ofRandom(0.001, 0.05);
		particles.push_back(myParticle);
	}
	
}

//--------------------------------------------------------------
void testApp::update(){

	// on every frame 
	// we reset the forces
	// add in any forces on the particle
	// perfom damping and
	// then update
	
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
		
		
		particles[i].addAttractionForce(freq, mouseY, ofRandom(150,200), 0.4);
		particles[i].addRepulsionForce(mouseX, finalVol, ofRandom(100,150), 0.4);
//
//		
		particles[i].addCounterClockwiseForce(mouseX, mouseY, 10, 0.1);
		//particles[i].addClockwiseForce(mouseX, mouseY, 200, 1);
		
		particles[i].addForce(0.0, ofRandom(0.001, 0.004));  // gravity
		particles[i].addDampingForce();
		particles[i].update();
	}

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofEnableAlphaBlending();
    

    ofEnableAlphaBlending();
	ofSetColor(107,196,255, 125);
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].draw();
	}

}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(){
}

//---------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){
    
    for (int i = 0; i < bufferSize; i++){
		
		float sampleValue=input [i]* input [i];
		vol += sampleValue;
		
        //cout << input[i] << endl;
    }
	
	float vol2 = vol / 256;
	vol = 0;
	finalVol = sqrt(vol2);
	//cout << finalVol << endl;
	
	/*for (int i = 0; i < bufferSize; i++){
     
     float sampleValue = input [i];
     
     if (sampleValue > 0 && input) {
     zeroCrossings ++;
     }
     
     lastSampleValue = sampleValue;
     
     
     
     
     //cout << input[i] << endl;
     }*/
	
	
    
	
	
	
	
	for (int i = 0; i < bufferSize-1; i++){
		
		if (input[i] > 0 && input[i+1] < 0) {
            
			zeroCrossings ++;
			
		}
		
		if (input[i] < 0 && input[i+1] > 0) {
			
			zeroCrossings ++;
			
		}
		
		
	}
	
	
	//44100 / 256
	
	freq = ((zeroCrossings * 44100.0) / 256.0) / 2.0;
	
	finalFreq = prevFreq * 0.95 + freq * 0.05;
	
	cout << finalFreq << endl;
	prevFreq = finalFreq;
	
	
	//cout << zeroCrossings << endl;
	zeroCrossings = 0;
	
}




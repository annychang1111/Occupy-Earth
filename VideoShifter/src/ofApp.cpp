#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	serial.setup(0, 9600);

	player.load("noise.mp3");

	vid.load("DMZ.mp4");
	vid.play();

	vidShift.allocate(640, 480, OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void ofApp::update() {

	while (serial.available()) {
		char b = serial.readByte();
		if (b == '\n') {
			distance = ofToInt(buffer);
			//warn = ofToInt(buffer);
			buffer = "";
		}
		else {
			buffer += b;
		}
	}

	if (distance <= 3000 && distance >= 0) {
		distanceMapX = ofMap(distance, 0, 3000, ofGetWidth(), 0);
		distanceMapY = ofMap(distance, 0, 3000, ofGetHeight(), 0);
		warn = 1;
	}
	else {
		warn = 0;
	}

	float time = ofGetElapsedTimef();

	vid.update();

	if (vid.isFrameNew())
	{

		float noiseX = ofMap(distanceMapX, 0, ofGetWidth(), 0, 200);
		float noiseY = ofMap(distanceMapY, 0, ofGetHeight(), 0, 200);

		for (int y = 0; y<vid.getHeight(); y++) {
			for (int x = 0; x<vid.getWidth(); x++) {

				int xOffset = ofNoise(y * .005, time) * noiseX;
				int yOffset = ofNoise(x * .005, time) * noiseY;

				int newX = (x + xOffset) % int(vid.getWidth());
				int newY = (y + yOffset) % int(vid.getHeight());

				ofColor color = vid.getPixels().getColor(x, y);
				vidShift.setColor(newX, newY, color);

			}
		}

		vidShift.update();
	}



}

//--------------------------------------------------------------
void ofApp::draw() {
	if (player.isLoaded() == true) {
		if (warn == 1) {
			player.play();
			vidShift.draw(0, 0, ofGetWidth(), ofGetHeight());
		}
		if (warn == 0) {
			player.stop();
			vid.draw(0, 0, ofGetWidth(), ofGetHeight());
		}
		cout << distance << "\n";
		cout << warn << "\n";
	}
	preWarn == warn;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

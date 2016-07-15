#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxTextSuite.h"

#define MODE_GRID	1
#define MODE_PIXEL	2


#define FONT_SIZE	40


class ofApp : public ofBaseApp{
public:
	
	ofxDatGui *gui;
	
	float lineWidth = 6;
	int column = 8;
	int row = 8;
	
	int mode = MODE_GRID;
	
	ofShader pixelShader;
	
	ofColor backColor = ofColor(0);
	ofColor foreColor = ofColor(255);
	ofColor	highColor = ofColor(255, 0, 0);
	
	stringstream	ss;
	ofxTextBlock	text;
	
	
	//--------------------------------------------------
	
	void setup() {
		pixelShader.load("", "pixel.frag");
		
		gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
		gui->addSlider("LINE WIDTH", 1, 16)->bind(lineWidth);
		gui->setVisible(false);
		
		text.init("lucida-console.ttf", FONT_SIZE);
		text.setLineHeight(FONT_SIZE);
	};
	
	void update() {
	};
	
	void draw() {
		
		ofBackground(backColor);
		
		
		
		float w = ofGetWindowWidth();
		float h = ofGetWindowHeight();
		
		// grid
		if (mode == MODE_GRID) {
			float stepw = w / (float)column;
			float steph = h / (float)row;
			
			ofNoFill();
			ofSetLineWidth(lineWidth);
			for (int i = 0; i <= column; i++) {
				float p = i * stepw;
				if (i == 0) p += lineWidth / 2;
				if (i == column) p -= lineWidth / 2;
				if (i == 0 || i == column) {
					ofSetColor(highColor);
				} else {
					ofSetColor(foreColor);
				}
				ofDrawLine(p, 0, p, h);
			}
			for (int i = 0; i <= row; i++) {
				float p = i * steph;
				if (i == 0) p += lineWidth / 2;
				if (i == row) p -= lineWidth / 2;
				if (i == 0 || i == row) {
					ofSetColor(highColor);
				} else {
					ofSetColor(foreColor);
				}
				ofDrawLine(0, p, w, p);
			}
			
			ofSetColor(highColor);
			ofDrawLine(w / 2, 0, w / 2, h);
			ofDrawLine(0, h / 2, w, h / 2);
		
		} else if (mode == MODE_PIXEL) {
			
			pixelShader.begin();
			pixelShader.setUniform3f("color1", backColor.r / 255.0f, backColor.g / 255.0f, backColor.b / 255.0f);
			pixelShader.setUniform3f("color2", foreColor.r / 255.0f, foreColor.g / 255.0f, foreColor.b / 255.0f);
			ofDrawRectangle(0, 0, w, h);
			pixelShader.end();
		}
		
		ofFill();
		ss.str("");
		ss << w << "x" << h;
		text.setText(ss.str());
		text.setColor(highColor.r, highColor.g, highColor.b, 255);
		text.drawLeft(50, 50);
		
		
		
	};

	void keyPressed(int key) {
		
		switch (key) {
			case OF_KEY_RIGHT:
				column++;
				break;
			case OF_KEY_LEFT:
				column = max(column - 1, 1);
				break;
			case OF_KEY_DOWN:
				row++;
				break;
			case OF_KEY_UP:
				row = max(row - 1, 1);
				break;
				
			case 'f':
				ofToggleFullscreen();
				gui->setVisible(false);
				break;
				
			case 'h':
				gui->setVisible(!gui->getVisible());
				break;
				
			// mode
			case '1':
				mode = MODE_GRID;
				break;
			case '2':
				mode = MODE_PIXEL;
				break;
		}
	};
	
	
	
//	void keyReleased(int key);
//	void mouseMoved(int x, int y );
//	void mouseDragged(int x, int y, int button);
//	void mousePressed(int x, int y, int button);
//	void mouseReleased(int x, int y, int button);
//	void mouseEntered(int x, int y);
//	void mouseExited(int x, int y);
//	void windowResized(int w, int h);
//	void dragEvent(ofDragInfo dragInfo);
//	void gotMessage(ofMessage msg);
	
};

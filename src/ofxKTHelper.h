#pragma once

#include "ofMain.h"
#include "ofxKTScroller.h"
#include "ofxKTFlipper.h"

class ofxKTHelper {
    
public:
    
    void setup(string fontPath);
    
    float getStringWidth(string text, float height);
    
    vector<ofPath> getStringOutlineInBox(string text, ofRectangle boundingBox, Boolean bKeepAspectRatio);
    void drawStringOutlineInBox(string text, ofRectangle boundingBox, Boolean bKeepAspectRatio);
    
    void createScroller(string name, string text, glm::vec2 textDimensions, glm::vec2 scrollVelocity, int xCount, int yCount, Boolean bKeepAspectRatio);
    void updateScrollers();
    void drawScrollers();
    
    void createFlipper(string name, string currentText, string nextText, glm::vec2 textDimensions, glm::vec2 textPosition, Boolean bKeepAspectRatio);
    void updateFlippers();
    void drawFlippers();
    void flipFlipper(string name, string nextText, FlipDirection flipDirection);
    bool isFlipping(string name);

    ofTrueTypeFont font;
    map<string, ofxKTScroller> scrollers;
    map<string, ofxKTFlipper> flippers;
    
};

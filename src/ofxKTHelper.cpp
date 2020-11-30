#include "ofxKTHelper.h"

void ofxKTHelper::setup(string fontPath) {
    font.load(fontPath, 300, true, true, true, 0.1, 300);
    font.setLetterSpacing(1);
}

float ofxKTHelper::getStringWidth(string text, float height) {
    ofRectangle bb = font.getStringBoundingBox(text, 0, 0);
    return bb.getWidth() * height / bb.getHeight();
}

vector<ofPath> ofxKTHelper::getStringOutlineInBox(string text, ofRectangle boundingBox, Boolean bKeepAspectRatio) {
    
    // get paths with baseline at (0, 0)
    vector<ofPath> paths = font.getStringAsPoints(text, false, false);
    
    // get the original bounding box
    ofRectangle originalBoundingBox = font.getStringBoundingBox(text, 0, 0);
    
    // get the offsets to center the original bounding box
    float xCenter = -originalBoundingBox.x - originalBoundingBox.getWidth() / 2;
    float yCenter = -originalBoundingBox.y - originalBoundingBox.getHeight() / 2;
    
    // get the offsets to move to the target bounding box
    float xTarget = boundingBox.x + 0.5 * boundingBox.getWidth();
    float yTarget = boundingBox.y + 0.5 * boundingBox.getHeight();
    
    // get the scaling factors
    float xScale = boundingBox.getWidth() / originalBoundingBox.getWidth();
    float yScale = boundingBox.getHeight() / originalBoundingBox.getHeight();
    if (bKeepAspectRatio) {
        ofRectangle boundingBoxScaled = originalBoundingBox;
        boundingBoxScaled.scaleTo(boundingBox, OF_ASPECT_RATIO_KEEP);
        xScale = boundingBoxScaled.getWidth() / originalBoundingBox.getWidth();
        yScale = boundingBoxScaled.getHeight() / originalBoundingBox.getHeight();
    }
    
    for (int i = 0; i < paths.size(); i++) {
        
        // apply the centering offsets
        paths[i].translate(glm::vec3(xCenter, yCenter, 0));
        
        // apply scaling factors
        paths[i].scale(xScale, yScale);
        
        // translate to target bounding box
        paths[i].translate(glm::vec3(xTarget, yTarget, 0));
        
    }
    
    return paths;
    
}

void ofxKTHelper::drawStringOutlineInBox(string text, ofRectangle boundingBox, Boolean bKeepAspectRatio) {
    
    // get the original bounding box
    ofRectangle originalBoundingBox = font.getStringBoundingBox(text, 0, 0);
    
    // get the offsets to center the original bounding box
    float xCenter = -originalBoundingBox.x - originalBoundingBox.getWidth() / 2;
    float yCenter = -originalBoundingBox.y - originalBoundingBox.getHeight() / 2;
    
    // get the offsets to move to the target bounding box
    float xTarget = boundingBox.x + 0.5 * boundingBox.getWidth();
    float yTarget = boundingBox.y + 0.5 * boundingBox.getHeight();
    
    // get the scaling factors
    float xScale = boundingBox.getWidth() / originalBoundingBox.getWidth();
    float yScale = boundingBox.getHeight() / originalBoundingBox.getHeight();
    if (bKeepAspectRatio) {
        ofRectangle boundingBoxScaled = originalBoundingBox;
        boundingBoxScaled.scaleTo(boundingBox, OF_ASPECT_RATIO_KEEP);
        xScale = boundingBoxScaled.getWidth() / originalBoundingBox.getWidth();
        yScale = boundingBoxScaled.getHeight() / originalBoundingBox.getHeight();
    }
    
    ofPushMatrix();
        ofTranslate(xTarget, yTarget);
        ofScale(xScale, yScale);
        ofTranslate(xCenter, yCenter);
        font.drawStringAsShapes(text, 0, 0);
    ofPopMatrix();
    
}

void ofxKTHelper::createScroller(string name, string text, glm::vec2 textDimensions, glm::vec2 scrollVelocity, int xCount, int yCount, Boolean bKeepAspectRatio) {
    
    ofxKTScroller scroller;
    scroller.font = &font;
    scroller.text = text;
    scroller.textDimensions = textDimensions;
    scroller.scrollVelocity = scrollVelocity;
    scroller.xCount = xCount;
    scroller.yCount = yCount;
    scroller.bKeepAspectRatio = bKeepAspectRatio;
    
    scroller.setup();
    
    scrollers.insert(pair<string, ofxKTScroller>(name, scroller));
    
}

//void ofxKTHelper::createScroller(string name, string text, float scale, glm::vec2 scrollVelocity) {
//    
//    ofxKTScroller scroller;
//    scroller.font = &font;
//    scroller.text = text;
//    scroller.textDimensions = textDimensions;
//    scroller.scrollVelocity = scrollVelocity;
//    scroller.xCount = 1;
//    scroller.yCount = yCount;
//    scroller.bKeepAspectRatio = bKeepAspectRatio;
//    
//    scroller.setup();
//    
//    scrollers.insert(pair<string, ofxKTScroller>(name, scroller));
//    
//}

void ofxKTHelper::updateScrollers() {
    
    map<string, ofxKTScroller>::iterator itr;
    for (itr = scrollers.begin(); itr != scrollers.end(); ++itr) {
        itr->second.update();
    }
    
}

void ofxKTHelper::drawScrollers() {
    
    map<string, ofxKTScroller>::iterator itr;
    for (itr = scrollers.begin(); itr != scrollers.end(); ++itr) {
        itr->second.fbo.draw(0, 0);
    }
    
}

void ofxKTHelper::createFlipper(string name, string currentText, string nextText, glm::vec2 textDimensions, glm::vec2 textPosition, Boolean bKeepAspectRatio) {
    
    ofxKTFlipper flipper;
    flipper.font = &font;
    flipper.currentText = currentText;
    flipper.textDimensions = textDimensions;
    flipper.textPosition = textPosition;
    flipper.flipSpeed = 0.05;
    flipper.bKeepAspectRatio = bKeepAspectRatio;
    
    flipper.setup();
    
    flippers.insert(pair<string, ofxKTFlipper>(name, flipper));
    
}

//void ofxKTHelper::createScroller(string name, string text, float scale, glm::vec2 scrollVelocity) {
//
//    ofxKTScroller scroller;
//    scroller.font = &font;
//    scroller.text = text;
//    scroller.textDimensions = textDimensions;
//    scroller.scrollVelocity = scrollVelocity;
//    scroller.xCount = 1;
//    scroller.yCount = yCount;
//    scroller.bKeepAspectRatio = bKeepAspectRatio;
//
//    scroller.setup();
//
//    scrollers.insert(pair<string, ofxKTScroller>(name, scroller));
//
//}

void ofxKTHelper::updateFlippers() {
    map<string, ofxKTFlipper>::iterator itr;
    for (itr = flippers.begin(); itr != flippers.end(); ++itr) {
        itr->second.update();
    }
}

void ofxKTHelper::drawFlippers() {
    map<string, ofxKTFlipper>::iterator itr;
    for (itr = flippers.begin(); itr != flippers.end(); ++itr) {
        itr->second.fbo.draw(itr->second.textPosition);
    }
}

void ofxKTHelper::flipFlipper(string name, string nextText, FlipDirection flipDirection) {
    std::map<string, ofxKTFlipper>::iterator it = flippers.find(name);
    if (it != flippers.end()) {
        it->second.isFlipping = true;
        it->second.flipDirection = flipDirection;
        it->second.nextText = nextText;
    }
}

bool ofxKTHelper::isFlipping(string name) {
    std::map<string, ofxKTFlipper>::iterator it = flippers.find(name);
    if (it != flippers.end()) {
        return it->second.isFlipping;
    } else {
        return false;
    }
}

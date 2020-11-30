#include "ofxKTFlipper.h"

void ofxKTFlipper::setup() {
    
    ofRectangle originalBoundingBox = font->getStringBoundingBox(currentText, 0, 0);
    
    center.x = -originalBoundingBox.getX() - originalBoundingBox.getWidth() / 2;
    center.y = -originalBoundingBox.getY() - originalBoundingBox.getHeight() / 2;
    
    scale.x = textDimensions.x / originalBoundingBox.getWidth();
    scale.y = textDimensions.y / originalBoundingBox.getHeight();
    if (bKeepAspectRatio) {
        ofRectangle boundingBoxScaled = originalBoundingBox;
        boundingBoxScaled.scaleTo(ofRectangle(0, 0, textDimensions.x, textDimensions.y), OF_ASPECT_RATIO_KEEP);
        scale.x = boundingBoxScaled.getWidth() / originalBoundingBox.getWidth();
        scale.y = boundingBoxScaled.getHeight() / originalBoundingBox.getHeight();
    }
    
    current = glm::vec2(0, 0);
    
    fbo.allocate(textDimensions.x, textDimensions.y, GL_RGBA, 4);
    fbo.begin();
        ofClear(0);
        ofPushMatrix();
            ofTranslate(current);
            ofTranslate(textDimensions.x / 2, textDimensions.y / 2);
            ofScale(scale.x, scale.y);
            font->drawStringAsShapes(currentText, center.x, center.y);
        ofPopMatrix();
    fbo.end();
    
    flipPercent = 0;
    isFlipping = false;
    
}

void ofxKTFlipper::update() {
    
    if (isFlipping) {
        
//        flipPercent += flipSpeed;
        flipPercent = 0.9 * flipPercent + 0.105;
        flipPercent = MIN(flipPercent, 1);
        
        fbo.begin();
            ofClear(0);
            ofSetColor(255);
            switch (flipDirection) {
                case FlipDirection::UP:
                    drawStringOutlineInBox(currentText, ofRectangle(0, 0, textDimensions.x, (1 - flipPercent) * textDimensions.y), false);
                    drawStringOutlineInBox(nextText, ofRectangle(0, (1 - flipPercent) * textDimensions.y, textDimensions.x, flipPercent * textDimensions.y), false);
                    break;
                case FlipDirection::DOWN:
                    drawStringOutlineInBox(currentText, ofRectangle(0, flipPercent * textDimensions.y, textDimensions.x, (1 - flipPercent) * textDimensions.y), false);
                    drawStringOutlineInBox(nextText, ofRectangle(0, 0, textDimensions.x, flipPercent * textDimensions.y), false);
                    break;
                case FlipDirection::LEFT:
                    drawStringOutlineInBox(currentText, ofRectangle(0, 0, (1 - flipPercent) * textDimensions.x, textDimensions.y), false);
                    drawStringOutlineInBox(nextText, ofRectangle((1 - flipPercent) * textDimensions.x, 0, flipPercent * textDimensions.x, textDimensions.y), false);
                    break;
                case FlipDirection::RIGHT:
                    drawStringOutlineInBox(currentText, ofRectangle(flipPercent * textDimensions.x, 0, (1 - flipPercent) * textDimensions.x, textDimensions.y), false);
                    drawStringOutlineInBox(nextText, ofRectangle(0, 0, flipPercent * textDimensions.x, textDimensions.y), false);
                    break;
            }
        fbo.end();
        
        if (flipPercent >= 0.999) {
            isFlipping = false;
            flipPercent = 0;
            currentText = nextText;
        }
        
    }
    
    
//    current.x = fmod(current.x + scrollVelocity.x + fbo.getWidth() + textDimensions.x, fbo.getWidth() +  textDimensions.x);
//    current.y = fmod(current.y + scrollVelocity.y + fbo.getHeight() + textDimensions.y, fbo.getHeight() +  textDimensions.y);
//
//    fbo.begin();
//    ofClear(0);
//    ofSetColor(255);
//    for (float i = 0; i < fbo.getWidth() + textDimensions.x; i += textDimensions.x) {
//        for (float j = 0; j < fbo.getHeight() + textDimensions.y; j += textDimensions.y) {
//            float xActual = fmod(current.x + i, fbo.getWidth() + textDimensions.x) - textDimensions.x;
//            float yActual = fmod(current.y + j, fbo.getHeight() + textDimensions.y) - textDimensions.y;
//            ofPushMatrix();
//            ofTranslate(textDimensions.x / 2, textDimensions.y / 2);
//            ofTranslate(xActual, yActual);
//            ofScale(scale.x, scale.y);
//            font->drawStringAsShapes(text, center.x, center.y);
//            ofPopMatrix();
//        }
//    }
//    fbo.end();
    
}

void ofxKTFlipper::drawStringOutlineInBox(string text, ofRectangle boundingBox, Boolean bKeepAspectRatio) {
    
    // get the original bounding box
    ofRectangle originalBoundingBox = font->getStringBoundingBox(text, 0, 0);
    
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
        font->drawStringAsShapes(text, 0, 0);
    ofPopMatrix();
    
}

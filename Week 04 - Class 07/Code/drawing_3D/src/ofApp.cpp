#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	
	ofSetFrameRate(60.f);
	ofBackground(255);
	
	bMakingRibbon = false;	// will be true when we are drawing
	
	zSpeed = 2.f;  // normal "drift" speed
	
	ofSetLineWidth(5.);
	
}

//--------------------------------------------------------------
void ofApp::update()
{
	// add z-axis "drift"

	for (int i=0; i<ribbons.size(); i++)
	{
		for (int j=0; j<ribbons[i].size(); j++)
		{
			// for every pt in every polyline...

			ribbons[i][j].z -= zSpeed; // push z back
		}
	}
	
	// make sure we delete old ribbons
	
	while (ribbons.size() > 20)
	{
		ribbons.erase(ribbons.begin());	// remove oldest ribbon
	}

}

//--------------------------------------------------------------
void ofApp::draw()
{
	// draw the ribbons
	
	for (int i=0; i<ribbons.size(); i++)
	{
		
		ofColor color = ofColor::fromHsb( 0,255,200 ); 	// we'll create a base color and just change the hue

		for (int j=1; j<ribbons[i].size(); j++)
		{
			// draw ribbon segments in rainbow hues
			
			color.setHue( ofMap(j, 0, ribbons[i].size(), 0, 255) );
			ofSetColor(color);
			
            glm::vec3 pt1 = ribbons[i][j-1];
            glm::vec3 pt2 = ribbons[i][j];
			
			ofDrawLine( pt1, pt2 ); // draw line from prev pt to current pt
		}
	}

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	
    glm::vec3 mouse = glm::vec3( x,y,0 );
    glm::vec3 prevMouse = glm::vec3( ofGetPreviousMouseX(), ofGetPreviousMouseY(), 0 );
	
	if (!bMakingRibbon)
	{
		ribbons.push_back(ofPolyline());    // start a new ribbon
		bMakingRibbon = true;
	}
	
	ribbons.back().addVertex(mouse);
    zSpeed = glm::distance(mouse, prevMouse);
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
	bMakingRibbon = false;
    zSpeed = 2.0;
}






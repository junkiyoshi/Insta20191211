#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh_list.clear();
	this->frame_list.clear();

	for (int x = 120; x < ofGetWidth(); x += 240) {

		for (int y = 120; y < ofGetHeight(); y += 240) {

			ofMesh mesh, frame;
			frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
			for (int radius = 30; radius <= 100; radius += 10) {

				for (int deg = 0; deg < 360; deg += 1) {

					auto location = glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0);
					auto param = int(ofGetFrameNum() + location.x + x + y) % 450;
					auto angle = 0.f;
					if (param > 225) {

						angle = ofMap(param, 225, 450, 0, PI * 6);
					}
					auto rotation = glm::rotate(glm::mat4(), angle, glm::vec3(1, 0, 0));
					location = glm::vec3(x, y, 0) + glm::vec4(location, 0) * rotation;

					if (radius == 30 || radius == 100) {

						frame.addVertex(location);
					}

					mesh.addVertex(location);
				}
			}

			for (int base = 0; base < mesh.getNumVertices() - 360; base += 360) {

				for (int i = base; i < base + 360; i += 1) {

					mesh.addIndex(i); mesh.addIndex(i + 360); mesh.addIndex((i + 1) % 360 + base + 360);
					mesh.addIndex(i); mesh.addIndex((i + 1) % 360 + base); mesh.addIndex((i + 1) % 360 + base + 360);
				}
			}

			for (int i = 0; i < 360; i++) {

				frame.addIndex(i); frame.addIndex((i + 1) % 360);
				frame.addIndex(i + 360); frame.addIndex((i + 1) % 360 + 360);
			}

			this->mesh_list.push_back(mesh);
			this->frame_list.push_back(frame);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSetColor(39);
	for(auto& mesh : this->mesh_list){

		mesh.draw();
	}

	ofSetColor(239);
	for (auto& frame : this->frame_list) {

		frame.drawWireframe();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}

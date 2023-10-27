#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	float x_span = 1;
	auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));

	for (int x_param = -1; x_param <= 1; x_param += 2) {

		int start_index = this->face.getNumVertices();
		for (float x = 150;  x < 300; x += x_span) {

			float next_x = x + x_span;
			int index = this->face.getNumVertices();

			float angle_x = (ofGetFrameNum() + x) * 2;
			auto rotation_x = glm::rotate(glm::mat4(), angle_x * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));

			float angle_y = (ofGetFrameNum() + x) * 5;
			auto rotation_y = glm::rotate(glm::mat4(), angle_y * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));

			float next_angle_x = (ofGetFrameNum() + x + 1) * 2;
			auto next_rotation_x = glm::rotate(glm::mat4(), next_angle_x * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));

			float next_angle_y = (ofGetFrameNum() + x + 1) * 5;
			auto next_rotation_y = glm::rotate(glm::mat4(), next_angle_y * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec4(x * x_param, 20, 0, 0) * rotation_y * rotation_x);
			vertices.push_back(glm::vec4(next_x * x_param, 20, 0, 0)* next_rotation_y* next_rotation_x);
			vertices.push_back(glm::vec4(next_x * x_param, -20, 0, 0) * next_rotation_y * next_rotation_x);
			vertices.push_back(glm::vec4(x * x_param, -20, 0, 0) * rotation_y * rotation_x);

			this->face.addVertices(vertices);
			this->frame.addVertices(vertices);

			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
			this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

			this->frame.addIndex(index + 0); this->frame.addIndex(index + 1);
			this->frame.addIndex(index + 2); this->frame.addIndex(index + 3);
		}

		this->frame.addIndex(start_index + 0); this->frame.addIndex(start_index + 3);
		this->frame.addIndex(this->frame.getNumVertices() - 2); this->frame.addIndex(this->frame.getNumVertices() - 3);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 2.44);

	ofSetColor(39);
	this->face.draw();

	ofSetColor(239, 0, 0);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
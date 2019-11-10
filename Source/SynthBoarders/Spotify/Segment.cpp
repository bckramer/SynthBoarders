#include <stdio.h>
#include <iostream>

using namespace std;

class Segment {
private:
	float start;
	float duration;
	float confidence;
	float loudnessStart;
	float loudnessMaxTime;
	float loudnessMax;
	float* pitches;
	float* timbre;
	string json;

public:
	Segment(float start, float duration, float confidence, float loudnessStart,
	 float loudnessMaxTime, float loudnessMax, float* pitches, float* timbre, string json) {
		this->start = start;
		this->duration = duration;
		this->confidence = confidence;
		this->loudnessStart = loudnessStart;
		this->loudnessMaxTime = loudnessMaxTime;
		this->loudnessMax = loudnessMax;
		this->pitches = pitches;
		this->timbre = timbre;
		this->json = json;
	}
	float getStart();
	float getDuration();
	float getConfidence();
	float getLoudnessStart();
	float getLoudnessMaxTime();
	float getLoudnessMax();
	float* getPitches();
	float* getTimbre();
	string getJson();

};

float Segment::getStart() {
	return start;
}

float Segment::getDuration() {
	return duration;
}

float Segment::getConfidence() {
	return confidence;
}

float Segment::getLoudnessStart() {
	return loudnessStart;
}

float Segment::getLoudnessMaxTime() {
	return loudnessMaxTime;
}

float Segment::getLoudnessMax() {
	return loudnessMax;
}

float* Segment::getPitches() {
	return pitches;
}

float* Segment::getTimbre() {
	return timbre;
}

string Segment::getJson() {
	return json;
}

#include <stdio.h>
#include <iostream>

using namespace std;

class Section {
private:
	float start;
	float duration;
	float confidence;
	float loudness;
	float tempo;
	float tempoConfidence;
	int key;
	float keyConfidence;
	int mode;
	float modeConfidence;
	int timeSignature;
	float timeSignatureConfidence;
	string json;

public:
	Section(float start, float duration, float confidence, float loudness, float tempo, float tempoConfidence,
		int key, float keyConfidence, int mode, float modeConfidence, int timeSignature,
		float timeSignatureConfidence, string json) {
		this->start = start;
		this->duration = duration;
		this->confidence = confidence;
		this->loudness = loudness;
		this->tempo = tempo;
		this->tempoConfidence = tempoConfidence;
		this->key = key;
		this->keyConfidence = keyConfidence;
		this->mode = mode;
		this->modeConfidence = modeConfidence;
		this->timeSignature = timeSignature;
		this->timeSignatureConfidence = timeSignatureConfidence;
		this->json = json;
	}

	float getStart();
	float getDuration();
	float getConfidence();
	float getLoudness();
	float getTempo();
	float getTempoConfidence();
	int getKey();
	float getKeyConfidence();
	int getMode();
	float getModeConfidence();
	int getTimeSignature();
	float getTimeSignatureConfidence();
	string getJson();
};

float Section::getStart() {
	return start;
}

float Section::getDuration() {
	return duration;
}

float Section::getConfidence() {
	return confidence;
}

float Section::getLoudness() {
	return loudness;
}

float Section::getTempo() {
	return tempo;
}

float Section::getTempoConfidence() {
	return tempoConfidence;
}

int Section::getKey() {
	return key;
}

float Section::getKeyConfidence() {
	return keyConfidence;
}

int Section::getMode() {
	return mode;
}

float Section::getModeConfidence() {
	return modeConfidence;
}

int Section::getTimeSignature() {
	return timeSignature;
}

float Section::getTimeSignatureConfidence() {
	return timeSignatureConfidence;
}

string Section::getJson() {
	return json;
}

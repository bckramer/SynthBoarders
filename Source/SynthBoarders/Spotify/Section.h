#ifndef SECTION_H
#define SECTION_H

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

#endif

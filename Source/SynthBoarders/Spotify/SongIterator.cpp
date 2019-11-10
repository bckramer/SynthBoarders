#include <stdio.h>
#include <iostream>
#include "CurrentlyPlayedTrack.h"
#include "SpotifyVisualizerClient.h"
#include "CurrentlyPlayedTrack.h"
#include <chrono>

class SongIterator {
private:
  CurrentlyPlayedTrack* track;
  long start;
  int currentSection;
  int currentSegment;


public:

  long getTime();

  SongIterator(CurrentlyPlayedTrack* song) {
    this->track = song;
    this->start = getTime();
  }

  void seek();

  Section* getCurrentSection();

  Segment* getCurrentSegment();

  int progress();

};


long SongIterator::getTime() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void SongIterator::seek() {
  int* output = new int[2];
  output[0] = -1;
  output[1] = -1;
  int currentProgress = track->getProgress();
  vector<Section*> sections = track->getSections();
  vector<Segment*> segments = track->getSegments();
  for (int i = 0; i < sections.size(); i++) {
    Section* curSection = sections.at(i);
    float target = (float) currentProgress / 1000.0f;
    float sectionTime = curSection->getStart();
    float sectionDuration = curSection->getDuration();
    if (target >= sectionTime && target <= sectionTime + sectionDuration) {
      currentSection = i;
      break;
    }
  }
  for (int i = 0; i < segments.size(); i++) {
    Segment* curSegment = segments.at(i);
    float target = (float) currentProgress / 1000.0f;
    float segmentTime = curSegment->getStart();
    float segmentDuration = curSegment->getDuration();
    if (target >= segmentTime && target <= segmentTime + segmentDuration) {
      currentSegment = i;
      break;
    }
  }
}

int SongIterator::progress() {
  int currentProgress = (float) track->getProgress() / 1000.0f + (float) (getTime() - start) / 1000.0f;
  vector<Section*> sections = track->getSections();
  vector<Segment*> segments = track->getSegments();
  int output = 0;
  if (currentSection < sections.size() - 1) {
    for (int i = currentSection; i < sections.size(); i++) {
      Section* curSection = sections.at(i);
      float sectionTime = curSection->getStart();
      float sectionDuration = curSection->getDuration();
      if ((currentProgress >= sectionTime && currentProgress <= sectionTime + sectionDuration) && i > currentSection) {
        currentSection = i;
        output++;
        break;
      }
    }
  }
  if (currentSegment < segments.size() - 1) {
    for (int i = currentSegment; i < segments.size(); i++) {
      Segment* curSegment = segments.at(i);
      float segmentTime = curSegment->getStart();
      float segmentDuration = curSegment->getDuration();
      if ((currentProgress >= segmentTime && currentProgress <= segmentTime + segmentDuration) && i > currentSegment) {
        currentSegment = i;
        output++;
        break;
      }
    }
  }
  return output;
}

Section* SongIterator::getCurrentSection() {
  return track->getSections().at(currentSection);
}

Segment* SongIterator::getCurrentSegment() {
  return track->getSegments().at(currentSegment);
}

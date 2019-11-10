#ifndef SONG_ITERATOR_H
#define SONG_ITERATOR_H

#include <stdio.h>
#include <iostream>
#include "CurrentlyPlayedTrack.h"
#include "SpotifyVisualizerClient.h"
#include "CurrentlyPlayedTrack.h"

class SongIterator {
private:
  CurrentlyPlayedTrack* track;
  long start;
  int currentSection;
  int currentSegment;


public:
  SongIterator(CurrentlyPlayedTrack* song) {
    this->track = song;
    this->start = getTime();
  }

  long getTime();

  void seek();

  Section* getCurrentSection();

  Segment* getCurrentSegment();

  int progress();

};

#endif

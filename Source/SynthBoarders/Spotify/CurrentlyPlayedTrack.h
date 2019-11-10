#ifndef CURRENTLY_PLAYED_TRACK_H
#define CURRENTLY_PLAYED_TRACK_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Section.h"
#include "Segment.h"

using namespace std;

class CurrentlyPlayedTrack {
private:
  int duration;
  int progress;
  string trackId;
  string artistName;
  string albumName;
  string trackName;
  vector<Section*> sections;
  vector<Segment*> segments;

public:
  CurrentlyPlayedTrack(int duration, int progress, string trackId, string artistName,
    string albumName, string trackName, vector<Section*> sections, vector<Segment*> segments) {

    this->duration = duration;
    this->progress = progress;
    this->trackId = trackId;
    this->artistName = artistName;
    this->albumName = albumName;
    this->trackName = trackName;
    this->sections = sections;
    this->segments = segments;
  }

  int getDuration();

  int getProgress();

  int getTrackDurationMinutes();

  int getTrackDurationSeconds();

  int getTrackProgressMinutes();

  int getTrackProgressSeconds();

  string getTrackId();

  string getArtistName();

  string getAlbumName();

  string getTrackName();

  vector<Segment*> getSegments();

  vector<Section*> getSections();
};

#endif

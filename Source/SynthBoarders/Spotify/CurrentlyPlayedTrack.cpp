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

int CurrentlyPlayedTrack::getDuration() {
  return duration;
}

int CurrentlyPlayedTrack::getProgress() {
  return progress;
}

int CurrentlyPlayedTrack::getTrackDurationMinutes() {
  return ((duration / 1000) / 60) % 60;
}

int CurrentlyPlayedTrack::getTrackDurationSeconds() {
  return ((duration / 1000) - getTrackDurationMinutes() * 60);
}

int CurrentlyPlayedTrack::getTrackProgressMinutes() {
  return ((progress / 1000) / 60) % 60;
}

int CurrentlyPlayedTrack::getTrackProgressSeconds() {
  return ((progress / 1000) - getTrackProgressMinutes() * 60);
}

string CurrentlyPlayedTrack::getTrackId() {
  return trackId;
}

string CurrentlyPlayedTrack::getArtistName() {
  return artistName;
}

string CurrentlyPlayedTrack::getAlbumName() {
  return albumName;
}

string CurrentlyPlayedTrack::getTrackName() {
  return trackName;
}


vector<Segment*> CurrentlyPlayedTrack::getSegments() {
  return segments;
}

vector<Section*> CurrentlyPlayedTrack::getSections() {
  return sections;
}

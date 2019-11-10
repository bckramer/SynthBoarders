#include <stdio.h>
#include <iostream>
#include "CurrentlyPlayedTrack.h"
#include "SpotifyVisualizerClient.h"
#include "SongIterator.h"

using namespace std;

int main() {
  CurrentlyPlayedTrack* currentTrack = getCurrentTrackDetails();
  cout << "\n\nTrack ID:\t\t" << currentTrack->getTrackId() << endl;
  cout << "Track Name:\t\t" << currentTrack->getTrackName() << endl;
  cout << "Artist Name:\t\t" << currentTrack->getArtistName() << endl;
  cout << "Album Name:\t\t" << currentTrack->getAlbumName() << endl;
  cout << "Track Duration:\t\t" << currentTrack->getTrackDurationMinutes() <<
  " minutes and " << currentTrack->getTrackDurationSeconds() << " seconds" << endl;
  cout << "Current Track Progress:\t" << currentTrack->getTrackProgressMinutes() <<
  " minutes and " << currentTrack->getTrackProgressSeconds() << " seconds " << endl;

  SongIterator* si = new SongIterator(currentTrack);
  si->seek();

  while (1) {
    int change = si->progress();
    if (change) {
      cout << si->getCurrentSegment()->getJson() << endl;
    }
  }

}

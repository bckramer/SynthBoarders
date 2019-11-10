#ifndef SPOTIFY_VISUALIZER_CLIENT
#define SPOTIFY_VISUALIZER_CLIENT

#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include <vector>

CurrentlyPlayedTrack* getCurrentTrackDetails();
std::vector<Section*> getSection(string songId);
std::vector<Segment> getSegment(string songId);
Json::Value httpGet(string uri);

#endif

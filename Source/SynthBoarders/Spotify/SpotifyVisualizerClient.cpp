#include <stdio.h>
#include <iostream>
#include <cstdint>
#include <memory>
#include <string>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include "CurrentlyPlayedTrack.h"
#include <vector>

Json::Value httpGet(string);

namespace
{
    std::size_t callback(
            const char* in,
            std::size_t size,
            std::size_t num,
            std::string* out)
    {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }
}

std::vector<Section*> getSection(string songId) {
  string uri = "http://localhost:8889/getSectionData?songid=";
  uri.append(songId);
  Json::Value jsonData = httpGet(uri);
  std::vector<Section*> sections;
  for (int i = 0; i < jsonData.size(); i++) {
    for (int j = 0; j < jsonData[i].size();  i++) {
      Json::Value obj = jsonData[i];
      float start = std::stof(obj["start"].asString());
      float duration = std::stof(obj["duration"].asString());
      float confidence = std::stof(obj["confidence"].asString());
      float loudness = std::stof(obj["loudness"].asString());
      float tempo = std::stof(obj["tempo"].asString());
      float tempoConfidence = std::stof(obj["tempoConfidence"].asString());
      int key = std::stoi(obj["key"].asString());
      float keyConfidence = std::stof(obj["keyConfidence"].asString());
      int mode = std::stoi(obj["mode"].asString());
      float modeConfidence = std::stof(obj["modeConfidence"].asString());
      int timeSignature = std::stoi(obj["timeSignature"].asString());
      float timeSignatureConfidence = std::stof(obj["timeSignatureConfidence"].asString());
      Section* section = new Section(start, duration, confidence, loudness, tempo,
         tempoConfidence, key, keyConfidence, mode, modeConfidence, timeSignature,
          timeSignatureConfidence, jsonData[i].toStyledString());
      sections.push_back(section);
    }
  }
  return sections;
}

std::vector<Segment*> getSegment(string songId) {
  string uri = "http://localhost:8889/getSegmentData?songid=";
  uri.append(songId);
  Json::Value jsonData = httpGet(uri);
  std::vector<Segment*> segments;
  for (int i = 0; i < jsonData.size(); i++) {
    for (int j = 0; j < jsonData[i].size();  i++) {
      Json::Value obj = jsonData[i];
      float start = std::stof(obj["start"].asString());
      float duration = std::stof(obj["duration"].asString());
      float confidence = std::stof(obj["confidence"].asString());
      float loudnessStart = std::stof(obj["loudnessStart"].asString());
      float loudnessMaxTime = std::stof(obj["loudnessMaxTime"].asString());
      float loudnessMax = std::stof(obj["loudnessMax"].asString());
      Json::Value pitchJson = obj["pitches"];
      Json::Value timbreJson = obj["timbre"];
      int pitchSize = pitchJson.size();
      int timbreSize = timbreJson.size();
      float* pitches = new float[pitchSize];
      float* timbre = new float[timbreSize];
      for (int k = 0; k < pitchSize; k++) {
        pitches[k] = std::stof(pitchJson[k].asString());
      }
      for (int k = 0; k < timbreSize; k++) {
        timbre[k] = std::stof(timbreJson[k].asString());
      }
      Segment* segment = new Segment(start, duration, confidence, loudnessStart,
         loudnessMaxTime, loudnessMax, pitches, timbre, jsonData[i].toStyledString());
      segments.push_back(segment);
    }
  }
  return segments;
}

CurrentlyPlayedTrack* getCurrentTrackDetails() {
  string uri = "http://localhost:8889/getCurrentlyPlayedSongInformation";
  Json::Value jsonData = httpGet(uri)[0];
  int duration = std::stoi(jsonData["duration"].asString());
  int progress = std::stoi(jsonData["progress"].asString());
  string trackId = jsonData["track_id"].asString();
  string artistName = jsonData["artist_name"].asString();
  string albumName = jsonData["album_name"].asString();
  string trackName = jsonData["track_name"].asString();
  std::vector<Section*> sections = getSection(trackId);
  std::vector<Segment*> segments = getSegment(trackId);
  return new CurrentlyPlayedTrack(duration, progress, trackId, artistName,
     albumName, trackName, sections, segments);
}

Json::Value httpGet(string uri) {
  const std::string url(uri);

  CURL* curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  long httpCode(0);
  std::unique_ptr<std::string> httpData(new std::string());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
  curl_easy_perform(curl);
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
  curl_easy_cleanup(curl);
  Json::Value jsonData;
  if (httpCode == 200) {
      std::cout << "\nGot successful response from " << url << std::endl;
      Json::Reader jsonReader;

      if (jsonReader.parse(*httpData.get(), jsonData)) {
          std::cout << "Parsed HTTP Request as JSON" << std::endl;
      }
      else {
          std::cout << "Could not parse HTTP data as JSON" << std::endl;
          std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
      }
  }
  else {
      std::cout << "Couldn't GET from " << url << " - exiting" << std::endl;
  }

  return jsonData;
}

#pragma once

#include "SFML/Audio.hpp"

class SoundFileCache
{
public:
  SoundFileCache(void);
  ~SoundFileCache(void);

  sf::Sound GetSound(std::string) const;
  sf::Music* GetSong(std::string) const;

private:
  static std::map<std::string, sf::SoundBuffer*> _sounds;
  static std::map<std::string, sf::Music*> _music;

  /*struct SoundFileDeallocator
    {
      void operator()(const std::pair<std::string,sf::SoundBuffer*> & p) 
      {
        delete p.second;
      }
    };
  
  struct MusicFileDeallocator
    {
      void operator()(const std::pair<std::string,sf::Music*> & p) 
      {
        delete p.second;
      }
    };*/
  
  template <typename T>
    struct Deallocator{
      void operator()(const std::pair<std::string,T> &p) 
      {
        delete p.second;
      }
  };
};


class SoundNotFoundExeception : public std::runtime_error
{
  public:
        SoundNotFoundExeception(std::string const& msg):
            std::runtime_error(msg)
        {}
};
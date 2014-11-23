#include "stdafx.h"
#include "SFMLSoundProvider.h"
#include "SoundFileCache.h"

SFMLSoundProvider::SFMLSoundProvider() :
currentSongName("")
{
}

void SFMLSoundProvider::PlaySound(std::string filename) 
{
	int availChannel = -1;
	for(int i = 0; i < MAX_SOUND_CHANNELS;i++)
	{
		if(currentSounds[i].getStatus() != sf::Sound::Playing)
		{
			availChannel = i;
			break;
		}
	}
	
	// If all sound channels are in use, do nothing for now
	if(availChannel != -1)
	{
		try
		{
			currentSounds[availChannel] = soundFileCache.GetSound(filename);
			currentSounds[availChannel].play();
		}
		catch(SoundNotFoundExeception& snfe)
		{
			// ERROR, file wasnt found, should handle error here
			// snfe.what will contain the exception details
		}
	}
	
	
}
	
void SFMLSoundProvider::PlaySong(std::string filename, bool looping)
{
	sf::Music * currentSong;
	try
	{
		currentSong = soundFileCache.GetSong(filename);
	}
	catch(SoundNotFoundExeception&)
	{
		// This one is dire, means we couldn't find or load the selected song
		// So, lets exit!
		return;
	}
	// See if prior song is playing still, if so, stop it
	if(currentSongName != "")
	{
		try
		{
			sf::Music* priorSong = soundFileCache.GetSong(currentSongName);
			if(priorSong->getStatus() != sf::Sound::Stopped)
			{
				priorSong->stop();
			}
		}
		catch(SoundNotFoundExeception&)
		{
			// Do nothing, this exception isn't dire.  It simply means the previous sound we were
			// trying to stop wasn't located.
		}
		
	}
	currentSongName = filename;
	currentSong->setLoop(looping);
	currentSong->play();
}

void SFMLSoundProvider::StopAllSounds() 
{
	for(int i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		currentSounds[i].stop();
	}
	
	if(currentSongName != "")
	{
		sf::Music * currentSong = soundFileCache.GetSong(currentSongName);
		if(currentSong->getStatus() == sf::Sound::Playing)
		{
			currentSong->stop(); 
		}
	}
}
	
bool SFMLSoundProvider::IsSoundPlaying()
{
	for(int i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		if(currentSounds[i].getStatus() == sf::Sound::Playing)
			return true;
	}
	return false;
}


bool SFMLSoundProvider::IsSongPlaying()
{
	if(currentSongName != "")
	{
		return soundFileCache.GetSong(currentSongName)->getStatus() == sf::Music::Playing;	
	}
	return false;
}
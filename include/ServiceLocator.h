#pragma once

#include "stdafx.h"
#include "IAudioProvider.h"

class ServiceLocator
{
public:
  static IAudioProvider* GetAudio()  { return audioProvider; } const

  static void RegisterServiceLocator(IAudioProvider *provider)
  {
    audioProvider = provider;
  }

private:
  static IAudioProvider * audioProvider;
};
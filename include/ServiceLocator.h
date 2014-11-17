#pragma once

#include "stdafx.h"
#include "IAudioProvider.h"

class ServiceLocator
{
public:
  static IAudioProvider* GetAudio()  { return _audioProvider; } const

  static void RegisterServiceLocator(IAudioProvider *provider)
  {
    _audioProvider = provider;
  }

private:
  static IAudioProvider * _audioProvider;
};
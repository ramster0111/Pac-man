


#ifndef AUDIO_H
#define AUDIO_H

#include "config.h"

class audio
{
      public:
             audio();
             ~audio();
             
             void loadWavSoundData();
             void playSound(int id);
             void setSoundVolume(int id, int volume);
      private:
             Mix_Chunk *wavSounds[AUDIO_SOUND_COUNT];
};

#endif

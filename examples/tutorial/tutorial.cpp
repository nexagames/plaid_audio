#include <iostream>
#include <plaid/audio.h>
#include <plaid/audio/synth.h>

using namespace plaid;

int main(int argc, char **argv)
{
    //Create an audio engine with default settings.
    Audio audio;

    //Create a sine wave Oscillator and store it in a Ref.
    Ref<Oscillator> oscillator = new Oscillator(audio.format(), 440.0f, Oscillator::SINE, .05f);

    //Play the oscillator
    audio.play(oscillator);

    while (true)
    {
        //Update the audio system so that changes to our audio are applied.
        //Ideally this should happen regularly, for example every frame of a game.
        audio.update();

        //Prompt the user for a new frequency, and quit on invalid input.
        int freq = 0;
        std::cout << "Enter new frequency:" << std::endl;
        std::cin >> freq;
        if (freq == 0) break;
        oscillator->frequency(freq);
    }
}
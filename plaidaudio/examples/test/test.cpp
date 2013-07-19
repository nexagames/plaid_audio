#include <ctime>
#include <iostream>
#include <string>

#include <Windows.h>
#undef min
#undef max

#include <plaid/audio.h>
#include <plaid/audio/effects.h>
#include <plaid/audio/synth.h>


using namespace std;
using namespace plaid;



int main(int argc, char *argv)
{
	Audio *audio = new Audio();

	//Sound sine = audio->stream(L"C:\\Creations\\Plaidgadget\\dev\\game\\audio\\sine.ogg", true);

	Sound sine(new Oscillator(audio->format(), 220.0f, Oscillator::SINE, .05f));
	Ref<Pitch> pitch(new Pitch(sine));
	audio->play(pitch);

	float note = 0.0f;

	std::cout << "Sweep" << std::endl;
	for (int i = 0; i < 512; ++i)
	{
		audio->update();
		Sleep(10);

		if (i & 128) note -= .2f;
		else note += .2f;

		pitch->note(note);
	}

	std::cout << "Chord" << std::endl;
	for (int i = 0; i < 1024; ++i)
	{
		audio->update();
		Sleep(10);

		if (i & 16) note = 0.0f;
		else if (i & 32) note = ((i&512) ? 5.0f : 4.0f);
		else note = ((i&256) ? 9.0f : 7.0f);

		pitch->note(note);
	}

	std::cout << "Arpeggio" << std::endl;
	for (int i = 0; i < 1024; ++i)
	{
		audio->update();
		Sleep(10);

		if (i & 4) note = 0.0f;
		else if (i & 8) note = ((i>512) ? 5.0f : 4.0f);
		else note = ((i>768) ? 11.0f : ((i>256) ? 9.0f : 7.0f));

		pitch->note(note);
	}

	Sound sine2(new Oscillator(audio->format(), 880.0f, Oscillator::SINE, .03f));
	Ref<Pitch> pitch2(new Pitch(sine2));
	audio->play(pitch2);
	float note2 = 0.0f;

	std::cout << "Dual Arpeggio" << std::endl;
	for (int i = 0; i < 1024; ++i)
	{
		audio->update();
		Sleep(10);

		if (i & 4) note = 0.0f;
		else if (i & 8) note = ((i>512) ? 5.0f : 4.0f);
		else note = ((i>768) ? 11.0f : ((i>256) ? 9.0f : 7.0f));

		if ((i&255)%48 >= 32) note2 = 0.0f;
		else if ((i&255)%48 >= 16) note2 = ((i&512) ? 5.0f : 4.0f);
		else note2 = ((i&256) ? 9.0f : 7.0f);

		pitch->note(note);
		pitch2->note(note2);
	}

	Ref<Pitch> sPitch(new Pitch(Sound(new Oscillator(audio->format(), 440.0f, Oscillator::SINE, .1f))));
	Ref<Amp> sAmp(new Amp(Sound(sPitch)));
	audio->play(sAmp);

	std::cout << "Melody" << std::endl;
	for (int t = 0; t < 2; ++t) for (int i = 0; i < 1024; ++i)
	{
		audio->update();
		Sleep(10);

		if (i & 4) note = 0.0f;
		else if (i & 8) note = ((i>512) ? 5.0f : 4.0f);
		else note = ((i>768) ? 11.0f : ((i>256) ? 9.0f : 7.0f));

		if ((i&255)%48 >= 32) note2 = 0.0f;
		else if ((i&255)%48 >= 16) note2 = ((i&512) ? 5.0f : 4.0f);
		else note2 = ((i&256) ? 9.0f : 7.0f);

		switch (i / 256)
		{
		case 0: sPitch->note(9.0f); sAmp->decibels((-(i&255))/20.0f); break;
		case 1: sPitch->note(0.0f); sAmp->decibels((-(i&255))/20.0f); break;
		case 2: sPitch->note(5.0f); sAmp->decibels((-(i&255))/20.0f); break;
		case 3: sPitch->note((i&128) ? 2.0f : 4.0f); sAmp->decibels((-(i&127))/20.0f); break;
		}

		pitch->note(note);
		pitch2->note(note2);
	}

	audio->stop(pitch);
	audio->stop(pitch2);

	std::cout << "Finale" << std::endl;
	for (int i = 0; i < 1024; ++i)
	{
		audio->update();
		Sleep(10);

		sPitch->note(0.0f);
		sAmp->decibels(-i/20.0f);
	}

	delete audio;
}

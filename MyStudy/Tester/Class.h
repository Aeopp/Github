#pragma once

#include <iostream>

#include <fmod.h>
#include <fmod.hpp>
#include <fmod_dsp.h>


class Class
{
public : 
	void Header_Only()
	{
		FMOD::Channel* qwe;
		FMOD::Sound* abc;
		std::cout << __FUNCTION__ << std::endl;
	}
	void FooFoo();
	
};



/*
	File: RFXFile.h
	Author: Abramov Nickolai
	Desc: Simple container for render monkey rfx file
*/

#ifndef _H_RFX_FILE
#define _H_RFX_FILE

#include <cstring>

class RFXPass
{
public:
	char* vertexShader;
	char* fragmentShader;
	RFXPass() : vertexShader(0), fragmentShader(0) {};
};

class RFXEffect
{
public:
	char* name;
	RFXPass* pass;
	int passCount;
	void AddPass()
	{
		if (passCount == 0)
		{
			passCount++;
			pass = new RFXPass[passCount];
			return;
		}
		RFXPass* old = new RFXPass[passCount];
		memcpy(old, pass, sizeof(RFXPass)*passCount);
		delete[] pass;
		pass = new RFXPass[passCount+1];
		memcpy(pass, old, sizeof(RFXPass)*passCount);
		delete[] old;
		passCount++;
	}
	RFXPass& GetLastPass()
	{
		return pass[passCount-1];
	}
	RFXEffect() : name(""), pass(0), passCount(0) {}
};

class RFXFile
{
public:
	RFXEffect* effect;
	int effectsCount;
	void AddEffect(const char* name)
	{
		if (effectsCount == 0)
		{
			effectsCount++;
			effect = new RFXEffect[effectsCount];
		}
		else
		{
			RFXEffect* old = new RFXEffect[effectsCount];
			memcpy(old, effect, sizeof(RFXEffect)*effectsCount);
			delete[] effect;
			effect = new RFXEffect[effectsCount+1];
			memcpy(effect, old, sizeof(RFXEffect)*effectsCount);
			delete[] old;
			effectsCount++;
		}
		char** p = &(effect[effectsCount-1].name);
		*p = new char(strlen(name)+1);
		memcpy(*p, name, strlen(name));
		(*p)[strlen(name)] = 0;
	}
	RFXEffect& GetLastEffect()
	{
		return effect[effectsCount-1];
	}
	~RFXFile()
	{
		for (int i = 0; i < effectsCount; i++)
		{
			for (int j = 0; j < effect[i].passCount; j++)
			{
				delete[] effect[i].pass[j].vertexShader;
				delete[] effect[i].pass[j].fragmentShader;
			}
			delete[] effect[i].name;
			delete[] effect[i].pass;
		}
		delete[] effect;
	}
	RFXFile() : effect(0), effectsCount(0) {}
};
#endif
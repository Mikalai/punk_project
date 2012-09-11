/*
	File: ShaderProgram.h
	Author: Abramau Mikalai
	Description: common interface for GLSL and Cg program
*/

#ifndef _SHADER_PROGRAM_H
#define _SHADER_PROGRAM_H

#include "../string/string.h"

const int UNIFORM_WORLD = 0;
const int UNIFORM_VIEW  = 1;
const int UNIFORM_PROJ = 2;
const int UNIFORM_PROJVIEWWORLD = 3;
const int UNIFORM_DIFFUSE_COLOR = 4;
const int UNIFORM_RADIUS = 5;
const int UNIFORM_DIFFUSE_MAP = 6;

class ShaderProgram
{
public:
	virtual int  GetLocation(int uniform) = 0;
	virtual void Bind(int passNumber = 0) = 0;
	virtual void Unbind() = 0;
	virtual void CreateFromFile(const System::string& vertexProgramFileName, const System::string& fragmentProgramFileName, const System::string& geometryProgramFileName) = 0;
	virtual void CreateFromMemory(const System::Buffer& vertexProgram, const System::Buffer& fragmentProgram, const System::Buffer& geometryProgramFileName) = 0;
	virtual void CreateFromRFX(const System::string& fileName, const System::string& effectGroup, const System::string& effectName) = 0;
	virtual void Clear() = 0;
	virtual int GetPassCount() const = 0;
	virtual bool SetUniformVector4f( const char * name, const float* value) = 0;
	virtual bool SetUniformVector4f( int loc, const float* value) = 0;
	virtual bool SetUniformVector3f( const char * name, const float* value) = 0;
	virtual bool SetUniformVector3f( int loc, const float* value) = 0;
	virtual bool SetUniformVector2f( const char * name, const float* value) = 0;
	virtual bool SetUniformVector2f( int loc, const float* value) = 0;
	virtual bool SetUniformFloat( const char * name, float value) = 0;
	virtual bool SetUniformFloat( int loc, float value) = 0;
	virtual bool SetUniformMatrix4f( const char * name, const float* value) = 0;
	virtual bool SetUniformMatrix4f( int loc, const float* value) = 0;
	virtual bool SetUniformArrayMatrix4f(int loc, int count, const float* value) = 0;
	virtual bool SetUniformMatrix3f( const char * name, const float*  value) = 0;
	virtual bool SetUniformMatrix3f( int loc, const float*  value) = 0;
	virtual bool SetUniformInt( const char * name, int value) = 0;
	virtual bool SetUniformInt( int loc, int value) = 0;
	virtual bool SetTexture( const char * name, int texUnit) = 0;
	virtual bool SetTexture( int loc, int texUnit) = 0;
	virtual int GetUniformLocation( const char * name) = 0;
	virtual int GetAttribLocation(const char* attrib) = 0;
};

#endif
// Mega

#pragma once

#ifndef JSON_SCENE_H
#define JSON_SCENE_H

#include <string>
#include <vector>

#include <rapidjson\document.h>

class Camera;
class Document;
class PipelineState;
class Renderable;
class RenderTarget;
class Value;

using rapidjson::Document;
using rapidjson::Value;
using std::string;
using std::vector;

class JsonScene
{
public:		
	explicit JsonScene( string filename );	// Constructor
	~JsonScene();							// ~Destructor
		
	vector<Camera *>		ParseCameras		() const;	// Parse and return cameras from .json file
	vector<PipelineState *>	ParsePipelineStates	() const;	// Parse and return pipeline states from .json file
	vector<Renderable *>	ParseRenderables	() const;	// Parse and return renderables from .json file

private:	
	Camera				*ParseCamera		( const Value &v ) const;	// Parse and return camera from value object
	PipelineState		*ParsePipelineState	( const Value &v ) const;	// Parse and return pipeline state from value object
	RenderTarget		*ParseRenderTarget	( const Value &v ) const;	// Parse and return render target from value object
	Renderable			*ParseRenderable	( const Value &v ) const;	// Parse and return renderable from value object
	Renderable			*ParseRenderable	( const Value &v, const string &pipelineState, const string &camera, const string &shape, int layer ) const;	// Parse and return renderable from value object
	
	void ParseIncludes( const string &s );	// parse includes

	vector<const Value * const> FindValues(const string &s) const;	// find vector of value from all open documents
	
private:	
	vector<const Document * const> mDocuments;	// open documents
};	

#endif 
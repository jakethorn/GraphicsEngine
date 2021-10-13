// Mega

#pragma once

#ifndef GAME_MASTER_H
#define GAME_MASTER_H

#include <string>
#include <vector>

class Camera;
class PipelineState;
class Renderable;

using std::string;
using std::vector;

namespace gm
{
	namespace camera
	{
		void Set( const vector<Camera *> &c );

		void Move( string camName, float x, float y, float z );
		void Turn( string camName, float x, float y );
		void Update();
	}

	namespace pps
	{
		void Set( const vector<PipelineState *> &nPpsDescs );

		void AttachAll();
		void ClearAll();
		void SetActive( const PipelineState * const pps );
	}

	namespace renderable
	{
		void Set( const vector<Renderable *> &rndrs );

		void SetCameraAll( Camera * const c );
		void SetCameraAll();

		void SetPpsAll( const vector<PipelineState *> &pps );
		void SetPpsAll();

		void OrderAll();
		void RenderAll();

		vector<Renderable *> &Get();
	}

	void Unin();
}

#endif
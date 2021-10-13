// Mega

#pragma once

#ifndef RENDERER_H
#define RENDERER_H

// includes

#include <d3d11.h>
#include <d3dx11.h>
#include <vector>

// using

using std::vector;

// functions 

namespace renderer
{
	void Init();
	void Update( float dt );
	void Render();
	void Unin();

	void OnMouseDown( WPARAM btnState, int x, int y );
	void OnMouseUp( WPARAM btnState, int x, int y );
	void OnMouseMove( WPARAM btnState, int x, int y );
	void OnKeyDown( WPARAM key );
	void OnKeyUp( WPARAM key );
}

#endif
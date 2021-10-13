// Mega

#ifndef SHADOW_TEX_DATA
#define SHADOW_TEX_DATA

#include "WorldViewProjData.h"

class ShadowTexData : public WorldViewProjData
{
public:
	explicit ShadowTexData( const IConstantVariableData &worldData, Camera *camera );
	
	void* operator()() const;
};

#endif /* SHADOW_TEX_DATA */
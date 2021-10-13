// Mega

#ifndef SKY_BOX_WVP_DATA_H
#define SKY_BOX_WVP_DATA_H

#include "WorldViewProjData.h"

class SkyBoxWVPData : public WorldViewProjData
{
public:
	explicit SkyBoxWVPData( const IConstantVariableData &worldData, Camera *camera );

	void *operator()() const;
};

#endif /* SKY_BOX_WVP_DATA_H */
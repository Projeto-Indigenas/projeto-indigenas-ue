#pragma once

#include "UnrealEd.h"

class PROJETOINDIGENASEDITOR_API FProjetoIndigenasEditor : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
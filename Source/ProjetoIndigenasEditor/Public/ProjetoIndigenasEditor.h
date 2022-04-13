#pragma once

#include "Debug/PICustomEditor.h"

class PROJETOINDIGENASEDITOR_API FProjetoIndigenasEditor : public IModuleInterface
{
	TArray<TSharedPtr<FPICustomEditor>> _customEditors;

	void RegisterCustomEditors();
	
public:
	virtual void StartupModule() override;

	FPICustomEditor* GetCustomEditor(UClass* cls) const;
};

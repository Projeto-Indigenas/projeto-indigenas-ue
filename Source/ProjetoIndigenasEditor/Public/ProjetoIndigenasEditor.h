#pragma once

#include "Debug/PICustomEditor.h"

class PROJETOINDIGENASEDITOR_API FProjetoIndigenasEditor : public IModuleInterface
{
	TMap<UClass*, TSharedPtr<FPICustomEditor>> _customEditorsMap;

	void RegisterCustomEditors();
	
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	template<typename TEditor>
	TEditor* GetCustomEditor(UClass* cls)
	{
		const TSharedPtr<FPICustomEditor>* customEditorPtr = _customEditorsMap.Find(cls);
		if (customEditorPtr == nullptr) return nullptr;
		return static_cast<TEditor*>(customEditorPtr->Get());
	}
};

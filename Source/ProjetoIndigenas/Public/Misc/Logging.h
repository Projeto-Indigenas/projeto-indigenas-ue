#pragma once

#if !UE_BUILD_SHIPPING

#define PI_SCREEN_LOG(key, duration, format, ...) \
	{ \
		const FString& message = FString::Printf(format, ##__VA_ARGS__); \
		GEngine->AddOnScreenDebugMessage(key, duration, FColor::Red, message); \
	}

#define PI_SCREEN_LOGV(variable, duration, format, ...) \
	if (variable->GetBool()) \
	PI_SCREEN_LOG(GetLogKey(), duration, format, ##__VA_ARGS__)

#define PI_LOGV(verbosity, message) \
	UE_LOG(LogTemp, verbosity, TEXT("[%s::%s] - %s"), typeid(decltype(*this)).name(), *FString(__FUNCTION__), message)
#define PI_LOGV_UOBJECT(verbosity, message) \
	UE_LOG(LogTemp, verbosity, TEXT("[%s::%s] - %s"), *StaticClass()->GetName(), *FString(__FUNCTION__), message)

#define PI_LOGVF(verbosity, format, ...) PI_LOGV(verbosity, *FString::Printf(format, ##__VA_ARGS__))
#define PI_LOGVF_UOBJECT(verbosity, format, ...) PI_LOGV_UOBJECT(verbosity, *FString::Printf(format, ##__VA_ARGS__))

#define PI_LOG(message) PI_LOGV(Log, message)
#define PI_LOG_UOBJECT(message) PI_LOGV_UOBJECT(Log, message)

#define PI_LOGF(format, ...) PI_LOGVF(Log, format, ##__VA_ARGS__)
#define PI_LOGF_UOBJECT(format, ...) PI_LOGVF_UOBJECT(Log, format, ##__VA_ARGS__)

#else

#define PI_LOGV(verbosity, message)
#define PI_LOGV_UOBJECT(verbosity, message)

#define PI_LOGVF(verbosity, format, ...)
#define PI_LOGVF_UOBJECT(verbosity, format, ...)

#define PI_LOG(message)
#define PI_LOG_UOBJECT(message)

#define PI_LOGF(format, ...)
#define PI_LOGF_UOBJECT(format, ...)

#endif

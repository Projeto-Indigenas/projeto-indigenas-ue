#pragma once

#if !UE_BUILD_SHIPPING

#define PI_SCREEN_LOG(variable, duration, format, ...) \
	if (variable->GetBool()) \
	{ \
		const FString& message = FString::Printf(format, ##__VA_ARGS__); \
		GEngine->AddOnScreenDebugMessage(GetLogKey(), duration, FColor::Red, message); \
	}

#define PI_LOG_V_FMT(verbosity, format, ...) \
const FString& message = FString::Printf(format, ##__VA_ARGS__); \
PI_LOG_V_MSG(verbosity, *message)

#define PI_LOG_V_MSG(verbosity, message) \
UE_LOG(LogTemp, verbosity, TEXT("[%s::%s] - %s"), *StaticClass()->GetName(), __func__, message);

#define PI_LOG_FMT(format, ...) \
PI_LOG_V_FMT(Log, format, ##__VA_ARGS__)

#define PI_LOG_MSG(message) \
PI_LOG_V_MSG(Log, message)

#else

#define PI_LOG_V_FMT(verbosity, format, ...)
#define PI_LOG_V_MSG(message)
#define PI_LOG_FMT(format, ...)
#define PI_LOG_MSG(message)

#endif

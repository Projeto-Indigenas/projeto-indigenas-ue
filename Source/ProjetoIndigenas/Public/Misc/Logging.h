#pragma once

#if !UE_BUILD_SHIPPING

#define PI_SCREEN_LOG(variable, duration, format, ...) \
	if (variable->GetBool()) \
	{ \
		const FString& message = FString::Printf(format, ##__VA_ARGS__); \
		GEngine->AddOnScreenDebugMessage(GetLogKey(), duration, FColor::Red, message); \
	}

#define PI_LOG_FMT(format, ...) \
	const FString& message = FString::Printf(format, ##__VA_ARGS__); \
	PI_LOG_MSG(*message)

#define PI_LOG_MSG(message) \
	UE_LOG(LogTemp, Verbose, TEXT("[%s::%s] - %s"), *StaticClass()->GetName(), __func__, message);

#else

#define PI_LOG_FMT(format, ...)
#define PI_LOG_MSG(message)

#endif

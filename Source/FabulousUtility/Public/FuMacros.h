﻿#pragma once

#include "HAL/Platform.h"

#define FU_STRINGIFY_IMPLEMENTATION(Value) #Value

#define FU_STRINGIFY(Value) FU_STRINGIFY_IMPLEMENTATION(Value)

#define FU_GET_TYPE_STRING(Type) \
	((void) sizeof UEAsserts_Private::GetMemberNameCheckedJunk(static_cast<Type*>(nullptr)), TEXTVIEW(#Type))

#define FU_GET_ENUM_VALUE_STRING(Enum, EnumValue) \
	((void) sizeof UEAsserts_Private::GetMemberNameCheckedJunk(Enum::EnumValue), TEXTVIEW(#EnumValue))

// A lightweight version of the ensure() macro that doesn't generate a C++ call stack and doesn't send a
// crash report, because it doesn't happen instantly and causes the editor to freeze, which can be annoying.

#if DO_ENSURE && !USING_CODE_ANALYSIS

#define FU_ENSURE_IMPLEMENTATION(Expression, bEnsureAlways, Format, Capture, ...) \
	(LIKELY(Expression) || ([Capture](const auto& FinalFormat) UE_DEBUG_SECTION \
	{ \
		static auto bExecuted{false}; \
		\
		if ((bEnsureAlways || !bExecuted) && FPlatformMisc::IsEnsureAllowed()) \
		{ \
			bExecuted = true; \
			\
			UE_LOG(LogOutputDevice, Warning, TEXT("Ensure failed: ") TEXT(#Expression) TEXT(", File: ") __FILE__ TEXT(", Line: ") TEXT(FU_STRINGIFY(__LINE__)) TEXT(".")); \
			UE_LOG(LogOutputDevice, Warning, FinalFormat, ##__VA_ARGS__); \
			\
			PrintScriptCallstack(); \
			\
			if (FPlatformMisc::IsDebuggerPresent()) \
			{ \
				PLATFORM_BREAK_IF_DESIRED(); \
			} \
			else \
			{ \
				FPlatformMisc::PromptForRemoteDebugging(true); \
			} \
		} \
	}(Format), false))

#define FU_ENSURE(Expression) FU_ENSURE_IMPLEMENTATION(Expression, false, TEXT(""), )
#define FU_ENSURE_MESSAGE(Expression, Format, ...) FU_ENSURE_IMPLEMENTATION(Expression, false, Format, &, ##__VA_ARGS__)
#define FU_ENSURE_ALWAYS(Expression) FU_ENSURE_IMPLEMENTATION(Expression, true, TEXT(""), )
#define FU_ENSURE_ALWAYS_MESSAGE(Expression, Format, ...) FU_ENSURE_IMPLEMENTATION(Expression, true, Format, &, ##__VA_ARGS__)

#else

#define FU_ENSURE(Expression) (Expression)
#define FU_ENSURE_MESSAGE(Expression, Format, ...) (Expression)
#define FU_ENSURE_ALWAYS(Expression) (Expression)
#define FU_ENSURE_ALWAYS_MESSAGE(Expression, Format, ...) (Expression)

#endif

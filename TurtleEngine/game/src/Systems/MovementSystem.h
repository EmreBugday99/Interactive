#pragma once
#include <speechapi_cxx.h>

class MovementSystem
{
public:
	static std::shared_ptr<Microsoft::CognitiveServices::Speech::SpeechConfig> speechConfig;
	static std::shared_ptr<Microsoft::CognitiveServices::Speech::Audio::AudioConfig> audioConfig;
	static std::shared_ptr<Microsoft::CognitiveServices::Speech::SpeechRecognizer> recognizer;
	static std::future<std::shared_ptr<Microsoft::CognitiveServices::Speech::SpeechRecognitionResult>> resultFuture;

	static void Initialize();
	static void MovementUpdate(float deltaTime);
};

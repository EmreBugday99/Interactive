#include "MovementSystem.h"
#include "Engine.h"
#include "components/TransformComponent.hpp"
#include "ObstacleSystem.h"
#include "debugging/Logger.h"
#include "../Components/MovementComponent.hpp"
#include "../SecretKey.hpp"

std::shared_ptr<Microsoft::CognitiveServices::Speech::SpeechConfig> MovementSystem::speechConfig;
std::shared_ptr<Microsoft::CognitiveServices::Speech::Audio::AudioConfig> MovementSystem::audioConfig;
std::shared_ptr<Microsoft::CognitiveServices::Speech::SpeechRecognizer> MovementSystem::recognizer;
std::future<std::shared_ptr<Microsoft::CognitiveServices::Speech::SpeechRecognitionResult>> MovementSystem::resultFuture;

void MovementSystem::Initialize()
{
	speechConfig = Microsoft::CognitiveServices::Speech::SpeechConfig::FromSubscription(SubscriptionKey, ServiceRegion);
	speechConfig->SetSpeechRecognitionLanguage("en-US");
	audioConfig = Microsoft::CognitiveServices::Speech::Audio::AudioConfig::FromDefaultMicrophoneInput();
	recognizer = Microsoft::CognitiveServices::Speech::SpeechRecognizer::FromConfig(speechConfig, audioConfig);
}

void MovementSystem::MovementUpdate(float deltaTime)
{
	using namespace Microsoft::CognitiveServices::Speech;
	using namespace Microsoft::CognitiveServices::Speech::Audio;

	if (resultFuture.valid() == false)
	{
		resultFuture = recognizer->RecognizeOnceAsync();
		TurtleCore::Logger::LogWarning("Please provide voice command.");
	}

	std::chrono::milliseconds futureSpan(100);
	while (resultFuture.wait_for(futureSpan) == std::future_status::timeout)
	{
		return;
	}
	if (resultFuture.valid() == false)
		return;

	const std::shared_ptr<SpeechRecognitionResult> result = resultFuture.get();

	if (result->Reason != ResultReason::RecognizedSpeech)
	{
		TurtleCore::Logger::LogWarning("No Input.");
		return;
	}

	const auto view = TurtleCore::Engine::GetWorld().Registry.view<TurtleCore::TransformComponent, MovementComponent>();
	for (const entt::entity entity : view)
	{
		TurtleCore::TransformComponent& transform = view.get<TurtleCore::TransformComponent>(entity);

		if (result->Text == "Move up.")
		{
			transform.Position.y += 0.1f;
			TurtleCore::Logger::LogWarning("Recognized Command: ", result->Text);
			ObstacleSystem::MoveObstacles();
		}
		if (result->Text == "Move down.")
		{
			transform.Position.y -= 0.1f;
			TurtleCore::Logger::LogWarning("Recognized Command: ", result->Text);
			ObstacleSystem::MoveObstacles();
		}
		if (result->Text == "Move left.")
		{
			transform.Position.x -= 0.1f;
			TurtleCore::Logger::LogWarning("Recognized Command: ", result->Text);
			ObstacleSystem::MoveObstacles();
		}
		if (result->Text == "Move right.")
		{
			transform.Position.x += 0.1f;
			TurtleCore::Logger::LogWarning("Recognized Command: ", result->Text);
			ObstacleSystem::MoveObstacles();
		}
		if (result->Text == "Stay put.")
		{
			TurtleCore::Logger::LogWarning("Recognized Command: ", result->Text);
			ObstacleSystem::MoveObstacles();
		}
	}
}
#pragma once
class Interactive;

class ScriptEngine
{
private:
	Interactive* Engine;

public:
	ScriptEngine(Interactive* engine);
	/// <summary>
	/// Constructs LuaComponents from .lua script files.
	/// </summary>
	void StartScriptEngine();
};

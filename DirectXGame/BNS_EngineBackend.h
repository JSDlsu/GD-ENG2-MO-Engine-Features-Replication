#pragma once
class BNS_EngineBackend
{
public:
	static BNS_EngineBackend* getInstance();
	static void initialize();
	static void destroy();

	enum EditorMode
	{
		EDITOR = 0,
		PLAY = 1,
		PAUSED = 2
	};

	void setMode(EditorMode mode);
	void startFrameStep();
	void endFrameStep();
	bool insideFrameStep();
	EditorMode getMode();

private:
	BNS_EngineBackend();
	~BNS_EngineBackend();
	BNS_EngineBackend(BNS_EngineBackend const&) {};
	BNS_EngineBackend& operator=(BNS_EngineBackend const&) {};

	static BNS_EngineBackend* sharedInstance;

	EditorMode editorMode = EditorMode::EDITOR;

	bool frameStepping = false;
};


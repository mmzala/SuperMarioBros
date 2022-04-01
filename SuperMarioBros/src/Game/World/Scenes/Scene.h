#pragma once

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Load();
	virtual void UnLoad();
	virtual void Update(const float deltaTime);

protected:
	/// <summary>
	/// Each scene in SMB has the main UI that shows the score, time etc.
	/// </summary>
	virtual void CreateUI();
};


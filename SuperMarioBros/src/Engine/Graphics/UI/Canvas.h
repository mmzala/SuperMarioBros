#pragma once

#include <vector>

class UIElement;
class Camera;

/// <summary>
/// Canvas manages UI elements.
/// </summary>
class Canvas
{
public:
	Canvas();
	virtual ~Canvas();

	virtual void Update();

	/// <summary>
	/// When you pass an element here, you don't need to delete it yourself. 
	/// When the canvas gets deleted, it also deletes all of its elements.
	/// </summary>
	/// <param name="element">: Element to add </param>
	void AddElement(UIElement* element);

private:
	Camera* camera;
	std::vector<UIElement*> elements;
};


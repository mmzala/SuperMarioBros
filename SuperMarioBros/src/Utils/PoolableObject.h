#pragma once

class PoolableObject
{
public:
	virtual void SetInUse(bool value)
	{
		inUse = value;
	}

	[[nodiscard]] bool isInUse()
	{
		return inUse;
	}

private:
	bool inUse = false;
};


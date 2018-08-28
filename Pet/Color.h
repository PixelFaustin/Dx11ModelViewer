#pragma once

struct Color
{
	Color(float R, float G, float B, float A)
	{
		Data[0] = R;
		Data[1] = G;
		Data[2] = B;
		Data[3] = A;
	}

	inline const float* GetRGBA() const
	{
		return Data;
	}

	inline float R() const
	{
		return Data[0];
	}

	inline float G() const
	{
		return Data[1];
	}

	inline float B() const
	{
		return Data[2];
	}

	inline float A() const
	{
		return Data[3];
	}
private:
	float Data[4];
};
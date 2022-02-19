#include "BeatmapElements.h"
#include "SDL.h"
BeatmapElements BeatmapElements::sInstance;

const TimingPoint& BeatmapElements::GetTimingPoint(int32_t time)
{
/*
	uint32_t i;
	for (i=0; i<mTimingPoints.size(); ++i)
	{
		if (mTimingPoints[i].Time > time)
			break;
	}
	return mTimingPoints[MathHelper::Max(i-1, 0)];
*/
	uint32_t i;
	for (
		i = mTimingPoints.size() - 1;
		i > 0 && mTimingPoints[i].Time > time;
		--i
	);
	return mTimingPoints[i];
}

const TimingPoint& BeatmapElements::GetTimingPoint()
{
	return GetTimingPoint(GameClock::Clock().Time());
}

const bool BeatmapElements::IsBreak()
{
	for (uint32_t i=0; i<mBreakPoints.size(); ++i)
	{
		if (GameClock::Clock().Time() > mBreakPoints[i].StartTime && GameClock::Clock().Time() < mBreakPoints[i].EndTime)
			return true;
	}
	return false;
}

SDL_Color BeatmapElements::GetNextColour()
{
	//backwards compatibility - increase counter BEFORE returning
	if (++mCurrentColour >= mColours.size())
		mCurrentColour = 0;
	
	return mColours[mCurrentColour];
}

void BeatmapElements::AddTimingPoint(int32_t time, float beattime, uint8_t samplesetid)
{
	TimingPoint tPoint = {
		time,
		beattime,
		samplesetid
	};
	
	mTimingPoints.push_back(tPoint);
}

void BeatmapElements::AddBreakPoint(int32_t start, int32_t end)
{
	BreakPoint bPoint = {
		start,
		end
	};
	
	mBreakPoints.push_back(bPoint);
}

void BeatmapElements::ResetColours(bool fill)
{
	mCurrentColour = 0;

    if (!fill) {
        mColours.clear();
    }

    if (mColours.empty() && fill) {
        mColours.push_back(SDL_Color({229, 198, 255}));
        mColours.push_back(SDL_Color({176, 225, 255}));
        mColours.push_back(SDL_Color({254, 218, 244}));
        mColours.push_back(SDL_Color({223, 255, 250}));
    }
}

// Somehow SDL color modulations doesn't like 0/255 values.
inline SDL_Color AdjustColor(SDL_Color c) {
    SDL_Color y;
    y.r = std::min(254, c.r + 1);
    y.g = std::min(254, c.g + 1);
    y.b = std::min(254, c.b + 1);
    return y;
}

void BeatmapElements::AddColor(SDL_Color c)
{
    mColours.push_back(AdjustColor(c));
}

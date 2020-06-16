#include "Sprite.h"

Sprite::Sprite(int init_x, int init_y, int width, int height, const IntRect& clipBounds, const char* filename)
	:
	pos(init_x, init_y),
	drawRect(0, width, height, 0),
	clipBounds(clipBounds),
	image(filename),
	drawRectPos(0, 0),
	nFrames(image.bmpInfoHeader.biWidth / width),
	nStates(image.bmpInfoHeader.biHeight / height),
	currState(0)
{
}

int Sprite::GetState() const
{
	return currState;
}

void Sprite::AdvanceFrame()
{
	if (drawRectPos.x + drawRect.GetWidth() >= image.bmpInfoHeader.biWidth -1)
		drawRectPos.x = 0;
	else
		drawRectPos.x += drawRect.GetWidth();
}

void Sprite::Draw(Graphics& gfx, Color chromaKey) const
{
	for (int x = drawRectPos.x; x < drawRectPos.x + drawRect.GetWidth(); x++)
	{
		for (int y = drawRectPos.y; y < drawRectPos.y + drawRect.GetHeight(); y++)
		{
			Color pixel = image.GetPixel(x, y);
			if (pixel.dword == chromaKey.dword) continue;
			else gfx.PutPixel(pos.x + x - drawRectPos.x, pos.y + y - drawRectPos.y, pixel);
		}
		
	}
}

void Sprite::SetState(int state)
{
	if (state >= nStates) return;
	currState = state;
	drawRectPos.y = state * drawRect.GetWidth();
}
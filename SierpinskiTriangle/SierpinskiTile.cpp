#include "SierpinskiTile.hpp"

SierpinskiTile::~SierpinskiTile() {
	for (auto itr : rects)
		delete itr;
}

void SierpinskiTile::setTile(int x_index, int y_index) {
	SDL_Rect *rectToAdd = new SDL_Rect;
	rectToAdd->x = x_index * tileW;
	rectToAdd->y = y_index * tileH;
	rectToAdd->w = tileW;
	rectToAdd->h = tileH;
	rects.push_back(rectToAdd);
}

bool SierpinskiTile::isThereTile(int x_index, int y_index) {
	for (auto itr : rects)
		if (itr->x == tileW * x_index
			&& itr->y == tileH * y_index)
			return true;

	return false;
}

void SierpinskiTile::calculate(int y_index) {
	int y = 0;
	if (y_index > -1) {
		y = y_index;

		for (int x = 0; x < scrW / tileW; x++) {
			if ((isThereTile(x, y) || isThereTile(x + 1, y) || isThereTile(x - 1, y))
				&& !(isThereTile(x, y) && isThereTile(x + 1, y) && isThereTile(x - 1, y))
				)
				setTile(x, y + 1);
		}
	}
	else {
		for (; y < scrH / tileH; y++)
			for (int x = 0; x < scrW / tileW; x++) {
				if ((isThereTile(x, y) || isThereTile(x + 1, y) || isThereTile(x - 1, y))
					&& !(isThereTile(x, y) && isThereTile(x + 1, y) && isThereTile(x - 1, y))
					)
					setTile(x, y + 1);
			}
	}
}

void SierpinskiTile::draw(SDL_Renderer*& renderer, int r, int g, int b, int y_index) {
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);

	std::list<SDL_Rect*> deleteRects; 
	for (auto itr : rects) {
		SDL_RenderFillRect(renderer, itr); 

		if (itr->y <= tileH * y_index)
			deleteRects.push_back(itr);
	}

	for (auto itr : deleteRects) {
		rects.remove(itr);
		delete itr;
	}
	deleteRects.clear();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
}
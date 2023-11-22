#include "utils.h"
namespace Utils {

int clamp(int min, int val, int max) {
	if (val < min) return min;
	if (val > max) return max;
	return val;
}

float floatClamp(float min, float val, float max) {
	if (val < min) return min;
	if (val > max) return max;
	return val;
}

Colors PALETTE = {
	{ // primary 
		0xB102BE, // darker
		0x3E0042, // dark
		0x4C0051, // main
		0xDFCDE1, // foggy
		0xEAC9EC, // light
	},
	{ // secondary
		0x00B6A9, // darker
		0x003E3A, // dark
		0x004C46, // main
		0xCADDDC, // foggy
		0xC7EAE7, // light
	},
	{ // complementary
		0xFFA900, // darker
		0x654300, // dark
		0x7C5200, // main
		0xFFF8E9, // foggy
		0xFFF2D9, // light
	},
	{ // text
		0x000000, // darker
		0x000000, // dark
		0x000000, // main
		0x000000, // foggy
		0x000000, // light
	},
};

}
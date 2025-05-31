#pragma once

namespace annotate {
	// Usage: mini-gimp text --text "Hello" --x 100 --y 50 --scale 1.5 --color 0,0,255 --thickness 2 in.jpg out.jpg
	int run(int argc, char** argv);
}

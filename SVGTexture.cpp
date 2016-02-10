
#include "SVGTexture.h"

#define NANOSVG_IMPLEMENTATION
#define NANOSVGRAST_IMPLEMENTATION
#include "nanosvg/nanosvg.h"
#include "nanosvg/nanosvgrast.h"

#include <memory>

namespace sf
{
	bool SVGTexture::loadFromSvgFile (Texture& targetTexture, const std::string & filename, const std::string & units, float dpi) {
		//Smart ptr with custom deleter function
		std::unique_ptr<NSVGimage, void(*)(NSVGimage*)> image (nsvgParseFromFile(filename.c_str(), units.c_str(), dpi), &nsvgDelete);
		if (image == NULL) {
			printf("Could not open SVG image.\n");
			return false;
		}

		int w, h;
		w = (int)image->width;
		h = (int)image->height;	
		
		//Smart ptr with custom deleter function
		std::unique_ptr<NSVGrasterizer, void(*)(NSVGrasterizer*)> rast (nsvgCreateRasterizer(), &nsvgDeleteRasterizer);

		if (rast == NULL) {
			printf("Could not init rasterizer.\n");
			return false;
		}
	
		std::unique_ptr<unsigned char[]> img (new unsigned char[w*h*4]);
		if (img == NULL) {
			printf("Could not alloc image buffer.\n");
			return false;
		}
	
		//rasterizing image
		nsvgRasterize(rast.get(), image.get(), 0,0,1, img.get(), w, h, w*4);
	
		targetTexture.create(w,h);
		targetTexture.update(img.get(), w,h, 0,0 );
	
		return true;
	}
}

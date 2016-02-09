
#include "SVGTexture.h"

#define NANOSVG_IMPLEMENTATION
#define NANOSVGRAST_IMPLEMENTATION
#include "nanosvg/nanosvg.h"
#include "nanosvg/nanosvgrast.h"

namespace sf
{
	bool SVGTexture::loadFromSvgFile (const std::string & filename, const std::string & units, float dpi) {
		NSVGimage *image = NULL;
		NSVGrasterizer *rast = NULL;
		unsigned char* img = NULL;
		int w, h;
	
		//printf("parsing %s\n", filename);
		image = nsvgParseFromFile(filename.c_str(), units.c_str(), dpi);
		if (image == NULL) {
			printf("Could not open SVG image.\n");
			goto error;
		}
		w = (int)image->width;
		h = (int)image->height;
	
		rast = nsvgCreateRasterizer();
		if (rast == NULL) {
			printf("Could not init rasterizer.\n");
			goto error;
		}
	
		img = (unsigned char*) malloc(w*h*4);
		if (img == NULL) {
			printf("Could not alloc image buffer.\n");
			goto error;
		}
	
		//printf("rasterizing image %d x %d\n", w, h);
		nsvgRasterize(rast, image, 0,0,1, img, w, h, w*4);
	
		this->create(w,h);
		this->update(img, w,h, 0,0 );
	
		free(img);
		return true;
	error:
		nsvgDeleteRasterizer(rast);
		nsvgDelete(image);
	
		return false;
	}
}

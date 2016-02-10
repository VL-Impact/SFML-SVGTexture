#pragma once 

#include <SFML/Graphics/Texture.hpp>
#include <string>

namespace sf
{
	class SVGTexture {
	public:
		
		// The units passed to NanoVG should be one of: 'px', 'pt', 'pc' 'mm', 'cm', or 'in'.
		// DPI (dots-per-inch) controls how the unit conversion is done.
		static bool loadFromSvgFile (Texture& targetTexture, const std::string & filename, const std::string & units = "px", float dpi = 96.0f);
	};
}

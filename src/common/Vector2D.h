#pragma once

namespace TDC
{ 
	template <typename valType> 
	class Vector2D
	{
		public:
			Vector2D(valType _x, valType _y) { x = _x; y = _y; };
			~Vector2D() {};

			valType x;
			valType y;
	};

}
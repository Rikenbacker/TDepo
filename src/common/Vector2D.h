#pragma once

namespace TDC
{ 
	template <typename valType> 
	class Vector2D
	{
		public:
			Vector2D(valType _x, valType _y) { x = _x; y = _y; };
            Vector2D() {};
			~Vector2D() {};

            void add(Vector2D _add) { x += _add.x; y += _add.y;};

			valType x;
			valType y;
	};

}
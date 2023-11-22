#ifndef FIRSTCPPGAME_PHYSICS_H
#define FIRSTCPPGAME_PHYSICS_H

namespace Physics {
	struct Point2 {
		float x, y;
	};

	struct  Vector2 {
		Point2 start, end;
	};

	struct Area {
		Vector2 bottomLeftCorner;
		Vector2 topRightCorner;
	};

	class Physics2Object {
	public:
		Physics2Object() {}
		Point2 position = {0, 0};
		Vector2 speed = { {0, 0}, {0, 0} };
		Vector2 size = { {0, 0}, {0, 0} };
		float friction = 0;
	};

	/** 
	 * Calculates the distance between 2 points given the coordinates of
	 * each one
	 */
	extern int distance(float x0, float y0, float x1, float y1);

	/**
	 * Calculates the distance between 2 points given the two Point2 objects.
	 */
	extern int distance(Point2 a, Point2 b);

	/**
	 * Calculates the length of a vector.
	 */
	extern int distance(Vector2 vector);

	extern Point2 clampPoint2(Vector2 limiter, Point2 point);

	extern Vector2 clampVector2(Vector2 limiter, Vector2 vector);

	extern Point2 sumPoints(Point2 point1, Point2 point2);

	extern Vector2 sumVectors(Vector2 vec0, Vector2 vec1);
}

#endif
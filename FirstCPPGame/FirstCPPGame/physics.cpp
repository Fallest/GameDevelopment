#include "physics.h"
#include <cmath>

namespace Physics {
/**
* Calculates the distance between 2 points given the coordinates of
* each one
*/
int distance(float x0, float y0, float x1, float y1) {
	return sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2));
}

/**
* Calculates the distance between 2 points given the two Point2 objects.
*/
int distance(Point2 start, Point2 end) {
	return distance(start.x, start.y, end.x, end.y);
}

/**
* Calculates the length of a vector.
*/
int distance(Vector2 vector) {
	return distance(vector.start, vector.end);
}

Point2 clampPoint2(Vector2 limiter, Point2 point) {
	if (limiter.start.x > point.x) point.x = limiter.start.x;
	if (limiter.start.y > point.y) point.y = limiter.start.y;
	if (limiter.end.x < point.x) point.x = limiter.end.x;
	if (limiter.end.y < point.y) point.y = limiter.end.y;

	return point;
}

/**
 * Clamps the points of a vector to a specific limiter vector. 
 */
Vector2 clampVector2(Vector2 limiter, Vector2 vector) {
	if (limiter.start.x > vector.start.x) vector.start.x = limiter.start.x;
	if (limiter.start.y > vector.start.y) vector.start.y = limiter.start.y;
	if (limiter.end.x < vector.end.x) vector.end.x = limiter.end.x;
	if (limiter.end.y < vector.end.y) vector.end.y = limiter.end.y;

	return vector;
}

/**
 * Returns the sum of two points
 */
Point2 sumPoints(Point2 point1, Point2 point2) {
	point1.x += point2.x;
	point1.y += point2.y;
	return point1;
}

/**
 * Returns the sum of two vectors
 */
Vector2 sumVectors(Vector2 vec0, Vector2 vec1) {
	vec0.start = sumPoints(vec0.start, vec1.start);
	vec0.end= sumPoints(vec0.end, vec1.end);
	return vec0;
}
}
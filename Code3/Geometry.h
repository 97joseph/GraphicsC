#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <iostream>
#include <memory>
#include <vector>

class Point; // forward declaration

class Shape {

public:

	// Constructor specifying the depth of the object.
	// If d is negative, throw a std::invalid_argument exception
	Shape(int d);

	// Set depth of object to d. If d is negative, return false and
	// do not update depth. Otherwise return true
	bool setDepth(int d);

	// Return the depth of object
	int getDepth() const;

	// Return the dimension of the object (0, 1 or 2)
	int dim() const;

	// Translate the object horizontally by x and vertically by y
	virtual void translate(float x, float y) = 0;

	// Return true if the object contains p and false otherwise.
	// Depths are ignored for purpose of comparison
	virtual bool contains(const Point& p) const = 0;

	// Rotate the object 90 degrees around its centre
	virtual void rotate() = 0;

	// Scale the object by a factor f relative to its centre.
	// If f is zero or negative, throw a std::invalid-argument exception.
	virtual void scale(float f) = 0;

	// the constant pi
	static constexpr double PI = 3.1415926;

protected:
  int dimension_;

private:
  int d_;
};

class Point : public Shape {

public:
	// Constructor. Depth defaults to 0
	Point(float x, float y, int d=0);

	// Return basic information (see assignment page)
	float getX() const;
	float getY() const;

	void translate(float x, float y) final;

	bool contains(const Point& p) const final;

	void rotate() final;

	void scale(float f) final;

private:
	float x_;
	float y_;
};

class LineSegment : public Shape {

public:
	// Constructor.
	// If the two points have different depths, or have the same x- and
	// y-coordinate, or if the line is not axis-aligned, throw a
	// std::invalid_argument exception
	LineSegment(const Point& p, const Point& q);

	// Return basic information (see assignment page)
	float getXmin() const;
	float getXmax() const;
	float getYmin() const;
	float getYmax() const;

	// Return the length of the line segment
	float length() const;

	void translate(float x, float y) final;

	bool contains(const Point& p) const final;

	void rotate() final;

	void scale(float f) final;

private:
	Point* p_;
	Point* q_;
};

class TwoDShape : public Shape {

public:

	// Constructor specifying the depth d
	TwoDShape(int d);

	// Return the area of the object
	virtual float area() const = 0;

	virtual void translate(float x, float y) override = 0;

	virtual bool contains(const Point& p) const override = 0;

	virtual void rotate() override = 0;

	virtual void scale(float f) override = 0;

};

class Rectangle : public TwoDShape {

public:
	// Constructor.
	// If the two points have different depths, or have the same x-
	// and/or y-coordinate, throw a std::invalid_argument exception
	Rectangle(const Point& p, const Point& q);

	// Return basic information (see assignment page)
	float getXmin() const;
	float getYmin() const;
	float getXmax() const;
	float getYmax() const;

	float area() const final;

	void translate(float x, float y) final;

	bool contains(const Point& p) const final;

	void rotate() final;

	void scale(float f) final;

private:
	Point* p_;
	Point* q_;
};

class Circle : public TwoDShape {

public:
	// Constructor.
	// If r is zero or negative, throw a std::invalid-argument exception.
	Circle(const Point& c, float r);

	// Return basic information (see assignment page)
	float getX() const;
	float getY() const;
	float getR() const;

	float area() const final;

	void translate(float x, float y) final;

	bool contains(const Point& p) const final;

	void rotate() final;

	void scale(float f) final;

private:
	Point* c_;
	float r_;
};


class Scene {

public:
	// Constructor
	Scene();

	// Add the pointer to the collection of pointers stored
	void addObject(std::shared_ptr<Shape> ptr);

	// Set the drawing depth to d
	void setDrawDepth(int d);

	// Constants specifying the size of the drawing area
	static constexpr int WIDTH = 60;
	static constexpr int HEIGHT = 20;

private:
	std::vector<std::shared_ptr<Shape>> collection_;
	int draw_depth_;
	bool draw_depth_set_;


// Draw objects as specified in the assignment page
friend std::ostream& operator<<(std::ostream& out, const Scene& s);

};

#endif /* GEOMETRY_H_ */

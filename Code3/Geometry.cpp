#include "Geometry.h"
#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;

// ============ Shape class =================

Shape::Shape(int d) {
	if (!setDepth(d)) {
		throw std::invalid_argument("invalid depth");
	}
}

bool Shape::setDepth(int d) {
	if (d >= 0) {
    d_ = d;
    return true;
	}
  return false;
}

int Shape::getDepth() const {
	return d_;
}

int Shape::dim() const {
	return dimension_;
}

// =============== Point class ================

Point::Point(float x, float y, int d) : Shape(d) {
	x_ = x;
	y_ = y;
	dimension_ = 0;
}

float Point::getX() const {
	return x_;
}

float Point::getY() const {
	return y_;
}

void Point::translate(float x, float y) {
	x_ += x;
	y_ += y;
}

void Point::rotate() {}

bool Point::contains(const Point& p) const {
	return (p.getX() == x_ && p.getY() == y_);
}

void Point::scale(float f) {
	if (f <= 0) {
		throw std::invalid_argument("scale factor must be greater than 0");
	}
}

// =========== LineSegment class ==============

LineSegment::LineSegment(const Point& p, const Point& q) : Shape(p.getDepth()) {
  if (!(p.getX() == q.getX()) && !(p.getY() == q.getY())) {
    throw std::invalid_argument("invalid shape for line segment");
  }
  if ((p.getX() == q.getX()) && (p.getY() == q.getY())) {
    throw std::invalid_argument("invalid shape for line segment");
  }
  if (p.getDepth() != q.getDepth()) {
    throw std::invalid_argument("invalid depth for line segment");
  }

	p_ = new Point(p.getX(), p.getY(), p.getDepth());
	q_ = new Point(q.getX(), q.getY(), q.getDepth());
	dimension_ = 1;
}

float LineSegment::getXmin() const {
	return fmin(p_->getX(), q_->getX());
}

float LineSegment::getXmax() const {
	return fmax(p_->getX(), q_->getX());
}

float LineSegment::getYmin() const {
	return fmin(p_->getY(), q_->getY());
}

float LineSegment::getYmax() const {
	return fmax(p_->getY(), q_->getY());
}

float LineSegment::length() const {
  if (p_->getX() == q_->getX()) {
    return getYmax() - getYmin();
	} else {
		return getXmax() - getXmin();
	}
}

void LineSegment::translate(float x, float y) {
  p_->translate(x, y);
  q_->translate(x, y);
}

bool LineSegment::contains(const Point& p) const {
	if (p.getX() >= getXmin() && p.getX() <= getXmax()) {
		if (p.getY() >= getYmin() && p.getY() <= getYmax()) {
			return true;
		}
	}
	return false;
}

void LineSegment::rotate() {
  float center = length() / 2;

  if (p_->getX() == q_->getX()) {  // for vertical lines
    if (p_->getY() < q_->getY()) {  // if p is below q
      p_->translate(-center, center);
      q_->translate(center, -center);
    } else {  // if p is above q
      p_->translate(-center, center);
      q_->translate(center, -center);
    }
  } else {  // for horizontal lines
    if (p_->getX() < q_->getX()) {  // if p is left of q
      p_->translate(center, center);
      q_->translate(-center, -center);
    } else {  // if p is right of q
      p_->translate(-center, -center);
      q_->translate(center, center);
    }
  }
}

void LineSegment::scale(float f) {
	if (f <= 0) {
		throw std::invalid_argument("scale factor must be greater than 0");
	}

	float center_x = (getXmin() + getXmax()) / 2;
	float center_y = (getYmin() + getYmax()) / 2;

	float px_move = ((p_->getX() - center_x) * f) - (p_->getX() - center_x);
	float py_move = ((p_->getY() - center_y) * f) - (p_->getY() - center_y);
	p_->translate(px_move, py_move);

	float qx_move = ((q_->getX() - center_x) * f) - (q_->getX() - center_x);
	float qy_move = ((q_->getY() - center_y) * f) - (q_->getY() - center_y);
	q_->translate(qx_move, qy_move);
}

// ============ TwoDShape class ================

TwoDShape::TwoDShape(int d) : Shape(d) {}

// ============== Rectangle class ================

Rectangle::Rectangle(const Point& p, const Point& q) : TwoDShape(p.getDepth()) {
	if (p.getX() == q.getX() || p.getY() == q.getY()) {
		throw std::invalid_argument("invalid shape for rectangle");
	}

  if (p.getDepth() != q.getDepth()) {
    throw std::invalid_argument("invalid depth for rectangle");
  }

	p_ = new Point(p.getX(), p.getY(), p.getDepth());
	q_ = new Point(q.getX(), q.getY(), q.getDepth());
	dimension_ = 2;
}

float Rectangle::getXmin() const {
	return fmin(p_->getX(), q_->getX());
}

float Rectangle::getXmax() const {
	return fmax(p_->getX(), q_->getX());
}

float Rectangle::getYmin() const {
	return fmin(p_->getY(), q_->getY());
}

float Rectangle::getYmax() const {
	return fmax(p_->getY(), q_->getY());
}

float Rectangle::area() const {
	return (getXmax() - getXmin()) * (getYmax() - getYmin());
}

void Rectangle::translate(float x, float y) {
	p_->translate(x, y);
  q_->translate(x, y);
}

bool Rectangle::contains(const Point& p) const {
	if (p.getX() >= getXmin() && p.getX() <= getXmax()) {
		if (p.getY() >= getYmin() && p.getY() <= getYmax()) {
			return true;
		}
	}
	return false;
}

void Rectangle::rotate() {
  float center_x = (getXmax() - getXmin()) / 2;
  float center_y = (getYmax() - getYmin()) / 2;

  if (p_->getX() < q_->getX()) {
    if (p_->getY() < q_->getY()) {  // if p is left+below q
      p_->translate(center_x - center_y, center_x + center_y);
      q_->translate(-(center_x - center_y), -(center_x + center_y));
    } else {  // if p is left+above q
      p_->translate(center_x + center_y, center_x - center_y);
      q_->translate(-(center_x + center_y), -(center_x - center_y));
    }
  } else {
    if (p_->getY() < q_->getY()) {  // if p is right+below q
      p_->translate(-(center_x + center_y), -(center_x - center_y));
      q_->translate(center_x + center_y , center_x - center_y);
    } else {  // if p is right+above q
      p_->translate(-(center_x - center_y), -(center_x + center_y));
      q_->translate(center_x - center_y, center_x + center_y);
    }
  }
}

void Rectangle::scale(float f) {
	if (f <= 0) {
		throw std::invalid_argument("scale factor must be greater than 0");
	}

	float center_x = (getXmin() + getXmax()) / 2;
	float center_y = (getYmin() + getYmax()) / 2;

	float px_move = ((p_->getX() - center_x) * f) - (p_->getX() - center_x);
	float py_move = ((p_->getY() - center_y) * f) - (p_->getY() - center_y);
	p_->translate(px_move, py_move);

	float qx_move = ((q_->getX() - center_x) * f) - (q_->getX() - center_x);
	float qy_move = ((q_->getY() - center_y) * f) - (q_->getY() - center_y);
	q_->translate(qx_move, qy_move);
}

// ================== Circle class ===================

Circle::Circle(const Point& c, float r) : TwoDShape(c.getDepth()) {
  if (r <= 0) {
    throw std::invalid_argument("radius must be greater than 0");
  }
	c_ = new Point(c.getX(), c.getY(), c.getDepth());
	r_ = r;
	dimension_ = 2;
}

float Circle::getX() const {
	return c_->getX();
}

float Circle::getY() const {
	return c_->getY();
}

float Circle::getR() const {
	return r_;
}

float Circle::area() const {
	return PI * pow(r_, 2);
}

void Circle::translate(float x, float y) {
  c_->translate(x, y);
}

bool Circle::contains(const Point& p) const {
	return sqrt(pow(p.getX() - c_->getX(), 2) + pow(p.getY() - c_->getY(), 2)) <= r_;
}

void Circle::rotate() {}

void Circle::scale(float f) {
	if (f <= 0) {
		throw std::invalid_argument("scale factor must be greater than 0");
	}
	r_ *= f;
}

// ================= Scene class ===================

Scene::Scene() {
	draw_depth_set_ = false;
}

void Scene::addObject(std::shared_ptr<Shape> ptr) {
	collection_.push_back(ptr);
}

void Scene::setDrawDepth(int depth) {
	draw_depth_ = depth;
	draw_depth_set_ = true;
}

std::ostream& operator<<(std::ostream& out, const Scene& s) {
	for (int j=s.HEIGHT-1; j>=0; j--) {
		for (int i=0; i<s.WIDTH; i++) {
			bool filled = false;
			for (auto shape : s.collection_) {
        if (!s.draw_depth_set_ || shape->getDepth() <= s.draw_depth_) {
          if (shape->contains(Point(i, j))) {
            out << '*';
            filled = true;
            break;
          }
        }
			}
			if (!filled) {
				out << ' ';
			}
		}
		out << "\n";
	}
	return out;
}

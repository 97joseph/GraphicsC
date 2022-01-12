#include "Geometry.h"

// ============ Shape class =================

Shape::Shape() {} // REMOVE ME

Shape::Shape(int d) {
    // IMPLEMENT ME
}

bool Shape::setDepth(int d) {
    // IMPLEMENT ME
    return false; // dummy
}

int Shape::getDepth() const {
    // IMPLEMENT ME
    return -999; // dummy
}

int Shape::dim() const {
    // IMPLEMENT ME
    return -999; // dummy
}

void Shape::translate(float x, float y) {
    // IMPLEMENT ME
}

void Shape::rotate() {
    // IMPLEMENT ME
}

void Shape::scale(float f) {
    // IMPLEMENT ME
}

bool Shape::contains(const Point& p) const {
    // IMPLEMENT ME
    return false; // dummy
}

// =============== Point class ================

Point::Point(float x, float y, int d) {
    // IMPLEMENT ME
}

float Point::getX() const {
    // IMPLEMENT ME
    return -999; // dummy
}

float Point::getY() const {
    // IMPLEMENT ME
    return -999; // dummy
}

// =========== LineSegment class ==============

LineSegment::LineSegment(const Point& p, const Point& q) {
    // IMPLEMENT ME
}

float LineSegment::getXmin() const {
    // IMPLEMENT ME
    return -999; // dummy
}

float LineSegment::getXmax() const {
    // IMPLEMENT ME
    return -999; // dummy
}

float LineSegment::getYmin() const {
    // IMPLEMENT ME
    return -999; // dummy
}

float LineSegment::getYmax() const {
    // IMPLEMENT ME
    return -999; // dummy
}

float LineSegment::length() const {
    // IMPLEMENT ME
    return -999; // dummy
}

// ============ TwoDShape class ================

TwoDShape::TwoDShape(){} // REMOVE ME

TwoDShape::TwoDShape(int d) {
    // IMPLEMENT ME
}

float TwoDShape::area() const {
    // IMPLEMENT ME
    return -999; // dummy
}

// ============== Rectangle class ================

Rectangle::Rectangle(const Point& p, const Point& q) {
    // IMPLEMENT ME
}

float Rectangle::getXmin() const {
    // IMPLEMENT ME
    return -999; // dummy
}

float Rectangle::getYmin() const {
    // IMPLEMENT ME
    return -999; // dummy
}

float Rectangle::getXmax() const {
    // IMPLEMENT ME
    return -999; // dummy
}

float Rectangle::getYmax() const {
    // IMPLEMENT ME
    return -999; // dummy
}

// ================== Circle class ===================

Circle::Circle(const Point& c, float r) {
    // IMPLEMENT ME
}

float Circle::getX() const {
    // IMPLEMENT ME
    return -999; // dummy
}

float Circle::getY() const {
    // IMPLEMENT ME
    return -999; // dummy
}

float Circle::getR() const {
    // IMPLEMENT ME
    return -999; // dummy
}

// ================= Scene class ===================

Scene::Scene() {
    // IMPLEMENT ME
}

void Scene::addObject(std::shared_ptr<Shape> ptr) {
    // IMPLEMENT ME
}

void Scene::setDrawDepth(int depth) {
    // IMPLEMENT ME
}

std::ostream& operator<<(std::ostream& out, const Scene& s) {
    // IMPLEMENT ME
    return out;
}

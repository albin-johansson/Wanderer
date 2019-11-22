#include "catch.hpp"
#include "vector_2.h"
#include <cmath>

using namespace wanderer::core;

TEST_CASE("Vector2DefaultCtor", "[Vector2]") {
  Vector2 vector; // should be (0, 0)
  CHECK(vector.GetX() == 0);
  CHECK(vector.GetY() == 0);
  CHECK(vector.IsZero());
}

TEST_CASE("Vector2Ctor", "[Vector2]") {
  float x = 53.8;
  float y = 125.2;
  auto vector = Vector2(x, y);

  CHECK(vector.GetX() == x);
  CHECK(vector.GetY() == y);
  CHECK(!vector.IsZero());
}

TEST_CASE("Vector2CopyCtor", "[Vector2]") {
  auto original = Vector2(87.3f, 39.5f);
  auto copy = Vector2(original);

  CHECK(original.GetX() == copy.GetX());
  CHECK(original.GetY() == copy.GetY());
}

TEST_CASE("Vector2::Scale", "[Vector2]") {
  float x = 24.5f;
  float y = 83.7f;
  Vector2 vector(x, y);

  float factor = 3.2f;
  vector.Scale(factor);

  CHECK(vector.GetX() == Approx(x * factor));
  CHECK(vector.GetY() == Approx(y * factor));

  vector.Scale(0);
  CHECK(vector.IsZero());
}

TEST_CASE("Vector2::Add1", "[Vector2]") {
  float x = 19.9f;
  float y = 27.2f;
  Vector2 vector(x, y);

  float dx = 53;
  float dy = -23;

  Vector2 other(dx, dy);
  vector.Add(other);

  CHECK(other.GetX() == dx);
  CHECK(other.GetY() == dy);

  CHECK(vector.GetX() == Approx(x + dx));
  CHECK(vector.GetY() == Approx(y + dy));
}

TEST_CASE("Vector2::Add2", "[Vector2]") {
  float x = 44.1f;
  float y = 38.6f;
  Vector2 vector(x, y);

  float dx = -29;
  float dy = 12;

  vector.Add(dx, dy);
  CHECK(vector.GetX() == Approx(x + dx));
  CHECK(vector.GetY() == Approx(y + dy));
}

TEST_CASE("Vector2::Sub", "[Vector2]") {
  float x = 24.5f;
  float y = 83.7f;
  Vector2 vector(x, y);

  float x1 = 88.2f;
  float y1 = 24.8f;

  Vector2 other(x1, y1);

  vector.Sub(other);
  CHECK(vector.GetX() == Approx(x - x1));
  CHECK(vector.GetY() == Approx(y - y1));
}

TEST_CASE("Vector2::Norm", "[Vector2]") {
  Vector2 vector(12.0f, 92.3f);

  vector.Norm();

  CHECK(vector.IsUnit());
  CHECK(vector.GetLength() == Approx(1));
}

TEST_CASE("Vector2::Set", "[Vector2]") {
  Vector2 vector(91, 3);
  Vector2 other(123, 45);

  vector.Set(other);

  CHECK(vector.GetX() == Approx(other.GetX()));
  CHECK(vector.GetY() == Approx(other.GetY()));
}

TEST_CASE("Vector2::SetX", "[Vector2]") {
  Vector2 vector(91, 3);

  float x = 82.4f;
  vector.SetX(x);
  CHECK(vector.GetX() == Approx(x));
}

TEST_CASE("Vector2::SetY", "[Vector2]") {
  Vector2 vector(4, 77);

  float y = 33.4f;
  vector.SetY(y);
  CHECK(vector.GetY() == Approx(y));
}

TEST_CASE("Vector2::SetLength", "[Vector2]") {
  Vector2 vector(52, 93);

  float length = 4;
  vector.SetLength(length);
  CHECK(vector.GetLength() == Approx(length));
}

TEST_CASE("Vector2::LookAt(Vector2, float)", "[Vector2]") {
  Vector2 vector(412, 287);

  CHECK_NOTHROW(vector.LookAt(vector, 0));
  CHECK_NOTHROW(vector.LookAt(vector, -1));
}

TEST_CASE("Vector2::DistanceTo", "[Vector2]") {
  Vector2 vector(377, 518);
  Vector2 other(123, 411);

  auto dx = other.GetX() - vector.GetX();
  auto dy = other.GetY() - vector.GetY();
  auto expected = std::sqrt(dx * dx + dy * dy);
  CHECK(expected == vector.DistanceTo(other));
  CHECK(vector.DistanceTo(other) == other.DistanceTo(vector));

  CHECK(vector.DistanceTo(vector) == 0);
}

TEST_CASE("Vector2::DistanceTo2", "[Vector2]") {
  Vector2 vector(58, 832);
  Vector2 other(284, 550);

  CHECK(std::sqrt(vector.DistanceTo2(other)) == vector.DistanceTo(other));
  CHECK(vector.DistanceTo2(vector) == 0);
}

TEST_CASE("Vector2::GetLength", "[Vector2]") {
  Vector2 vector;

  CHECK(vector.GetLength() == 0);
  CHECK(vector.IsZero());
}

TEST_CASE("Vector2::GetLength2", "[Vector2]") {
  Vector2 vector;

  CHECK(vector.GetLength2() == 0);
  CHECK(vector.IsZero());
}

TEST_CASE("Vector2::IsZero", "[Vector2]") {
  Vector2 first;
  CHECK(first.IsZero());

  Vector2 other(12, 95);
  CHECK(!other.IsZero());
}

TEST_CASE("Vector2::IsUnit", "[Vector2]") {
  Vector2 vector(1, 0);
  CHECK(vector.IsUnit());

  vector.Scale(0.5f);
  CHECK(!vector.IsUnit());

  vector.Norm();
  CHECK(vector.IsUnit());
}
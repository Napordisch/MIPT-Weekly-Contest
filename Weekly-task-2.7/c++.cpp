#include <iostream>
#include <cstdlib>
#include <math.h>
#include <cstring>
#include <vector>

int ScalarProduct(Vector one, Vector two) {
  return (one.GetX() * two.GetX()) + (one.GetY() * two.GetY());
}

double VectorLength(Vector one) {
  double Length = std::sqrt(one.GetX() * one.GetX() + one.GetY() * one.GetY());
}


namespace geometry {
  class Vector;

  class AbstractShape;
  class Point;
  class Segment;
  class Ray;
  class Line;
  class Polygon;
  class Circle;


  class Vector {
    public:
      Vector(const Point &A, const Point &B);

      int GetX() const;
      int GetY() const;

    private:
      int x_ = 0;
      int y_ = 0;
  };

  class AbstractShape {

    public:
      virtual AbstractShape* Move(const Vector &ab) = 0;
      virtual bool ContainsPoint(const Point &a) const = 0;
      virtual bool CrossSegment(const Segment &ab) const = 0;
      virtual AbstractShape *Clone() const = 0;
      virtual void Print() = 0;
      virtual ~AbstractShape() = default;

    // define pure virtual methods
  };

  class Point : public AbstractShape {
    public:

      Point();
 
      Point(int x, int y);

      void SetX(int x);

      void SetY(int y);

      void Set(int x, int y);

      int GetX() const;

      int GetY() const;

      Point* Move(const Vector &ab) override;

      bool ContainsPoint(const Point &a) const override;

      bool CrossSegment(const Segment &ab) const override;

      Point *Clone() const override;

      void Print() override; 

    private:
      int x_ = 0;
      int y_ = 0;
  };

  class Segment : public AbstractShape {
    public:

      Segment(Point a, Point b);

      double GetGradient();
      
      double GetB(double gradient);

      Segment* Move(const Vector &ab) override;
      bool ContainsPoint(const Point &a) const override;
      bool CrossSegment(const Segment &ab) const override;
      Segment *Clone() const override;
      void Print() override;

    private:
      Point a_;
      Point b_;
  };

  class Line : public AbstractShape {
    public:
      Line* Move(const Vector &ab) override;
      bool ContainsPoint(const Point &a) const override;
      bool CrossSegment(const Segment &ab) const override;
      Line *Clone() const override;
      void Print() override;
    // implement
  };

  class Ray : public AbstractShape {
    public:
      Ray* Move(const Vector &ab) override;
      bool ContainsPoint(const Point &a) const override;
      bool CrossSegment(const Segment &ab) const override;
      Ray *Clone() const override;
      void Print() override;
    // implement
  };

  class Polygon : public AbstractShape {
    public:
      Polygon* Move(const Vector &ab) override;
      bool ContainsPoint(const Point &a) const override;
      bool CrossSegment(const Segment &ab) const override;
      Polygon *Clone() const override;
      void Print() override;
    // implement
  };

  class Circle : public AbstractShape {
    public:
      Circle* Move(const Vector &ab) override;
      bool ContainsPoint(const Point &a) const override;
      bool CrossSegment(const Segment &ab) const override;
      Circle *Clone() const override;
      void Print() override;
    //implement
  };

//Vector methods
  Vector::Vector(const Point &A, const Point &B) {
    x_ = B.GetX() - A.GetX();
    y_ = B.GetY() - A.GetY();
  }

  int Vector::GetX() const {
    return x_;
  }

  int Vector::GetY() const {
    return y_;
  }




//Point methods

  Point::Point() = default;

  Point::Point(int x, int y) {
    Set(x, y);
  }

  void Point::SetX(int x) {
    x_ = x;
  }

  void Point::SetY(int y) {
    y_ = y;
  }

  void Point::Set(int x, int y) {
    SetX(x);
    SetY(y);
  }

  int Point::GetX() const {
    return x_;
  }

  int Point::GetY() const {
    return y_;
  }

  Point* Point::Move(const Vector &ab) {
    int dx = ab.GetX();
    int dy = ab.GetY();
    return new Point(x_ + dx, y_ + dy);
  }

  bool Point::ContainsPoint(const Point &a) const {
    return (x_ == a.GetX() && y_ == a.GetY());
  }

  bool Point::CrossSegment(const Segment &ab) const {
    return ab.ContainsPoint(*this);
  }

  Point* Point::Clone() const {
    return new Point(x_, y_);
  }

  void Point::Print() { 
    std::cout << x_ << ' ';
    std::cout << y_ << ' ';
    std::cout << '\n';
  }

//segment methods
  Segment::Segment(Point a, Point b) {
    a_ = *(a.Clone());
    b_ = *(b.Clone());
  }

  double Segment::GetGradient() {
    Point horizontal_line_point(b_.GetX(), a_.GetY());
    Vector parallel_vector(a_, b_);
    Vector horizontal_vector(a_, horizontal_line_point);
    double scalar_product = ScalarProduct(parallel_vector, horizontal_vector);

    double length_product = VectorLength(parallel_vector)
                          * VectorLength(horizontal_vector);

    double angle = std::acos((scalar_product) / (length_product));
    double gradient = std::tan(angle);
    return gradient;
  }

  double Segment::GetB(double gradient) {
    double b = a_.GetY() - (gradient * a_.GetX());
    return b;
  }


  Segment* Segment::Move(const Vector&ab) {
    int dx = ab.GetX();
    int dy = ab.GetY();
    Point new_a(a_.GetX() + dx, a_.GetY() + dy);
    Point new_b(b_.GetX() + dx, b_.GetY() + dy);
    return new Segment(new_a, new_b);
  }

  bool Segment::ContainsPoint(const Point &a) const {

    int y1 = a_.GetY();
    int y2 = b_.GetY();

    int y_min = std::min(y1, y2);
    int y_max = std::max(y1, y2);

    int x1 = a_.GetX();
    int x2 = b_.GetX();

    int x_min = std::min(x1, x2);
    int x_max = std::max(x1, x2);

    int x = a.GetX();
    int y = a.GetY();

    bool on_the_line = (y - y1) / (y2 - y1) == (x - x1) / (x2 - x1);
    bool in_the_rectangle = x < x_max &&
                            x > x_min &&
                            y < x_max &&
                            y > x_min;

    return (on_the_line && in_the_rectangle);
  }

  bool Segment::CrossSegment(const Segment &ab) const {
    double this_gradient = GetGradient();
    double b = GetB(this_gradient);
  }

  Segment* Segment::Clone() const {
    return new Segment(a_, b_);
  }

  void Segment::Print() {
    std::cout << a_.GetX() << ' ';
    std::cout << a_.GetY() << ' ';
    std::cout << b_.GetX() << ' ';
    std::cout << b_.GetY() << ' ';
  }


}


void CheckFunctions(const geometry::AbstractShape* shape, const geometry::Point& A, const geometry::Point& B) {
  if (shape->ContainsPoint(A)) {
    std::cout << "Given shape contains point A" << std::endl;
  } else {
    std::cout << "Given shape does not contain point A" << std::endl;
  }

  geometry::Segment AB(A, B);
  if (shape->CrossSegment(AB)) {
    std::cout << "Given shape crosses segment AB" << std::endl;
  } else {
    std::cout << "Given shape does not cross segment AB" << std::endl;
  }

  geometry::Vector ab(A, B);
  geometry::AbstractShape* clonedShape = shape->Clone();
  clonedShape->Move(ab)->Print();
  delete clonedShape;
}

int main() {
  geometry::AbstractShape* shape;
  char command[10];
  std::cin >> command;

  // object creation
  if (!strcmp(command, "point")) {
    int x, y;
    std::cin >> x >> y;
    shape = new geometry::Point(x, y);
//  } else if (!strcmp(command, "segment")) {
//    int x1, y1, x2, y2;
//    std::cin >> x1 >> y1 >> x2 >> y2;
//    shape = new geometry::Segment(geometry::Point(x1, y1), geometry::Point(x2, y2));
//  } else if (!strcmp(command, "ray")) {
//    int x1, y1, x2, y2;
//    std::cin >> x1 >> y1 >> x2 >> y2;
//    shape = new geometry::Ray(geometry::Point(x1, y1), geometry::Point(x2, y2));
//  } else if (!strcmp(command, "line")) {
//    int x1, y1, x2, y2;
//    std::cin >> x1 >> y1 >> x2 >> y2;
//    shape = new geometry::Line(geometry::Point(x1, y1), geometry::Point(x2, y2));
//  } else if (!strcmp(command, "polygon")) {
//    size_t n_points;
//    std::cin >> n_points;
//    std::vector<geometry::Point> points;
//    points.reserve(n_points);
//    for (size_t i = 0; i < n_points; ++i) {
//      int x, y;
//      std::cin >> x >> y;
//      points.push_back(geometry::Point(x, y));
//    }
//    shape = new geometry::Polygon(points, n_points);
//  } else if (!strcmp(command, "circle")) {
//    int x, y;
//    std::cin >> x >> y;
//    Point center(x, y);
//    int radius;
//    std::cin >> radius;
//    shape = new geometry::Circle(center, radius);
  } else { 
    std::cerr << "Undefined command" << std::endl;
    return 1;
  }

  int ax, ay, bx, by;
  std::cin >> ax >> ay >> bx >> by;
  geometry::Point A(ax, ay), B(bx, by);

  CheckFunctions(shape, A, B);

  return 0;
}

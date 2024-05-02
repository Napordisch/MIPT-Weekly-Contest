#include <vector>
#include <iostream>

using std::cin;
using std::cout;
using std::vector;

struct Point
{ // a.k.a. Vector
	Point() = default;
	Point(int new_x, int new_y)
	{
		x = new_x;
		y = new_y;
	}
	int x = 0;
	int y = 0;
};

struct Segment
{
	Segment(Point a, Point b)
	{
		a_point = a;
		b_point = b;
	}
	Point a_point;
	Point b_point;
};

struct Ray
{
	Ray(Point s, Point new_end)
	{
		start = s;
		end = new_end;
	}
	Point start;
	Point end;
	Point Direction() const
	{ // vector
		return Point(end.x - start.x, end.y - start.y);
	}
};

struct Polygon
{
	void ConnectPoints ()
	{
		segments.clear();
		unsigned int amount_of_points = points.size();
		for (unsigned int i = 0; i < amount_of_points; i += 2)
		{
			unsigned int from = i;
			unsigned int to = i + 1;
			if (to >= amount_of_points)
			{
				to = 0;
			}
			segments.emplace_back(points[from], points[to]);
		}
		points_connected = true;
	}	

	vector<Point> points;
	vector<Segment> segments;
	bool points_connected;

	void PrintSegments() {
		for (Segment s : segments) {
			cout << s.a_point.x << ',' << s.a_point.y << ';' << ' ';
			cout << s.b_point.x << ',' << s.b_point.y << ';';
			cout << '\n';
		}
	}
};

Point SegmentToVector(const Segment &s)
{ // also to point
	Point the_vector(s.b_point.x - s.a_point.x, s.b_point.y - s.a_point.y);
	return the_vector;
}

int operator^(const Point &a, const Point &b)
{
	return (a.x * b.y) - (a.y * b.x);
}

int operator*(const Point &a, const Point &b)
{
	return (a.x * b.x) + (a.y * b.y);
}

bool PointOnRay(const Point &p, const Ray &r)
{
	Ray aux_ray(r.start, p);
	bool on_line = ((r.Direction() ^ aux_ray.Direction()) == 0);
	bool sharp_angle = ((r.Direction() * aux_ray.Direction()) >= 0);
	return on_line && sharp_angle;
}

bool RaySegmentIntersection(const Ray &the_ray, const Segment &the_segment)
{
	Point s_a_to_ray_start(the_ray.start.x - the_segment.a_point.x, the_ray.start.y - the_segment.a_point.y);
	Point along_the_segment(the_segment.b_point.x - the_segment.a_point.x, the_segment.b_point.y - the_segment.a_point.y);
	Point along_the_ray(the_ray.Direction());

	int first = (s_a_to_ray_start ^ along_the_segment);
	int second = (the_ray.Direction() ^ along_the_segment);
	bool different_cross_product_signs_by_formula = (first < 0 && second > 0) || (first > 0 && second < 0);

	Point ray_start_to_a(the_segment.a_point.x - the_ray.start.x, the_segment.a_point.y - the_ray.start.y);
	Point ray_start_to_b(the_segment.b_point.x - the_ray.start.x, the_segment.b_point.y - the_ray.start.y);
	int ray_to_a_angle = (along_the_ray ^ ray_start_to_a);
	int ray_to_b_angle = (along_the_ray ^ ray_start_to_b);

	bool different_angle_signs = (ray_to_a_angle < 0 && ray_to_b_angle > 0) || (ray_to_a_angle > 0 && ray_to_b_angle < 0);

	return different_cross_product_signs_by_formula && different_angle_signs;
}

bool PointInsidePolygon(const Point &p, Polygon &s) 
{
	if (!s.points_connected)
	{
		s.ConnectPoints();
	}
	int amount_of_intersections = 0;

	Ray horizontal_from_point(p, Point(p.x + 1, p.y));

	for (size_t i = 0; i < s.segments.size(); ++i)
	{
		if(RaySegmentIntersection(horizontal_from_point, s.segments[i])) {
			++amount_of_intersections;
		}
	}
	
	// TODO: check points
	// for (size_t i = 0; i < s.points.size(); ++i)
	// {
		
	// }

	return amount_of_intersections % 2 == 0;
}

void Solve()
{
	int n = 0;
	int px = 0;
	int py = 0;
	cin >> n >> px >> py;
	Point pokemon(px, py);
	Polygon court;
	for (int i = 0; i < n; ++i)
	{
		int x = 0;
		int y = 0;
		cin >> x >> y;
		court.points.emplace_back(x, y);
	}
	court.ConnectPoints();
	court.PrintSegments();
	if (PointInsidePolygon(pokemon, court))
	{
		cout << "YES" << '\n';
	}
	else
	{
		cout << "NO" << '\n';
	}
}

int main()
{
	Solve();
	return 0;
}
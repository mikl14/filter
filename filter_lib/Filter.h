#pragma once
#include "iostream"
#include <list>
#include <string>

class point
{
public:
	std::string sensor;
	float X;
	float Y;
	float Z;
	point()
	{
		sensor = '-';
		X = 0;
		Y = 0;
		Z = 0;
	}
	point(std::string sens, float x, float y, float z)
	{
		sensor = sens;
		X = x;
		Y = y;
		Z = z;
	}

	point operator += (point p1)
	{
		X += p1.X;
		Y += p1.Y;
		Z += p1.Z;
		return *this;
	}

	point operator /= (int i)
	{
		X /= i;
		Y /= i;
		Z /= i;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& stream, const point& point)
	{
		return stream << point.sensor << " " << point.X << " " << point.Y << " " << point.Z;
	}
	void SetPoint(std::string sens, float x, float y, float z)
	{
		sensor = sens;
		X = x;
		Y = y;
		Z = z;
	}
};


class filter
{
private:
	int strength = 2;

	std::list <point> Str_parce(std::string points_str)
	{
		std::list <point> point_list;
		point dot;
		std::string sensor, X, Y, Z;
		while (points_str.length() != 0)
		{
			if (points_str.find("sensor") == -1) break;
			//dot.SetPoint(points_str.substr(points_str.find("sensor") + 10, 4), 1, 1, 2);
			sensor = points_str.substr(points_str.find("sensor") + 10, 4);
			points_str.erase(0, points_str.find("sensor") + 10);
			X = points_str.substr(points_str.find("point':") + 9, 17);
			points_str.erase(0, points_str.find(X) + X.length());
			Y = points_str.substr(points_str.find(',') + 2, 17);
			points_str.erase(0, points_str.find(Y) + Y.length());
			Z = points_str.substr(points_str.find(',') + 2, 17);
			points_str.erase(0, points_str.find(Z) + Z.length());

			dot.SetPoint(sensor, stof(X), stof(Y), stof(Z));
			point_list.push_back(dot);
		}
		return point_list;
	}

	std::list <point> list_point_avg(std::list <point> list_point)
	{
		std::list <point> result_points_avg;
		int counter = 0;

		point newPoint;

		newPoint.SetPoint("", 0, 0, 0);
		for (point i : list_point)
		{
			newPoint += i;
			counter++;
			if (counter == strength)
			{
				newPoint /= strength;
				newPoint.sensor = i.sensor;
				result_points_avg.push_back(newPoint);
				newPoint.SetPoint("", 0, 0, 0);
				counter = 0;
			}

		}
		return result_points_avg;
	}

	std::list <point> add_list(std::list <point> l1, std::list <point> l2)
	{
		for (point i : l2)
		{
			l1.push_back(i);
		}
		return l1;
	}
	//	list <point> points_list;
public:
	void SetStrength(int local_strength)
	{
		if (local_strength % 2 == 0) strength = local_strength;
		else strength = local_strength + 1;

		if (strength > 10) strength = 10;
	}

	std::list <point> GetFiltered(std::string points_str)
	{
		std::list <point> points = Str_parce(points_str);
		std::list <point> left_points, right_points, front_points, back_points;
		for (point i : points)
		{
			if (i.sensor == "left")
			{
				left_points.push_back(i);
			}
			if (i.sensor == "righ")
			{
				right_points.push_back(i);
			}
			if (i.sensor == "fron")
			{
				front_points.push_back(i);
			}
			if (i.sensor == "back")
			{
				back_points.push_back(i);
			}

		}

		left_points = list_point_avg(left_points);
		right_points = list_point_avg(right_points);
		front_points = list_point_avg(front_points);
		back_points = list_point_avg(back_points);

		points.clear();
		points = add_list(points, left_points);
		points = add_list(points, right_points);
		points = add_list(points, front_points);
		points = add_list(points, back_points);

		return points;
	};
};
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>  // used for std::iota

// for_each - non-modifying sequence operation
void test1() {
	std::cout << "\nTest1 =============================" << std::endl;
	std::vector<int> nums{ 10,20,30,40,50 };

	std::for_each(nums.begin(), nums.end(), [](int num) {
		std::cout << num << " ";
		});
}

// is_permutation - non-modifying sequence operation
// tests whether two triangles are equivalent
// triangles are defined by a vector of three points in any order
// regardles of the order of points, if two triangles contain the same three points
// then they are equivalent
void test2() {
	std::cout << "\n\nTest2 ============================" << std::endl;

	struct Point {
		int x;
		int y;
	};

	Point pt1{ 1,2 };
	Point pt2{ 4,3 };
	Point pt3{ 3,5 };
	Point pt4{ 3,1 };

	std::vector<Point> triangle1{ pt1, pt2, pt3 };
	std::vector<Point> triangle2{ pt2,pt3,pt1 };
	std::vector<Point> triangle3{ pt1,pt2,pt4 };

	// test whether triangle1 and triangle2 are equivalent
	if (std::is_permutation(triangle1.begin(),
		triangle1.end(),
		triangle2.begin(),
		[](Point lhs, Point rhs) {
			return lhs.x == rhs.x && lhs.y == rhs.y;
		})) {
		std::cout << "Triangle1 and Triangle2 are equivalent!" << std::endl;
	}
	else {
		std::cout << "Triangle1 and Triangle2 are not equivalent!" << std::endl;
	}

	// test whether triangle1 and triangle2 are equivalent
	if (std::is_permutation(triangle1.begin(),
		triangle1.end(),
		triangle3.begin(),
		[](Point lhs, Point rhs) {return lhs.x == rhs.x && lhs.y == rhs.y; }
	)) {
		std::cout << "Triangle1 and Triangle3 are equivalent!" << std::endl;
	}
	else {
		std::cout << "Triangle1 and Triangle3 are not equivalent!" << std::endl;
	}
}

void test3() {
	std::cout << "\nTest3 =========================" << std::endl;

	std::vector<int> test_scores{ 93,88,75,68,65 };
	int bonus_points{ 5 };

	std::transform(test_scores.begin(),
		test_scores.end(),
		test_scores.begin(),
		[bonus_points](int score) {return score += bonus_points; }
	);

	// display updated test_scores
	for (int score : test_scores){
		std::cout << score << " ";
	}
}

// remove_if - modifying sequence operator
void test4() {
	std::cout << "\n\nTest4 ===========================" << std::endl;

	std::vector<int> nums{ 1,2,3,4,5 };

	nums.erase(std::remove_if(nums.begin(), nums.end(),
		[](int num) {return num % 2 == 0; }
	), nums.end());

	// display update nums
	for (int num : nums) {
		std::cout << num << " ";
	}
}



int main() {
	test1();
	test2();
	test3();
	test4();

	return 0;
}
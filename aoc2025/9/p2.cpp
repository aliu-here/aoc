#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

std::vector<std::string> split(const std::string s, const std::string delimiter) 
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }
    res.push_back(s.substr (pos_start));
    return res;
}

struct rect
{
    long long left, top, right, bottom;
};

struct segment
{
    std::array<long long, 2> range;
    long long y;
};

long long area(rect r) {
    return (r.right - r.left) * (r.top - r.bottom);
}

void print_rect(rect rect) {
    std::cout << "bottom: " << rect.bottom << ", top: " << rect.top << ", left: " << rect.left << ", right: " << rect.right << '\n';
}

long long rect_int_area(rect a, rect b) {
    rect intersect;
    intersect.left = std::max(a.left, b.left);
    intersect.right = std::min(a.right, b.right);
    intersect.bottom = std::max(a.bottom, b.bottom);
    intersect.top = std::min(a.top, b.top);

//    std::cout << "intersect: ";
//    print_rect(intersect);

    if (intersect.left < intersect.right && intersect.bottom < intersect.top) {
        return area(intersect);
    }
    return 0;
}

int main()
{
    std::ifstream in("input.txt");
    std::vector<std::string> lines;
    std::string line;
    while (getline(in, line)) {
        lines.push_back(line);
    }

    auto start = std::chrono::steady_clock::now();
    long long out = 0;
    
    std::vector<std::array<long long, 2>> points;
    for (std::string line : lines) {
        auto tmp = split(line, ",");
        points.push_back({std::stol(tmp[0]), std::stol(tmp[1])});
    }

    std::vector<segment> segments;
    for (int i=0; i<points.size(); i++) {
        int next = (i + 1) % points.size();
        if (points[next][1] == points[i][1]) {
            segment seg;
            seg.range = {std::min(points[next][0], points[i][0]),
                         std::max(points[next][0], points[i][0])};
            seg.y = points[next][1];
            segments.push_back(seg);
        }
    }


    std::sort(points.begin(), points.end(), [](std::array<long long, 2> a, std::array<long long, 2> b) {
                return a[0] < b[0];
            });

    std::sort(segments.begin(), segments.end(), [](segment a, segment b) {
                return a.range[0] == b.range[0] ? (a.range[0] < b.range[0]) : a.y < b.y;
            });

    std::vector<rect> rectangles;
    std::vector<segment> curr_segs;
    int last_x = 0;
    bool first = 0;
    int rect_count = 0;
    for (auto point : points) {
        if (point[0] <= last_x) {
            continue;
        }

        std::array<long long, 2> range = {last_x, point[0] - 1};
        last_x = point[0];

        if (curr_segs.size() > 1) {
            rect tmp;
            for (int i=0; i<curr_segs.size(); i += 2) {
                if (first) {
                    tmp.left = range[0];
                } else {
                    tmp.left = range[0] - 1;
                }
                tmp.right = range[1];
                tmp.top = curr_segs[i+1].y + 1;
                tmp.bottom = curr_segs[i].y;
                rectangles.push_back(tmp);
            }
            first = false;
        }
        
        std::vector<segment> next_curr_segs;
        for (int i=0; i<segments.size(); i++) {
            if (segments[i].range[0] == point[0]) {
                next_curr_segs.push_back(segments[i]);
            }
        }
        for (auto seg : curr_segs) {
            if (seg.range[1] > point[0]) {
                next_curr_segs.push_back(seg);
            }
        }

        if (next_curr_segs.size() == 0) {
            rect tmp;
            for (int i=0; i<curr_segs.size(); i += 2) {
                tmp.left = point[0] - 1;
                tmp.right = point[0] + 1;
                tmp.top = curr_segs[i+1].y + 1;
                tmp.bottom = curr_segs[i].y;
            }
            rectangles.push_back(tmp);
        }

        curr_segs = next_curr_segs;
        std::sort(curr_segs.begin(), curr_segs.end(), [](segment a, segment b) {
                    return a.y < b.y;
                });
    }

    for (int i=0; i<points.size(); i++) {
        for (int j=i + 1; j<points.size(); j++) {
            rect rectangle;
            rectangle.left = std::min(points[i][0], points[j][0]);
            rectangle.right = std::max(points[i][0], points[j][0]) + 1;
            rectangle.bottom = std::min(points[i][1], points[j][1]);
            rectangle.top = std::max(points[i][1], points[j][1]) + 1;

            long long total_int = 0;
            for (auto rect : rectangles) {
                total_int += rect_int_area(rectangle, rect);
            }
            
            if (total_int == area(rectangle)) {
                out = std::max(area(rectangle), out);
            }
        }
    }


    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us " << '\n';
    std::cout << out << '\n';
}

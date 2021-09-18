//
// Created by artem on 18.09.2021.
//

#ifndef TEST_PROBLEM_DOT_H
#define TEST_PROBLEM_DOT_H


class Dot {
protected:
    int x{}, y{};
public:
    Dot(int x, int y);

    Dot() = default;

    [[nodiscard]] int get_x() const;

    [[nodiscard]] int get_y() const;

};


#endif //TEST_PROBLEM_DOT_H

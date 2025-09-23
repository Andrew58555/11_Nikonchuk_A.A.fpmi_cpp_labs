#include <catch.hpp>

#include <matrix.h>

#include <sstream>
#include <vector>

template <size_t M, size_t N, typename Field>
void CheckMatrix(const Matrix<M, N, Field>& actual,
                 const std::vector<std::vector<Field>>& expected) {
    REQUIRE(M == expected.size());
    REQUIRE(N == expected[0].size());
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            REQUIRE(actual(i, j) == expected[i][j]);
        }
    }
}

template <size_t N, typename Field>
void CheckIdentityMatrix(const Matrix<N, N, Field>& matrix) {
    Field field_zero = Field(0);
    Field field_one = Field(1);
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (i == j) {
                REQUIRE(matrix(i, j) == field_one);
            } else {
                REQUIRE(matrix(i, j) == field_zero);
            }
        }
    }
}

template <typename T>
void CheckVectors(const std::vector<T>& actual, const std::vector<T>& expected) {
    REQUIRE(actual.size() == expected.size());
    for (size_t i = 0; i < actual.size(); ++i) {
        REQUIRE(actual[i] == expected[i]);
    }
}

TEST_CASE("defaut_constructible", "[matrix]") {

    STATIC_REQUIRE(std::is_default_constructible_v<Matrix<3, 3, int>>);
    STATIC_REQUIRE(!std::is_default_constructible_v<Matrix<3, 4, int>>);

    STATIC_REQUIRE(std::is_default_constructible_v<Matrix<3, 3>>);
    STATIC_REQUIRE(!std::is_default_constructible_v<Matrix<3, 4>>);

    STATIC_REQUIRE(std::is_default_constructible_v<SquareMatrix<3, int>>);

    STATIC_REQUIRE(std::is_default_constructible_v<SquareMatrix<3>>);

    {
        Matrix<2, 2, int> matrix;
        CheckIdentityMatrix(matrix);
    }

    {
        SquareMatrix<10, int64_t> matrix;
        CheckIdentityMatrix(matrix);
    }
}

TEST_CASE("vector_constructible", "[matrix]") {
    {
        std::vector<std::vector<int>> v_matrix = {{1, 2}, {4, 5}, {7, 8}};
        Matrix<3, 2, int> matrix(v_matrix);
        CheckMatrix(matrix, v_matrix);
    }
    {
        std::vector<std::vector<double>> v_matrix = {{1.0, 2.0, 3.4}, {4.7, 5.0, 6.2}};
        Matrix<2, 3, double> matrix(v_matrix);
        CheckMatrix(matrix, v_matrix);
    }
    {
        std::vector<std::vector<int>> v_matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        SquareMatrix<3, int> matrix(v_matrix);
        CheckMatrix(matrix, v_matrix);
    }
    {
        std::vector<std::vector<int>> v_matrix = {{1, 2, 3}, {4, 5, 6}};
        Matrix<2, 3, int64_t> matrix(v_matrix);
        CheckMatrix(matrix, std::vector<std::vector<int64_t>>{{1, 2, 3}, {4, 5, 6}});
    }
    {
        std::vector<std::vector<int>> v_matrix = {{1, 2, 3}, {4, 5, 6}};
        Matrix<2, 3> matrix(v_matrix);
        CheckMatrix(matrix, std::vector<std::vector<Rational>>{{1, 2, 3}, {4, 5, 6}});
    }
}

TEST_CASE("comparison_tests", "[matrix]") {
    {
        std::vector<std::vector<int>> v_matrix = {{1, 2, 3}, {4, 5, 6}};
        Matrix<2, 3, int> a(v_matrix);
        Matrix<2, 3, int> b(v_matrix);
        REQUIRE(a == b);
    }
    {
        std::vector<std::vector<int>> v_matrix = {{1, 2, 3}, {4, 5, 6}};
        Matrix<2, 3, int64_t> a(v_matrix);
        Matrix<2, 3, int> b(v_matrix);
        REQUIRE(a == b);
    }
    {
        std::vector<std::vector<int>> v_matrix = {{1, 2, 3}, {4, 5, 6}};
        Matrix<2, 3, int> a(v_matrix);
        Matrix<2, 2, int> b;
        REQUIRE(a != b);
    }
    {
        std::vector<std::vector<int>> v_matrix_a = {{1, 2, 3}, {4, 5, 6}};
        std::vector<std::vector<int>> v_matrix_b = {{1, 2, 3}, {4, 5, 6}};
        Matrix<2, 3, int> a(v_matrix_a);
        Matrix<2, 3, int> b(v_matrix_b);
        REQUIRE(a == b);
    }
    {
        std::vector<std::vector<int>> v_matrix_a = {{1, 2, 3}, {4, 5, 6}};
        std::vector<std::vector<int>> v_matrix_b = {{1, 2, 3}, {4, 5, 6}};
        Matrix<2, 3, int> a(v_matrix_a);
        Matrix<2, 3, int64_t> b(v_matrix_b);
        REQUIRE(a == b);
    }
    {
        std::vector<std::vector<int>> v_matrix_a = {{1, 2, 3}, {4, 5, 6}};
        std::vector<std::vector<int>> v_matrix_b = {{1, 2, 3}, {4, 5, 6}};
        Matrix<2, 3, int> a(v_matrix_a);
        Matrix<2, 3> b(v_matrix_b);
        REQUIRE(a == b);
    }
    {
        std::vector<std::vector<int>> v_matrix_a = {{1, 2, 3}, {4, 5, 6}};
        std::vector<std::vector<int>> v_matrix_b = {{1, 2, 3}, {5, 5, 6}};
        Matrix<2, 3, int> a(v_matrix_a);
        Matrix<2, 3> b(v_matrix_b);
        REQUIRE(a != b);
    }
}

TEST_CASE("arithmetic_tests", "[matrix]") {
    std::vector<std::vector<int>> v_matrix = {{1, 2, 3}, {4, 5, 6}};
    Matrix<2, 3, int> a(v_matrix);
    Matrix<2, 3, int> b(v_matrix);

    // +, -, +=, -=
    CheckMatrix(a + a, std::vector<std::vector<int>>{{2, 4, 6}, {8, 10, 12}});
    CheckMatrix(a - a, std::vector<std::vector<int>>{{0, 0, 0}, {0, 0, 0}});

    CheckMatrix(Matrix<3, 3>() + Matrix<3, 3>(),
                std::vector<std::vector<Rational>>{{2, 0, 0}, {0, 2, 0}, {0, 0, 2}});

    CheckMatrix(SquareMatrix<3>() + SquareMatrix<3>(),
                std::vector<std::vector<Rational>>{{2, 0, 0}, {0, 2, 0}, {0, 0, 2}});

    CheckMatrix(Matrix<3, 3, double>() - Matrix<3, 3, double>(),
                std::vector<std::vector<double>>{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});

    CheckMatrix(SquareMatrix<3, int>() - SquareMatrix<3, int>(),
                std::vector<std::vector<int>>{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});

    a += b;
    CheckMatrix(a, std::vector<std::vector<int>>{{2, 4, 6}, {8, 10, 12}});
    a += a;
    CheckMatrix(a, std::vector<std::vector<int>>{{4, 8, 12}, {16, 20, 24}});
    a -= b;
    CheckMatrix(a, std::vector<std::vector<int>>{{3, 6, 9}, {12, 15, 18}});
    a -= a;
    CheckMatrix(a, std::vector<std::vector<int>>{{0, 0, 0}, {0, 0, 0}});
    a += b;
    CheckMatrix(a, std::vector<std::vector<int>>{{1, 2, 3}, {4, 5, 6}});

    // *(Field), *=(Field)
    CheckMatrix(a * 1, v_matrix);
    CheckMatrix(a * 2, std::vector<std::vector<int>>{{2, 4, 6}, {8, 10, 12}});
    CheckMatrix(a * 3, std::vector<std::vector<int>>{{3, 6, 9}, {12, 15, 18}});
    a *= 1;
    CheckMatrix(a, std::vector<std::vector<int>>{{1, 2, 3}, {4, 5, 6}});
    a *= 5;
    CheckMatrix(a, std::vector<std::vector<int>>{{5, 10, 15}, {20, 25, 30}});

    // *, *=
    CheckIdentityMatrix(SquareMatrix<3>() * SquareMatrix<3>());
    CheckIdentityMatrix(SquareMatrix<5>() * SquareMatrix<5>());
    CheckIdentityMatrix(SquareMatrix<10>() * SquareMatrix<10>());
    CheckIdentityMatrix(SquareMatrix<100>() * SquareMatrix<100>());
    // CheckIdentityMatrix(SquareMatrix<500>() * SquareMatrix<500>());

    Matrix<3, 2, int> c(std::vector<std::vector<int>>{{1, 4}, {2, 5}, {3, 6}});
    REQUIRE(std::is_same_v<decltype(b * c), Matrix<2, 2, int>>);
    CheckMatrix(b * c, std::vector<std::vector<int>>{{14, 32}, {32, 77}});

    REQUIRE(std::is_same_v<decltype(c * b), Matrix<3, 3, int>>);
    CheckMatrix(c * b, std::vector<std::vector<int>>{{17, 22, 27}, {22, 29, 36}, {27, 36, 45}});

    std::vector<std::vector<Rational>> d_matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<3, 3> d(d_matrix);
    d *= SquareMatrix<3>{};
    CheckMatrix(d, d_matrix);
    d *= d;
    CheckMatrix(d, std::vector<std::vector<Rational>>{{30, 36, 42}, {66, 81, 96}, {102, 126, 150}});
    d *= SquareMatrix<3>{};
    CheckMatrix(d, std::vector<std::vector<Rational>>{{30, 36, 42}, {66, 81, 96}, {102, 126, 150}});
}

TEST_CASE("determinant_tests", "[matrix]") {

    {
        Matrix<10, 10, int> m;
        REQUIRE(m.det() == 1);  // 1
    }

    {
        Matrix<2, 2, int> m(std::vector<std::vector<int>>{{1, 2}, {3, 4}});
        REQUIRE(m.det() == -2);  // -2
    }

    {
        Matrix<2, 2, int> m(std::vector<std::vector<int>>{{21, 1}, {3, 4}});
        REQUIRE(m.det() == 81);  // 81
    }

    {
        Matrix<3, 3, int> m(std::vector<std::vector<int>>{{1, 2, 3}, {0, 0, 0}, {5, 4, 3}});
        REQUIRE(m.det() == 0);  // 0
    }

    {
        Matrix<3, 3> m(std::vector<std::vector<Rational>>{{1, -3, 4}, {2, 5, -3}, {4, -2, 7}});
        REQUIRE(m.det() == Rational(11));  // 11
    }

    {
        Matrix<4, 4, int> m(std::vector<std::vector<int>>{
            {1, 2, 3, 4}, {5, 7, 3, 5}, {6, 8, 7, 6}, {11, -2, 6, 9}});
        REQUIRE(m.det() == -861);  // -861
    }

    {
        Matrix<100, 100, int> m;
        REQUIRE(m.det() == 1);  // 1
    }

    //{
    //    Matrix<500, 500, int> m;
    //    REQUIRE(m.det() == 1); // 1
    //}
}

TEST_CASE("transposed_tests", "[matrix]") {
    Matrix<2, 3, int> a(std::vector<std::vector<int>>{{1, 2, 3}, {4, 5, 6}});
    STATIC_REQUIRE(std::is_same_v<decltype(a.transposed()), Matrix<3, 2, int>>);
    CheckMatrix(a.transposed(), std::vector<std::vector<int>>{{1, 4}, {2, 5}, {3, 6}});

    SquareMatrix<100> e;
    CheckIdentityMatrix(e.transposed());
}

TEST_CASE("rank_tests", "[matrix]") {
    {
        Matrix<2, 3, int> m(std::vector<std::vector<int>>{{1, 2, 4}, {4, 5, 6}});
        REQUIRE(m.rank() == 2u);
    }
    {
        Matrix<3, 2, int> m(std::vector<std::vector<int>>{{1, 2}, {2, 4}, {3, 6}});
        REQUIRE(m.rank() == 1u);
    }
    {
        Matrix<3, 2> m(std::vector<std::vector<int>>{{2, 3}, {4, 6}, {6, 7}});
        REQUIRE(m.rank() == 2u);
    }
    {
        Matrix<3, 2, int> m(std::vector<std::vector<int>>{{1, 2}, {2, 3}, {4, 5}});
        REQUIRE(m.rank() == 2u);
    }
    {
        Matrix<3, 3, int> m(std::vector<std::vector<int>>{{1, 2, 3}, {2, 4, 6}, {3, 6, 9}});
        REQUIRE(m.rank() == 1u);
    }
    {
        Matrix<3, 3, int> m(std::vector<std::vector<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        REQUIRE(m.rank() == 2u);
    }
    {
        const Matrix<3, 3> m(std::vector<std::vector<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 7}});
        REQUIRE(m.rank() == 3u);
    }
    {
        SquareMatrix<100> m;
        REQUIRE(m.rank() == 100u);
    }
    {
        const SquareMatrix<100> m;
        REQUIRE(m.rank() == 100u);
    }
    {
        Matrix<3, 4, int> m3(
            std::vector<std::vector<int>>{{1, 2, 3, 4}, {1, 2, 7, 9}, {1, 2, 7, 8}});
        REQUIRE(m3.rank() == 3u);
    }
    {
        Matrix<3, 4, int> m3(
            std::vector<std::vector<int>>{{1, 2, 3, 4}, {1, 2, 7, 9}, {1, 2, 7, 9}});
        REQUIRE(m3.rank() == 2u);
    }
    {
        Matrix<3, 4, int> m3(
            std::vector<std::vector<int>>{{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}});
        REQUIRE(m3.rank() == 1u);
    }
}

TEST_CASE("trace_tests", "[matrix]") {
    {
        Matrix<3, 3, int> m(std::vector<std::vector<int>>{{1, 2, 3}, {2, 4, 6}, {3, 6, 9}});
        REQUIRE(m.trace() == 14);
    }
    {
        Matrix<3, 3, int> m(std::vector<std::vector<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        REQUIRE(m.trace() == 15);
    }
    {
        const Matrix<3, 3> m(std::vector<std::vector<int>>{{0, 2, 3}, {14, 5, 6}, {27, 8, 7}});
        REQUIRE(m.trace() == Rational(12));
    }
    {
        SquareMatrix<100> m;
        REQUIRE(m.trace() == Rational(100));
    }
    {
        const SquareMatrix<100> m;
        REQUIRE(m.trace() == Rational(100));
    }
}

TEST_CASE("invert_tests", "[matrix]") {
    {
        SquareMatrix<3> m;
        CheckIdentityMatrix(m.inverted());
        m.invert();
        CheckIdentityMatrix(m);
    }
    {
        SquareMatrix<10> m;
        CheckIdentityMatrix(m.inverted());
        m.invert();
        CheckIdentityMatrix(m);
    }
    {
        SquareMatrix<50> m;
        CheckIdentityMatrix(m.inverted());
        m.invert();
        CheckIdentityMatrix(m);
    }
    {
        Matrix<3, 3> m(std::vector<std::vector<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 7}});
        CheckIdentityMatrix(m * m.inverted());
        CheckMatrix(m.inverted(), std::vector<std::vector<Rational>>{{{-13, 6}, {5, 3}, {-1, 2}},
                                                                     {{7, 3}, {-7, 3}, {1, 1}},
                                                                     {{-1, 2}, {1, 1}, {-1, 2}}});
        m.invert();
        CheckMatrix(m, std::vector<std::vector<Rational>>{{{-13, 6}, {5, 3}, {-1, 2}},
                                                          {{7, 3}, {-7, 3}, {1, 1}},
                                                          {{-1, 2}, {1, 1}, {-1, 2}}});
    }
    {
        Matrix<3, 3, int> m(std::vector<std::vector<int>>{{2, 1, 1}, {3, 2, 1}, {2, 1, 2}});
        CheckIdentityMatrix(m * m.inverted());
        CheckMatrix(m.inverted(),
                    std::vector<std::vector<int>>{{3, -1, -1}, {-4, 2, 1}, {-1, 0, 1}});
        m.invert();
        CheckMatrix(m, std::vector<std::vector<int>>{{3, -1, -1}, {-4, 2, 1}, {-1, 0, 1}});
    }
}

TEST_CASE("getting_row_column_tests", "[matrix]") {
    {
        SquareMatrix<3> m;
        STATIC_REQUIRE(std::is_same_v<decltype(m.getRow(1)), std::vector<Rational>>);
        STATIC_REQUIRE(std::is_same_v<decltype(m.getColumn(1)), std::vector<Rational>>);
        for (size_t i = 0; i < 3; ++i) {
            CheckVectors(m.getRow(i), m.getColumn(i));
        }
    }
    {
        Matrix<3, 4, int> m(
            std::vector<std::vector<int>>{{1, 2, 3, 4}, {5, 6, 7, 8}, {1, 0, 1, 0}});
        CheckVectors(m.getRow(0), std::vector<int>{1, 2, 3, 4});
        CheckVectors(m.getRow(1), std::vector<int>{5, 6, 7, 8});
        CheckVectors(m.getRow(2), std::vector<int>{1, 0, 1, 0});
        CheckVectors(m.getColumn(0), std::vector<int>{1, 5, 1});
        CheckVectors(m.getColumn(1), std::vector<int>{2, 6, 0});
        CheckVectors(m.getColumn(2), std::vector<int>{3, 7, 1});
        CheckVectors(m.getColumn(3), std::vector<int>{4, 8, 0});
    }
    {
        const Matrix<4, 3, int> m(
            std::vector<std::vector<int>>{{1, 2, 3}, {5, 6, 7}, {1, 0, 1}, {2, 5, 4}});
        CheckVectors(m.getRow(0), std::vector<int>{1, 2, 3});
        CheckVectors(m.getRow(1), std::vector<int>{5, 6, 7});
        CheckVectors(m.getRow(2), std::vector<int>{1, 0, 1});
        CheckVectors(m.getRow(3), std::vector<int>{2, 5, 4});
        CheckVectors(m.getColumn(0), std::vector<int>{1, 5, 1, 2});
        CheckVectors(m.getColumn(1), std::vector<int>{2, 6, 0, 5});
        CheckVectors(m.getColumn(2), std::vector<int>{3, 7, 1, 4});
    }
}

TEST_CASE("indexes_tests", "[matrix]") {
    const Matrix<3, 4, int> m(
        std::vector<std::vector<int>>{{1, 2, 3, 4}, {5, 6, 7, 8}, {1, 0, 1, 0}});
    REQUIRE(m[0][0] == 1);
    REQUIRE(m(0, 0) == 1);
    REQUIRE(m[1][2] == 7);
    REQUIRE(m(1, 2) == 7);
    REQUIRE(m[2][3] == 0);
    REQUIRE(m(2, 3) == 0);

    SquareMatrix<3> m1(std::vector<std::vector<Rational>>{{1, 2, 0}, {0, 1, 3}, {1, 1, 1}});
    REQUIRE(m1[0][0] == 1);
    REQUIRE(m1(0, 0) == 1);
    m1[0][1] = 0;
    m1(1, 2) = 0;
    m1[2][0] = 0;
    m1(2, 1) = 0;
    CheckIdentityMatrix(m1);
}

TEST_CASE("input_output_tests", "[matrix]") {
    {
        Matrix<3, 4, int> m(std::vector<std::vector<int>>(3, std::vector<int>(4)));
        std::stringstream ss("1 2 3 4 5 6 7 8 9 10 11 12");
        ss >> m;
        CheckMatrix(m, std::vector<std::vector<int>>{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}});
    }
    {
        SquareMatrix<3, int> m(std::vector<std::vector<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        std::stringstream ss;
        ss << m;
        SquareMatrix<3, int> m1;
        ss >> m1;
        CheckMatrix(m1, std::vector<std::vector<int>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    }
}

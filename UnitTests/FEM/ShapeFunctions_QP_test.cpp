#include "../catch.hpp"
#include "FEM/ShapeFunctions/COME_ShapeFunctions_QP.hpp"

TEST_CASE("Shape function tests")
{
    ShapeFunctions::FE_QP<1> fe1(1);
    ShapeFunctions::FE_QP<1> fe2(2);
    ShapeFunctions::FE_QP<1> fe3(3);
    ShapeFunctions::FE_QP<1> fe4(4);
    ShapeFunctions::FE_QP<1> fe5(5);
    ShapeFunctions::FE_QP<1> fe6(6);
    double pol_1 = 0.0;
    double pol_2 = 0.0;
    double pol_3 = 0.0;
    double pol_4 = 0.0;
    double pol_5 = 0.0;
    double pol_6 = 0.0;

    double pol_1_2 = 0.0;
    double pol_2_2 = 0.0;
    double pol_3_2 = 0.0;
    double pol_4_2 = 0.0;
    double pol_5_2 = 0.0;
    double pol_6_2 = 0.0;

    double x_eval = 1.0;
    double x_eval_2 = -1.0;

    for (int i = 0; i < 2; i++)
    {
        pol_1 += fe1.get_shape_function_value(i, x_eval);
        pol_1_2+= fe1.get_shape_function_value(i, x_eval_2);
    }
    for (int i = 0; i < 3; i++)
    {
        pol_2 += fe2.get_shape_function_value(i, x_eval);
        pol_2_2 += fe2.get_shape_function_value(i, x_eval_2);
    }
    for (int i = 0; i < 4; i++)
    {
        pol_3 += fe3.get_shape_function_value(i, x_eval);
        pol_3_2 += fe3.get_shape_function_value(i, x_eval_2);
    }
    for (int i = 0; i < 5; i++)
    {
        pol_4 += fe4.get_shape_function_value(i, x_eval);
        pol_4_2 += fe4.get_shape_function_value(i, x_eval_2);
    }
    for (int i = 0; i < 6; i++)
    {
        pol_5 += fe5.get_shape_function_value(i, x_eval);
        pol_5_2 += fe5.get_shape_function_value(i, x_eval_2);
    }
    for (int i = 0; i < 7; i++)
    {
        pol_6 += fe6.get_shape_function_value(i, x_eval);
        pol_6_2 += fe6.get_shape_function_value(i, x_eval_2);
    }
    REQUIRE(pol_1 == Approx(1.0));
    REQUIRE(pol_2 == Approx(1.0));
    REQUIRE(pol_3 == Approx(1.0));
    REQUIRE(pol_4 == Approx(1.0));
    REQUIRE(pol_5 == Approx(1.0));
    REQUIRE(pol_6 == Approx(1.0));
    REQUIRE(pol_1_2 == Approx(1.0));
    REQUIRE(pol_2_2 == Approx(1.0));
    REQUIRE(pol_3_2 == Approx(1.0));
    REQUIRE(pol_4_2 == Approx(1.0));
    REQUIRE(pol_5_2 == Approx(1.0));
    REQUIRE(pol_6_2 == Approx(1.0));

}

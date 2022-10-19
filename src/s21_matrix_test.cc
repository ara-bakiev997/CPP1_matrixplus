#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

// int main() {
//   std::cout << "_______FIRST_matrix_______" << std::endl;
//   s21::S21Matrix mtr(3, 3);
//   mtr.init(5);
//   mtr.print();
//   //
//   //  std::cout << "_______SECOND_matrix______" << std::endl;
//   //  s21::S21Matrix mtr1(3, 3);
//   //  mtr1.init(5);
//   //  mtr1.print();
//   //
//   std::cout << "_______RESULT_matrix______" << std::endl;
//   //  mtr.operator*=(10);
//   mtr.SetRows(7);
//   mtr.SetCols(7);
//   mtr.print();
//   //  std::cout << "Cols = " << mtr.GetCols() << " Rows = " << mtr.GetRows()
//   <<
//   //  std::endl;
//   // std::cout << (mtr1 == mtr ? "\nmatrix equal\n" : "\nmatrix isn't
//   equal\n")
//   // << std::endl;

//   //	s21::S21Matrix test(3 , 3);
//   //	test.init(1);
//   //	test.print();
//   //	std::cout << "[0][0] = " << test(0, 0) << std::endl;
//   //	std::cout << "[0][0] = " << (test(0, 0) = 5) << std::endl;
//   //  int p = 5;
//   //  printf("____%p____", p);
//   //  printf("\n____%p____\n", 10);

//   return 0;
// }

TEST(SquareRootTest, NegativeNos) { ASSERT_EQ(1, 1); }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#include "mock_turtle.h"
#include "painter.cpp"

#include <gtest/gtest.h>

using testing::AtLeast;
using testing::Return;
using testing::ReturnRef;
using testing::_;
using testing::Ge;
using testing::InSequence;
using testing::AnyNumber;

TEST(PainterTest, CanDrawSomething) {
	MockTurtle turtle;
	EXPECT_CALL(turtle, PenDown())
	.Times(AtLeast(1));

	Painter painter(&turtle);

	EXPECT_TRUE(painter.DrawCircle(0, 0, 10));

}

TEST(PainterTest, CanGetX) {
	MockTurtle turtle;
	int x_pos = 0;

	EXPECT_CALL(turtle, GetX())
	.Times(5)
	.WillOnce(Return(100))
	.WillOnce(Return(150))
	.WillRepeatedly(Return(200));

	Painter painter(&turtle);

	x_pos = painter.Get_Position_X();
	EXPECT_EQ(x_pos,100);

	x_pos = painter.Get_Position_X();
	EXPECT_EQ(x_pos,150);

	x_pos = painter.Get_Position_X();
	EXPECT_EQ(x_pos,200);

	x_pos = painter.Get_Position_X();
	EXPECT_EQ(x_pos,200);

	x_pos = painter.Get_Position_X();
	EXPECT_EQ(x_pos,200);

}

TEST(PainterTest, CanForward) {
	MockTurtle turtle;

	EXPECT_CALL(turtle, Forward(100));

	Painter painter(&turtle);

	EXPECT_TRUE(painter.Move_Forward(100));

}

TEST(PainterTest, CanGoTo) {
	MockTurtle turtle;

	// Expects that the turtle jumps to somewhere on the x=50 line.
	EXPECT_CALL(turtle, GoTo(50,_));

	Painter painter(&turtle);

	EXPECT_TRUE(painter.Move_To(50,7));

}

TEST(PainterTest, CanForwardGe) {
	MockTurtle turtle;

	// Expects the turtle moves forward by at least 100
	EXPECT_CALL(turtle, Forward(Ge(100)));

	Painter painter(&turtle);

	EXPECT_TRUE(painter.Move_Forward(100));

}

TEST(PainterTest, CanForwardNoArg) {
	MockTurtle turtle;

	// Expects the turtle to move forward.
	EXPECT_CALL(turtle, Forward);

	Painter painter(&turtle);

	EXPECT_TRUE(painter.Move_Forward(100));

}

TEST(PainterTest, CanGoToNoArg) {
	MockTurtle turtle;

	// Expects that the turtle to jump somewhere.
	EXPECT_CALL(turtle, GoTo);

	Painter painter(&turtle);

	EXPECT_TRUE(painter.Move_To(50,7));

}

TEST(PainterTest, CanGetXWillOnce) {
	MockTurtle turtle;
	int x_pos = 0;

	EXPECT_CALL(turtle, GetX())
	.WillOnce(Return(100))
	.WillOnce(Return(200))
	.WillOnce(Return(300));

	Painter painter(&turtle);

	x_pos = painter.Get_Position_X();
	EXPECT_EQ(x_pos,100);

	x_pos = painter.Get_Position_X();
	EXPECT_EQ(x_pos,200);

	x_pos = painter.Get_Position_X();
	EXPECT_EQ(x_pos,300);

}

TEST(PainterTest, CanGetYWillOnce) {
	MockTurtle turtle;
	int y_pos = 0;

	EXPECT_CALL(turtle, GetY())
	.WillOnce(Return(100))
	.WillOnce(Return(200))
	.WillRepeatedly(Return(300));

	Painter painter(&turtle);

	y_pos = painter.Get_Position_Y();
	EXPECT_EQ(y_pos,100);

	y_pos = painter.Get_Position_Y();
	EXPECT_EQ(y_pos,200);

	y_pos = painter.Get_Position_Y();
	EXPECT_EQ(y_pos,300);

}

TEST(PainterTest, CanGetXDefaultAction) {
	MockTurtle turtle;
	int x_pos = 0;

	EXPECT_CALL(turtle, GetX())
	.Times(5)
	.WillOnce(Return(100))
	.WillOnce(Return(150))
	.WillOnce(Return(200));

	Painter painter(&turtle);

	x_pos = painter.Get_Position_X();
	EXPECT_EQ(x_pos,100);

	x_pos = painter.Get_Position_X();
	EXPECT_EQ(x_pos,150);

	x_pos = painter.Get_Position_X();
	EXPECT_EQ(x_pos,200);

	x_pos = painter.Get_Position_X();
	EXPECT_EQ(x_pos,0);

	x_pos = painter.Get_Position_X();
	EXPECT_EQ(x_pos,0);

}

TEST(PainterTest, CanGetXSideEffects) {
	MockTurtle turtle;
	int x_pos = 0;
	int n = 100;

	EXPECT_CALL(turtle, GetX())
	.Times(4)
	.WillRepeatedly(Return(n++));

	Painter painter(&turtle);

	x_pos = painter.Get_Position_X();
	EXPECT_EQ(x_pos,100);

	x_pos = painter.Get_Position_X();
	EXPECT_EQ(x_pos,100);

	x_pos = painter.Get_Position_X();
	EXPECT_EQ(x_pos,100);

	x_pos = painter.Get_Position_X();
	EXPECT_EQ(x_pos,100);

}

TEST(PainterTest, CanForwardMultipleExpectations) {
	MockTurtle turtle;

	// Expects the turtle to move forward.
	EXPECT_CALL(turtle, Forward(_)); // #1
	EXPECT_CALL(turtle, Forward(10))
	.Times(2); // #2

	Painter painter(&turtle);

	EXPECT_TRUE(painter.Move_Forward(10));
	EXPECT_TRUE(painter.Move_Forward(10));
	// EXPECT_TRUE(painter.Move_Forward(10));  // Error if replace with the line below.
	EXPECT_TRUE(painter.Move_Forward(20));

}

TEST(PainterTest, CanFooOrderedCalls) {
	//DrawsLineSegment
	MockTurtle turtle;

	{
		InSequence seq;

		EXPECT_CALL(turtle, PenDown()); // #1
		EXPECT_CALL(turtle, Forward(100)); // #2
		EXPECT_CALL(turtle, PenUp()); // #2
	}

	Painter painter(&turtle);

	EXPECT_TRUE(painter.Foo());
}

TEST(PainterTest, CanGoToSticky) {
	MockTurtle turtle;


	EXPECT_CALL(turtle, GoTo(_,_))  // #1
	.Times(AnyNumber());

	EXPECT_CALL(turtle, GoTo(0,0))  // #2
	.Times(2);


	Painter painter(&turtle);

	EXPECT_TRUE(painter.Move_To(10,0));
	EXPECT_TRUE(painter.Move_To(0,0));
	EXPECT_TRUE(painter.Move_To(0,0));
	EXPECT_TRUE(painter.Move_To(10,5));

}

TEST(PainterTest, CanGetXRetire1) {
	MockTurtle turtle;
	int x_pos = 0;
	int n = 10;

	for (int i = n; i > 0; i--) {
		EXPECT_CALL(turtle, GetX())  // #1
	  	  			  .WillOnce(Return(10*i))  // Comment follwing line to the error.
					  .RetiresOnSaturation();
	}

	Painter painter(&turtle);

	for (int i = 1; i <= n; i++) {
		x_pos = painter.Get_Position_X();
		EXPECT_EQ(x_pos,10*i);
	}

}

TEST(PainterTest, CanGetXRetire2) {
	MockTurtle turtle;
	int x_pos = 0;
	int n = 10;

	{

		InSequence s;
		for (int i = 1; i <= n; i++) {
			EXPECT_CALL(turtle, GetX())  // #1
	  	  			  .WillOnce(Return(10*i))
					  .RetiresOnSaturation();
		}
	}

	Painter painter(&turtle);

	for (int i = 1; i <= n; i++) {
		x_pos = painter.Get_Position_X();
		EXPECT_EQ(x_pos,10*i);
	}

}

int main(int argc, char** argv) {
	// The following line must be executed to initialize Google Mock
	// (and Google Test) before running the tests.
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}

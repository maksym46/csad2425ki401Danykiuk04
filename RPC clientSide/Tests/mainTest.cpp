#include <gtest/gtest.h>
#include <string>


std::string determineWinner(const std::string& clientMove, const std::string& serverMove) {
    if (clientMove == serverMove) return "Draw";
    if ((clientMove == "Rock" && serverMove == "Scissors") ||
        (clientMove == "Paper" && serverMove == "Rock") ||
        (clientMove == "Scissors" && serverMove == "Paper")) {
        return "Client wins!";
    }
    else {
        return "Server wins!";
    }
}


TEST(RockPaperScissorsTest, TestClientRockServerScissors) {
    EXPECT_EQ(determineWinner("Rock", "Scissors"), "Client wins!");
}

TEST(RockPaperScissorsTest, TestClientRockServerPaper) {
    EXPECT_EQ(determineWinner("Rock", "Paper"), "Server wins!");
}

TEST(RockPaperScissorsTest, TestClientRockServerRock) {
    EXPECT_EQ(determineWinner("Rock", "Rock"), "Draw");
}

TEST(RockPaperScissorsTest, TestClientPaperServerRock) {
    EXPECT_EQ(determineWinner("Paper", "Rock"), "Client wins!");
}

TEST(RockPaperScissorsTest, TestClientPaperServerScissors) {
    EXPECT_EQ(determineWinner("Paper", "Scissors"), "Server wins!");
}

TEST(RockPaperScissorsTest, TestClientPaperServerPaper) {
    EXPECT_EQ(determineWinner("Paper", "Paper"), "Draw");
}

TEST(RockPaperScissorsTest, TestClientScissorsServerPaper) {
    EXPECT_EQ(determineWinner("Scissors", "Paper"), "Client wins!");
}

TEST(RockPaperScissorsTest, TestClientScissorsServerRock) {
    EXPECT_EQ(determineWinner("Scissors", "Rock"), "Server wins!");
}

TEST(RockPaperScissorsTest, TestClientScissorsServerScissors) {
    EXPECT_EQ(determineWinner("Scissors", "Scissors"), "Draw");
}

TEST(RockPaperScissorsTest, TestInvalidMove) {
    EXPECT_NE(determineWinner("InvalidMove", "Rock"), "Client wins!");  
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

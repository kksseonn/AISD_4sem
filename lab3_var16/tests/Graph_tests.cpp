#include <Graph/Graph.h>
#include <gtest/gtest.h>


TEST(GraphTest, HasVertex) {
    Graph<int> g;
    g.add_vertex(1);

    EXPECT_TRUE(g.has_vertex(1));
    EXPECT_FALSE(g.has_vertex(2));
}

TEST(GraphTest, AddVertex) {
    Graph<int> g;
    g.add_vertex(1);

    EXPECT_TRUE(g.has_vertex(1));
    EXPECT_THROW(g.add_vertex(1), std::invalid_argument);
}

TEST(GraphTest, RemoveVertex) {
    Graph<int> g;
    g.add_vertex(1);

    EXPECT_TRUE(g.has_vertex(1));
    EXPECT_TRUE(g.remove_vertex(1));
    EXPECT_FALSE(g.has_vertex(1));
    EXPECT_FALSE(g.remove_vertex(1));
}

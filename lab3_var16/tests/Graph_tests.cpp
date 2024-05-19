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

TEST(GraphTest, AddEdge) {
    Graph<int> g;
    g.add_vertex(1);
    g.add_vertex(2);

    g.add_edge(1, 2, 5.0);

    EXPECT_TRUE(g.has_edge(1, 2));
    EXPECT_THROW(g.add_edge(1, 2, 3.0), std::invalid_argument);
}

TEST(GraphTest, RemoveEdge) {
    Graph<int> g;
    g.add_vertex(1);
    g.add_vertex(2);

    g.add_edge(1, 2, 5.0);

    EXPECT_TRUE(g.has_edge(1, 2));
    EXPECT_TRUE(g.remove_edge(1, 2));
    EXPECT_FALSE(g.has_edge(1, 2));
    EXPECT_FALSE(g.remove_edge(1, 2));
}

TEST(GraphTest, HasEdge) {
    Graph<int> g;
    g.add_vertex(1);
    g.add_vertex(2);
    g.add_vertex(3);

    g.add_edge(1, 2, 5.0);

    EXPECT_TRUE(g.has_edge(1, 2));
    EXPECT_FALSE(g.has_edge(2, 1));
    EXPECT_FALSE(g.has_edge(1, 3));
}

TEST(GraphTest, Order) {
    Graph<int> g;
    g.add_vertex(1);
    g.add_vertex(2);
    g.add_vertex(3);

    EXPECT_EQ(g.order(), 3);
}

TEST(GraphTest, Degree) {
    Graph<int> g;
    g.add_vertex(1);
    g.add_vertex(2);
    g.add_vertex(3);
    g.add_vertex(4);

    g.add_edge(1, 2, 5.0);
    g.add_edge(1, 3, 3.0);
    g.add_edge(1, 4, 2.0);

    EXPECT_EQ(g.degree(1), 3);
    EXPECT_EQ(g.degree(2), 1);
    EXPECT_EQ(g.degree(3), 1);
    EXPECT_EQ(g.degree(4), 1);
}
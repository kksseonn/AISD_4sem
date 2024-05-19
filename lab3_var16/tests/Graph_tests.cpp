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

TEST(GraphTest, ShortestPath) {
    Graph<std::string, double> g;
    g.add_vertex("A");
    g.add_vertex("B");
    g.add_vertex("C");
    g.add_vertex("D");

    g.add_edge("A", "B", 1.0);
    g.add_edge("A", "C", 1.5);
    g.add_edge("B", "D", 2.0);
    g.add_edge("C", "D", 2.5);

    EXPECT_TRUE(g.has_vertex("A"));
    EXPECT_TRUE(g.has_vertex("B"));
    EXPECT_TRUE(g.has_vertex("C"));
    EXPECT_TRUE(g.has_vertex("D"));
    EXPECT_TRUE(g.has_edge("A", "B"));
    EXPECT_TRUE(g.has_edge("A", "C"));
    EXPECT_TRUE(g.has_edge("B", "D"));
    EXPECT_TRUE(g.has_edge("C", "D"));

    std::vector<Graph<std::string, double>::Edge> path = g.shortest_path("A", "D");

    ASSERT_EQ(path.size(), 2);
    ASSERT_EQ(path[0].from, "A");
    ASSERT_EQ(path[0].to, "B");
    ASSERT_EQ(path[0].distance, 1.0);
    ASSERT_EQ(path[1].from, "B");
    ASSERT_EQ(path[1].to, "D");
    ASSERT_EQ(path[1].distance, 2.0);
}

TEST(GraphTest, Walk) {
    Graph<int> g;
    g.add_vertex(1);
    g.add_vertex(2);
    g.add_vertex(3);

    g.add_edge(1, 2, 1.0);
    g.add_edge(2, 3, 1.0);

    auto walk_result = g.walk(1);
    std::vector<int> expected_walk = { 1, 2, 3 };

    EXPECT_EQ(walk_result.size(), expected_walk.size());
    EXPECT_TRUE(std::equal(walk_result.begin(), walk_result.end(), expected_walk.begin()));

    // Тест для несуществующей вершины
    EXPECT_THROW(g.walk(4), std::invalid_argument);
}
//
// Created by voitovm on 11/6/2026.
//

 // Tests for the grid and tile model.
 // The doctest main is defined in test_main.cpp.
 #include <doctest/doctest.h>

 #include <stdexcept>

 #include "world/Grid.h"

 using eco::Grid;
 using eco::Position;
 using eco::TileType;

 DOCTEST_TEST_CASE("grid reports its dimensions") {
     Grid grid(5, 4);

     DOCTEST_CHECK(grid.getWidth() == 5);
     DOCTEST_CHECK(grid.getHeight() == 4);
 }

 DOCTEST_TEST_CASE("grid rejects non-positive dimensions") {
     DOCTEST_CHECK_THROWS_AS(Grid(0, 4), std::invalid_argument);
     DOCTEST_CHECK_THROWS_AS(Grid(5, 0), std::invalid_argument);
     DOCTEST_CHECK_THROWS_AS(Grid(-1, 4), std::invalid_argument);
     DOCTEST_CHECK_THROWS_AS(Grid(5, -1), std::invalid_argument);
 }

 DOCTEST_TEST_CASE("grid identifies positions inside and outside its bounds") {
     Grid grid(5, 4);

     DOCTEST_CHECK(grid.inBounds(Position{0, 0}));
     DOCTEST_CHECK(grid.inBounds(Position{4, 3}));
     DOCTEST_CHECK(grid.inBounds(Position{2, 1}));

     DOCTEST_CHECK_FALSE(grid.inBounds(Position{-1, 0}));
     DOCTEST_CHECK_FALSE(grid.inBounds(Position{0, -1}));
     DOCTEST_CHECK_FALSE(grid.inBounds(Position{5, 3}));
     DOCTEST_CHECK_FALSE(grid.inBounds(Position{4, 4}));
 }

 DOCTEST_TEST_CASE("new grid tiles start as dirt with no nutrients") {
     Grid grid(3, 2);
     DOCTEST_CHECK(grid.at(Position{0, 0}).type == TileType::Dirt);
     DOCTEST_CHECK(grid.at(Position{0, 0}).nutrients == doctest::Approx(0.0));
     DOCTEST_CHECK(grid.at(Position{2, 1}).type == TileType::Dirt);
     DOCTEST_CHECK(grid.at(Position{2, 1}).nutrients == doctest::Approx(0.0));
 }

 DOCTEST_TEST_CASE("grid at accesses the tile at a position") {
     Grid grid(3, 2);
     grid.at(Position{1, 0}).type = TileType::Grass;
     grid.at(Position{1, 0}).nutrients = 7.5;
     DOCTEST_CHECK(grid.at(Position{1, 0}).type == TileType::Grass);
     DOCTEST_CHECK(grid.at(Position{1, 0}).nutrients == doctest::Approx(7.5));
     DOCTEST_CHECK(grid.at(Position{0, 0}).type == TileType::Dirt);
 }

 DOCTEST_TEST_CASE("grid neighbors include valid surrounding tiles") {
     Grid grid(3, 3);


     DOCTEST_CHECK(grid.neighbors(Position{1, 1}).size() == 8);
     DOCTEST_CHECK(grid.neighbors(Position{0, 0}).size() == 3);
     DOCTEST_CHECK(grid.neighbors(Position{1, 0}).size() == 5);
 }

 DOCTEST_TEST_CASE("grid neighbors never contain out-of-bounds positions or the center") {
     Grid grid(3, 3);
     const Position center{1, 1};
     for (const Position& neighbor : grid.neighbors(center)) {
         DOCTEST_CHECK(grid.inBounds(neighbor));
         DOCTEST_CHECK((neighbor.x != center.x || neighbor.y != center.y));
     }
 }

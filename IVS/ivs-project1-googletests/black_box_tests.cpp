//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     MAREK SUCHARDA <xsucha18@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author MAREK SUCHARDA
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//


//** EMPTY TREE TESTY **//
// vytvarim prazdny strom
class EmptyTree : public ::testing::Test
{
protected: 
    BinaryTree tree;
};

TEST_F(EmptyTree, InsertNode) {
    // pokud uzel jeste neexistuje - vytvarim prvni s hodnotou 3
    auto insert = tree.InsertNode( 3 ); 
    EXPECT_TRUE(insert.first); 
    EXPECT_EQ(insert.second->key, 3); 

    // uzel s hodnotou 3 uz existuje, zkousim ho pridat znova a ocekavam false 
    auto insert2 = tree.InsertNode( 3 ); 
    EXPECT_FALSE(insert2.first); 
    EXPECT_EQ(insert.second->key, 3); 
}

TEST_F(EmptyTree, DeleteNode) {
    // pridam novej uzel s hodnotou 5, overim ze se pridal
    auto insert = tree.InsertNode( 5 ); 
    EXPECT_TRUE(insert.first); 

    // uzel s hodnotou 5 najdu a odstranim, ocekavam true 
    auto del = tree.DeleteNode( 5 ); 
    EXPECT_TRUE(del); 

    // snazim se smazat uzel s hodnotou kterou jsem neinsertnul, ocekavam false - uzel nenalezen
    auto del2 = tree.DeleteNode( 6 ); 
    EXPECT_FALSE(del2); 
}

TEST_F(EmptyTree, FindNode) {
    // pridam novej uzel s hodnotou 6, overim ze se pridal
    auto insert = tree.InsertNode( 6 ); 
    EXPECT_TRUE(insert.first); 

    // jdu ho najit, ocekavam true pac existuje
    auto find = tree.FindNode( 6 ); 
    EXPECT_TRUE(find); 

    // zkusim najit neexistujici, ocekavam NULL 
    auto find2 = tree.FindNode( 10 ); 
    EXPECT_EQ(find2, nullptr); 
}


//** NON EMPTY TREE TESTY **//
// vytvarim strom s hodnotami
class NonEmptyTree : public ::testing::Test
{
protected: 
    BinaryTree tree; 

    virtual void SetUp() {
        int values[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; 
        for (auto value: values) { 
            tree.InsertNode(value);
        }
     }
}; 

TEST_F(NonEmptyTree, InsertNode) {
    // pridam uzel s hodnotou, ktera jeste neexistuje, ocekavam true
    auto insert = tree.InsertNode( 11 ); 
    EXPECT_TRUE(insert.first); 
    EXPECT_EQ(insert.second->key, 11); 

    // pridam uzel s hodnotou, ktera uz existuje, ocekavam false
    auto insert2 = tree.InsertNode( 3 ); 
    EXPECT_FALSE(insert2.first); 
    EXPECT_EQ(insert2.second->key, 3);  
}

TEST_F(NonEmptyTree, DeleteNode) {
    // zkusim smazat uzel s hodnotou 3, ktery existuje, ocekavam true 
    auto del = tree.DeleteNode( 3 ); 
    EXPECT_TRUE(del); 

    // zkusim smazat uzel s hodnotou 25, ktera neexistuje, ocekavam false
    auto del2 = tree.DeleteNode( 25 ); 
    EXPECT_FALSE(del2); 
}

TEST_F(NonEmptyTree, FindNode) {
    // zkusim najit existujici uzel, ocekavam true
    auto find = tree.FindNode( 5 ); 
    EXPECT_TRUE(find); 

    // zkusim najit neexistujici uzel, ocekavam NULL 
    auto find2 = tree.FindNode( 15 ); 
    EXPECT_EQ(find2, nullptr); 
}


//** TREE AXIOMS TESTY **// 
// vsechny listove uzly jsou cerne, uzly bez potomku 
TEST_F(NonEmptyTree, Axiom1)
{
    // funkce getleafnodes hleda uzly, ktere nemaji potomky
    std::vector<BinaryTree::Node_t *> leafNodes {};
    tree.GetLeafNodes(leafNodes);

    for (auto node : leafNodes) {
        EXPECT_EQ(node->color, BLACK); 
    }
} 

// pokud je uzel cerveny, oba jeho potomci jsou cerni 
TEST_F(NonEmptyTree, Axiom2)
{
    std::vector<BinaryTree::Node_t *> allNodes {};
    tree.GetAllNodes(allNodes);

    // pro vsechny nodes
    for (auto node : allNodes) {
        // pokud je uzel cerveny
        if (node->color == RED) {
            // potomek vlevo a vpravo musi byt cerny
            EXPECT_EQ(node->pLeft->color, BLACK); 
            EXPECT_EQ(node->pRight->color, BLACK); 
        }
    }
} 

// stejny pocet cesty uzly nevim co to znamena 
TEST_F(NonEmptyTree, Axiom3)
{
    std::vector<BinaryTree::Node_t *> leafNodes {};
    tree.GetLeafNodes(leafNodes); 

    // nastavim si path length a iterace at se mi nastavi v loopu delka path na pocet leaf nodes
    int pathLength = 0;
    int iteration = 0;

    for(auto leafNode : leafNodes) {
        int blackLeafCount = 0; 
      
        // pokud je leaf black, zvys pocet leafu, dokud existuji leafy
        do {
            if (leafNode->color == BLACK) blackLeafCount++; 
            
            leafNode = leafNode->pParent;
        }
        while (leafNode != nullptr); 

        if (iteration == 0) pathLength = blackLeafCount;  

        iteration++;

        EXPECT_EQ(pathLength, blackLeafCount);
    }
} 